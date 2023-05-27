#include "../headers/queue.h"
#include "../headers/error.h"

dQueue d_init_queue()
{
    dQueue queue;
    queue.start = NULL;
    queue.end = NULL;
    return queue;
}

int d_push_queue(dQueue *queue, void *content)
{
    if (content == NULL)
        return DSTRUCT_PARAMETER_NULL;
    dChain *new = d_create_chain(content);
    if (new == NULL)
        return DSTRUCT_MALLOC_ERROR;
    if (queue->start == NULL)
    {
        queue->start = new;
        queue->end = new;
    }
    else
    {
        queue->end->next = new;
        queue->end = queue->end->next;
    }
    return DSTRUCT_NO_ERROR;
}

void *d_pop_queue(dQueue *queue)
{
    dChain *to_delete = queue->start;
    if (to_delete == NULL)
    {
        return NULL;
    }
    if (to_delete->next == NULL)
    {
        queue->end = NULL;
    }
    queue->start = to_delete->next;
    return d_destroy_chain(to_delete);
}

int d_clear_queue(dQueue *queue, void (*free_content)(void *))
{
    while (queue->start != NULL)
    {
        void *to_delete = d_pop_queue(queue);
        if (to_delete != NULL)
            free_content(to_delete);
    }
    return DSTRUCT_NO_ERROR;
}