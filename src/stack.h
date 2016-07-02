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

#ifndef JCOLLECTIONS_STACK_H
#define JCOLLECTIONS_STACK_H

#include "jcdatatype.h"
#include "lklist.h"

#define SK_COUNT(sk)    sk->stack.count
#define SK_ISEMPTY(sk)  (sk->stack.count==0)

struct Stack {
    struct LkList stack;
};

JCErr sk_push(struct Stack *sk, void *value);

void sk_cleanup(struct Stack *sk, bool freemem);

void sk_clear(struct Stack *sk);

void sk_init(struct Stack *sk, void(*free)(void *obj));

void *sk_peek(struct Stack *sk);

void *sk_pop(struct Stack *sk);

#endif
