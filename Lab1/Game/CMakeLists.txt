project(Game)

set(HEADER_FILES
        Game.h)

set(SOURCE_FILES
        Game.cpp)

add_library(Game STATIC ${SOURCE_FILES} ${HEADER_FILES})