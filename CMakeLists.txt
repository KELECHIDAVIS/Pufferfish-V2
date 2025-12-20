cmake_minimum_required(VERSION 3.15)
project(Pufferfish VERSION 1.0 LANGUAGES C CXX) # Added CXX for GTest

enable_testing()

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14) # GTest requires C++
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Create a Library for the Engine Logic
# Exclude main.c from the library so it doesn't conflict with GTest's main
add_library(engine_lib STATIC
    src/board.c
    src/moves.c
    src/perft.c
    src/attack_patterns.c
)

target_include_directories(engine_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include [cite: 2]
)

# 2. Define the Executable (links to the library)
add_executable(pufferfish src/main.c)
target_link_libraries(pufferfish PRIVATE engine_lib)

# 3. Setup GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Fix for the GCC attribute error: Disable GoogleMock 
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# For Windows/MSVC compatibility
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 4. Define the Test Executable
add_executable(engine_tests 
    tests/test_board.cpp 
)
target_link_libraries(engine_tests PRIVATE 
    gtest_main 
    engine_lib
    )

# 5. Enable Testing
include(GoogleTest)
gtest_discover_tests(engine_tests)