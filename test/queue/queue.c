#include <stdlib.h>
#include <stdio.h>

#include <queue.h>
#include <assert.h>

int main(int argc, char **argv)
{
    struct Queue qu;
    int *nums = (int *)malloc(6*sizeof(int));
    nums[0]=10;
    nums[1]=12;
    nums[2]=14;
    nums[3]=24;
    nums[4]=26;
    nums[5]=18;
    printf("qu_init\t[OK]\n");
    qu_init(&qu,free);
    assert(QU_ISEMPTY((&qu))==true);
    qu_enqueue(&qu,nums+5);
    assert(QU_ISEMPTY((&qu))==false);
    qu_enqueue(&qu,nums+3);
    qu_enqueue(&qu,nums+2);
    assert(QU_COUNT((&qu))==3);
    assert(*((int *)qu_dequeue(&qu))==nums[5]);
    assert(QU_COUNT((&qu))==2);
    assert(*((int *)qu_dequeue(&qu))==nums[3]);
    assert(*((int *)qu_dequeue(&qu))==nums[2]);
    assert(QU_ISEMPTY((&qu))==true);
    free(nums);
    nums = (int *)malloc(sizeof(int));
    *nums=12;
    qu_enqueue(&qu,nums);
    nums = (int *)malloc(sizeof(int));
    *nums=24;
    qu_enqueue(&qu,nums);
    assert(QU_COUNT((&qu))==2);
    qu_clear(&qu);
    assert(QU_COUNT((&qu))==0);
    qu_cleanup(&qu,false);
    printf("qu_cleanup\t[OK]\n");
}