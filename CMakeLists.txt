cmake_minimum_required(VERSION 3.10)
project(Spitfire-v2)

set(CMAKE_CXX_STANDARD 23)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)      
include_directories(${CMAKE_SOURCE_DIR}/src/core) 
include_directories(${CMAKE_SOURCE_DIR}/src/utils) 


# Source files
add_executable(Spitfire-v2 
    src/main.cpp 
    src/core/board.h
    src/core/board.cpp
    src/core/movegen.h
    src/core/movegen.cpp
    src/core/move.h
    src/core/move.cpp
    src/core/game.h
    src/core/game.cpp
    src/core/definitions.h
    src/utils/display.h
    src/utils/display.cpp
    src/utils/input.h
    src/utils/input.cpp
)

# Link any required libraries (if needed)
target_link_libraries(Spitfire-v2)
