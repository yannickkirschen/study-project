cmake_minimum_required(VERSION 3.27)
project(blink VERSION 1.0.0 DESCRIPTION "Blinks an LED on the Raspberry Pi Pico")

set(CMAKE_C_STANDARD 23)

add_executable(blink
        src/blink.c
)

pico_add_extra_outputs(blink)
target_link_libraries(blink pico_stdlib)
