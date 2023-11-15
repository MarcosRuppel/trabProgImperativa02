cmake_minimum_required(VERSION 3.26)
project(trabProgImperativa02 C)

set(CMAKE_C_STANDARD 99)

add_executable(gerador
        gerador.c
        lista.h)

add_executable(exportador
        exportador.c
        lista.h)

add_executable(editor
        editor.c
        lista.h)