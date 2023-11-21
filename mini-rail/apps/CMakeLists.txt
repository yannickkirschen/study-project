project(apps LANGUAGES C)

add_executable(mini-rail src/mini-rail.c)

target_link_libraries(mini-rail
        interlocking
        sqlite3
)
