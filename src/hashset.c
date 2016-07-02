//
// Created by jdl on 01/07/16.
//

#include <stdbool.h>
#include <stdlib.h>

#include "JCdatatype.h"
#include "hashset.h"

bool hset_contains(struct HSet *hset, void *obj) {
    if (obj == NULL)
        return hset->containsNULL;
    return ht_contains(&hset->table, obj);
}

bool hset_remove(struct HSet *hset, void *obj) {
    if (obj == NULL) {
        hset->containsNULL = false;
        hset->items--;
        return true;
    }
    if (ht_remove(&hset->table, obj)) {
        hset->items--;
        return true;
    }
    else
        return false;
}

JCErr hset_add(struct HSet *hset, void *obj) {
    JCErr err;
    if (obj == NULL) {
        if (hset->containsNULL)
            return JCERR_KEYEXIST;
        else {
            hset->containsNULL = true;
            hset->items++;
            return JCERR_SUCCESS;
        }
    }
    if ((err = ht_put(&hset->table, obj, obj)) == JCERR_SUCCESS)
        hset->items++;
    return err;
}

void hset_cleanup(struct HSet *hset, bool freemem) {
    hset->items = 0;
    hset->containsNULL = false;
    ht_cleanup(&hset->table, false);
    if (freemem)
        free(hset);
}

void hset_clear(struct HSet *hset) {
    hset->items = 0;
    hset->containsNULL = false;
    ht_clear(&hset->table, true);
}

void hset_init(struct HSet *hset, jcsize size, jcsize (*hash)(void *obj), bool (*equals_to)(void *obj1, void *obj2),
               void (*free)(void *obj)) {
    hset->items = 0;
    hset->containsNULL = false;
    ht_init(&hset->table, size, HT_DEFLOADF, hash, equals_to, (void (*)(void *, void *)) free);
}