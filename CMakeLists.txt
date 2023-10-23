cmake_minimum_required(VERSION 3.22)
project(OpenGLStudy)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
link_directories(lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY out)

add_executable(OpenGLStudy main.cpp)
