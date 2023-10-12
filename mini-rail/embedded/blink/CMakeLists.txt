project(blink VERSION 1.0.0 DESCRIPTION "Blinks an LED on the Raspberry Pi Pico")

add_executable(blink
        src/blink.c
)

pico_add_extra_outputs(blink)
target_link_libraries(blink pico_stdlib)
