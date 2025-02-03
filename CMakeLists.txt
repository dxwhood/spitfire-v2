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
    src/core/moves.h
    src/core/moves.cpp
    src/utils/display.h
    src/utils/display.cpp
)

# Link any required libraries (if needed)
target_link_libraries(Spitfire-v2)
