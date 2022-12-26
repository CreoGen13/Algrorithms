cmake_minimum_required(VERSION 3.24)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(main ${SOURCE_FILES})

include_directories(Game)
add_subdirectory(Game)

target_link_libraries(main Game)
