/*
 * stack, part of JCollections.
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
 * @file stack.h
 * @brief Provides functions for manage the stack.
 */

#ifndef JCOLLECTIONS_STACK_H
#define JCOLLECTIONS_STACK_H

#include "jcdatatype.h"
#include "lklist.h"

/**
 * @brief Obtains number of elements in the stack.
 * @return Obtains number of elements in the stack.
 */
#define SK_COUNT(sk)    sk->stack.count

/**
 * @brief Check whether the stack is empty.
 * @return true if the stack is empty, otherwise returns false.
 */
#define SK_ISEMPTY(sk)  (sk->stack.count==0)

/**
 * @brief This structure represent the stack.
 *
 * It can be used in this way:
 * @code
 * char *str;
 * struct Stack stack;
 * sk_init(&stack, free);
 * sk_push(&stack, value);
 * str = (char *)sk_pop(&stack);
 * sk_cleanup(&stack,false);
 * @endcode
 */
struct Stack {
    struct LkList stack;
};

/**
 * @brief Inserts an element into the stack.
 * @param sk Pointer to stack.
 * @param value The value to be inserted into the stack.
 * @return If the item was inserted JCERR_SUCCESS is returned.
 * @warning In case of out of memory JCERR_ENOMEM is returned.
 */
JCErr sk_push(struct Stack *sk, void *value);

/**
 * @brief Dismiss stack and releases all resources.
 * @param sk Pointer to stack.
 * @param freemem Release memory?
 */
void sk_cleanup(struct Stack *sk, bool freemem);

/**
 * @brief Remove all elements from the stack.
 * @param sk Pointer to stack.
 */
void sk_clear(struct Stack *sk);

/**
 * @brief Initialize a new stack.
 * @param sk Pointer to stack.
 * @param free Pointer to the function called to free memory.
 */
void sk_init(struct Stack *sk, void(*free)(void *obj));

/**
 * @brief Gets an item without removing it from the stack.
 * @param sk Pointer to stack.
 */
void *sk_peek(struct Stack *sk);

/**
 * @brief Gets an item from the stack.
 * @param sk Pointer to stack.
 */
void *sk_pop(struct Stack *sk);

#endif
