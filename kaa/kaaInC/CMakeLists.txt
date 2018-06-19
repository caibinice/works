cmake_minimum_required(VERSION 2.8.12)
project(test3 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g -Wall -Wextra")

add_subdirectory(kaa)

add_executable(test3 src/main.c src/cmd.c)

target_link_libraries(test3 kaac)