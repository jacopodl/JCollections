//
// Created by jdl on 29/06/16.
//

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "JCdatatype.h"
#include "utils.h"

bool eq4int(void *int1, void *int2) {
    return *((int *) int1) == *((int *) int2);
}

bool eq4str(void *str1, void *str2) {
    return strcmp((char *) str1, (char *) str2) == 0;
}

// djb2 by Daniel J. Bernstein
jcsize hash4str(void *str) {
    unsigned char *s = (unsigned char *) str;
    unsigned long hash = 5381;
    int c;

    while ((c = *s++)!=0)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (jcsize)hash;
}

void ht_gfree(void *obj1, void *obj2) {
    free(obj1);
    free(obj2);
}
