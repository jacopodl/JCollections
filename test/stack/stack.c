//
// Created by jdl on 27/06/16.
//

#include <stdlib.h>
#include <stdio.h>

#include <stack.h>
#include <assert.h>

int main(int argc, char **argv)
{
    struct Stack sk;
    int *nums = NULL;
    printf("sk_init\t[OK]\n");
    sk_init(&sk,free);
    nums = (int *)malloc(sizeof(int));
    *nums=3;
    assert(SK_ISEMPTY((&sk))==true);
    sk_push(&sk,nums);
    assert(SK_ISEMPTY((&sk))==false);
    nums = (int *)malloc(sizeof(int));
    *nums=2;
    sk_push(&sk,nums);
    nums = (int *)malloc(sizeof(int));
    *nums=1;
    sk_push(&sk,nums);
    assert(SK_COUNT((&sk))==3);
    assert(*((int *)sk_peek(&sk))==1);
    assert(SK_COUNT((&sk))==3);
    nums = (int *)sk_pop(&sk);
    assert(*nums==1);
    free(nums);
    nums = (int *)sk_pop(&sk);
    assert(*nums==2);
    free(nums);
    assert(SK_COUNT((&sk))==1);
    sk_clear(&sk);
    assert(SK_ISEMPTY((&sk))==true);
    sk_cleanup(&sk,false);
    printf("sk_cleanup\t[OK]\n");
}