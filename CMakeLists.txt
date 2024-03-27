cmake_minimum_required(VERSION 3.26)
project(bazadanych)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(bazadanych main.cpp
        Tosoba.cpp
        Tstudent.cpp
        Twykladowca.cpp
        OblusgaBleduCin.cpp
        BazaDanychFunkcje.cpp)
