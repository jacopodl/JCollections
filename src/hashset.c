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

#include <stdbool.h>
#include <stdlib.h>

#include "jcdatatype.h"
#include "hashset.h"

inline bool hset_contains(struct HSet *hset, void *obj) {
    return ht_contains(&hset->table, obj);
}

inline bool hset_iterator(struct HSet *hset, void **obj) {
    return ht_iterator(&hset->table, obj, NULL);
}

inline bool hset_remove(struct HSet *hset, void *obj) {
    return ht_remove(&hset->table, obj);
}

inline JCErr hset_add(struct HSet *hset, void *obj) {
    return ht_put(&hset->table, obj, obj);
}

void hset_cleanup(struct HSet *hset, bool freemem) {
    ht_cleanup(&hset->table, false);
    if (freemem)
        free(hset);
}

inline void hset_clear(struct HSet *hset) {
    ht_clear(&hset->table, true);
}

inline void hset_init(struct HSet *hset, jcsize size, jcsize (*hash)(void *obj),
                      bool (*equals_to)(void *obj1, void *obj2), void (*free)(void *obj)) {
    ht_init(&hset->table, size, HT_DEFLOADF, hash, equals_to, (void (*)(void *, void *)) free);
}