cmake_minimum_required(VERSION 3.26)
project(Tabela_hash C)

set(CMAKE_C_STANDARD 17)

add_executable(Tabela_hash main.c
        Tabela.c
        Tabela.h
        ../Arvores/Arvore.c)
