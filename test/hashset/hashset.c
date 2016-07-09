#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <hashset.h>
#include <utils.h>

char *mkstr(char *str)
{
    char *s = malloc(strlen(str));
    strcpy(s,str);
    return s;
}

int main(int argc, char **argv)
{
    struct HSet set;
    printf("hset_init\t[OK]\n");
    hset_init(&set, 5, hash4str, eq4str, free);
    assert(HSET_ISEMPTY((&set))==true);
    assert(hset_add(&set,mkstr("carboxylic acid"))==JCERR_SUCCESS);
    assert(HSET_ISEMPTY((&set))==false);
    assert(hset_add(&set,"carboxylic acid")==JCERR_KEYEXIST);
    assert(hset_add(&set,mkstr("benzene"))==JCERR_SUCCESS);
    assert(hset_add(&set,mkstr("methyl"))==JCERR_SUCCESS);
    assert(hset_add(&set,mkstr("methane"))==JCERR_SUCCESS);
    assert(HSET_COUNT((&set))==4);
    assert(hset_contains(&set,"benzene"));
    assert(hset_contains(&set,"water")==false);
    assert(hset_contains(&set,NULL)==false);
    assert(HSET_COUNT((&set))==4);
    hset_remove(&set,"methane");
    assert(hset_contains(&set,"methane")==false);
    hset_clear(&set);
    assert(HSET_ISEMPTY((&set))==true);
    assert(hset_contains(&set,"methyl")==false);
    hset_cleanup(&set,false);
    printf("hset_cleanup\t[OK]\n");
}