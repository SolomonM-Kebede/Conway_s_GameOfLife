cmake_minimum_required(VERSION 3.10)
project(Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Game
        main.cpp
        WorldClass.cpp
        WorldClass.h
        Interface.cpp
        Interface.h
)