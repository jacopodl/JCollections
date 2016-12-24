#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include <vrtqueue.h>

struct my_entry {
    int num;
    char alpha;
    VRTQUEUE_ENTRY(my_entry);
};

VRTQUEUE_QUEUE(my_queue,my_entry);

int main(int argc, char **argv) {
    struct my_queue queue = VRTQUEUE_INIT;
    struct my_entry *mye;
    struct my_entry e1 = {1, 'a', VRTQUEUE_ENTRY_INIT};
    struct my_entry e2 = {2, 'b', VRTQUEUE_ENTRY_INIT};

    assert(VRTQUEUE_EMPTY((&queue)));

    VRTQUEUE_ENQUEUE((&queue), (&e1));
    assert(VRTQUEUE_EMPTY((&queue)) == false);
    VRTQUEUE_ENQUEUE((&queue), (&e2));
    VRTQUEUE_DEQUEUE((&queue),mye);
    assert(mye->num == e1.num);
    VRTQUEUE_DEQUEUE((&queue),mye);
    assert(mye->num == e2.num);
    assert(VRTQUEUE_EMPTY((&queue)) == true);
}