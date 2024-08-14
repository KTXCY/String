cmake_minimum_required(VERSION 3.28)
project(String)

set(CMAKE_CXX_STANDARD 17)

add_executable(KMP01 String/KMP01.cpp)
add_executable(KMP02 String/KMP02.cpp)

add_executable(test01 String_0/KMP_0.c;String_0/KMP_0.h;String_0/test01.c)