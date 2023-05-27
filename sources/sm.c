#include "../headers/sm.h"
#include "../headers/error.h"
#include <stdlib.h>

int sort_state(void *state1, void *state2);
int sort_link(void *link1, void *link2);

dState *create_state(int num_state, void (*test_state)(void *, void *));
dLinkState *create_link(int num_next_state, void (*action_link)(void *));

dStateMachine d_init_state_machine(void *content)
{
    dStateMachine state_machine;
    state_machine.content = content;
    state_machine.current_state = NULL;
    state_machine.graph = d_init_graph(DSTRUCT_ORIENTED, sort_state, sort_link);
    return state_machine;
}

int d_add_state_machine(dStateMachine *state_machine, int num_state, void (*test_state)(void *, void *))
{
    dState *new = create_state(num_state, test_state);
    if (new == NULL)
        return DSTRUCT_MALLOC_ERROR;
    return d_insert_vertice_graph(&(state_machine->graph), new);
}

int d_link_state_machine(dStateMachine *state_machine, int num_state1, int num_state2, void (*action_link)(void *))
{
    dState state1, state2;
    state1.num = num_state1;
    state2.num = num_state2;
    dLinkState *new = create_link(num_state2, action_link);
    if (new == NULL)
        return DSTRUCT_MALLOC_ERROR;
    dVertice *vertice1 = d_find_eq_vertice_graph(&(state_machine->graph), &state1);
    dVertice *vertice2 = d_find_eq_vertice_graph(&(state_machine->graph), &state2);
    if (vertice1 == NULL || vertice2 == NULL)
        return DSTRUCT_STATE_NOT_FOUND;
    return d_insert_edge_graph(&(state_machine->graph), new, vertice1, vertice2);
}

dState *d_find_eq_state_machine(dStateMachine *state_machine, int num_state)
{
    dState state;
    state.num = num_state;
    dVertice *vertice = d_find_eq_vertice_graph(&(state_machine->graph), &state);
    return (vertice == NULL) ? NULL : vertice->content;
}

dLinkState *d_find_eq_link_state_machine(dStateMachine *state_machine, int num_state1, int num_state2)
{
    dState tail;
    tail.num = num_state1;
    dLinkState link;
    link.num_next = num_state2;
    dVertice *vertice = d_find_eq_vertice_graph(&(state_machine->graph), &tail);
    if (vertice == NULL)
        return NULL;
    dEdge *edge = d_find_eq_edge_by_content(vertice, &link);
    return (edge == NULL) ? NULL : edge->content;
}

int d_remove_state_machine(dStateMachine *state_machine, int num_state)
{
    dState state;
    state.num = num_state;
    dVertice *vertice = d_find_eq_vertice_graph(&(state_machine->graph), &state);
    if (vertice == NULL)
        return DSTRUCT_STATE_NOT_FOUND;
    free(d_remove_vertice_graph(&(state_machine->graph), vertice, free));
    return DSTRUCT_NO_ERROR;
}

int d_remove_link_state_machine(dStateMachine *state_machine, int num_state1, int num_state2)
{
    dState tail;
    tail.num = num_state1;
    dLinkState link;
    link.num_next = num_state2;
    dVertice *vertice = d_find_eq_vertice_graph(&(state_machine->graph), &tail);
    if (vertice == NULL)
        return DSTRUCT_STATE_NOT_FOUND;
    dEdge *edge = d_find_eq_edge_by_content(vertice, &link);
    if (edge == NULL)
        return DSTRUCT_LINK_STATE_NOT_FOUND;
    free(d_remove_edge_graph(&(state_machine->graph), vertice, edge));
    return DSTRUCT_NO_ERROR;
}

int d_clear_state_machine(dStateMachine *state_machine, void (*free_content)(void *))
{
    free_content(state_machine->content);
    state_machine->content = NULL;
    state_machine->current_state = NULL;
    return d_clear_graph(&(state_machine->graph), free, free);
}

int d_start_state_machine(dStateMachine *state_machine, int num_start_state)
{
    state_machine->current_state = d_find_eq_state_machine(state_machine, num_start_state);
    if (state_machine->current_state == NULL)
        return DSTRUCT_STATE_NOT_FOUND;
    return DSTRUCT_NO_ERROR;
}

int d_refresh_state_machine(dStateMachine *state_machine, void *what_s_new)
{
    if (state_machine->current_state != NULL)
        state_machine->current_state->test_state(state_machine, what_s_new);
    return DSTRUCT_NO_ERROR;
    return DSTRUCT_STATE_MACHINE_NOT_STARTED;
}

int d_next_state_machine(dStateMachine *state_machine, int num_next_state)
{
    if (state_machine->current_state != NULL)
    {
        dLinkState *link = d_find_eq_link_state_machine(state_machine,state_machine->current_state->num, num_next_state);
        if (link != NULL)
        {
            state_machine->current_state = d_find_eq_state_machine(state_machine, num_next_state);
            if (state_machine->current_state == NULL)
                return DSTRUCT_STATE_NOT_FOUND;
            link->action_link(state_machine);
            return DSTRUCT_NO_ERROR;
        }
        return DSTRUCT_LINK_STATE_NOT_FOUND;
    }
    return DSTRUCT_STATE_MACHINE_NOT_STARTED;
}

int d_reset_state_machine(dStateMachine *state_machine, void *new_content, void (*free_content)(void *))
{
    free_content(state_machine->content);
    state_machine->content = new_content;
    state_machine->current_state = NULL;
    return DSTRUCT_NO_ERROR;
}

int sort_state(void *state1, void *state2)
{
    return (((dState *)state1)->num == ((dState *)state2)->num) ? 0 : (((dState *)state1)->num > ((dState *)state2)->num) ? -1
                                                                                                                          : 1;
}

int sort_link(void *link1, void *link2)
{
    return (((dLinkState *)link1)->num_next == ((dLinkState *)link2)->num_next) ? 0 : (((dLinkState *)link1)->num_next > ((dLinkState *)link2)->num_next) ? -1
                                                                                                                                                          : 1;
}

dState *create_state(int num_state, void (*test_state)(void *, void *))
{
    dState *state = (dState *)malloc(sizeof(dState));
    if (state == NULL)
        return NULL;
    state->num = num_state;
    state->test_state = test_state;
    return state;
}

dLinkState *create_link(int num_next_state, void (*action_link)(void *))
{
    dLinkState *link = (dLinkState *)malloc(sizeof(dLinkState));
    if (link == NULL)
        return NULL;
    link->num_next = num_next_state;
    link->action_link = action_link;
    return link;
}