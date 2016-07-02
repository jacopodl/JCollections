/*
* JCdatatype, part of JCollections.
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

#ifndef JCOLLECTIONS_JCDATATYPE_H
#define JCOLLECTIONS_JCDATATYPE_H

typedef enum {
    JCERR_SUCCESS,
    JCERR_NULLVAL,
    JCERR_ENOMEM,
    JCERR_KEYEXIST
} JCErr;

typedef unsigned int jcsize;

#endif