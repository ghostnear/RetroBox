set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(emulator
main.cpp)

# Uncomment this if you don't want console output with the program
# if(WIN32)
	# set_property(TARGET emulator PROPERTY WIN32_EXECUTABLE TRUE)
# endif()

add_subdirectory(core)
add_subdirectory(emulators)

target_link_libraries(emulator PUBLIC core emulators)
set_target_properties(emulator PROPERTIES
	OUTPUT_NAME Owari)