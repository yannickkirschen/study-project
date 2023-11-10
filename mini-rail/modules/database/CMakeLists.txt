project(database LANGUAGES C VERSION 1.0.0 DESCRIPTION "Database connectivity for MiniRail.")

add_library(database STATIC
        src/database.c
)

link_libraries(database sqlite3 stb-ds-helper error graph interlocking vacancy-detection)
