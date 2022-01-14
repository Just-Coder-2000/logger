cmake_minimum_required(VERSION 3.10)

project(logger VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE "Release")

include_directories(./include)

add_executable(${PROJECT_NAME} ./main.cpp)

# install

set(CMAKE_INSTALL_PREFIX /usr/local)

install(FILES ${CMAKE_SOURCE_DIR}/include/logger.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/logger)