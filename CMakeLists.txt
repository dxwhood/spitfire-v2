cmake_minimum_required(VERSION 3.10)
project(Spitfire-v2)

set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)      # Add src/ to include path
include_directories(${CMAKE_SOURCE_DIR}/src/core) # Add src/core/ explicitly

# Source files
add_executable(Spitfire-v2 
    src/main.cpp 
    src/core/board.h
    src/core/board.cpp
    src/core/moves.h
    src/core/moves.cpp
)

# Link any required libraries (if needed)
target_link_libraries(Spitfire-v2)
