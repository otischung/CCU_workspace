cmake_minimum_required(VERSION 3.0.0)

project(B_plus_tree)

# Add executable target
add_executable(BTree main.cpp)

# Add include directories
target_include_directories(BTree PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Set C++ standard
set_property(TARGET BTree PROPERTY CXX_STANDARD 11)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -fsanitize=address -fsanitize=undefined -fsanitize=leak")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

# Make install
install(TARGETS BTree DESTINATION bin)
