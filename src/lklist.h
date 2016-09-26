/*
 * lklist, part of JCollections.
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
 * @file lklist.h
 * @brief Provides functions for manage linkedlist.
 */

#ifndef JCOLLECTIONS_LkList_H
#define JCOLLECTIONS_LkList_H

#include <stdbool.h>
#include "jcdatatype.h"

#define STATIC_LKLIST_INITIALIZER           {NULL, NULL, NULL, 0, NULL}
#define STATIC_LKLIST_INITIALIZER1(free)    {NULL, NULL, NULL, 0, free}

/**
 * @brief Obtains number of elements in this linked-list.
 * @param list Pointer to linked-list.
 * @return The number of elements in this linked-list.
 */
#define LK_COUNT(list)    list->count

/**
 * @brief Returns true if this linked-list contains no elements.
 * @param list Pointer to linked-list.
 * @return true if this linked-list contains no elements.
 */
#define LK_ISEMPTY(list)  (list->count==0)

struct LkNode {
    void *value;
    struct LkNode *next;
    struct LkNode *prev;
};

/**
 * @brief This structure represent a linked-list.
 *
 * It can be used in this way:
 * @code
 * char *str;
 * struct LkList lkl;
 * lk_init(&lkl, equals_to, free);
 * lk_push(&lkl, value);
 * lk_push(&lkl, value2);
 * str = (char *) lk_pop(&lkl);
 * lk_cleanup(&lkl,false);
 * @endcode
 */
struct LkList {
    struct LkNode *list;
    struct LkNode *tail;
    jcsize count;

    void (*free)(void *obj);
};

struct LkIterator {
    struct LkList *lklist;
    struct LkNode *cursor;
    bool start;
};

/**
 * @brief Returns true if this linked-list contains the specified element.
 * @param list Pointer to linked-list.
 * @param value Element whose presence in this linked-list is to be tested.
 * @param equals_to Pointer to comparison function.
 * @return true if this list contains the specified element, false otherwise.
 */
bool lk_contains(struct LkList *list, void *value, bool(*equals_to)(void *obj1, void *obj2));

/**
 * @brief Inserts the specified element at the beginning of this linked-list.
 * @param list Pointer to linkedlist.
 * @param value The element to add.
 * @return If the value is added to linked-list JCERR-success is returned.
 * @warning In case of out of memory JCERR_ENOMEM is returned.
 */
JCErr lk_push(struct LkList *list, void *value);

/**
 * @brief Appends the specified element to the end of this linked-list.
 * @param list Pointer to linked-list.
 * @param value  the element to add.
 * @return If the value is added to linked-list JCERR-success is returned.
 * @warning In case of out of memory JCERR_ENOMEM is returned.
 */
JCErr lk_push_last(struct LkList *list, void *value);

/**
 * @brief Obtains iterator for linked-list.
 * @param list Pointer to linked-list.
 * @return LkIterator object.
 */
struct LkIterator lk_get_iterator(struct LkList *list);

/**
 * @brief Dismiss linked-list and releases all resources.
 * @param list Pointer to linked-list.
 * @param freemem Release memory?
 */
void lk_cleanup(struct LkList *list, bool freemem);

/**
 * @brief Removes all of the elements from this linked-list.
 * @param list Pointer to linked-list.
 */
void lk_clear(struct LkList *list);

/**
 * @brief Initialize a new linked-list.
 * @param list Pointer to linked-list.
 * @param equals_to Pointer to the function called for compare two objects.
 * @param free Pointer to the function called to free memory.
 */
void lk_init(struct LkList *list, void(*free)(void *obj));

/**
 * @brief Returns an iterator over the elements in this linked list.
 * @param iter Pointer to list iterator.
 * @return Returns the next element in the linkedlist if present, otherwise NULL is returned.
 */
void *lk_iterate(struct LkIterator *iter);

/**
 * @brief Removes(free(value)) the last element returned by this iterator.
 * @param iter Pointer to linked-list iterator.
 */
void lk_iter_remove(struct LkIterator *iter);

/**
 * @brief Retrieves, but does not remove, the first element of this linked-list.
 * @param list Pointer to linked-list.
 * @return the first element of this linked-list, or null if this list is empty.
 */
void *lk_peek(struct LkList *list);

/**
 * @brief Retrieves, but does not remove, the last element of this linked-list.
 * @param list Pointer to linked-list.
 * @return the last element of this linked-list, or null if this list is empty.
 */
void *lk_peek_last(struct LkList *list);

/**
 * @brief Removes and returns the first element of this linked-list.
 * @param list Pointer to linked-list.
 * @return the element at the front of this linked-list, or null if this list is empty.
 */
void *lk_pop(struct LkList *list);

/**
 * @brief Removes and returns the last element of this linked-list.
 * @param list Pointer to linked-list.
 * @return the element at the end of this linked-list, or null if this list is empty.
 */
void *lk_pop_last(struct LkList *list);

/**
 * @brief Remove the element at the specified position in this linked-list.
 * @param list Pointer to linked-list.
 * @param value The value to be removed from this linked-list.
 * @return pointer to value if this list contains element at the indicated position, NULL otherwise.
 */
void *lk_remove_at_index(struct LkList *list, jcsize index);

/**
 * @brief Remove an element in this linked-list.
 * @param list Pointer to linkedlist.
 * @param value The value to be removed from this linked-list.
 * @param equals_to Pointer to comparison function.
 * @return pointer to value if this list contains the specified element, NULL otherwise.
 */
void *lk_remove_object(struct LkList *list, void *value, bool(*equals_to)(void *obj1, void *obj2));

/**
 * @brief Reset iterator.
 * @param iter Pointer to list iterator.
 */
void lk_reset_iterator(struct LkIterator *iter);

static void __lk_rmnode(struct LkList *list, struct LkNode *ptr);

#endif
