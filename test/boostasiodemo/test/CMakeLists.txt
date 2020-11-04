cmake_minimum_required(VERSION 3.10)

include_directories(../asio/asio/include)
set(CMAKE_CXX_STANDARD 11)

add_executable(server_client server_client.cc)