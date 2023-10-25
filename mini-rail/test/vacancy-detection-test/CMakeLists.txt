project(vacancy-detection-test LANGUAGES C VERSION 1.0.0 DESCRIPTION "Tests for the vacancy detection.")

add_executable(vacancy-detection-test-straight
        src/assert.h
        src/assert.c
        src/vacancy-detection-test-straight.c
)

add_executable(vacancy-detection-test-switch
        src/assert.h
        src/assert.c
        src/vacancy-detection-test-switch.c
)

target_link_libraries(vacancy-detection-test-straight vacancy-detection error)
target_link_libraries(vacancy-detection-test-switch vacancy-detection error)
