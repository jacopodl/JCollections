/*
 * hashtable, part of JCollections.
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
 * @file hashtable.h
 * @brief Provides functions for manage hashtable.
 */

#ifndef JCOLLECTIONS_HASHTABLE_H
#define JCOLLECTIONS_HASHTABLE_H

#include <stdbool.h>

#include "jcdatatype.h"

#define HT_DEFLOADF 0.75
#define STATIC_HASHTABLE_INITIALIZER(size, hash, equals_to, free)    {NULL,NULL,size,size,0,0,1,HT_DEFLOADF,hash,equals_to,free}

#define __HT_INTERNAL_CLEARMODE_CLEAR     0x00
#define __HT_INTERNAL_CLEARMODE_RESET     0x01
#define __HT_INTERNAL_CLEARMODE_DESTROY   0x02

/**
 * @brief Obtains number of elements in this hashtable.
 * @param ht Pointer to hashtable.
 * @return The number of elements in this hashtable.
 */
#define HT_COUNT(ht)    ht->items

/**
 * @brief Returns the real size of this hashtable.
 * @param ht Pointer to hashtable.
 * @return the real size of this hashtable.
 */
#define HT_SIZE(ht)     ht->size

/**
 * @brief Returns true if this hashtable contains no elements.
 * @param ht Pointer to hashtable.
 * @return true if this hashtable contains no elements.
 */
#define HT_ISEMPTY(ht)  (ht->items==0)

struct HashNode {
    void *value;
    void *key;
    struct HashNode *next;
};

/**
 * @brief This structure represent an hashtable.
 *
 * It can be used in this way:
 * @code
 * char *str;
 * struct HTable ht;
 * ht_init(&ht,HT_DEFLOADF,5,hash,equals_to,free);
 * ht_put(&ht,key,value);
 * str = (char *) ht_get(&ht,key);
 * ht_cleanup(&ht,false);
 * @endcode
 */
struct HTable {
    struct HashNode **htable;
    struct HashNode *iter_ptr;
    jcsize size;
    jcsize bsize;
    jcsize items;
    jcsize iter_idx;
    unsigned int rhcount;
    float loadFactor;

    jcsize (*hash)(void *key);

    bool (*equals_to)(void *key1, void *key2);

    void (*free)(void *key, void *value);
};

/**
 * @brief Returns true if this hashtable contains the specified element.
 * @param htable Pointer to hashtable.
 * @param value Element whose presence in this hashtable is to be tested.
 * @return true if this hashtable contains the specified element, false otherwise.
 */
bool ht_contains(struct HTable *htable, void *key);

/**
 * @brief Returns an iterator over the elements in this hashtable.
 * @param htable Pointer to hashtable.
 * @param __OUT__key Key Value associated to value.
 * @param __OUT__value Value associated to key.
 * @return Returns true if the iteration has more elements.
 * @warning The following operations resets the iterator: add, remove, clear.
 */
bool ht_iterator(struct HTable *htable, void **key, void **value);

/**
 * @brief Remove an element from hashtable.
 * @param htable Pointer to hashtable.
 * @param value The value to be removed from hashtable.
 * @return If the value does not exist false is returned, otherwise true is returned.
 */
bool ht_remove(struct HTable *htable, void *key);

static struct HashNode *__ht_search_node(struct HTable *htable, void *key);

/**
 * @brief Inserts an element into hashtable.
 * @param htable Pointer to hashtable.
 * @param value The value to be inserted into hashtable.
 * @return If the value does not exist is inserted and JCERR_SUCCESS is returned, otherwise JCERR_KEYEXIST is returned.
 * @warning In case of out of memory JCERR_ENOMEM is returned.
 */
JCErr ht_put(struct HTable *htable, void *key, void *value);

/**
 * @brief Change the value associated to a key.
 * @param htable Pointer to hashtable.
 * @param value The value to be inserted into hashtable.
 * @return Same as ht_put, but the value associated to a key will be overwritten if already exists.
 * @warning In case of out of memory JCERR_ENOMEM is returned.
 */
JCErr ht_set(struct HTable *htable, void *key, void *value);

static JCErr __ht_insert(struct HTable *htable, void *key, void *value, bool override);

static JCErr __ht_rehash(struct HTable *htable);

/**
 * @brief Dismiss hashtable and releases all resources.
 * @param htable Pointer to hashtable.
 * @param freemem Release memory?
 */
void ht_cleanup(struct HTable *htable, bool freemem);

/**
 * @brief Removes all of the elements from this hashtable.
 * @param htable Pointer to hashtable.
 */
void ht_clear(struct HTable *htable, bool size_reset);

static void __ht_clear_table(struct HTable *htable, int mode);

/**
 * @brief Returns the value to which the specified key is mapped.
 * @param htable Pointer to hashtable.
 * @return the value to which the specified key is mapped, or null if this map contains no mapping for the key.
 */
void *ht_get(struct HTable *htable, void *key);

/**
 * @brief Initialize a new hashtable.
 * @param htable Pointer to hashtable.
 * @param size Starting size.
 * @param loadFactor Load factor for hashtable.
 * @param hash Pointer to the function called to hash an object.
 * @param equals_to Pointer to the function called for compare two objects.
 * @param free Pointer to the function called to free memory.
 */
void ht_init(struct HTable *htable, jcsize size, float loadFactor, jcsize (*hash)(void *key),
             bool (*equals_to)(void *key1, void *key2), void (*free)(void *key, void *value));

static void __ht_reset_iterator(struct HTable *htable);

#endif
