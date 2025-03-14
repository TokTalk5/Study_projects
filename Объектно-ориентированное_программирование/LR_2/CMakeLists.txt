cmake_minimum_required(VERSION 3.26)
project(LR2)

set(CMAKE_CXX_STANDARD 17)

add_executable(LR2
        number.h
        SquareMatrix.cpp
        Application.h
        ConsoleApplication.cpp
        Matrix.h
        complex.cpp
        complex.h)