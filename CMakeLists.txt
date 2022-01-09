cmake_minimum_required(VERSION 3.10)

project(logger VERSION 1.0)

include_directories(./include)

add_executable(${PROJECT_NAME} ./main.cpp)