cmake_minimum_required(VERSION 3.20.2)

set(CMAKE_C_STANDARD 11)

project(dSruct)

set(SRCS
    sources/avl.c
    sources/file.c
    sources/liste.c
    sources/maillons.c
    sources/pile.c
    sources/tas.c
    )
    
set(HEADERS
    headers/avl.h
    headers/dstruct.h
    headers/file.h
    headers/liste.h
    headers/maillons.h
    headers/pile.h
    headers/tas.h     
    )

add_library(dStruct ${SRCS} ${HEADERS})