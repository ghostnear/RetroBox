add_library(
    emulators
    STATIC
    headers/emulators.hpp
)

add_subdirectory(chip8)

target_include_directories(emulators PUBLIC headers)
target_link_libraries(emulators PUBLIC core chip8)
