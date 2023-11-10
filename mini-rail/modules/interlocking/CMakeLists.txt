project(interlocking LANGUAGES C VERSION 1.0.0 DESCRIPTION "Digital interlocking system for a model railway")

add_library(interlocking STATIC
        src/database.c
        src/signal.c
        src/switch.c
        src/interlocking.c
        src/element.c
        src/open-track.c
)

target_link_libraries(interlocking stb-ds-helper error)
