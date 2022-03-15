add_library(
    rendering
    STATIC
    window/window.cpp
)

target_include_directories(rendering PUBLIC window)
target_link_libraries(rendering PUBLIC sdl2)