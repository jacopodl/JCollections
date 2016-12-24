/*
* VRTQUEUE, part of JCollections.
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

#ifndef LIBJCOLLECTIONS_VRTQUEUE_H
#define LIBJCOLLECTIONS_VRTQUEUE_H

#include "vrtlist.h"

#define VRTQUEUE_COUNT(queue)           VRTLIST_COUNT(queue)
#define VRTQUEUE_DEQUEUE(queue, entry)  VRTLIST_POP_LAST(queue, entry)
#define VRTQUEUE_EMPTY(queue)           VRTLIST_EMPTY(queue)
#define VRTQUEUE_ENQUEUE(queue, entry)  VRTLIST_PUSH(queue, entry)
#define VRTQUEUE_ENTRY(etype)           VRTLIST_ENTRY(etype)
#define VRTQUEUE_ENTRY_INIT             VRTLIST_ENTRY_INIT
#define VRTQUEUE_INIT                   VRTLIST_INIT
#define VRTQUEUE_PEEK(queue, entry)     VRTLIST_PEEK_LAST(queue, entry)
#define VRTQUEUE_QUEUE(qname, etype)    VRTLIST_LIST(qname, etype)

#endif //LIBJCOLLECTIONS_VRTQUEUE_H
