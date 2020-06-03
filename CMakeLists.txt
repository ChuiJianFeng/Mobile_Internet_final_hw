cmake_minimum_required(VERSION 3.16)
project(practice_circular_queue C)

set(CMAKE_C_STANDARD 11)

add_executable(practice_circular_queue main.c circular_queue.c)
add_executable(server server.c circular_queue.c )
add_executable(test_shared_vars test_shared_vars.c)