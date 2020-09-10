#最低版本要求
cmake_minimum_required(VERSION 2.6)

#项目工程信息
project(TORNADOIMSERVER)

#设置为 Debug 模式
set(CMAKE_BUILD_TYPE "Debug")

#设置编译选项
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g")


#因为 .cpp 文件里已经 include 了 .h 文件，所以不需要再把 .h 文件包含进来
set(toollib_srcs
    ./toollib/DirectoryHelper.cpp
    ./toollib/Md5Helper.cpp
    )

set(chatserver_srcs
    ./chatserversrc/main.cpp
    )


add_executable(chatserver ${toollib_srcs} ${chatserver_srcs} )


#把存放elf文件的位置设置为工程根目录下的bin目录
#EXECUTABLE_OUTPUT_PATH ：目标二进制可执行文件的存放位置
#PROJECT_SOURCE_DIR：工程的根目录
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)




