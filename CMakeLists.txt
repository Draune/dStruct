cmake_minimum_required(VERSION 3.20.2)

set(CMAKE_C_STANDARD 11)

project(test)

add_executable(test
               tests/main_test.c
               tests/creer_int.c
               tests/creer_int.h
               tests/test_file/test_file.c           
               tests/test_file/test_file.h
               tests/test_pile/test_pile.c           
               tests/test_pile/test_pile.h
               tests/test_tas/test_tas.c           
               tests/test_tas/test_tas.h
               tests/test_liste/test_liste.c           
               tests/test_liste/test_liste.h
               tests/test_avl/test_avl.c           
               tests/test_avl/test_avl.h)  

add_subdirectory(dStruct)
target_link_libraries(test dStruct)