//
// Created by jdl on 01/07/16.
//

#ifndef JCOLLECTIONS_HASHSET_H
#define JCOLLECTIONS_HASHSET_H

#include <stdbool.h>

#include "hashtable.h"
#include "JCdatatype.h"

#define HSET_COUNT(hset)    hset->items
#define HSET_ISEMPTY(hset)  (hset->items==0)

struct HSet
{
    struct HTable table;
    unsigned long items;
    bool containsNULL;
};

bool hset_contains(struct HSet *hset, void *obj);

bool hset_remove(struct HSet *hset, void *obj);

JCErr hset_add(struct HSet *hset, void *obj);

void hset_cleanup(struct HSet *hset, bool freemem);

void hset_clear(struct HSet *hset);

void hset_init(struct HSet *hset, unsigned long size, unsigned long (*hash)(void *obj),
               bool (*equals_to)(void *obj1, void *obj2), void (*free)(void *obj));

#endif
