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

#include <stdlib.h>

#include "jcdatatype.h"
#include "queue.h"

inline JCErr qu_enqueue(struct Queue *qu, void *value)
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