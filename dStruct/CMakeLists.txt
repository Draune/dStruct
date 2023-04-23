cmake_minimum_required(VERSION 3.20.2)

set(CMAKE_C_STANDARD 11)

project(dSruct)

set(SRCS
    sources/avl.c
    sources/queue.c
    sources/list.c
    sources/link.c
    sources/stack.c
    sources/heap.c
    sources/vector.c
    )
    
set(HEADERS
    headers/avl.h
    headers/dstruct.h
    headers/queue.h
    headers/list.h
    headers/link.h
    headers/stack.h
    headers/heap.h     
    headers/vector.h     
    )

add_library(dStruct ${SRCS} ${HEADERS})

target_link_libraries(dStruct m)