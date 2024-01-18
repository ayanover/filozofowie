cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled src/main.cpp
        Headers/Table.h
        src/Philosopher.cpp
        Headers/Fork.h
        Headers/ConstValues.h
        Headers/Philosopher.h
        Headers/Enums.h
        src/Table.cpp
        src/Viewer.cpp
        Headers/Viewer.h
)
