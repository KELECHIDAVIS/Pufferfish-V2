cmake_minimum_required(VERSION 3.15)
project(Pufferfish VERSION 1.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Export compile commands for better IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler-specific settings for GCC/MinGW
if(CMAKE_C_COMPILER_ID MATCHES "GNU")
    # Debug flags: strict warnings, all optimizations off, debugging symbols
    set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic -Werror -Wformat=2 -Wconversion -Wsign-conversion -Wstrict-prototypes")
    
    # Release flags: optimizations on, no debug symbols
    set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()

# Define the executable
add_executable(pufferfish
    main.c
    board.c
    moves.c
    perft.c
)

# If you have header files, you can specify include directories
# target_include_directories(pufferfish PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Optional: Add custom target for running the program
add_custom_target(run
    COMMAND pufferfish
    DEPENDS pufferfish
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)