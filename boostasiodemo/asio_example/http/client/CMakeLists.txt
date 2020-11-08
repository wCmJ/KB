cmake_minimum_required(VERSION 3.10)

project(client_liwei)
set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cc client.cc connection.cc)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../asio/asio/include)
