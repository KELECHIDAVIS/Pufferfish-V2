cmake_minimum_required(VERSION 3.15)
project(Pufferfish VERSION 1.0 LANGUAGES C CXX)

enable_testing()

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Create a Library for the Engine Logic
add_library(engine_lib STATIC
    src/board.c
    src/moves.c
    src/perft.c
    src/attack_patterns.c
)

target_include_directories(engine_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Enable DEBUG mode for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(engine_lib PRIVATE DEBUG)
    message(STATUS "Debug mode enabled - validation checks active")
endif()

# 2. Define the Executable
add_executable(pufferfish src/main.c)
target_link_libraries(pufferfish PRIVATE engine_lib)

# Also enable DEBUG for the executable in Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(pufferfish PRIVATE DEBUG)
endif()

# 3. Setup GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
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