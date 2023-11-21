project(interlocking LANGUAGES C)

add_library(interlocking STATIC
        src/database.c
        src/signal.c
        src/switch.c
        src/interlocking.c
        src/element.c
        src/open-track.c
)

target_link_libraries(interlocking)
