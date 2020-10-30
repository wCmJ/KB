cmake_minimum_required(VERSION 3.10)

include_directories(../asio/asio/include)
set(CMAKE_CXX_STANDARD 11)

add_executable(server_client server_client.cc)

#add_executable(rw rw.cc)

#add_executable(async_test async_test.cc)

add_executable(timeout_operation timeout_operation_test.cc)

add_executable(timercc timer.cc)

add_executable(async_read async_read.cc)


add_executable(async_write async_write.cc)