cmake_minimum_required(VERSION 3.14)
project(knapsack_dp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(knapsack_dp
    src/main.cpp
    src/knapsack_dp.cpp
    src/knapsack_backtrack.cpp
    src/data_loader.cpp
)

target_include_directories(knapsack_dp PRIVATE include)

if(MSVC)
    target_compile_options(knapsack_dp PRIVATE /W4)
else()
    target_compile_options(knapsack_dp PRIVATE -Wall -Wextra -pedantic)
endif()
