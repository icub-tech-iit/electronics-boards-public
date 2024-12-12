/*
 * Very simple but very effective user-space memory tester.
 * Originally by Simon Kirby <sim@stormix.com> <sim@neato.org>
 * Version 2 by Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Version 3 not publicly released.
 * Version 4 rewrite:
 * Copyright (C) 2004-2010 Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Licensed under the terms of the GNU General Public License version 2 (only).
 * See the file COPYING for details.
 *
 * This file contains typedefs, structure, and union definitions.
 *
 */

#ifndef XIL_MEMTESTER_TYPES_H_
#define XIL_MEMTESTER_TYPES_H_

#include "sizes.h"
#include "stdlib.h"

typedef unsigned long ul;
typedef unsigned long volatile ulv;

typedef unsigned long long ull;
typedef unsigned char volatile u8v;
typedef unsigned short volatile u16v;

#if defined (__aarch64__)
typedef unsigned int volatile u32v;
#endif

struct test {
    char *name;
    int (*fp)(ulv*, ulv*, size_t);
    int FastTest;
};

#endif /* XIL_MEMTESTER_TYPES_H_ */
