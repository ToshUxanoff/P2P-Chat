cmake_minimum_required(VERSION 3.0)
project(client)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/client/ClientWindow.cpp)




