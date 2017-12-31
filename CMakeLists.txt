cmake_minimum_required(VERSION 3.2.2)
project(simpleinterpreter)

enable_testing()
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
add_subdirectory(tests)
