cmake_minimum_required(VERSION 3.15...4.4)

project(tcn_from_scratch)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Catch2 3 REQUIRED)

# micrograd
add_executable(micrograd micrograd/src/main.cpp)
add_executable(tests micrograd/tests/test_main.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)