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
 * lk_init(&lkl, compare_to, free);
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

    int(*compare_to)(void *obj1, void *obj2);

    void(*free)(void *obj);
};

/**
 * @brief Returns true if this linked-list contains the specified element.
 * @param list Pointer to linked-list.
 * @param value Element whose presence in this linked-list is to be tested.
 * @return true if this list contains the specified element, false otherwise.
 */
bool lk_contains(struct LkList *list, void *value);

/**
 * @brief Removes the element at the specified position in this linked-list.
 * @param list Pointer to linked-list.
 * @param value The value to be removed from this linked-list.
 * @return true if this list contains the specified element, false otherwise.
 */
bool lk_remove_at_index(struct LkList *list, jcsize index);

/**
 * @brief Remove an element in this linked-list.
 * @param list Pointer to linkedlist.
 * @param value The value to be removed from this linked-list.
 * @return true if this list contains the specified element, false otherwise.
 */
bool lk_remove_object(struct LkList *list, void *value);

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
 * @param compare_to Pointer to the function called for compare two objects.
 * @param free Pointer to the function called to free memory.
 */
void lk_init(struct LkList *list, int(*compare_to)(void *obj1, void *obj2), void(*free)(void *obj));

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
 * @brief Removes the first element of this linked-list.
 * @param list Pointer to linked-list.
 */
void lk_remove(struct LkList *list);

/**
 * @brief Removes the last element of this linked-list.
 * @param list Pointer to linked-list.
 */
void lk_remove_last(struct LkList *list);

static void lk_rmnode(struct LkList *list, struct LkNode *ptr);

#endif
