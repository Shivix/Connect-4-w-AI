cmake_minimum_required(VERSION 3.14)
project(connect4)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        src/board.cpp
        src/opponent.cpp
        src/main.cpp)
set(INCLUDES
        include/board.hpp
        include/opponent.hpp)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_executable(connect4 ${SOURCES} ${INCLUDES})
