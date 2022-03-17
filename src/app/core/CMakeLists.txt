add_library(
    core
    STATIC
    timer/timer.cpp
    window/window.cpp
)

target_include_directories(core PUBLIC header)
target_link_libraries(core PUBLIC sdl2)