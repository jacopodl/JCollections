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

#ifndef JCOLLECTIONS_UTILS_H
#define JCOLLECTIONS_UTILS_H

#include <stdbool.h>

bool eq4int(void *int1, void *int2);

bool eq4str(void *str1, void *str2);

jcsize hash4str(void *str);

void ht_gfree(void *obj1, void *obj2);

#endif
