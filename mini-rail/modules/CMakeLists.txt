cmake_minimum_required(VERSION 3.27)
project(mini-rail-modules LANGUAGES C VERSION 1.0.0 DESCRIPTION "Logic of MiniRail.")

set(CMAKE_C_STANDARD 23)

add_subdirectory(error)
add_subdirectory(vacancy-detection)
