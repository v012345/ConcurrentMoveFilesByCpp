cmake_minimum_required(VERSION 3.10.0)
project(MoveFiles)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(${PROJECT_NAME} main.cpp)