cmake_minimum_required(VERSION 3.14)

project(06.container LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(/EHsc)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(container container.cpp)

add_executable(tests array_tests.cpp list_tests.cpp)
target_link_libraries(tests gtest_main)