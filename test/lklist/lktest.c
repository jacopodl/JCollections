#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <lklist.h>
#include <utils.h>
#include <assert.h>

void printer(struct LkList *list)
{
    void *num;
    while((num=lk_pop(list))!=NULL)
        printf("Num: %d\n",(*(int *)num));
}

void insertTest(struct LkList *list)
{
    int num[] = {23,24,25,26,27,28};
    lk_push(list,num);
    lk_push(list,num+1);
    lk_push(list,num+3);
    assert(*((int *)lk_peek(list))==num[3]);
    assert(*((int *)lk_peek_last(list))==num[0]);
    lk_pop(list);
    lk_pop(list);
    lk_pop(list);
    lk_push_last(list,num+2);
    lk_push_last(list,num+4);
    assert(*((int *)lk_pop(list))==num[2]);
    assert(*((int *)lk_pop(list))==num[4]);
    lk_push_last(list,num+2);
    lk_push_last(list,num+4);
    assert(*((int *)lk_pop_last(list))==num[4]);
    assert(*((int *)lk_pop_last(list))==num[2]);
    printer(list);
}

void containsTest(struct LkList *list)
{
    int num[] = {23,24,25,26,27,28};
    lk_push(list,num+4);
    lk_push_last(list,num+2);
    lk_push(list,num+1);
    assert(lk_contains(list,num+2));
    printer(list);
}

void removeTest(struct LkList *list)
{
    int snum=0;
    int *num = (int *)malloc(sizeof(int));
    *num=22;
    lk_push_last(list,num);
    num = (int *)malloc(sizeof(int));
    *num=23;
    lk_push_last(list,num);
    num = (int *)malloc(sizeof(int));
    *num=24;
    lk_push(list,num);
    assert(LK_COUNT(list)==3);
    lk_remove_last(list);
    assert(*((int *)lk_peek_last(list))==22);
    lk_clear(list);
    assert(LK_COUNT(list)==0);
    num = (int *)malloc(sizeof(int));
    *num=100;
    lk_push(list,num);
    num = (int *)malloc(sizeof(int));
    *num=200;
    lk_push(list,num);
    num = (int *)malloc(sizeof(int));
    *num=300;
    lk_push(list,num);
    snum=200;
    assert(lk_contains(list,&snum)==true);
    lk_remove_at_index(list,1);
    assert(lk_contains(list,&snum)==false);
    assert(LK_COUNT(list)==2);
    num = (int *)malloc(sizeof(int));
    *num=23;
    lk_push_last(list,num);
    snum=23;
    assert(lk_contains(list,&snum)==true);
    lk_remove_object(list,&snum);
    assert(lk_contains(list,&snum)==false);
    lk_peek_last(list);
    assert(LK_COUNT(list)==2);
    lk_remove(list);
    assert(LK_COUNT(list)==1);
    lk_clear(list);
    assert(LK_COUNT(list)==0);
    printer(list);
}

int main(int argc, char **argv)
{
    struct LkList list;
    lk_init(&list,eq4int,free);
    printf("lk_init\t[OK]\n");
    printf("insertTest(Static values)\n");
    insertTest(&list);
    printf("containsTest(Static values)\n");
    containsTest(&list);
    printf("removeTest(Dynamic Values)\n");
    removeTest(&list);
    assert(LK_ISEMPTY((&list))==true);
    lk_cleanup(&list,false);
    printf("lk_cleanup\t[OK]\n");
}

