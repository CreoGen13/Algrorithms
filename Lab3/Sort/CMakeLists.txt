project(Sort)

set(HEADER_FILES
        Sort.h)

set(SOURCE_FILES
        Sort.cpp)

add_library(Sort STATIC ${SOURCE_FILES} ${HEADER_FILES})