cmake_minimum_required(VERSION 3.23)

project(Pufferfish C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set debug build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Warning flags - these catch issues at compile time
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -Wall -Wextra -Wpedantic -Werror")

# Add extra helpful warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wuninitialized -Wmaybe-uninitialized -Wshadow -Wformat=2")

# Optional: Stack protection (works on MinGW)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-strong")
endif()

add_executable(Pufferfish 
    main.c
    board.c
    moves.c
)