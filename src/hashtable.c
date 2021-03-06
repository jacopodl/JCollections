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

#include <stdlib.h>
#include <string.h>

#include "jcdatatype.h"
#include "hashtable.h"

bool ht_contains(struct HTable *htable, void *key) {
    return __ht_search_node(htable, key) != NULL;
}

bool ht_iterate(struct HTIterator *iter, void **key, void **value) {
    for (; iter->iter_idx < iter->htable->size && iter->htable->htable != NULL; iter->iter_idx++) {
        if (iter->cursor == NULL)
            iter->cursor = iter->htable->htable[iter->iter_idx];
        if (iter->cursor != NULL) {
            if (key != NULL)
                (*key) = iter->cursor->key;
            if (value != NULL)
                (*value) = iter->cursor->value;
            iter->cursor = iter->cursor->next;
            if (iter->cursor == NULL)
                iter->iter_idx++;
            return true;
        }
    }
    return false;
}

static struct HashNode *__ht_search_node(struct HTable *htable, void *key) {
    struct HashNode *cursor;
    jcsize index;
    if (key != NULL && htable->htable != NULL) {
        index = htable->hash(key) % htable->size;
        for (cursor = htable->htable[index]; cursor != NULL; cursor = cursor->next)
            if (htable->equals_to(cursor->key, key))
                return cursor;
    }
    return NULL;
}

struct HTIterator ht_get_iterator(struct HTable *htable) {
    struct HTIterator iter;
    iter.htable = htable;
    iter.cursor = NULL;
    iter.iter_idx = 0;
    return iter;
}

JCErr ht_put(struct HTable *htable, void *key, void *value) {
    return __ht_insert(htable, key, value, false);
}

JCErr ht_set(struct HTable *htable, void *key, void *value) {
    return __ht_insert(htable, key, value, true);
}

JCErr __ht_insert(struct HTable *htable, void *key, void *value, bool override) {
    struct HashNode *cursor;

    if (value == NULL || key == NULL)
        return JCERR_NULLVAL;

    if (htable->htable == NULL) {
        if ((htable->htable = (struct HashNode **) calloc(htable->size, sizeof(struct HashNode *))) == NULL)
            return JCERR_ENOMEM;
    }

    if (((float) htable->items + 1) / htable->size > htable->loadFactor) {
        JCErr err;
        if ((err = __ht_rehash(htable)) != JCERR_SUCCESS)
            return err;
    }

    jcsize index = htable->hash(key) % htable->size;
    if ((cursor = __ht_search_node(htable, key)) != NULL) {
        if (override) {
            if (htable->free != NULL)
                htable->free(cursor->key, cursor->value);
            cursor->key = key;
            cursor->value = value;
            return JCERR_SUCCESS;
        } else
            return JCERR_KEYEXIST;
    }

    if ((cursor = (struct HashNode *) malloc(sizeof(struct HashNode))) == NULL)
        return JCERR_ENOMEM;
    cursor->value = value;
    cursor->key = key;
    cursor->next = htable->htable[index];
    htable->htable[index] = cursor;
    htable->items++;
    return JCERR_SUCCESS;
}

static JCErr __ht_rehash(struct HTable *htable) {
    struct HashNode **newtable;
    struct HashNode *prev;
    struct HashNode *cursor;
    struct HashNode *next;
    jcsize newsize;
    jcsize oldsize;
    jcsize newhash;

    newsize = htable->size + (htable->bsize * htable->rhcount++);
    oldsize = htable->size;

    if ((newtable = (struct HashNode **) realloc(htable->htable, newsize * sizeof(struct HashNode *))) == NULL)
        return JCERR_ENOMEM;
    for (jcsize i = oldsize; i < newsize; i++)
        newtable[i] = NULL;
    for (jcsize i = 0; i < oldsize; i++) {
        for (prev = NULL, cursor = newtable[i]; cursor != NULL; cursor = next) {
            newhash = htable->hash(cursor->key) % newsize;
            next = cursor->next;
            if (newhash == i) {
                prev = cursor;
                continue;
            }
            cursor->next = newtable[newhash];
            newtable[newhash] = cursor;
            if (prev != NULL)
                prev->next = next;
            else
                newtable[i] = next;
        }
    }
    htable->htable = newtable;
    htable->size = newsize;
    return JCERR_SUCCESS;
}

void ht_cleanup(struct HTable *htable, bool freemem) {
    __ht_clear_table(htable, __HT_INTERNAL_CLEARMODE_DESTROY);
    if (freemem)
        free(htable);
}

void ht_clear(struct HTable *htable, bool size_reset) {
    __ht_clear_table(htable, !size_reset ? __HT_INTERNAL_CLEARMODE_CLEAR : __HT_INTERNAL_CLEARMODE_RESET);
}

void *ht_get(struct HTable *htable, void *key) {
    struct HashNode *node;
    if ((node = __ht_search_node(htable, key)) != NULL)
        return node->value;
    return NULL;
}

void ht_init(struct HTable *htable, jcsize size, float loadFactor, jcsize (*hash)(void *key),
             bool (*equals_to)(void *key1, void *key2), void (*free)(void *key, void *value)) {
    htable->htable = NULL;
    htable->size = size;
    htable->bsize = size;
    htable->items = 0;
    htable->rhcount = 1;
    htable->loadFactor = loadFactor;
    htable->hash = hash;
    htable->equals_to = equals_to;
    htable->free = free;
}

void *ht_remove(struct HTable *htable, void *key) {
    struct HashNode *cursor;
    struct HashNode *prev;
    void *value = NULL;
    jcsize index;

    if (htable->htable != NULL) {
        index = htable->hash(key) % htable->size;
        for (prev = NULL, cursor = htable->htable[index]; cursor != NULL; prev = cursor, cursor = prev->next) {
            if (htable->equals_to(cursor->key, key)) {
                value = cursor->value;
                if (htable->free != NULL)
                    htable->free(cursor->key, NULL);
                if (prev == NULL)
                    htable->htable[index] = cursor->next;
                else
                    prev->next = cursor->next;
                free(cursor);
                htable->items--;
                break;
            }
        }
    }
    return value;
}

void ht_reset_iterator(struct HTIterator *iter) {
    iter->cursor = NULL;
    iter->iter_idx = 0;
}

static void __ht_clear_table(struct HTable *htable, int mode) {
    struct HashNode *cursor;
    struct HashNode *tmp;

    if (htable->htable == NULL)
        return;

    for (jcsize i = 0; i < htable->size; i++) {
        for (cursor = htable->htable[i]; cursor != NULL; cursor = tmp) {
            tmp = cursor->next;
            if (htable->free != NULL)
                htable->free(cursor->key, cursor->value);
            free(cursor);
        }
        htable->htable[i] = NULL;
    }
    htable->items = 0;
    switch (mode) {
        case __HT_INTERNAL_CLEARMODE_RESET:
            htable->size = htable->bsize;
            htable->rhcount = 1;
            free(htable->htable);
            htable->htable = NULL;
            break;
        case __HT_INTERNAL_CLEARMODE_DESTROY:
            free(htable->htable);
            memset(htable, 0x00, sizeof(struct HTable));
            htable->htable = NULL;
            break;
        default:    // __HT_INTERNAL_CLEARMODE_CLEAR
            break;
    }
}

