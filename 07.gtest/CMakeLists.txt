cmake_minimum_required(VERSION 3.5)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "cl.exe")
add_compile_options(/EHsc)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 1.17.0
)


project(06.container LANGUAGES CXX)
add_executable(container container.cpp)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory("C:\\dev\\googletest-1.17.0" googletest_build)

add_executable(tests array_tests.cpp list_tests.cpp)
target_link_libraries(tests gtest_main)