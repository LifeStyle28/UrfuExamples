cmake_minimum_required(VERSION 3.22)

project(TCP_UDP_Practice CXX)
set(CMAKE_CXX_STANDARD 20)

# Подключаем сгенерированный скрипт conanbuildinfo.cmake, созданный Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# Выполняем макрос из conanbuildinfo.cmake, который настроит СMake на работу с библиотеками, установленными Conan
conan_basic_setup()

# Добавляем два проекта
add_executable(TCPServer tcp_server.cpp)
add_executable(TCPClient tcp_client.cpp)

