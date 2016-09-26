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

#define STATIC_STACK_INITIALIZER        {STATIC_LKLIST_INITIALIZER}
#define STATIC_STACK_INITIALIZER1(free) {STATIC_LKLIST_INITIALIZER1(free)}

/**
 * @brief Obtains number of elements in this stack.
 * @param sk Pointer to stack.
 * @return The number of elements in this stack.
 */
#define SK_COUNT(sk)    sk->stack.count

/**
 * @brief Returns true if this stack contains no elements.
 * @param sk Pointer to stack.
 * @return true if this stack contains no elements.
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
 * @brief Inserts the specified element into the stack.
 * @param sk Pointer to stack.
 * @param value The element to add.
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
 * @brief Removes all of the elements from this stack.
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
 * @brief Looks at the object at the top of this stack without removing it from the stack.
 * @param sk Pointer to stack.
 * @return The object at the top of this stack or NULL if the stack is empty.
 */
void *sk_peek(struct Stack *sk);

/**
 * @brief Removes the object at the top of this stack and returns that object as the value of this function.
 * @param sk Pointer to stack.
 * @return The object at the top of this stack or NULL if the stack is empty.
 */
void *sk_pop(struct Stack *sk);

#endif
