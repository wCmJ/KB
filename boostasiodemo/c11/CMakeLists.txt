cmake_minimum_required(VERSION 3.10)

project(c11)

set(CMAKE_CXX_STANDARD 11)

include_directories(../asio/asio/include)

add_executable(exam exam.cc)

add_executable(exa2_4 exa2_4.cc)

add_executable(client_timer_test client_timer_test.cc)

add_executable(condition_test condition_test.cc)