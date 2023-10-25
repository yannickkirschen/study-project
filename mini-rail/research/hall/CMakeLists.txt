project(hall VERSION 1.0.0 DESCRIPTION "Demonstrates the use of a Hall-Sensor on the Raspberry Pi Pico")

add_executable(hall
        src/hall.c
)

pico_add_extra_outputs(hall)
target_link_libraries(hall pico_stdlib)
