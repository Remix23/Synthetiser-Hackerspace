#include <stdio.h>

#include <cmath>

#include <config.hpp>
#include <notes.hpp>
#include <engine.hpp>

#include <iostream>

// Pico SDK includes
#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/time.h>
#include <hardware/irq.h>
#include <hardware/pwm.h>
#include <hardware/sync.h>
#include <hardware/dma.h>

// TinyUSB
#include <bsp/board.h>
#include <tusb.h>

#define EMPTY_NOTE -128
#define NOTE_NOT_FOUND -1

#define AUDIO_PIN 13

long position = 0;
bool buffSel = 0;
bool newBuffer = true;

uint16_t buff[2][BUFFSIZE];

static int pwm_dma_chan;

Engine eng(false);
int8_t notes[MAXTRACKS] = {-128};
int new_note_idx = 0;

void dma_handler()
{
  dma_hw->ints0 = 1u << pwm_dma_chan;

  dma_channel_set_read_addr(pwm_dma_chan, &buff[buffSel], true);

  buffSel = !buffSel;
  newBuffer = true;
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

void inc_new_note_idx()
{
  new_note_idx++;
  new_note_idx = new_note_idx < MAXTRACKS ? new_note_idx : 0;
}

int find_note_in_notes(int8_t note)
{
  for (int i = 0; i < MAXTRACKS; i++)
  {
    if (note == notes[i])
      return i;
  }

  return NOTE_NOT_FOUND;
}

float note_to_freq(int note)
{
  float a = 440; // frequency of A (coomon value is 440Hz)
  return (a / 32) * pow(2, ((note - 9) / 12.0));
}

void handle_midi()
{
  uint8_t buffer[4];

  while (tud_midi_packet_read(buffer))
  {
    switch (buffer[0] & 0x0f)
    {
    case MIDI_CIN_NOTE_ON:
    {
      gpio_put(PICO_DEFAULT_LED_PIN, 1);

      int8_t note = buffer[2];

      notes[new_note_idx] = note;
      eng.setTrack(new_note_idx, note_to_freq(note));
      eng.activateTrack(new_note_idx);
      inc_new_note_idx();

      break;
    }

    case MIDI_CIN_NOTE_OFF:
    {
      int8_t note_num = buffer[2];

      int note = find_note_in_notes(note_num);

      if (note != NOTE_NOT_FOUND)
      {
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        notes[note] = EMPTY_NOTE;
        eng.deativateTrack(note);
      }

      break;
    }

    default:
      break;
    }
  }
}

void init_pwm()
{
  gpio_set_function(AUDIO_PIN, GPIO_FUNC_PWM);

  int audio_pin_slice = pwm_gpio_to_slice_num(AUDIO_PIN);

  pwm_set_wrap(audio_pin_slice, PWM_WRAP);

  pwm_set_gpio_level(AUDIO_PIN, 0);
  pwm_set_enabled(audio_pin_slice, true);

  pwm_dma_chan = dma_claim_unused_channel(true);

  dma_channel_config dma_conf = dma_channel_get_default_config(pwm_dma_chan);
  channel_config_set_transfer_data_size(&dma_conf, DMA_SIZE_16);
  channel_config_set_read_increment(&dma_conf, true);
  channel_config_set_write_increment(&dma_conf, false);
  channel_config_set_dreq(&dma_conf, pwm_get_dreq(audio_pin_slice));

  dma_channel_configure(
      pwm_dma_chan,
      &dma_conf,
      &pwm_hw->slice[audio_pin_slice].cc,
      NULL,
      BUFFSIZE,
      false);

  dma_channel_set_irq0_enabled(pwm_dma_chan, true);

  irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
  irq_set_enabled(DMA_IRQ_0, true);

  dma_handler();
}

bool usb_timer_callback(struct repeating_timer *t)
{
  tud_task();
  return true;
}

// This core handles the hardware audio output.
int main()
{
  stdio_init_all();

  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

  init_pwm();

  struct repeating_timer usb_timer;
  add_repeating_timer_ms(10, usb_timer_callback, NULL, &usb_timer);

  board_init();
  tusb_init();

  // Synth stuff
  eng.activateTrack(0);

  int8_t notes[MAXTRACKS] = {EMPTY_NOTE};

  while (1)
  {
    // Handle MIDI messages
    handle_midi();

    if (newBuffer)
    {
      newBuffer = false;
      for (int i = 0; i < BUFFSIZE; i++)
      {
        buff[buffSel][i] = (1.0f + eng.process()) * (((float)(PWM_WRAP)*0.5f) / 2.0f);
      }
    }
  }
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