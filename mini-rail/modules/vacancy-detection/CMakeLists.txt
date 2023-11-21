project(vacancy-detection LANGUAGES C)

add_library(vacancy-detection STATIC
        src/contact-counter.c
        src/contact-point.c
        src/vacancy-detection.c
)

target_link_libraries(vacancy-detection)
