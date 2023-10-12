project(vacancy-detection LANGUAGES C VERSION 1.0.0 DESCRIPTION "Vacancy detection for a model railway")

add_library(vacancy-detection STATIC
        src/vacancy-detection.c
)

target_link_libraries(vacancy-detection error)
