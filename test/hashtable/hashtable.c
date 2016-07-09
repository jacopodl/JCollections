#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <hashtable.h>
#include <utils.h>

char *mkstr(char *str)
{
    char *s = malloc(strlen(str));
    strcpy(s,str);
    return s;
}

int main(int argc, char **argv)
{
    struct HTable table;
    printf("ht_init\t[OK]\n");
    ht_init(&table, 5, HT_DEFLOADF, hash4str, eq4str, g2free);
    assert(HT_ISEMPTY((&table))==true);
    assert(HT_SIZE((&table))==5);
    ht_put(&table,mkstr("h20"),mkstr("water"));
    assert(ht_put(&table,mkstr("h20"),mkstr("err"))==JCERR_KEYEXIST);
    ht_put(&table,mkstr("ch4"),mkstr("methane"));
    ht_put(&table,mkstr("ch3"),mkstr("methyl"));
    assert(ht_contains(&table,"ch4")==true);
    ht_put(&table,mkstr("c6h6"),mkstr("benzene"));
    assert(HT_SIZE((&table))==10);
    ht_put(&table,mkstr("rcooh"),mkstr("carboxylic acid"));
    assert(ht_contains(&table,"ch4")==true);
    ht_put(&table,mkstr("c8h16"),mkstr("3-octane"));
    assert(strcmp(((char *)ht_get(&table,"c8h16")),"3-octane")==0);
    ht_set(&table,mkstr("c8h16"),mkstr("ethylcyclohexane"));
    assert(strcmp(((char *)ht_get(&table,"c8h16")),"ethylcyclohexane")==0);
    assert(strcmp(((char *)ht_get(&table,"ch3")),"methyl")==0);
    while(ht_iterator(&table,NULL,NULL));
    ht_remove(&table,"ch3");
    assert(ht_get(&table,"ch3")==NULL);
    assert(HT_COUNT((&table))==5);
    assert(HT_SIZE((&table))==10);
    ht_clear(&table,true);
    assert(HT_SIZE((&table))==5);
    assert(ht_contains(&table,"ch4")==false);
    ht_put(&table,mkstr("ch4"),mkstr("methane"));
    ht_put(&table,mkstr("ch3"),mkstr("methyl"));
    assert(strcmp(((char *)ht_get(&table,"ch3")),"methyl")==0);
    ht_cleanup(&table,false);
    printf("ht_cleanup\t[OK]\n");
}