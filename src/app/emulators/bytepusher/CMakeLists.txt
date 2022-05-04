add_library(
    bytepusher
    STATIC
    emulator.cpp
    state/state.cpp
    VM/vm.cpp
)

target_include_directories(bytepusher PUBLIC header)
target_link_libraries(bytepusher PUBLIC core)