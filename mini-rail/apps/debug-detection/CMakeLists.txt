project(debug-detection LANGUAGES C VERSION 1.0.0 DESCRIPTION "Vacancy detection for a model railway -- debug!")

add_executable(debug-detection
        src/debug-detection.c
)

target_link_libraries(debug-detection vacancy-detection error)
