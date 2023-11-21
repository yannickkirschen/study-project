project(str.c LANGUAGES C)

add_library(str.c STATIC
        src/str.c
)

link_libraries(str.c stb-ds-helper)
