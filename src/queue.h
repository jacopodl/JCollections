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

/**
 * @file queue.h
 * @brief Provides functions for manage the queue.
 */

#ifndef JCOLLECTIONS_QUEUE_H
#define JCOLLECTIONS_QUEUE_H

#include "jcdatatype.h"
#include "lklist.h"

/**
 * @brief Obtains number of elements in this queue.
 * @param qu Pointer to queue.
 * @return The number of elements in this queue.
 */
#define QU_COUNT(qu)    qu->queue.count

/**
 * @brief Returns true if this queue contains no elements.
 * @param qu Pointer to queue.
 * @return true if this linked-list contains no elements.
 */
#define QU_ISEMPTY(qu)  (qu->queue.count==0)

/**
 * @brief This structure represent the queue.
 *
 * It can be used in this way:
 * @code
 * char *str;
 * struct Queue queue;
 * qu_init(&queue, free);
 * qu_enqueue(&queue, value);
 * str = (char *) qu_dequeue(&queue);
 * qu_cleanup(&queue,false);
 * @endcode
 */
struct Queue {
    struct LkList queue;
};

/**
 * @brief Inserts the specified element into the queue.
 * @param qu Pointer to queue.
 * @param value The element to add.
 * @return If the item was inserted JCERR_SUCCESS is returned.
 * @warning In case of out of memory JCERR_ENOMEM is returned.
 */
JCErr qu_enqueue(struct Queue *qu, void *value);

/**
 * @brief Dismiss queue and releases all resources.
 * @param qu Pointer to queue.
 * @param freemem Release memory?
 */
void qu_cleanup(struct Queue *qu, bool freemem);

/**
 * @brief Removes all of the elements from this queue.
 * @param qu Pointer to queue.
 */
void qu_clear(struct Queue *qu);

/**
 * @brief Removes and returns the first element of this queue.
 * @param qu Pointer to queue.
 */
void *qu_dequeue(struct Queue *qu);

/**
 * @brief Initialize a new queue.
 * @param qu Pointer to queue.
 * @param free Pointer to the function called to free memory.
 */
void qu_init(struct Queue *qu, void(*free)(void *obj));

/**
 * @brief Retrieves, but does not remove, the first element of this queue.
 * @param qu Pointer to queue.
 */
void *qu_peek(struct Queue *qu);

#endif
