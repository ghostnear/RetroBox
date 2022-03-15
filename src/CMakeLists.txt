cmake_minimum_required(VERSION 3.8)

project(Owari)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Owari_SOURCE_DIR}/../bin/)

add_subdirectory(external)
add_subdirectory(app)