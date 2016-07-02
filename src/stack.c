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

#include <stdlib.h>

#include "JCdatatype.h"
#include "stack.h"

inline JCErr sk_push(struct Stack *sk, void *value)
{
    return lk_push(&sk->stack, value);
}

void sk_cleanup(struct Stack *sk, bool freemem)
{
    lk_cleanup(&sk->stack,false);
    if(freemem)
        free(sk);
}

inline void sk_clear(struct Stack *sk)
{
    lk_clear(&sk->stack);
}

inline void sk_init(struct Stack *sk, void(*free)(void *obj))
{
    lk_init(&sk->stack,NULL,free);
}

inline void *sk_peek(struct Stack *sk)
{
    return lk_peek(&sk->stack);
}

inline void *sk_pop(struct Stack *sk)
{
    return lk_pop(&sk->stack);
}