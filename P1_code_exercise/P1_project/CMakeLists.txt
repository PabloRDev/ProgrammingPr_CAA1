cmake_minimum_required(VERSION 3.29)
project(P1_project C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(P1_project
    csv.c
    csv.h
    main.c
    taxation.c
    taxation.h)
