cmake_minimum_required(VERSION 4.0)
project(Projet)

set(CMAKE_CXX_STANDARD 26)

add_executable(Projet main.cpp
        fonctionsTests.cpp
        Vector.cpp
        Vector.h
        Frame3D.cpp
        Frame3D.h
        Frame.h
        fonctionsTests.h)

target_link_options(Projet PRIVATE -static)