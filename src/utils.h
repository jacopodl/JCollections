//
// Created by jdl on 29/06/16.
//

#ifndef JCOLLECTIONS_UTILS_H
#define JCOLLECTIONS_UTILS_H

#include <stdbool.h>

bool eq4int(void *int1, void *int2);

bool eq4str(void *str1, void *str2);

jcsize hash4str(void *str);

void ht_gfree(void *obj1, void *obj2);

#endif
