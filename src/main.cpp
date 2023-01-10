#include <stdio.h>

#include <math.h>

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
uint16_t buff[2][BUFFSIZE];

static int pwm_dma_chan;

// void pwm_interrupt_handler()
// {
//   pwm_clear_irq(pwm_gpio_to_slice_num(AUDIO_PIN));
//   if (position < ((BUFFSIZE << 3) - 1))
//   {
//     uint8_t sample = (uint8_t)((1.0f + buff[buffSel][position >> 3]) * (100.0f / 2.0f));
//     pwm_set_gpio_level(AUDIO_PIN, sample);
//     position++;
//   }
//   else
//   {
//     position = 0;
//     buffSel = !buffSel;
//     multicore_fifo_push_blocking(!buffSel);
//   }
// }

void dma_handler()
{
  irq_clear(DMA_IRQ_0);
  // dma_hw->ints0 = 1u << pwm_dma_chan;

  dma_channel_set_read_addr(pwm_dma_chan, &buff[buffSel], true);

  buffSel = !buffSel;
  // multicore_fifo_push_blocking(!buffSel);
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
  return NOTE_NOT_FOUND;
}

void handle_midi(int8_t notes[MAXTRACKS], uint8_t *buffer, size_t buffer_size)
{
  size_t packet_start = 0;

  while (packet_start < buffer_size)
  {
    switch (buffer[packet_start++])
    {
    case MIDI_CIN_NOTE_ON:
    {
      int empty = find_note_in_notes(EMPTY_NOTE, notes);
      int note = buffer[packet_start++] & 0x7F;
      if (find_note_in_notes(note, notes) == NOTE_NOT_FOUND && empty != NOTE_NOT_FOUND)
      {
        notes[empty] = note;
      }
      packet_start++;
      break;
    }

    case MIDI_CIN_NOTE_OFF:
    {
      int note_num = find_note_in_notes(buffer[packet_start++] & 0x7F, notes);
      if (note_num != NOTE_NOT_FOUND)
      {
        notes[note_num] = EMPTY_NOTE;
      }
      packet_start++;
      break;
    }

    default:
      break;
    }
  }
}

float note_to_freq(int note)
{
  float a = 440; // frequency of A (coomon value is 440Hz)
  return (a / 32) * pow(2, ((note - 9) / 12.0));
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

// This core handles the audio generation.
void core1_entry()
{
  stdio_init_all();
  init_pwm();

  // Synth stuff
  Engine eng(false);

  int8_t notes[MAXTRACKS] = {EMPTY_NOTE};

  bool prevBuffSel = buffSel; // Initial value doesn't matter
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
      tud_midi_stream_read((void *)buffer, midi_msg_size);

      // Handle MIDI messages
      handle_midi(notes, buffer, midi_msg_size);

      free(buffer);

      for (int note = 0; note < MAXTRACKS; note++)
      {
        if (notes[note] != EMPTY_NOTE)
        {
          eng.setTrack(note, note_to_freq(notes[note]));
          eng.activateTrack(note);
        }
        else
        {
          eng.deativateTrack(note);
        }
      }
    }

    if (buffSel != prevBuffSel)
    {
      prevBuffSel = buffSel;
      for (int i = 0; i < BUFFSIZE; i++)
      {
        buff[!buffSel][i] = (uint8_t)((1.0f + eng.process()) * (100.0f / 2.0f));
      }
    }
  }
}

// This core handles the hardware audio output.
int main()
{
  board_init();
  tusb_init();

  multicore_launch_core1(core1_entry);

  while (1)
  {
    tud_task(); // Handle TinyUSB device task
    tight_loop_contents();
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