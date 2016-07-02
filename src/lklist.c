/*
* LkList, part of JCollections.
* Copyright (C) 2014-2016 Jacopo De Luca
*
* This program is free library: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <errno.h>

#include "JCdatatype.h"
#include "lklist.h"

bool lk_contains(struct LkList *list, void *value) {
    struct LkNode *cursor;
    for (cursor = list->list; cursor != NULL; cursor = cursor->next)
        if (list->equals_to(value, cursor->value))
            return true;
    return false;
}

bool lk_remove_at_index(struct LkList *list, jcsize index) {
    struct LkNode *cursor;
    jcsize i = 0;
    if (index>=list->count) {
        errno = EINVAL;
        return false;
    }
    cursor = list->list;
    while (cursor != NULL) {
        if (i == index) {
            list->free(cursor->value);
            lk_rmnode(list, cursor);
            break;
        }
        cursor = cursor->next;
        i++;
    }
    return true;
}

bool lk_remove_object(struct LkList *list, void *value) {
    struct LkNode *cursor;
    for (cursor = list->list; cursor != NULL; cursor = cursor->next)
        if (list->equals_to(value, cursor->value)) {
            list->free(cursor->value);
            lk_rmnode(list, cursor);
            return true;
        }
    return false;
}

JCErr lk_push(struct LkList *list, void *value) {
    struct LkNode *node;
    if ((node = (struct LkNode *) malloc(sizeof(struct LkNode))) == NULL)
        return JCERR_ENOMEM;
    node->next = list->list;
    node->prev=NULL;
    node->value = value;
    if(node->next!=NULL)
        node->next->prev=node;
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
    if (list->tail == NULL) {
        node->next = list->list;
        node->prev = NULL;
        list->list = node;
    }
    else {
        node->next = NULL;
        node->prev = list->tail;
    }
    if(node->prev!=NULL)
        node->prev->next=node;
    list->tail = node;
    list->count++;
    return JCERR_SUCCESS;
}

void lk_cleanup(struct LkList *list, bool freemem) {
    lk_clear(list);
    if(freemem)
        free(list);
}

void lk_clear(struct LkList *list) {
    struct LkNode *cursor;
    struct LkNode *tmp;
    for (cursor = list->list; cursor != NULL; tmp = cursor->next, free(cursor), cursor = tmp)
        list->free(cursor->value);
    list->list = NULL;
    list->tail = NULL;
    list->count = 0;
}

void lk_init(struct LkList *list, bool(*equals_to)(void *obj1, void *obj2), void(*free)(void *obj)) {
    list->list = NULL;
    list->tail = NULL;
    list->count = 0;
    list->equals_to = equals_to;
    list->free = free;
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
        lk_rmnode(list, list->list);
    }
    return value;
}

void *lk_pop_last(struct LkList *list) {
    void *value = NULL;
    if (list->tail != NULL) {
        value = list->tail->value;
        lk_rmnode(list, list->tail);
    }
    return value;
}

void lk_remove(struct LkList *list) {
    if (list->list != NULL) {
        list->free(list->list->value);
        lk_rmnode(list, list->list);
    }
}

void lk_remove_last(struct LkList *list) {
    if (list->tail != NULL) {
        list->free(list->tail->value);
        lk_rmnode(list, list->tail);
    }
}

static void lk_rmnode(struct LkList *list, struct LkNode *ptr) {
    struct LkNode *prev = ptr->prev;
    struct LkNode *next = ptr->next;
    if (prev == NULL) {
        list->list = next;
        if (next != NULL)
            next->prev = NULL;
        else
            list->tail = NULL;
    }
    else {
        prev->next = next;
        if (next != NULL)
            next->prev = prev;
        else
            list->tail = prev;
    }
    free(ptr);
    list->count--;
}