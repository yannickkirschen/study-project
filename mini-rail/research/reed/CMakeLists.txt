project(reed VERSION 1.0.0 DESCRIPTION "Demonstrates the use of a Reed-Contact on the Raspberry Pi Pico")

add_executable(reed
        src/reed.c
)

add_executable(reed-multi
        src/reed-multi.c
)

pico_add_extra_outputs(reed)
target_link_libraries(reed pico_stdlib)

pico_add_extra_outputs(reed-multi)
target_link_libraries(reed-multi pico_stdlib)
