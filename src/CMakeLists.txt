set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(fmt)

include_directories(. ${FMT_INCLUDE_DIRS})

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE fmt::fmt)