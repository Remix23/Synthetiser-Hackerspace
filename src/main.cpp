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

// TinyUSB
#include <bsp/board.h>
#include <tusb.h>

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

int find_note_in_notes(int8_t note, int8_t notes[MAXTRACKS])
{
  for (int i = 0; i < MAXTRACKS; i++)
  {
    if (note == notes[i])
      return i;
  }
  return -1;
}

void handle_midi(int8_t notes[MAXTRACKS], uint8_t *buffer, size_t buffer_size)
{
  size_t packet_start = 0;

  while (packet_start < buffer_size)
  {
    switch (buffer[packet_start])
    {
    case MIDI_CIN_NOTE_ON:
      if (!find_note_in_notes(buffer[packet_start] & 0x7F, notes))
      {
        size_t empty;
      }
      break;

    case MIDI_CIN_NOTE_OFF:
      /* code */
      break;

    default:
      break;
    }
  }
}

// This core handles the audio generation.
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

  int8_t notes[MAXTRACKS] = {INT8_MIN};

  bool select = 1; // Initial value doesn't matter
  while (1)
  {
    /*
      This check below needs to happen because malloc(0) is undefined and *MAY NOT RETURN NULL*. Why（ ﾟДﾟ）?
    */
    size_t midi_msg_size = (size_t)tud_midi_available();
    if (midi_msg_size)
    {
      uint8_t *buffer = (uint8_t *)malloc(midi_msg_size);
      if (!buffer)
        panic("Failed to allocate buffer!");
      tud_midi_read((void *)buffer, midi_msg_size);

      handle_midi(notes, buffer, midi_msg_size);

      free(buffer);
    }

    if (multicore_fifo_rvalid())
    {
      select = multicore_fifo_pop_blocking();
      for (int i = 0; i < BUFFSIZE; i++)
      {
        buff[select][i] = eng.process();
      }
    }
  }
}

// This core handles the hardware audio output.
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

  board_init();
  tusb_init();

  while (1)
    tud_task(); // Handle TinyUSB device task

  return 0;
}

void tud_mount_cb(void)
{
}

void tud_umount_cb(void)
{
}

void tud_suspend_cb(bool remote_wake_en)
{
  (void)remote_wake_en;
}

void tud_resume_cb(void)
{
}