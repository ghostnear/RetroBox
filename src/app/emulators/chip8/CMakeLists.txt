add_library(
    chip8
    STATIC
    emulator.cpp
    state/state.cpp
    cpu/interpreter.cpp
)

target_include_directories(chip8 PUBLIC header)
target_link_libraries(chip8 PUBLIC core)