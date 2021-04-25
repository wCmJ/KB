cmake_minimum_required(VERSION 3.10)

project(Tutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

option(USE_MYMATH "Use tutorial provided math implementation" ON)
configure_file(tutorial.h.in tutorial.h)


if(USE_MYMATH)
  add_subdirectory(MathFunctions)
  #list(APPEND EXTRA_LIBS MathFunctions)
  #list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
endif()

message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
message("EXTRA_INCLUDES: " ${EXTRA_INCLUDES})
#message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})

add_executable(Tutorial tutorial.cc)

if(USE_MYMATH)
target_link_libraries(Tutorial PUBLIC MathFunctions)
endif()

target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/MathFunctions")


