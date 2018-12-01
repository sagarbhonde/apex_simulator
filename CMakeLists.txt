cmake_minimum_required(VERSION 3.12)
project(apex_simulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(apex_simulator
        cpu.cpp
        cpu.h
        file_parser.cpp
        helper.cpp
        helper.h
        main.cpp
        Makefile)
