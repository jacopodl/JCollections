//
// Created by jdl on 27/06/16.
//

#include <stdlib.h>

#include "stack.h"

inline bool sk_push(struct Stack *sk, void *value)
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