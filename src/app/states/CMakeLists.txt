add_library(
  states
  STATIC
  headers/states.hpp
  boot/boot.cpp
)

target_include_directories(states PUBLIC headers boot)
target_link_libraries(states PUBLIC core)
