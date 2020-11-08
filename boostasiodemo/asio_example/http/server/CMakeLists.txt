cmake_minimum_required(VERSION 3.10)

project(server_liwei)

set(CMAKE_CXX_STANDARD 11)

set(INC_FILES
    server.cc
    connection.cc
    connection_manager.cc
    )

add_executable(${PROJECT_NAME} main.cc ${INC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ../../../asio/asio/include)




