project(graph LANGUAGES C VERSION 1.0.0 DESCRIPTION "Graph implementation using an adjacency list.")

add_library(graph STATIC
        src/graph.c
        src/depth-first-search.c
)

link_libraries(graph stb-ds-helper interlocking)
