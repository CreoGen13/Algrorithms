cmake_minimum_required(VERSION 3.24)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(main ${SOURCE_FILES})

include_directories(DynamicArray)
add_subdirectory(DynamicArray)

target_link_libraries(main DynamicArray)

add_subdirectory(Google_tests)
