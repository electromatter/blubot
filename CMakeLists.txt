project(blubot.hex)
cmake_minimum_required(VERSION 2.8)

include_directories(src/)

aux_source_directory(src/ BLUBOT_SRC)

add_executable(blubot src/ ${BLUBOT_SRC})
