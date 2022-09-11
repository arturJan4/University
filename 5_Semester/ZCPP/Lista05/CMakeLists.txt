cmake_minimum_required(VERSION 3.16)
project(Lista5)

set(CMAKE_CXX_STANDARD 20)

add_executable(zad1 zad1.cpp token.cpp token.hpp)
add_executable(zad2 zad2.cpp dfa.cpp dfa.hpp)
add_executable(zad3 zad3.cpp weighted_graph.cpp weighted_graph.hpp)