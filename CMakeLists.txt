cmake_minimum_required(VERSION 3.16)
project(GravitySimulationCpp)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.zip
)

FetchContent_MakeAvailable(raylib)

add_executable(GravitySimulation src/main.cpp)
target_link_libraries(GravitySimulation raylib)