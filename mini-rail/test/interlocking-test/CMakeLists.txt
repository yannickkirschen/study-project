project(interlocking-test LANGUAGES C VERSION 1.0.0 DESCRIPTION "Tests for the interlocking system.")

add_executable(interlocking-test
        src/interlocking-test.c
)

target_link_libraries(interlocking-test interlocking graph)
