cmake_minimum_required(VERSION 3.10)


project(hello)


add_library(${PROJECT_NAME} SHARED src/hello.cc)
target_include_directories(${PROJECT_NAME} PUBLIC include/)

