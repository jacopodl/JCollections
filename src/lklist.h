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

#ifndef JCOLLECTIONS_LkList_H
#define JCOLLECTIONS_LkList_H

#include <stdbool.h>
#include "JCdatatype.h"

#define LK_COUNT(LkList)    LkList->count
#define LK_ISEMPTY(LkList)  (LkList->count==0)

struct LkNode {
    void *value;
    struct LkNode *next;
    struct LkNode *prev;
};

struct LkList {
    struct LkNode *list;
    struct LkNode *tail;
    unsigned long count;

    bool(*equals_to)(void *obj1, void *obj2);

    void(*free)(void *obj);
};

bool lk_contains(struct LkList *list, void *value);

bool lk_remove_at_index(struct LkList *list, unsigned long index);

bool lk_remove_object(struct LkList *list, void *value);

JCErr lk_push(struct LkList *list, void *value);

JCErr lk_push_last(struct LkList *list, void *value);

void lk_cleanup(struct LkList *list, bool freemem);

void lk_clear(struct LkList *list);

void lk_init(struct LkList *list, bool(*equals_to)(void *obj1, void *obj2), void(*free)(void *obj));

void *lk_peek(struct LkList *list);

void *lk_peek_last(struct LkList *list);

void *lk_pop(struct LkList *list);

void *lk_pop_last(struct LkList *list);

void lk_remove(struct LkList *list);

void lk_remove_last(struct LkList *list);

static void lk_rmnode(struct LkList *list, struct LkNode *ptr);

#endif
