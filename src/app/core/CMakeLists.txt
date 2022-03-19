add_library(
    core
    STATIC
    utils.cpp
    timer/timer.cpp
    window/window.cpp
    states/statemanager.cpp
)

target_include_directories(core PUBLIC header)
target_link_libraries(core PUBLIC imgui)