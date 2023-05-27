cmake_minimum_required(VERSION 3.20.2)

set(CMAKE_C_STANDARD 11)

project(test)

add_executable(test
               tests/main_test.c
               tests/create_int.c
               tests/create_int.h
               tests/test_queue/test_queue.c           
               tests/test_queue/test_queue.h
               tests/test_stack/test_stack.c           
               tests/test_stack/test_stack.h
               tests/test_heap/test_heap.c           
               tests/test_heap/test_heap.h
               tests/test_list/test_list.c           
               tests/test_list/test_list.h
               tests/test_avl/test_avl.c           
               tests/test_avl/test_avl.h
               tests/test_vector/test_vector.c           
               tests/test_vector/test_vector.h
               tests/test_graph/test_graph.c           
               tests/test_graph/test_graph.h
               tests/test_sm/test_sm.c           
               tests/test_sm/test_sm.h)


add_subdirectory(dStruct)
target_link_libraries(test dStruct)