
cmake_minimum_required(VERSION 3.10)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 17)

# Add Raylib
find_package(raylib REQUIRED)

# Include directories
include_directories(src)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(space_invaders ${SOURCES} main.cpp)

# Link Raylib
target_link_libraries(space_invaders raylib)
