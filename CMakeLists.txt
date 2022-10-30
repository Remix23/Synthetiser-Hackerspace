cmake_minimum_required(VERSION 3.16)

project(synth)

add_executable(synth
  src/main.cpp
  src/notes.cpp
  src/engine.cpp
  src/adsr.cpp
  src/channel.cpp
  src/waveTableOscilator.cpp
  src/baseFilter.cpp
)

target_include_directories(synth PUBLIC 
  headers 
  headers/lfo 
  headers/filters 
  headers/amp_envelope 
  headers/oscilator
)

