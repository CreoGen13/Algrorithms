cmake_minimum_required(VERSION 3.24)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(main ${SOURCE_FILES})

include_directories(Sort)
add_subdirectory(Sort)

target_link_libraries(main Sort)

add_subdirectory(Google_tests)