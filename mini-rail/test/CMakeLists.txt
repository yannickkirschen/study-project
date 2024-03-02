project(mini-rail-test LANGUAGES C)

add_executable(bin-test src/bin-test.c)
add_executable(serial-listener-test src/serial-listener-test.c)
add_executable(database-test src/database-test.c)
add_executable(graph-test src/graph-test.c)
add_executable(interlocking-test src/interlocking-test.c)
add_executable(messaging-test src/messaging-test.c)
add_executable(vacancy-detection-straight-test src/vacancy-detection-test-straight.c)
add_executable(vacancy-detection-switch-test src/vacancy-detection-test-switch.c)

target_link_libraries(serial-listener-test
        serial
)

target_link_libraries(database-test
        vacancy-detection
        interlocking
        sqlite3
)

target_link_libraries(graph-test
        vacancy-detection
        interlocking
        sqlite3
)

target_link_libraries(interlocking-test
        vacancy-detection
        interlocking
        sqlite3
)

target_link_libraries(vacancy-detection-straight-test
        vacancy-detection
        interlocking
        sqlite3
)

target_link_libraries(vacancy-detection-switch-test
        vacancy-detection
        interlocking
        sqlite3
)

