/*
 * Very simple but very effective user-space memory tester.
 * Originally by Simon Kirby <sim@stormix.com> <sim@neato.org>
 * Version 2 by Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Version 3 not publicly released.
 * Version 4 rewrite:
 * Copyright (C) 2004-2012 Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Licensed under the terms of the GNU General Public License version 2 (only).
 * See the file COPYING for details.
 *
 * This file contains some macro definitions for handling 32/64 bit platforms.
 *
 */

#ifndef XIL_MEMTESTER_SIZES_H_
#define XIL_MEMTESTER_SIZES_H_

#if defined (__aarch64__)
	#define rand_ul() ((unsigned long) rand() | ( (unsigned long) rand() << 32))
	#define UL_ONEBITS 0xffffffffffffffff
	#define UL_LEN 64
	#define CHECKERBOARD1 0x5555555555555555
	#define CHECKERBOARD2 0xaaaaaaaaaaaaaaaa
	#define UL_BYTE(x) ((unsigned long) x | (unsigned long) x << 8 | (unsigned long) x << 16 | (unsigned long) x << 24 | \
               (unsigned long) x << 32 | (unsigned long) x << 40 | (unsigned long) x << 48 | (unsigned long) x << 56)

#else
	#define rand_ul() ((unsigned int) rand() | ( (unsigned int) rand() << 16))
	#define UL_ONEBITS 0xffffffff
	#define UL_LEN 32
	#define CHECKERBOARD1 0x55555555
	#define CHECKERBOARD2 0xaaaaaaaa
	#define UL_BYTE(x) ((x | x << 8 | x << 16 | x << 24))
#endif



#endif /* XIL_MEMTESTER_SIZES_H_ */
