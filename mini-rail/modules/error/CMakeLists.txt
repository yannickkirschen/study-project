project(error LANGUAGES C VERSION 1.0.0 DESCRIPTION "Error handling for C.")

add_library(error STATIC
        src/error.c
)
