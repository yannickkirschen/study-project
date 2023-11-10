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

add_subdirectory(lib/error)
add_subdirectory(lib/graph)
add_subdirectory(lib/stb_ds_helper)

if (TARGET_ARCH STREQUAL "pico")
    include_directories($ENV{PICO_SDK_PATH}/**)
    add_subdirectory(embedded)
    add_subdirectory(research)
else ()
    add_subdirectory(test)
endif ()
