/***************************************************************************
 *  Project          : Enclustra Reference Design
 *  File description : Memory Test
 *  File name        : main.c
 *  Author           : Christoph Glattfelder
 ***************************************************************************
 *  Copyright (c) 2018 by Enclustra GmbH, Switzerland
 *  All rights reserved.
 ***************************************************************************
 *  Notes:
 *
 ***************************************************************************
 *  File history:
 *
 *  Version | Date     | Author             | Remarks
 *  ------------------------------------------------------------------------
 *  1.0	    | 29.06.15 | Ch. Glattfelder    | Created
 *  1.1		| 16.07.15 | D. Ungureanu       | Cleaned-up code
 *  1.2		| 19.07.18 | D. Ungureanu       | Added info on Zynq Ultrascale+
 *          |          |                    |
 *  ------------------------------------------------------------------------
 *
 **************************************************************************/

#include <xparameters.h>
#include <stdio.h>
#include "ENC_memtester.h"
#include "xil_cache.h"
#include "StandardIncludes.h"


//Memory test offset - start testing the DDR memory starting from that point on
//used in case the code is executed on the DDR memory; the program will not be
//overwritten by the test
//approximated necessary value 1MB
#define TEST_OFFSET 0x100000

#define TEST_MARGIN 0x100000
//PSU__DDR_SW_REFRESH_ENABLED - by default enabled
//lower DDR part reserved (0x7ff00000 to 0x7fffffff)

//1Mb value
#define ONE_MB 0x100000

int main(){
	int i, errors = 0;

	int SdramSizePS1 = 2048;
	int SdramSizePS2 = 0;

	//up to 4GB PS DDR
	//int SdramSizePS2 = 2048;

	int SdramSizePL = 1024;
	
	Xil_DCacheEnable();
	Xil_ICacheEnable();

	for (i=0; i<20; i++)
		EN_PRINTF("\r\n");
	EN_PRINTF("== Enclustra Memory Test ==\r\n\r\n");

    EN_PRINTF("PS-DDR4: ");
	errors += run_ddr_test((XPAR_PSU_DDR_0_S_AXI_BASEADDR + TEST_OFFSET), SdramSizePS1*ONE_MB - TEST_OFFSET - TEST_MARGIN, 2, FALSE, TRUE);
	errors += run_ddr_test((XPAR_PSU_DDR_0_S_AXI_BASEADDR + TEST_OFFSET), 16*ONE_MB, 1, TRUE, TRUE);

    // when the memory is larger than 2GB, the DDR high region is used (see System Address Map, Zynq Ultrascale+ TRM)
    // for the second DDR section the base address is XPAR_PSU_DDR_1_S_AXI_BASEADDR (see xparameters.h for details)
	// TEST EXAMPLE:  errors += run_ddr_test(XPAR_PSU_DDR_1_S_AXI_BASEADDR, (SdramSizePS2-1)*ONE_MB, 2, FALSE, TRUE);
    // NOTE:  DDR high domain is not accessible when using Xilinx SDK debugger - a memory test can be run from a boot image (e.g. SD card boot image)
    // NOTE:  For PL masters access to DDR high domain, refer to Xilinx AR# 70712
    

	EN_PRINTF("PL-DDR4: ");
	//no offset required if the program runs from PS DDR
	errors += run_ddr_test(XPAR_DDR4_0_BASEADDR, (SdramSizePL-1)*ONE_MB, 2, FALSE, TRUE);
	errors += run_ddr_test(XPAR_DDR4_0_BASEADDR, 4*ONE_MB, 1, TRUE, TRUE);

	if (errors)
		EN_PRINTF("== Test finished, %d run contained errors ==\r\n\r\n", errors);
	else
		EN_PRINTF("== Test finished, no errors occurred ==\r\n\r\n");

	return 0;
}
