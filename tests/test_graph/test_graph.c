#include"test_graph.h"
#include"../../dStruct/headers/graph.h"
#include<stdlib.h>
#include<stdio.h>
#include"../create_int.h"

int sort_int_graph(void* int1,void* int2){
    return(*((int*)int1) == *((int*)int2))?0:(*((int*)int1) > *((int*)int2))?1:-1;
}

#define FIND_VALUE 3

void test_graph_1(void){
    dGraph graph = d_init_graph(DSTRUCT_ORIENTED,sort_int_graph,sort_int_graph);

    for(int i = 0;i<5;i++)
        d_insert_vertice_graph(&graph,create_int(i));
    
    int* test = create_int(FIND_VALUE);

    if(*((int*)(d_find_eq_vertice_graph(&graph,test)->content)) == FIND_VALUE)
        printf("test find vertice ok\n");
    else
        printf("test find vertice not-ok\n");

    *test = 4;
    int* test_remove = d_remove_vertice_graph(&graph,d_find_eq_vertice_graph(&graph,test),free);
    if(*test_remove == *test && d_find_eq_vertice_graph(&graph,test) == NULL)
        printf("test remove vertice ok\n");
    else
        printf("test remove vertice not-ok\n");

    *test = 2;
    *test_remove = 3;
    int* test_find = create_int(0);
    d_insert_edge_graph(&graph,create_int(0),d_find_eq_vertice_graph(&graph,test),d_find_eq_vertice_graph(&graph,test_remove));
    if(*((int*)d_find_eq_edge_by_content(d_find_eq_vertice_graph(&graph,test),test_find)->content) == *test_find)
        printf("test find edge by content ok\n");
    else
        printf("test find edge by content not-ok\n");
    if(*((int*)d_find_eq_edge_by_vertices(d_find_eq_vertice_graph(&graph,test),d_find_eq_vertice_graph(&graph,test_remove))->content) == *test_find)
        printf("test find edge by vertices ok\n");
    else
        printf("test find edge by vertices not-ok\n");

    *test = 0;
    *test_remove = 1;
    *test_find = 2;
    d_insert_edge_graph(&graph,create_int(2),d_find_eq_vertice_graph(&graph,test),d_find_eq_vertice_graph(&graph,test_remove));
    int* test_remove_edge = d_remove_edge_graph(&graph,d_find_eq_vertice_graph(&graph,test),d_find_eq_edge_by_content(d_find_eq_vertice_graph(&graph,test),test_find));
    if(*test_remove_edge == *test_find && d_find_eq_edge_by_content(d_find_eq_vertice_graph(&graph,test),test_find) == NULL)
        printf("test remove edge ok\n");
    else
        printf("test remove edge not-ok\n");

    free(test);
    free(test_remove);
    free(test_remove_edge);
    free(test_find);


    d_clear_graph(&graph,free,free);
}
