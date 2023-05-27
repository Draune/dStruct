#include "test_sm.h"
#include "../../dStruct/headers/sm.h"
#include <stdio.h>
#include <stdlib.h>

void test_state_1(void *state_machine, void *what_s_new);
void test_state_2(void *state_machine, void *what_s_new);
void test_state_3(void *state_machine, void *what_s_new);
void test_state_4(void *state_machine, void *what_s_new);

void action_link_1_1(void *state_machine);
void action_link_1_2(void *state_machine);
void action_link_1_3(void *state_machine);
void action_link_2_1(void *state_machine);
void action_link_3_4(void *state_machine);
void action_link_4_1(void *state_machine);

void test_find(dStateMachine *sm);
void test_running(dStateMachine *sm);
void test_remove(dStateMachine *sm);

void test_sm_1(void)
{
    dStateMachine sm = d_init_state_machine(malloc(sizeof(int)));

    d_add_state_machine(&sm, 1, test_state_1);
    d_add_state_machine(&sm, 2, test_state_2);
    d_add_state_machine(&sm, 3, test_state_3);
    d_add_state_machine(&sm, 4, test_state_4);

    d_link_state_machine(&sm, 1, 1, action_link_1_1);
    d_link_state_machine(&sm, 1, 2, action_link_1_2);
    d_link_state_machine(&sm, 1, 3, action_link_1_3);
    d_link_state_machine(&sm, 2, 1, action_link_2_1);
    d_link_state_machine(&sm, 3, 4, action_link_3_4);
    d_link_state_machine(&sm, 4, 1, action_link_4_1);

    test_find(&sm);
    test_running(&sm);
    test_remove(&sm);

    d_clear_state_machine(&sm, free);
}

void test_state_1(void *state_machine, void *what_s_new)
{
    switch (*((int *)what_s_new))
    {
    case 1:
        d_next_state_machine((dStateMachine *)state_machine, 1);
        break;
    case 2:
        d_next_state_machine((dStateMachine *)state_machine, 2);
        break;
    case 3:
        d_next_state_machine((dStateMachine *)state_machine, 3);
        break;
    default:
        break;
    }
}

void test_state_2(void *state_machine, void *what_s_new)
{
    switch (*((int *)what_s_new))
    {
    case 1:
        d_next_state_machine((dStateMachine *)state_machine, 1);
        break;
    default:
        break;
    }
}

void test_state_3(void *state_machine, void *what_s_new)
{
    switch (*((int *)what_s_new))
    {
    case 4:
        d_next_state_machine((dStateMachine *)state_machine, 4);
        break;
    default:
        break;
    }
}

void test_state_4(void *state_machine, void *what_s_new)
{
    switch (*((int *)what_s_new))
    {
    case 1:
        d_next_state_machine((dStateMachine *)state_machine, 1);
        break;
    default:
        break;
    }
}

void action_link_1_1(void *state_machine)
{
    *((int *)((dStateMachine *)state_machine)->content) = 11;
}

void action_link_1_2(void *state_machine)
{
    *((int *)((dStateMachine *)state_machine)->content) = 12;
}

void action_link_1_3(void *state_machine)
{
    *((int *)((dStateMachine *)state_machine)->content) = 13;
}

void action_link_2_1(void *state_machine)
{
    *((int *)((dStateMachine *)state_machine)->content) = 21;
}

void action_link_3_4(void *state_machine)
{
    *((int *)((dStateMachine *)state_machine)->content) = 34;
}

void action_link_4_1(void *state_machine)
{
    *((int *)((dStateMachine *)state_machine)->content) = 41;
}

void test_find(dStateMachine *sm)
{
    for (int i = 1; i <= 4; i++)
    {
        if (d_find_eq_state_machine(sm, i)->num == i)
            printf("find %d ok\n", i);
        else
            printf("find %d not-ok\n", i);
    }
    if (d_find_eq_state_machine(sm, 5) == NULL)
        printf("not-find 5 ok\n\n");
    else
        printf("not-find 5 not-ok\n\n");

    if (d_find_eq_link_state_machine(sm, 1, 3)->num_next == 3)
        printf("find 1->3 ok\n");
    else
        printf("find 1->3 not-ok\n");

    if (d_find_eq_link_state_machine(sm, 2, 4) == NULL)
        printf("not-find 2->4 ok\n");
    else
        printf("not-find 2->4 not-ok\n");
}

void test_running(dStateMachine *sm)
{
    d_start_state_machine(sm, 1);
    if (sm->current_state->num == 1)
        printf("start ok\n\n");
    else
        printf("start not-ok\n\n");

    int what_s_new = 1;
    d_refresh_state_machine(sm, &what_s_new);
    if (*((int *)sm->content) == 11)
        printf("11 ok\n");
    else
        printf("11 not-ok\n");

    what_s_new = 2;
    d_refresh_state_machine(sm, &what_s_new);
    if (*((int *)sm->content) == 12)
        printf("12 ok\n");
    else
        printf("12 not-ok\n");

    what_s_new = 1;
    d_refresh_state_machine(sm, &what_s_new);
    if (*((int *)sm->content) == 21)
        printf("21 ok\n");
    else
        printf("21 not-ok\n");

    what_s_new = 3;
    d_refresh_state_machine(sm, &what_s_new);
    if (*((int *)sm->content) == 13)
        printf("13 ok\n");
    else
        printf("13 not-ok\n");

    what_s_new = 4;
    d_refresh_state_machine(sm, &what_s_new);
    if (*((int *)sm->content) == 34)
        printf("34 ok\n");
    else
        printf("34 not-ok\n");

    what_s_new = 1;
    d_refresh_state_machine(sm, &what_s_new);
    if (*((int *)sm->content) == 41)
        printf("41 ok\n\n");
    else
        printf("41 not-ok\n\n");
}

void test_remove(dStateMachine *sm)
{
    d_remove_link_state_machine(sm,1,2);
    if (d_find_eq_link_state_machine(sm, 1, 2) == NULL)
        printf("remove 1->2 ok\n");
    else
        printf("remove 1->2 not-ok\n");

    d_remove_state_machine(sm,4);
    if (d_find_eq_state_machine(sm, 4) == NULL)
        printf("remove 4 ok\n\n");
    else
        printf("remove 4 not-ok\n\n");
}