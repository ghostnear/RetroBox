set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(emulator
main.cpp)

if(WIN32)
	set_property(TARGET emulator PROPERTY WIN32_EXECUTABLE TRUE)
endif()

add_subdirectory(rendering)

target_link_libraries(emulator PUBLIC rendering)
set_target_properties(emulator PROPERTIES
	OUTPUT_NAME Owari)