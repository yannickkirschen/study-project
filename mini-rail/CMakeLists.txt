cmake_minimum_required(VERSION 3.27)

if (TARGET_ARCH STREQUAL "pico")
    include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
endif ()
project(mini-rail LANGUAGES C VERSION 1.0.0 DESCRIPTION "A digital interlocking system for model railways.")

set(CMAKE_C_STANDARD 23)

if (TARGET_ARCH STREQUAL "pico")
    pico_sdk_init()
endif ()

include_directories(include)
add_subdirectory(modules)

if (TARGET_ARCH STREQUAL "pico")
    add_subdirectory(embedded)
else ()
    add_subdirectory(apps)
endif ()
