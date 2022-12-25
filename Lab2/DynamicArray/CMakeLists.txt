project(DynamicArray)

set(HEADER_FILES
        DynamicArray.h DynamicArrayDefinition.hpp)

set(SOURCE_FILES
        DynamicArray.cpp)

add_library(DynamicArray STATIC ${SOURCE_FILES} ${HEADER_FILES})