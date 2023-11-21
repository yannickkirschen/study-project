cmake_minimum_required(VERSION 3.26)

if (TARGET_ARCH STREQUAL "pico")
    include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
endif ()
project(mini-rail LANGUAGES C)

set(CMAKE_C_STANDARD 23)

if (TARGET_ARCH STREQUAL "pico")
    pico_sdk_init()
endif ()

include_directories(include)
include_directories(lib/stb)
add_subdirectory(modules)

if (TARGET_ARCH STREQUAL "pico")
    include_directories($ENV{PICO_SDK_PATH}/**)
    add_subdirectory(embedded)
    add_subdirectory(research)

    # The can2040 library
    include_directories(lib/can2040/src)
    add_library(can2040 STATIC lib/can2040/src/can2040.c)
else ()
    add_subdirectory(apps)
    add_subdirectory(test)
endif ()
