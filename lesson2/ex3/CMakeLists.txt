cmake_minimum_required(VERSION 3.22)

project(shared_object_example)

add_library(shared SHARED shared.cpp)

add_executable(main main.cpp)

target_link_libraries(main shared)
