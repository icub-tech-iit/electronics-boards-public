/**************************************************************
 *  Project          : Enclustra Vivado reference design
 *  File description : Memory Test
 *  File name        : ENC_memtester.c
 *  Author           : Christoph Glattfelder
 **************************************************************
 *  Copyright (c) 2015 by Enclustra GmbH, Switzerland
 *  All rights reserved.
 **************************************************************
 *  Notes:
 *
 **************************************************************
 *  File history:
 *
 *  Version | Date     | Author             | Remarks
 *  -----------------------------------------------------------
 *  1.0	    | 29.06.15 | S. Huerlimann      | Created
 *  2.0     | 04.07.18 | D. Ungureanu       | Adapted for 64-bit
 *  ------------------------------------------------------------
 *
 **************************************************************/



#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "ENC_memtester.h"
//#include "types.h"
#include "sizes.h"
#include "tests.h"
#include "StandardIncludes.h"


struct test tests[] = {
    { "Random Value", test_random_value, 0 },
    { "Compare XOR", test_xor_comparison, 0 },
    { "Compare SUB", test_sub_comparison, 0 },
    { "Compare MUL", test_mul_comparison, 0 },
    { "Compare DIV",test_div_comparison, 0 },
    { "Compare OR", test_or_comparison, 0 },
    { "Compare AND", test_and_comparison, 0 },
    { "Sequential Increment", test_seqinc_comparison, 1 },
    { "Solid Bits", test_solidbits_comparison, 0 },
    { "Block Sequential", test_blockseq_comparison, 0 },
    { "Checkerboard", test_checkerboard_comparison, 0 },
    { "Bit Spread", test_bitspread_comparison, 0 },
    { "Bit Flip", test_bitflip_comparison, 0 },
    { "Walking Ones", test_walkbits1_comparison, 0 },
    { "Walking Zeroes", test_walkbits0_comparison, 0 },
#ifdef TEST_NARROW_WRITES
    { "8-bit Writes", test_8bit_wide_random, 0 },
    { "16-bit Writes", test_16bit_wide_random, 0 },
#if defined (__aarch64__)
	{ "32-bit Writes", test_32bit_wide_random, 0 },
#endif

#endif
    { NULL, NULL, 0 }
};


extern off_t physaddrbase;
int tests_verbose;

ul run_ddr_test(ul BaseAddr, ul Length, ul loops, ul full_test, ul Verbose) {

	ul i = 0;
	ul bufsize = Length;
	ul loop;
	ul halflen = bufsize / 2;
	ul count = halflen / sizeof(ul);
	ul Errors = 0, LoopErros = 0;

	tests_verbose = Verbose;
	physaddrbase = BaseAddr;

	ulv* bufa = (ulv *) BaseAddr;
	ulv* bufb = (ulv *) ((size_t) bufa + halflen);

	// print header
	if (Verbose){
		EN_PRINTF("  Testing %dMB @ Address 0x%llx ", Length/0x100000, BaseAddr);
		if (full_test)
			EN_PRINTF("(full test)\r\n\r\n");
		else
			EN_PRINTF("(quick test)\r\n\r\n");
	}

	// run the memory test multiple times
	for(loop=1; ((!loops) || loop <= loops); loop++) {
		if (Verbose){
			EN_PRINTF("  Loop %d", loop);
			if (loops) {
				EN_PRINTF("/%d", loops);
			}
			EN_PRINTF(":\r\n");
		}

		// run test_stuck_address only for full test
		if (full_test){
			if (Verbose) EN_PRINTF("    %-20s: ", "Stuck Address");
			if (!test_stuck_address(bufa, bufsize / sizeof(ul))) {
				if (Verbose) EN_PRINTF("ok\r\n");
			} else {
				Errors++;
			}
		}

		// run the other tests
		for (i=0;;i++) {
			if (!tests[i].name) break;
			if (full_test || tests[i].FastTest){

				if (Verbose) EN_PRINTF("    %-20s: ", tests[i].name);
				if (!tests[i].fp(bufa, bufb, count)) {
					if (Verbose) EN_PRINTF("ok\r\n");
				}else {
					Errors++;
				}
			}
		}

		if (Verbose) EN_PRINTF("\r\n");
		if (Errors){
			LoopErros++;
			Errors = 0;
		}
	}
	return LoopErros;
}

