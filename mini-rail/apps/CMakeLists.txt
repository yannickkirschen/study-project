project(apps LANGUAGES C)

add_executable(mini-rail src/mini-rail.c)
add_executable(mini-rail-ui src/mini-rail-ui.c)

target_link_libraries(mini-rail interlocking sqlite3)
target_link_libraries(mini-rail-ui interlocking sqlite3 ${SDL2_LIBRARIES})
