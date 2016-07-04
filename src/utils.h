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

/**
 * @file utils.h
 * @brief In this file you may find useful functions such as hashing algorithms.
 */

#ifndef JCOLLECTIONS_UTILS_H
#define JCOLLECTIONS_UTILS_H

#include <stdbool.h>

/**
 * @brief Compute the hash for an arbitrary string.
 * @param str String.
 * @return The hash value.
 */
jcsize hash4str(void *str);

/**
 * @brief Compare two integer values.
 * @param int1 Integer 1.
 * @param int2 Integer 2.
 * @return The value 0 if the argument is equal; a value less than 0 if int1 is less than int2; and a value greater than 0 if int1 is greater than int2.
 */
int cmp4int(void *int1, void *int2);

/**
 * @brief Compare two strings.
 * @param str1 String 1.
 * @param str2 String 2.
 * @return See strcmp.
 */
int cmp4str(void *str1, void *str2);

/**
 * @brief Frees memory on the two generic objects, for example: char*, int*, ...
 * @param obj1 Object 1.
 * @param obj2 Object 2.
 */
void g2free(void *obj1, void *obj2);

#endif
