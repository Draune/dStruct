#ifndef DRAUNE_DSTRUCT_STATE_MACHINE
#define DRAUNE_DSTRUCT_STATE_MACHINE

#include "graph.h"

typedef struct
{
    unsigned int num;
    void (*test_state)(void *, void *);
} dState;

typedef struct
{
    unsigned int num_next;
    void (*action_link)(void *);
} dLinkState;

typedef struct
{
    dGraph graph;
    dState *current_state;
    void *content;
} dStateMachine;

dStateMachine d_init_state_machine(void *content);
int d_add_state_machine(dStateMachine *state_machine, int num_state, void (*test_state)(void *, void *));
int d_link_state_machine(dStateMachine *state_machine, int num_state1, int num_state2, void (*action_link)(void *));
dState *d_find_eq_state_machine(dStateMachine *state_machine, int num_state);
dLinkState *d_find_eq_link_state_machine(dStateMachine *state_machine, int num_state1, int num_state2);
int d_remove_state_machine(dStateMachine *state_machine, int num_state);
int d_remove_link_state_machine(dStateMachine *state_machine, int num_state1, int num_state2);
int d_clear_state_machine(dStateMachine *state_machine, void (*free_content)(void *));

int d_start_state_machine(dStateMachine *state_machine, int num_start_state);
// what_s_new will be passed as the second argument of test_state
// do not use d_refresh_state_machine in a fonction test_state or action_link to avoid recursivity
int d_refresh_state_machine(dStateMachine *state_machine, void *what_s_new);
// to use in test_state functions
int d_next_state_machine(dStateMachine *state_machine, int num_next_state);
int d_reset_state_machine(dStateMachine *state_machine, void *new_content, void (*free_content)(void *));

#endif