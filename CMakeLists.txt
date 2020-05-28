cmake_minimum_required(VERSION 3.16)
project(kurs_sem2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wconversion -Wnon-virtual-dtor -pedantic")

add_executable(kurs_sem2
        main.cpp
        Book.cpp
        Book.h
        Reader.cpp
        Reader.h
        BookList.cpp
        BookList.h
        ReaderList.cpp
        Reader.h
        Operation.cpp
        Operation.h
        OperationList.cpp
        OperationList.h
        GenericList.cpp
        GenericList.h)