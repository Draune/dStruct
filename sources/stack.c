#include "../headers/stack.h"
#include "../headers/error.h"

dStack d_init_stack()
{
    dStack stack;
    stack.start = NULL;
    return stack;
}

int d_push_stack(dStack *stack, void *content)
{
    if (content == NULL)
        return DSTRUCT_PARAMETER_NULL;
    dChain *new = d_create_chain(content);
    if (new == NULL)
        return DSTRUCT_MALLOC_ERROR;
    new->next = stack->start;
    stack->start = new;
    return DSTRUCT_NO_ERROR;
}

void *d_pop_stack(dStack *stack)
{
    dChain *to_delete = stack->start;
    if (to_delete == NULL)
    {
        return NULL;
    }
    stack->start = to_delete->next;
    return d_destroy_chain(to_delete);
}

int d_clear_stack(dStack *stack, void (*free_content)(void *))
{
    while (stack->start != NULL)
    {
        void *to_delete = d_pop_stack(stack);
        if (to_delete != NULL)
            free_content(to_delete);
    }
    return DSTRUCT_NO_ERROR;
}