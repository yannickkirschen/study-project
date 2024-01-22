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
add_subdirectory(modules/serial)
add_subdirectory(modules/vacancy-detection)

if (TARGET_ARCH STREQUAL "pico")
    include_directories($ENV{CAN2040_LIB_PATH}/src)

    add_subdirectory(embedded)
    add_subdirectory(research)
else ()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})

    add_subdirectory(modules/interlocking)
    add_subdirectory(apps)
    add_subdirectory(test)
endif ()
