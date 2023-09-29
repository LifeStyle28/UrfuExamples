cmake_minimum_required(VERSION 3.22)

project(static_object_example)

add_library(static STATIC static.cpp)

add_executable(main main.cpp)

target_link_libraries(main static)
