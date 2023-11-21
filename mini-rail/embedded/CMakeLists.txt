project(mini-rail-embedded LANGUAGES C CXX ASM)

add_executable(decoder src/decoder.c)
add_executable(vacancy-detection-reed src/vacancy-detection-reed.c)
add_executable(blink src/blink.c)

pico_add_extra_outputs(decoder)
pico_add_extra_outputs(vacancy-detection-reed)
pico_add_extra_outputs(blink)

target_link_libraries(decoder
        pico_stdlib
        interlocking
        error
        stb-ds-helper
)

target_link_libraries(vacancy-detection-reed
        pico_stdlib
        vacancy-detection
        error
        stb-ds-helper
)

target_link_libraries(blink pico_stdlib)
