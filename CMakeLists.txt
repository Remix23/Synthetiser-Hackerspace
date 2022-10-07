cmake_minimum_required(VERSION 3.16)

project(miniSystem_Audio)

add_library(miniSystem_Audio
  src/osc.cpp
)

target_include_directories(miniSystem_Audio PUBLIC headers)

project(miniSystem_Audio_test)

add_executable(miniSystem_Audio_test
  src/main.cpp
)

target_include_directories(miniSystem_Audio_test PUBLIC headers)
target_link_libraries(miniSystem_Audio_test PUBLIC miniSystem_Audio)

