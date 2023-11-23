project(research LANGUAGES C CXX ASM)

add_executable(can src/can-master.c $ENV{CAN2040_LIB_PATH}/src/can2040.c)
add_executable(can-slave src/can-slave.c $ENV{CAN2040_LIB_PATH}/src/can2040.c)
add_executable(hall src/hall.c)
add_executable(reed src/reed.c)
add_executable(reed-multi src/reed-multi.c)

pico_add_extra_outputs(can)
pico_add_extra_outputs(can-slave)
pico_add_extra_outputs(hall)
pico_add_extra_outputs(reed)
pico_add_extra_outputs(reed-multi)

target_link_libraries(can pico_stdlib cmsis_core)
target_link_libraries(can-slave pico_stdlib cmsis_core)
target_link_libraries(hall pico_stdlib)
target_link_libraries(reed pico_stdlib)
target_link_libraries(reed-multi pico_stdlib)
