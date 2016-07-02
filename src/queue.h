/*
* queue, part of JCollections.
* Copyright (C) 2014-2016 Jacopo De Luca
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 3 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef JCOLLECTIONS_QUEUE_H
#define JCOLLECTIONS_QUEUE_H

#include "jcdatatype.h"
#include "lklist.h"

#define QU_COUNT(qu)    qu->queue.count
#define QU_ISEMPTY(qu)  (qu->queue.count==0)

struct Queue {
    struct LkList queue;
};

JCErr qu_enqueue(struct Queue *qu, void *value);

void qu_cleanup(struct Queue *qu, bool freemem);

void qu_clear(struct Queue *qu);

void *qu_dequeue(struct Queue *qu);

void qu_init(struct Queue *qu, void(*free)(void *obj));

void *qu_peek(struct Queue *qu);
#endif
