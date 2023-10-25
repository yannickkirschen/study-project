project(interlocking LANGUAGES C VERSION 1.0.0 DESCRIPTION "Digital interlocking system for a model railway")

add_library(interlocking STATIC
        src/block.c
)

target_link_libraries(interlocking error)
