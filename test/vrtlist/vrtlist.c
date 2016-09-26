#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include <vrtlist.h>

struct my_entry {
    int num;
    char alpha;
    VRTLIST_ENTRY(my_entry);
};

VRTLIST_LIST(my_list, my_entry);

int main(int argc, char **argv) {
    struct my_list list = VRTLIST_INIT;
    struct my_entry e1 = {1, 'a', VRTLIST_ENTRY_INIT};
    struct my_entry e2 = {2, 'b', VRTLIST_ENTRY_INIT};
    struct my_entry e3 = {3, 'c', VRTLIST_ENTRY_INIT};

    assert(VRTLIST_EMPTY((&list)));
    VRTLIST_PUSH((&list), (&e1));
    assert(VRTLIST_EMPTY((&list)) == false);
    VRTLIST_PUSH_LAST((&list), (&e2));
    assert(VRTLIST_PEEK_LAST((&list))->num == e2.num);
    VRTLIST_PUSH((&list), (&e3));

    assert(VRTLIST_COUNT((&list)) == 3);

    VRTLIST_FOREACH((&list), my_entry, cursor)printf("foreach: %d\n", cursor->num);

    VRTLIST_FOREACH_REVERSE((&list), my_entry, cursor)printf("foreach_r: %d\n", cursor->num);

    struct my_entry *entry;
    VRTLIST_POP((&list), entry);
    assert(entry->num == e3.num);
    VRTLIST_POP_LAST((&list), entry);
    assert(entry->num == e2.num);

    assert(VRTLIST_COUNT((&list)) == 1);

    VRTLIST_REMOVE((&list), VRTLIST_PEEK((&list)));
    assert(VRTLIST_EMPTY((&list)) == true);

    VRTLIST_PUSH((&list), (&e1));
    VRTLIST_PUSH((&list), (&e2));
    VRTLIST_PUSH((&list), (&e3));

    VRTLIST_REMOVE((&list), VRTLIST_NEXT(VRTLIST_PEEK((&list))));
    assert(VRTLIST_PEEK((&list))->num == e3.num);
    assert(VRTLIST_PEEK_LAST((&list))->num == e1.num);
    assert(VRTLIST_COUNT((&list)) == 2);
}
