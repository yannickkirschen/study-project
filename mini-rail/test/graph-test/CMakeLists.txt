project(graph-test LANGUAGES C VERSION 1.0.0 DESCRIPTION "Tests for the graph.")

add_executable(graph-test
        src/graph-test.c
)

target_link_libraries(graph-test graph interlocking)
