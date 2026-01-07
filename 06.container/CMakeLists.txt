cmake_minimum_required(VERSION 3.5)


set(CMAKE_CXX_COMPILER "cl.exe")
add_compile_options(/EHsc)

project(06.container LANGUAGES CXX)
add_executable(container container.cpp)
