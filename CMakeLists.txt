cmake_minimum_required(VERSION 3.16)
project(LSMKVStorage CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Functions 

# Memtable
add_library(memtable_functions STATIC src/memtable.cpp)
target_include_directories(memtable_functions PUBLIC include)
target_compile_options(memtable_functions PRIVATE
    -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations
    -Wextra -Wpedantic -Werror)

# LSM_Tree
add_library(lsm_functions STATIC src/lsm_tree.cpp)
target_include_directories(lsm_functions PUBLIC include)
target_compile_options(lsm_functions PRIVATE
    -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations
    -Wextra -Wpedantic -Werror)

