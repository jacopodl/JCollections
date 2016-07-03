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

/**
 * @file hashset.h
 * @brief Provides functions for manage the hashset.
 */

#ifndef JCOLLECTIONS_HASHSET_H
#define JCOLLECTIONS_HASHSET_H

#include <stdbool.h>

#include "jcdatatype.h"
#include "hashtable.h"

/**
 * @brief Obtains number of elements in the hashset.
 * @return Obtains number of elements in the hashset.
 */
#define HSET_COUNT(hset)    hset->table.items

/**
 * @brief Check whether the hashset is empty.
 * @return true if the hashset is empty, otherwise returns false.
 */
#define HSET_ISEMPTY(hset)  (hset->table.items==0)

/**
 * @brief This structure represent the hashset.
 *
 * It can be used in this way:
 * @code
 * struct HSet hset;
 * hset_init(&hset, 5, hash, compare_to, free);
 * hset_add(&hset, value);
 * hset_add(&hset, value2);
 * hset_contains(&hset, value);
 * hset_cleanup(&hset,false);
 * @endcode
 */
struct HSet {
    struct HTable table;
};

/**
 * @brief Check if the value is contained in the hashset.
 * @param hset Pointer to hashset.
 * @param value The value to be removed from hashset.
 * @return If the value is contained in the hashset returns true, otherwise returns false.
 */
bool hset_contains(struct HSet *hset, void *obj);

/**
 * @brief Returns an iterator over the elements in this set.
 * @param hset Pointer to hashset.
 * @return Returns the next element in the hashset if present, otherwise NULL is returned.
 * @warning The following operations resets the iterator: add, remove, clear.
 */
bool hset_iterator(struct HSet *hset, void **obj);

/**
 * @brief Remove an element from hashset.
 * @param hset Pointer to hashset.
 * @param value The value to be removed from hashset.
 * @return If the value does not exist false is returned, otherwise true is returned.
 */
bool hset_remove(struct HSet *hset, void *obj);

/**
 * @brief Inserts an element into hashset.
 * @param hset Pointer to hashset.
 * @param value The value to be inserted into hashset.
 * @return If the value does not exist is inserted and JCERR_SUCCESS is returned, otherwise JCERR_KEYEXIST is returned.
 * @warning In case of out of memory JCERR_ENOMEM is returned.
 */
JCErr hset_add(struct HSet *hset, void *obj);

/**
 * @brief Dismiss hashset and releases all resources.
 * @param hset Pointer to hashset.
 * @param freemem Release memory?
 */
void hset_cleanup(struct HSet *hset, bool freemem);

/**
 * @brief Remove all elements from the hashset.
 * @param hset Pointer to hashset.
 */
void hset_clear(struct HSet *hset);

/**
 * @brief Initialize a new hashset.
 * @param hset Pointer to hashset.
 * @param size Starting size.
 * @param hash Pointer to the function called to hash an object.
 * @param compare_to Pointer to the function called for compare two objects.
 * @param free Pointer to the function called to free memory.
 */
void hset_init(struct HSet *hset, jcsize size, jcsize (*hash)(void *obj), int (*compare_to)(void *obj1, void *obj2),
               void (*free)(void *obj));

#endif
