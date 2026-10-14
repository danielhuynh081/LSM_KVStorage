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

# WAL 
add_library(WAL_functions STATIC src/WAL.cpp)
target_include_directories(WAL_functions PUBLIC include)
target_compile_options(WAL_functions PRIVATE
    -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations
    -Wextra -Wpedantic -Werror)

# LSM 
add_library(LSM_tree STATIC src/LSM.cpp)
target_include_directories(LSM_tree PUBLIC include)
target_compile_options(LSM_tree PRIVATE
    -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations
    -Wextra -Wpedantic -Werror)

# Tests
add_executable(memtable_test tests/memtable_test.cpp)
add_executable(WAL_test tests/WAL_test.cpp)

target_link_libraries(memtable_test PRIVATE memtable_functions)
target_link_libraries(WAL_test PRIVATE WAL_functions)

