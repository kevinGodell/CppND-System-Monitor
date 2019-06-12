cmake_minimum_required(VERSION 3.13)
project(CppND-System-Monitor)

set(CMAKE_CXX_STANDARD 17)

add_executable(CppND-System-Monitor ProcessParser.cpp Util.cpp SysInfo.cpp Process.cpp ProcessContainer.cpp main.cpp)