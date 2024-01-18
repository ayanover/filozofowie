cmake_minimum_required(VERSION 3.27)
project(philosophers)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

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
target_link_libraries(philosophers pthread ${CURSES_LIBRARIES})