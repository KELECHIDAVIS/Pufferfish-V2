cmake_minimum_required(VERSION 3.23)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_C_REQUIRED ON)

project(Pufferfish)

add_executable(Pufferfish)

target_sources(Pufferfish 
    PRIVATE 
        main.c
)