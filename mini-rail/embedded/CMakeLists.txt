cmake_minimum_required(VERSION 3.27)
project(mini-rail-embedded LANGUAGES C CXX ASM VERSION 1.0.0 DESCRIPTION "Executables of MiniRail for the Raspberry Pi Pico.")

set(CMAKE_C_STANDARD 23)

add_subdirectory(blink)
