//
// Created by jdl on 27/06/16.
//

#ifndef JCOLLECTIONS_STACK_H
#define JCOLLECTIONS_STACK_H

#include "JCdatatype.h"
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
