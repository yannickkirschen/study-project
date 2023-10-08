cmake_minimum_required(VERSION 3.25)

include(../lib/pico-sdk/external/pico_sdk_import.cmake)

project(embedded)
include_directories(../include)

pico_sdk_init()

FILE(GLOB BLINK_SRC blink/*.c)
FILE(GLOB RAIL_SRC ../modules/vacancy-detection/src/*.c)

add_executable(blink ${BLINK_SRC} ${RAIL_SRC})

pico_add_extra_outputs(blink)

target_link_libraries(blink pico_stdlib)
