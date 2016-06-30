//
// Created by jdl on 27/06/16.
//

#include <stdlib.h>

#include "queue.h"

inline bool qu_enqueue(struct Queue *qu, void *value)
{
    return lk_push(&qu->queue,value);
}

void qu_cleanup(struct Queue *qu, bool freemem)
{
    lk_cleanup(&qu->queue,false);
    if(freemem)
        free(qu);
}

inline void qu_clear(struct Queue *qu)
{
    lk_clear(&qu->queue);
}

inline void *qu_dequeue(struct Queue *qu)
{
    return lk_pop_last(&qu->queue);
}

inline void qu_init(struct Queue *qu, void(*free)(void *obj))
{
    lk_init(&qu->queue,NULL,free);
}

inline void *qu_peek(struct Queue *qu)
{
    return lk_peek_last(&qu->queue);
}