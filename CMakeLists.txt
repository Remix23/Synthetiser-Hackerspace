cmake_minimum_required(VERSION 3.16)

execute_process(
  COMMAND git submodule update --init
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/pico-sdk/
)

set(PICO_SDK_FETCH_FROM_GIT on)

include(pico-sdk/pico_sdk_init.cmake)

project(synth C CXX ASM)

pico_sdk_init()

add_executable(synth
  src/main.cpp
  src/notes.cpp
  src/engine.cpp
  src/adsr.cpp
  src/channel.cpp
  src/waveTableOscilator.cpp
  src/baseEffect.cpp
  src/customEffectsAndFilters.cpp
  src/functions.cpp
  src/usb_descriptors.c
)

target_include_directories(synth PUBLIC 
  headers 
  headers/lfo 
  headers/filters 
  headers/amp_envelope 
  headers/oscilator
)

target_link_libraries(synth 
  pico_stdlib 
  hardware_pwm
  hardware_dma
  pico_multicore
  tinyusb_device
  tinyusb_board
)

pico_enable_stdio_usb(synth 0)
pico_enable_stdio_uart(synth 1)

pico_add_extra_outputs(synth)