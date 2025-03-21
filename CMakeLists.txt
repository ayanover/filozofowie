cmake_minimum_required(VERSION 3.27)
project(philosophers)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

add_executable(untitled src/main.cpp
        Headers/Table.h
        src/Philosopher.cpp
        Headers/Fork.h
        Headers/ConstValues.h
        Headers/Philosopher.h
        Headers/Enums.h
        src/Table.cpp
        src/ConsoleViewer.cpp
        Headers/ConsoleViewer.h
)
