cmake_minimum_required(VERSION 3.20)
project(GLFWLearning)

set(CMAKE_CXX_STANDARD 20)

INCLUDE_DIRECTORIES(C:/dev/headers)
LINK_DIRECTORIES(C:/dev/lib/lib-mingw-w64)

add_executable(GLFWLearning main.cpp glad.c Util.cpp Util.hpp DrawTest01.cpp DrawTest01.hpp)

TARGET_LINK_LIBRARIES(GLFWLearning C:/dev/lib/lib-mingw-w64/libglfw3.a C:/dev/lib/lib-mingw-w64/libglfw3dll.a)
