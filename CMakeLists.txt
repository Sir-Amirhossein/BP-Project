cmake_minimum_required(VERSION 3.21)
project(Project C)

set(CMAKE_C_STANDARD 23)

add_executable(Project main.c sqlite3.c structures.h database.h database.c orders.h orders.c orders2.c orders2.h database2.c database2.h testcases.c testcases.h menu.c menu.h menuORDERS.c menuORDERS.h)
