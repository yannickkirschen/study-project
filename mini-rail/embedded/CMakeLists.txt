project(mini-rail-embedded LANGUAGES C CXX ASM)

add_executable(signal-decoder src/signal-decoder.c $ENV{CAN2040_LIB_PATH}/src/can2040.c)
add_executable(vacancy-detection-reed src/vacancy-detection-reed.c $ENV{CAN2040_LIB_PATH}/src/can2040.c)
add_executable(blink src/blink.c)

pico_add_extra_outputs(signal-decoder)
pico_add_extra_outputs(vacancy-detection-reed)
pico_add_extra_outputs(blink)

target_link_libraries(signal-decoder pico_stdlib cmsis_core)
target_link_libraries(vacancy-detection-reed pico_stdlib vacancy-detection cmsis_core)
target_link_libraries(blink pico_stdlib)

if (TARGET tinyusb_device)
    message(STATUS "Building can-serial-bridge because TinyUSB submodule is initialized in the SDK")
    add_executable(can-serial-bridge src/can-serial-bridge.c $ENV{CAN2040_LIB_PATH}/src/can2040.c)
    target_link_libraries(can-serial-bridge pico_stdlib cmsis_core)

    pico_enable_stdio_usb(can-serial-bridge 1)
    pico_enable_stdio_uart(can-serial-bridge 0)

    pico_add_extra_outputs(can-serial-bridge)
elseif (PICO_ON_DEVICE)
    message(WARNING "Not building can-serial-bridge because TinyUSB submodule is not initialized in the SDK")
endif ()
