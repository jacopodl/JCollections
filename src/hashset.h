/*
* hashset, part of JCollections.
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

#ifndef JCOLLECTIONS_HASHSET_H
#define JCOLLECTIONS_HASHSET_H

#include <stdbool.h>

#include "hashtable.h"
#include "jcdatatype.h"

#define HSET_COUNT(hset)    hset->table.items
#define HSET_ISEMPTY(hset)  (hset->table.items==0)

struct HSet {
    struct HTable table;
};

bool hset_contains(struct HSet *hset, void *obj);

bool hset_iterator(struct HSet *hset, void **obj);

bool hset_remove(struct HSet *hset, void *obj);

JCErr hset_add(struct HSet *hset, void *obj);

void hset_cleanup(struct HSet *hset, bool freemem);

void hset_clear(struct HSet *hset);

void hset_init(struct HSet *hset, jcsize size, jcsize (*hash)(void *obj), bool (*equals_to)(void *obj1, void *obj2),
               void (*free)(void *obj));

#endif
