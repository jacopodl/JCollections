/*
* utils, part of JCollections.
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
#include <stdbool.h>
#include <string.h>

#include "jcdatatype.h"
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
