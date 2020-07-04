cmake_minimum_required(VERSION 3.14)
project(connect4)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        board.cpp
        opponent.cpp
        main.cpp)
set(INCLUDES
        board.hpp
        opponent.hpp)

add_compile_options(-Wall -Werror)

add_executable(connect4 ${SOURCES} ${INCLUDES})
