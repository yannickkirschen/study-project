project(vacancy-detection LANGUAGES C VERSION 1.0.0 DESCRIPTION "Vacancy detection for a model railway")

add_library(vacancy-detection STATIC
        src/contact-counter.c
        src/contact-point.c
        src/vacancy-detection.c
        src/signal.c
        src/switch.c
)

target_link_libraries(vacancy-detection error)
