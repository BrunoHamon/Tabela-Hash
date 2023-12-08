cmake_minimum_required(VERSION 3.26)
project(Arvores C)

set(CMAKE_C_STANDARD 17)

add_executable(Arvores main.c
        Arvore.c
        Arvore.h)
