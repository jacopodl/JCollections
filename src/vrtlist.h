/*
* vrtlist, part of JCollections.
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

#ifndef LIBJCOLLECTIONS_VRTLIST_H
#define LIBJCOLLECTIONS_VRTLIST_H

#define VRTLIST_INIT    {NULL, NULL, 0}
#define VRTLIST_LIST(lname, etype)          \
    struct lname{                           \
        struct etype *head;                 \
        struct etype *tail;                 \
        unsigned int size;                  \
    }

#define VRTLIST_ENTRY_INIT  {NULL, NULL}
#define VRTLIST_ENTRY(etype)                \
    struct {                                \
        struct etype *next;                 \
        struct etype *prev;                 \
    }

#define VRTLIST_PUSH(list, entry)               \
    do {                                        \
        if((entry->next = list->head) !=NULL)   \
            entry->next->prev = entry;          \
        entry->prev = NULL;                     \
        list->head = entry;                     \
        if(list->tail == NULL)                  \
            list->tail = entry;                 \
        list->size ++;                          \
    } while(0)

#define VRTLIST_PUSH_LAST(list, entry)          \
    do {                                        \
        entry->next = NULL;                     \
        if((entry->prev = list->tail) == NULL)  \
            list->head = entry;                 \
        if(entry->prev != NULL)                 \
            entry->prev->next = entry;          \
        list->tail = entry;                     \
        list->size ++;                          \
    } while (0)

#define VRTLIST_POP(list, elem_ptr)             \
    do {                                        \
        elem_ptr = list->head;                  \
        VRTLIST_REMOVE(list, list->head);       \
    } while (0)

#define VRTLIST_POP_LAST(list, elem_ptr)        \
    do {                                        \
        elem_ptr = list->tail;                  \
        VRTLIST_REMOVE(list, list->tail);       \
    } while (0)

#define VRTLIST_PEEK(list) list->head
#define VRTLIST_PEEK_LAST(list) list->tail
#define VRTLIST_NEXT(elem) elem->next
#define VRTLIST_EMPTY(list) (list->size == 0)
#define VRTLIST_COUNT(list) (list->size)

#define VRTLIST_REMOVE(list, elem)                      \
    do {                                                \
        if(elem->next != NULL) {                        \
            if((elem->next->prev=elem->prev) == NULL)   \
                list->head = elem->next;                \
            else                                        \
                elem->prev->next=elem->next;            \
        } else {                                        \
            if((list->tail = elem->prev) != NULL)       \
                list->tail->next = NULL;                \
            else                                        \
                list->head = NULL;                      \
        } list->size --;                                \
    } while(0)

#define VRTLIST_FOREACH(list, etype, curname)       \
    for(struct etype *next, *curname = list->head; (curname != NULL) && (next = curname->next, 1); curname = next)

#define VRTLIST_FOREACH_REVERSE(list, etype, curname)       \
    for(struct etype *prev, *curname = list->tail; (curname != NULL) && (prev = curname->prev, 1); curname = prev)

#endif //LIBJCOLLECTIONS_VRTLIST_H
