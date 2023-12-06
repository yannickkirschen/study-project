project(mini-rail-embedded LANGUAGES C CXX ASM)

add_executable(signal-decoder src/signal-decoder.c)
add_executable(vacancy-detection-reed src/vacancy-detection-reed.c $ENV{CAN2040_LIB_PATH}/src/can2040.c)
add_executable(blink src/blink.c)

pico_add_extra_outputs(signal-decoder)
pico_add_extra_outputs(vacancy-detection-reed)
pico_add_extra_outputs(blink)

target_link_libraries(signal-decoder pico_stdlib)
target_link_libraries(vacancy-detection-reed pico_stdlib vacancy-detection cmsis_core)
target_link_libraries(blink pico_stdlib)
