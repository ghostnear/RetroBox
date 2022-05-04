add_library(
  core
  STATIC
  utils.cpp
  timer/timer.cpp
  input/input.cpp
  window/window.cpp
  locale/locale.cpp
  states/statemanager.cpp
  argparser/argparser.cpp
  window/renderer/renderer.cpp
)

target_include_directories(core PUBLIC header)
target_link_libraries(core PUBLIC imgui argparse)