cmake_minimum_required(VERSION 3.10)

project(as)

add_subdirectory(../ build)
add_library(${PROJECT_NAME} SHARED src/as.cc)
target_include_directories(${PROJECT_NAME} PUBLIC include/  ../include/)
target_link_libraries(${PROJECT_NAME} PRIVATE hello)


