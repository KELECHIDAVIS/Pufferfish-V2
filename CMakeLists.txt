cmake_minimum_required(VERSION 3.23)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c23 -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_C_REQUIRED ON)
set(CMAKE_C_STANDARD 23)

project(Pufferfish)

add_executable(Pufferfish)

target_sources(Pufferfish 
    main.c
)