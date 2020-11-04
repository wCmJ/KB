cmake_minimum_required(VERSION 3.10...3.18)

#set the project name
project(app VERSION 1.0
            DESCRIPTION "Very nice project"
            LANGUAGES CXX)

add_executable(one two.cpp three.h)

add_library(one STATIC two.cpp three.h) #STATIC SHARED MODULE

target_include_directories(one PUBLIC include)

add_library(another STATIC another.cpp another.h)

target_link_directories(another PUBLIC one)







set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

#add the executable
add_executable(app main.cpp)




