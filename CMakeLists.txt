cmake_minimum_required(VERSION 3.11)
project(chip8-emulator)

set(CMAKE_CXX_STANDARD 17)

add_library(chip8 STATIC Chip8/Chip8.h Chip8/Chip8Instructions.h Chip8/Chip8Instructions.cpp)

find_package(SFML COMPONENTS graphics REQUIRED)

add_executable(chip8-emulator main.cpp)
target_link_libraries(chip8-emulator chip8)
target_link_libraries(chip8-emulator sfml-graphics)