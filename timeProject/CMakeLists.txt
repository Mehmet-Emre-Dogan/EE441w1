cmake_minimum_required(VERSION 3.5)

project(timeProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(timeProject main.cpp)

install(TARGETS timeProject
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
