cmake_minimum_required(VERSION 3.2)
project(PhysicSim)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES
    "*.cpp"
)

include_directories(include)
add_executable(PhysicSim ${SOURCE_FILES})