cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_COMPILER "cl.exe")

project(03.homework)

add_executable(
	guess_a_number
	guess_a_number.cpp
	high_scores.cpp
)