//
// Created by jdl on 27/06/16.
//

#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

bool ht_clear(struct HTable *htable, bool size_reset) {
    return __ht_clear_table(htable, !size_reset ? __HT_INTERNAL_CLEARMODE_CLEAR : __HT_INTERNAL_CLEARMODE_RESET);
}

bool ht_contains(struct HTable *htable, void *key) {
    return __ht_search_node(htable, key) != NULL;
}

bool ht_init(struct HTable *htable, htsize size, float loadFactor, htsize (*hash)(void *key),
             bool (*equals_to)(void *key1, void *key2), void (*free)(void *key, void *value)) {
    htable->size = size;
    htable->bsize = size;
    htable->items = 0;
    htable->rhcount = 1;
    htable->loadFactor = loadFactor;
    htable->hash = hash;
    htable->equals_to = equals_to;
    htable->free = free;
    return (htable->htable = (struct HashNode **) calloc(htable->size, sizeof(struct HashNode *))) != NULL;
}

bool ht_remove(struct HTable *htable, void *key) {
    struct HashNode *cursor;
    struct HashNode *prev;
    htsize index;

    index = htable->hash(key) % htable->size;
    for (prev = NULL, cursor = htable->htable[index]; cursor != NULL; prev = cursor, cursor = prev->next) {
        if (htable->equals_to(cursor->key, key)) {
            if (prev == NULL)
                htable->htable[index] = cursor->next;
            else
                prev->next = cursor->next;
            htable->free(cursor->key, cursor->value);
            free(cursor);
            htable->items--;
            return true;
        }
    }
    return false;
}

static bool __ht_clear_table(struct HTable *htable, int mode) {
    struct HashNode *cursor;
    struct HashNode *tmp;

    for (htsize i = 0; i < htable->size; i++) {
        for (cursor = htable->htable[i]; cursor != NULL; cursor = tmp) {
            tmp = cursor->next;
            htable->free(cursor->key, cursor->value);
            free(cursor);
        }
        htable->htable[i] = NULL;
    }
    htable->items = 0;
    switch (mode) {
        case __HT_INTERNAL_CLEARMODE_CLEAR:
            break;
        case __HT_INTERNAL_CLEARMODE_RESET:
            htable->size = htable->bsize;
            htable->rhcount = 1;
            free(htable->htable);
            htable->htable;
            if ((htable->htable = (struct HashNode **) calloc(htable->size, sizeof(struct HashNode *))) == NULL)
                return false;
            break;
        case __HT_INTERNAL_CLEARMODE_DESTROY:
            free(htable->htable);
            memset(htable, 0x00, sizeof(struct HTable));
            break;
        default:
            break;
    }
    return true;
}

static struct HashNode *__ht_search_node(struct HTable *htable, void *key) {
    struct HashNode *cursor;
    htsize index;
    if (key != NULL) {
        index = htable->hash(key) % htable->size;
        for (cursor = htable->htable[index]; cursor != NULL; cursor = cursor->next)
            if (htable->equals_to(cursor->key, key))
                return cursor;
    }
    return NULL;
}

htop ht_put(struct HTable *htable, void *key, void *value) {
    return __ht_insert(htable, key, value, false);
}

htop ht_set(struct HTable *htable, void *key, void *value) {
    return __ht_insert(htable, key, value, true);
}

htop __ht_insert(struct HTable *htable, void *key, void *value, bool override) {
    if (value == NULL || key == NULL)
        return HTOP_NULLVAL;
    if (((float) htable->items + 1) / htable->size > htable->loadFactor) {
        htop err;
        if ((err = __ht_rehash(htable)) != HTOP_SUCCESS)
            return err;
    }
    htsize index = htable->hash(key) % htable->size;
    struct HashNode *cursor;
    for (cursor = htable->htable[index]; cursor != NULL; cursor = cursor->next) {
        if (htable->equals_to(cursor->key, key)) {
            if (override) {
                htable->free(cursor->key, cursor->value);
                cursor->key = key;
                cursor->value = value;
                return HTOP_SUCCESS;
            }
            else
                return HTOP_KEYEXIST;
        }
    }
    if ((cursor = (struct HashNode *) malloc(sizeof(struct HashNode))) == NULL)
        return HTOP_ENOMEM;
    cursor->value = value;
    cursor->key = key;
    cursor->next = htable->htable[index];
    htable->htable[index] = cursor;
    htable->items++;
    return HTOP_SUCCESS;
}

static htop __ht_rehash(struct HTable *htable) {
    struct HashNode **newtable;
    struct HashNode *prev;
    struct HashNode *cursor;
    struct HashNode *next;
    htsize newsize;
    htsize oldsize;
    htsize newhash;

    newsize = htable->size + (htable->bsize * htable->rhcount++);
    oldsize = htable->size;

    if ((newtable = (struct HashNode **) realloc(htable->htable, newsize * sizeof(struct HashNode *))) == NULL)
        return HTOP_ENOMEM;
    for (htsize i = oldsize; i < newsize; i++)
        newtable[i] = NULL;
    for (htsize i = 0; i < oldsize; i++) {
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
    return HTOP_SUCCESS;
}

void ht_cleanup(struct HTable *htable, bool freemem) {
    __ht_clear_table(htable, __HT_INTERNAL_CLEARMODE_DESTROY);
    if (freemem)
        free(htable);
}

void *ht_get(struct HTable *htable, void *key) {
    struct HashNode *node;
    if ((node = __ht_search_node(htable, key)) != NULL)
        return node->value;
    return NULL;
}


