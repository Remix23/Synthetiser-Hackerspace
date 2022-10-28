cmake_minimum_required(VERSION 3.16)

project(synth)

add_executable(synth
  src/main.cpp
  src/osc.cpp
  src/notes.cpp
)

target_include_directories(synth PUBLIC 
  headers 
  headers/lfo 
  headers/filters 
  headers/amp_envelope 
  headers/oscilator
)

