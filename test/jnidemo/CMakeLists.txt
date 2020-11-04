cmake_minimum_required(VERSION 3.10)

set(TARGET test)
project(${TARGET})

set(CMAKE_CXX_STANDARD 11)
file(GLOB SOURCES "src/*.cc")

add_library(${TARGET} SHARED ${SOURCES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/include)


