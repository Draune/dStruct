#include"../headers/graph.h"
#include"../headers/queue.h"
#include<stdlib.h>

int sort_vertices(void* vertice1,void* vertice2);
int sort_edges(void* edge1,void* edge2);

dVertice* create_vertice(void* content,int (*sort_vertices)(void*,void*),int (*sort_edges_content)(void*,void*));
dEdge* create_edge(void* content,dVertice* head);

void* destroy_vertice(dVertice* vertice,void (*free_edge_content)(void*));
void* destroy_edge(dEdge* edge);

dGraph d_init_graph(dOriented oriented,int (*sort_vertices_content)(void*,void*),int (*sort_edges_content)(void*,void*)){
    dGraph graph;
    graph.oriented = oriented;
    graph.sort_vertices = sort_vertices_content;
    graph.sort_edges = sort_edges_content;
    graph.vertices = d_init_avl(sort_vertices);
    return graph;
}

void d_insert_vertice_graph(dGraph* graph,void* content){
    d_insert_avl(&(graph->vertices),create_vertice(content,graph->sort_vertices,graph->sort_edges));
}

void d_insert_edge_graph(dGraph* graph,void* content,dVertice* tail,dVertice* head){
    if(tail != NULL && head != NULL){
        d_insert_avl(&(tail->edges),create_edge(content,head));
        if(graph->oriented == DSTRUCT_NOT_ORIENTED)
            d_insert_avl(&(head->edges),create_edge(content,tail));
    }
}

dVertice* d_find_vertice_graph(dGraph* graph,void* content){
    dVertice* search = create_vertice(content,graph->sort_vertices,graph->sort_edges);
    dVertice* return_ = (dVertice*)d_find_avl(&(graph->vertices),search);
    free(search);
    return return_;
}

dVertice* d_find_eq_vertice_graph(dGraph* graph,void* content){
    dVertice* return_ = d_find_vertice_graph(graph,content);
    return (return_ == NULL || graph->sort_vertices(return_->content,content) != 0)?NULL:return_;
}

dEdge* d_find_edge_by_content(dVertice* tail,void* content){
    if(tail == NULL)
        return NULL;
    dEdge* search = create_edge(content,tail);
    dEdge* return_ = d_find_avl(&(tail->edges),search);
    free(search);
    return return_; 
}
dEdge* d_find_eq_edge_by_content(dVertice* tail,void* content){
    dEdge* return_ = d_find_edge_by_content(tail,content);
    return (return_ == NULL || tail->sort_edges(return_->content,content) != 0)?NULL:return_;
}

dEdge* d_find_eq_edge_by_vertices(dVertice* tail,dVertice* head){
    if(tail == NULL || head == NULL)
        return NULL;
    dQueue node_queue = d_init_queue();
    dNode* current = tail->edges.start;
    while (current != NULL){
        if(((dEdge*)current->content)->head == head)
            return (dEdge*)current->content;
        if(current->left != NULL)
            d_push_queue(&node_queue,current->left);
        if(current->right != NULL)
            d_push_queue(&node_queue,current->right);
        current = (dNode*)d_pop_queue(&node_queue);
    }
    return NULL;
}

void* d_remove_vertice_graph(dGraph* graph,dVertice* vertice,void (*free_edge_content)(void*)){
    d_remove_avl(&(graph->vertices),vertice);
    return destroy_vertice(vertice,free_edge_content);
}

void* d_remove_edge_graph(dGraph* graph,dVertice* tail,dEdge* edge){
    d_remove_avl(&(tail->edges),edge);
    if(graph->oriented == DSTRUCT_NOT_ORIENTED)
        d_remove_avl(&(edge->head->edges),d_find_eq_edge_by_vertices(edge->head,tail));
    return destroy_edge(edge);
}

void d_clear_graph(dGraph* graph,void (*free_vertice_content)(void*),void (*free_edge_content)(void*)){
    if(graph->vertices.start != NULL){
        dNode* more_on_right = graph->vertices.start;
        while(more_on_right->right != NULL)
            more_on_right = more_on_right->right;
        dVertice* more_on_right_vertice = (dVertice*)d_remove_node_avl(&(graph->vertices),more_on_right);
        while (graph->vertices.start != NULL)
            free_vertice_content(destroy_vertice(d_remove_avl(&(graph->vertices),more_on_right_vertice),free_edge_content));
        free_vertice_content(destroy_vertice(more_on_right_vertice,free_edge_content));
    }
}

int sort_vertices(void* vertice1,void* vertice2){
    return ((dVertice*)vertice1)->sort_vertices(((dVertice*)vertice1)->content,((dVertice*)vertice2)->content);
}

int sort_edges(void* edge1,void* edge2){
    return ((dEdge*)edge1)->head->sort_edges(((dEdge*)edge1)->content,((dEdge*)edge2)->content);
}

dVertice* create_vertice(void* content,int (*sort_vertices_content)(void*,void*),int (*sort_edges_content)(void*,void*)){
    dVertice* vertice = (dVertice*)malloc(sizeof(dVertice));
    vertice->edges = d_init_avl(sort_edges);
    vertice->content = content;
    vertice->sort_vertices = sort_vertices_content;
    vertice->sort_edges = sort_edges_content;
    return vertice;
}

dEdge* create_edge(void* content,dVertice* head){
    dEdge* edge = (dEdge*)malloc(sizeof(dEdge));
    edge->content = content;
    edge->head = head;
    return edge;
}

void* destroy_vertice(dVertice* vertice,void (*free_edge_content)(void*)){
    if(vertice->edges.start != NULL){
        dNode* more_on_right = vertice->edges.start;
        while(more_on_right->right != NULL)
            more_on_right = more_on_right->right;
        dEdge* more_on_right_edge = (dEdge*)d_remove_node_avl(&(vertice->edges),more_on_right);
        while (vertice->edges.start != NULL)
            free_edge_content(destroy_edge(d_remove_avl(&(vertice->edges),more_on_right_edge)));
        free_edge_content(destroy_edge(more_on_right_edge));
    }
    void* return_ = vertice->content;
    free(vertice);
    return return_;
}

void* destroy_edge(dEdge* edge){
    void* return_ = edge->content;
    free(edge);
    return return_;
}