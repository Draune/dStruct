#ifndef DRAUNE_DSTRUCT_GRAPH
#define DRAUNE_DSTRUCT_GRAPH

#include"avl.h"

typedef enum{
    DSTRUCT_ORIENTED,
    DSTRUCT_NOT_ORIENTED
}dOriented;

typedef struct{
    void* content;
    dAVL edges;
    int (*sort_vertices)(void*,void*);
    int (*sort_edges)(void*,void*);
}dVertice;

typedef struct{
    void* content;
    dVertice* head;
}dEdge;

typedef struct{
    dAVL vertices;

    int (*sort_vertices)(void*,void*);
    int (*sort_edges)(void*,void*);

    dOriented oriented;
}dGraph;

dGraph d_init_graph(dOriented oriented,int (*sort_vertices_content)(void*,void*),int (*sort_edges_content)(void*,void*));
void d_insert_vertice_graph(dGraph* graph,void* content);
void d_insert_edge_graph(dGraph* graph,void* content,dVertice* tail,dVertice* head);

dVertice* d_find_vertice_graph(dGraph* graph,void* content);
dVertice* d_find_eq_vertice_graph(dGraph* graph,void* content);
dEdge* d_find_edge_by_content(dVertice* tail,void* content); // log(n) complexity
dEdge* d_find_eq_edge_by_content(dVertice* tail,void* content); // log(n) complexity
dEdge* d_find_eq_edge_by_vertices(dVertice* tail,dVertice* head); // n complexity

void* d_remove_vertice_graph(dGraph* graph,dVertice* vertice,void (*free_edge_content)(void*));
void* d_remove_edge_graph(dGraph* graph,dVertice* tail,dEdge* edge);
void d_clear_graph(dGraph* graph,void (*free_vertice_content)(void*),void (*free_edge_content)(void*));

#endif