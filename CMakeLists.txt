cmake_minimum_required(VERSION 3.11)
project(chip8-emulator)

set(CMAKE_CXX_STANDARD 11)

add_executable(chip8-emulator main.cpp main.cpp Chip8/Chip8.cpp Chip8/Chip8.h)