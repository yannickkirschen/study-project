project(error LANGUAGES C)

add_library(error STATIC
        src/error.c
)

link_libraries(error stb-ds-helper)
