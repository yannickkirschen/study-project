project(vacancy-detection-reed VERSION 1.0.0 DESCRIPTION "Vacancy detection using Reed contacts on the Raspberry Pi Pico")

add_executable(vacancy-detection-reed
        src/vacancy-detection-reed.c
)

pico_add_extra_outputs(vacancy-detection-reed)
target_link_libraries(vacancy-detection-reed pico_stdlib vacancy-detection)
