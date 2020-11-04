

cd <path/to/project>
mkdir build && cd build
# arm64
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/ios.toolchain.cmake -DPLATFORM=OS64 -DENABLE_BITCODE=0
# armv7
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/ios.toolchain.cmake -DPLATFORM=OS -DARCHS=armv7 -DENABLE_BITCODE=0
# or simulator
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/ios.toolchain.cmake -DPLATFORM=SIMULATOR64 -DENABLE_BITCODE=0
make -j


#注：此处gmhelper为我编译的静态库名字，需要替换
#DROOT是系统变量，主要指定头文件和链接库的路径 此处可替换成自己对应路径

cmake_minimum_required(VERSION 3.2)
project (test C CXX)

# 工程名
set(PROJECT_NAME test)
set(CMAKE_CXX_STANDARD 11)

# 源文件
# aux_source_directory为包含指定目录下所有的源文件
# 若不需要包含所有的源文件，则使用set定义，如：set(SRC_FILES 1.cpp 2.cpp)
# aux_source_directory(. SRC_FILES)
set(SRC_FILES
    recovery/test.cc
    recovery/http_client.cc)

 
# 头文件
# 若指定多个目录，使用空格分隔 .表示当前项目路径
#include_directories($ENV{DROOT}/inc .)
include_directories(third_party/asio/asio/include inc/)

    add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
    #target_include_directories(${PROJECT_NAME} PUBLIC third_party/asio/asio/include)


set_target_properties(${PROJECT_NAME} PROPERTIES
    FRAMEWORK TRUE
    MACOSX_FRAMEWORK_IDENTIFIER com..test
  )
  


# 链接/安装
    #target_link_libraries(${PROJECT_NAME}  pthread dl)

#cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=../cmake/ios.toolchain.cmake -DPLATFORM=OS64 -DENABLE_BITCODE=FALSE
#cmake --build . --config Release|Debug



#-DPLATFORM编译参数
#Set -DPLATFORM to "SIMULATOR" to build for iOS simulator 32 bit (i386) DEPRECATED
#Set -DPLATFORM to "SIMULATOR64" (example above) to build for iOS simulator 64 bit (x86_64)
#Set -DPLATFORM to "OS" to build for Device (armv7, armv7s, arm64)
#Set -DPLATFORM to "OS64" to build for Device (arm64)
#Set -DPLATFORM to "OS64COMBINED" to build for Device & Simulator (FAT lib) (arm64, x86_64)
#Set -DPLATFORM to "TVOS" to build for tvOS (arm64)
#Set -DPLATFORM to "TVOSCOMBINED" to build for tvOS & Simulator (arm64, x86_64)
#Set -DPLATFORM to "SIMULATOR_TVOS" to build for tvOS Simulator (x86_64)
#Set -DPLATFORM to "WATCHOS" to build for watchOS (armv7k, arm64_32)
#Set -DPLATFORM to "WATCHOSCOMBINED" to build for watchOS & Simulator (armv7k, arm64_32, i386)
#Set -DPLATFORM to "SIMULATOR_WATCHOS" to build for watchOS Simulator (i386)
# -DARCHS 可以指定编译某种架构的库
#  -DARCHS=armv7 则可以只编译armv7架构的库


# 编译时链接路径 此处对不同架构时的链接路径做了一些处理（如果不需要链接其他库可以注释掉）
#[[
if(${ARCHS} STREQUAL "arm64")
    set(LIB_DIR ios_arm64_r)
elseif(${ARCHS} STREQUAL "armv7")
    set(LIB_DIR ios_armv7_r)
elseif(${ARCHS} STREQUAL "armv7s")
    set(LIB_DIR ios_armv7s_r)
elseif(${ARCHS} STREQUAL "i386")
    set(LIB_DIR ios_i386_r)
elseif(${ARCHS} STREQUAL "x86_64")
    set(LIB_DIR ios_x86_64_r)
endif()
    link_directories($ENV{DROOT}/bin/${LIB_DIR})
]]
# 生成目标 STATIC和ARCHIVE对应静态库 SHARED和LIBRARY对应动态库