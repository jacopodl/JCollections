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

#include <stdlib.h>
#include <errno.h>

#include "jcdatatype.h"
#include "lklist.h"

bool lk_contains(struct LkList *list, void *value, bool(*equals_to)(void *obj1, void *obj2)) {
    struct LkNode *cursor;
    for (cursor = list->list; cursor != NULL; cursor = cursor->next)
        if (equals_to(value, cursor->value))
            return true;
    return false;
}

JCErr lk_push(struct LkList *list, void *value) {
    struct LkNode *node;
    if ((node = (struct LkNode *) malloc(sizeof(struct LkNode))) == NULL)
        return JCERR_ENOMEM;
    node->value = value;
    node->prev = NULL;
    if ((node->next = list->list) != NULL)
        node->next->prev = node;
    if (list->tail == NULL)
        list->tail = node;
    list->list = node;
    list->count++;
    return JCERR_SUCCESS;
}

JCErr lk_push_last(struct LkList *list, void *value) {
    struct LkNode *node;
    if ((node = (struct LkNode *) malloc(sizeof(struct LkNode))) == NULL)
        return JCERR_ENOMEM;
    node->value = value;
    node->next = NULL;
    if ((node->prev = list->tail) == NULL)
        list->list = node;
    if (node->prev != NULL)
        node->prev->next = node;
    list->tail = node;
    list->count++;
    return JCERR_SUCCESS;
}

struct LkIterator lk_get_iterator(struct LkList *list) {
    struct LkIterator iter;
    iter.lklist = list;
    iter.cursor = NULL;
    iter.start = true;
    return iter;
}

void lk_cleanup(struct LkList *list, bool freemem) {
    lk_clear(list);
    if (freemem)
        free(list);
}

void lk_clear(struct LkList *list) {
    struct LkNode *cursor;
    struct LkNode *tmp;
    for (cursor = list->list; cursor != NULL; tmp = cursor->next, free(cursor), cursor = tmp)
        if (list->free != NULL)
            list->free(cursor->value);
    list->list = NULL;
    list->tail = NULL;
    list->count = 0;
}

void lk_init(struct LkList *list, void(*free)(void *obj)) {
    list->list = NULL;
    list->tail = NULL;
    list->count = 0;
    list->free = free;
}

void *lk_iterate(struct LkIterator *iter) {
    if (iter->cursor == NULL && iter->start)
        iter->cursor = iter->lklist->list;
    else
        iter->cursor = iter->cursor->next;
    if (iter->cursor != NULL)
        return iter->cursor->value;
    return NULL;
}

void lk_iter_remove(struct LkIterator *iter) {
    struct LkNode *next;
    next = iter->cursor->prev;
    if (iter->lklist->free != NULL)
        iter->lklist->free(iter->cursor->value);
    __lk_rmnode(iter->lklist, iter->cursor);
    iter->cursor = next;
}

inline void *lk_peek(struct LkList *list) {
    if (list->list != NULL)
        return list->list->value;
    return NULL;
}

inline void *lk_peek_last(struct LkList *list) {
    if (list->tail != NULL)
        return list->tail->value;
    return NULL;
}

void *lk_pop(struct LkList *list) {
    void *value = NULL;
    if (list->list != NULL) {
        value = list->list->value;
        __lk_rmnode(list, list->list);
    }
    return value;
}

void *lk_pop_last(struct LkList *list) {
    void *value = NULL;
    if (list->tail != NULL) {
        value = list->tail->value;
        __lk_rmnode(list, list->tail);
    }
    return value;
}

void *lk_remove_at_index(struct LkList *list, jcsize index) {
    struct LkNode *cursor;
    void *value = NULL;
    jcsize i = 0;

    if (index >= list->count) {
        errno = EINVAL;
        return NULL;
    }
    cursor = list->list;
    while (cursor != NULL) {
        if (i == index) {
            value = cursor->value;
            __lk_rmnode(list, cursor);
            break;
        }
        cursor = cursor->next;
        i++;
    }
    return value;
}

void *lk_remove_object(struct LkList *list, void *value, bool(*equals_to)(void *obj1, void *obj2)) {
    struct LkNode *cursor;
    void *retv = NULL;
    for (cursor = list->list; cursor != NULL; cursor = cursor->next)
        if (equals_to(value, cursor->value)) {
            retv = cursor->value;
            __lk_rmnode(list, cursor);
            break;
        }
    return retv;
}

inline void lk_reset_iterator(struct LkIterator *iter) {
    iter->cursor = NULL;
    iter->start = true;
}

static void __lk_rmnode(struct LkList *list, struct LkNode *ptr) {
    struct LkNode *prev = ptr->prev;
    struct LkNode *next = ptr->next;
    if (prev == NULL) {
        list->list = next;
        if (next != NULL)
            next->prev = NULL;
        else
            list->tail = NULL;
    } else {
        prev->next = next;
        if (next != NULL)
            next->prev = prev;
        else
            list->tail = prev;
    }
    free(ptr);
    list->count--;
}