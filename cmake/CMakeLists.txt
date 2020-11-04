cmake_minimum_required(VERSION 3.10)

project(cmake)

message("CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})

execute_process(COMMAND bash ${CMAKE_SOURCE_DIR}/command.sh)

add_subdirectory(third_party/asio)
