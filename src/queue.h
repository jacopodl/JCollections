//
// Created by jdl on 27/06/16.
//

#ifndef JCOLLECTIONS_QUEUE_H
#define JCOLLECTIONS_QUEUE_H

#include "lklist.h"

#define QU_COUNT(qu)    qu->queue.count
#define QU_ISEMPTY(qu)  (qu->queue.count==0)

struct Queue {
    struct LkList queue;
};

bool qu_enqueue(struct Queue *qu, void *value);

void qu_cleanup(struct Queue *qu, bool freemem);

void qu_clear(struct Queue *qu);

void *qu_dequeue(struct Queue *qu);

void qu_init(struct Queue *qu, void(*free)(void *obj));

void *qu_peek(struct Queue *qu);
#endif
