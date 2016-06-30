//
// Created by jdl on 27/06/16.
//

#ifndef JCOLLECTIONS_HASHTABLE_H
#define JCOLLECTIONS_HASHTABLE_H

#include <stdbool.h>

#define HT_COUNT(ht)    ht->items
#define HT_SIZE(ht)     ht->size
#define HT_ISEMPTY(ht)  (ht->items==0)

#define HT_DEFLOADF 0.75

#define __HT_INTERNAL_CLEARMODE_CLEAR     0x00
#define __HT_INTERNAL_CLEARMODE_RESET     0x01
#define __HT_INTERNAL_CLEARMODE_DESTROY   0x02

typedef unsigned int htsize;

typedef enum {
    HTOP_SUCCESS,
    HTOP_NULLVAL,
    HTOP_ENOMEM,
    HTOP_KEYEXIST
} htop;

struct HashNode {
    void *value;
    void *key;
    struct HashNode *next;
};

struct HTable {
    struct HashNode **htable;
    htsize size;
    htsize bsize;
    htsize items;
    unsigned int rhcount;
    float loadFactor;

    htsize (*hash)(void *key);

    bool (*equals_to)(void *key1, void *key2);

    void (*free)(void *key, void *value);
};

bool ht_clear(struct HTable *htable, bool size_reset);

bool ht_contains(struct HTable *htable, void *key);

bool ht_init(struct HTable *htable, htsize size, float loadFactor, htsize (*hash)(void *key),
             bool (*equals_to)(void *key1, void *key2), void (*free)(void *key, void *value));

bool ht_remove(struct HTable *htable, void *key);

static bool __ht_clear_table(struct HTable *htable, int mode);

static struct HashNode *__ht_search_node(struct HTable *htable, void *key);

htop ht_put(struct HTable *htable, void *key, void *value);

htop ht_set(struct HTable *htable, void *key, void *value);

static htop __ht_insert(struct HTable *htable, void *key, void *value, bool override);

static htop __ht_rehash(struct HTable *htable);

void ht_cleanup(struct HTable *htable, bool freemem);

void *ht_get(struct HTable *htable, void *key);

#endif
