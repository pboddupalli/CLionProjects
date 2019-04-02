cmake_minimum_required(VERSION 3.13)
project(networking)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(client client.cpp epoll_server.cpp)
add_executable(server epoll_server.cpp)
