project(interlocking LANGUAGES C)

add_library(interlocking STATIC
        src/database-interlocking.c
        src/database-ui.c
        src/signal.c
        src/switch.c
        src/interlocking.c
        src/element.c
        src/open-track.c
)

target_link_libraries(interlocking)
