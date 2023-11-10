project(graph LANGUAGES C)

add_library(graph STATIC
        src/graph.c
        src/depth-first-search.c
)

link_libraries(graph stb-ds-helper)
