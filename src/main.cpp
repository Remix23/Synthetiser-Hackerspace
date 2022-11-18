#include <stdio.h>

#include <config.hpp>
#include <notes.hpp>
#include <engine.hpp>

#include <iostream>

// Pico SDK includes
#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <hardware/irq.h>
#include <hardware/pwm.h>
#include <hardware/sync.h>

#define AUDIO_PIN 13
long position = 0;
bool buffSel = 0;
float buff[2][BUFFSIZE];

void pwm_interrupt_handler()
{
  pwm_clear_irq(pwm_gpio_to_slice_num(AUDIO_PIN));
  if (position < ((BUFFSIZE << 3) - 1))
  {
    uint8_t sample = (uint8_t)((1.0f + buff[buffSel][position >> 3]) * (100.0f / 2.0f));
    pwm_set_gpio_level(AUDIO_PIN, sample);
    position++;
  }
  else
  {
    position = 0;
    buffSel = !buffSel;
    multicore_fifo_push_blocking(!buffSel);
  }
}

void printBuff(float buff[MAXTRACKS])
{
  std::cout << "[ ";
  for (int i = 0; i < MAXTRACKS; i++)
  {
    std::cout << buff[i] << ", ";
  }
  std::cout << "]\n";
}

void core1_entry()
{
  stdio_init_all();

  gpio_init(15);
  gpio_set_dir(15, GPIO_OUT);

  // Synth stuff
  Engine eng(false);

  eng.setTrack(0, 1);
  eng.activateTrack(0);

  eng.setTrack(1, 2);
  eng.activateTrack(1);

  bool select = 1;
  while (1)
  {
    for (int i = 0; i < BUFFSIZE; i++)
    {
      buff[select][i] = eng.process();
      // buff[1 - buffSel][i] = (((float)(i) / BUFFSIZE) * 2.0f) - 1.0f;
    }

    select = multicore_fifo_pop_blocking();
    gpio_put(15, select);
  }
}

int main()
{
  multicore_launch_core1(core1_entry);

  // Initializing pico for audio out
  set_sys_clock_khz(176000, true);
  gpio_set_function(AUDIO_PIN, GPIO_FUNC_PWM);

  int audio_pin_slice = pwm_gpio_to_slice_num(AUDIO_PIN);

  pwm_clear_irq(audio_pin_slice);
  pwm_set_irq_enabled(audio_pin_slice, true);
  irq_set_exclusive_handler(PWM_IRQ_WRAP, pwm_interrupt_handler);
  irq_set_enabled(PWM_IRQ_WRAP, true);

  pwm_config config = pwm_get_default_config();

  pwm_config_set_clkdiv(&config, 8.0f);
  pwm_config_set_wrap(&config, 250);
  pwm_init(audio_pin_slice, &config, true);

  pwm_set_gpio_level(AUDIO_PIN, 0);

  while (1)
    __wfi();

  return 0;
}