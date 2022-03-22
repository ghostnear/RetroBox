#=================== SDL2 =================== #

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/sdl2-cmake-scripts")

if(WIN32)
  set(SDL2_PATH "${CMAKE_CURRENT_SOURCE_DIR}/sdl/windows")
endif()

find_package(SDL2 REQUIRED)
add_library(sdl2 INTERFACE)
target_include_directories(sdl2 INTERFACE "${SDL2_INCLUDE_DIR}")
target_link_libraries(sdl2 INTERFACE "${SDL2_LIBRARY}")

#=================== IMGUI =================== #

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
add_library(imgui STATIC)

target_sources(imgui
  PRIVATE
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui.cpp
  PRIVATE
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl.cpp
)

target_include_directories(imgui
  PUBLIC ${IMGUI_DIR}
  PUBLIC ${IMGUI_DIR}/backends
  PUBLIC ${SDL2_DIR}/include
  PUBLIC ${IMGUI_DIR}/../imgui_memory_editor/imgui_memory_editor/
)

find_package(OpenGL REQUIRED)
target_link_libraries(imgui PUBLIC sdl2 ${CMAKE_DL_LIBS} ${OPENGL_LIBRARIES})

#=================== ARGPARSE =================== #
add_library(argparse STATIC argparse/argparse.c)
target_include_directories(argparse PUBLIC argparse)