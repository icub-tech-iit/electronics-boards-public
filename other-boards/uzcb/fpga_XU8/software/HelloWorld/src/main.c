/**************************************************************
 *  Project          : Enclustra Vivado reference design
 *  File description : Hello World
 *  File name        : main.c
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
 *  1.0	    | 29.06.15 | Ch. Glattfelder    | Created
 *  1.1     | 16.07.15 | D. Ungureanu       | Cleaned-up code
 *          |          |                    |
 *  ------------------------------------------------------------
 *
 **************************************************************/


#include <stdio.h>
#include "StandardIncludes.h"
#include "UtilityFunctions.h"

#if SYSTEM == XILINX_MICROBLAZE
	#define SLEEP_VALUE 100000
	#define SYSTEM_INIT
#elif SYSTEM == XILINX_ARM_SOC
	#define SLEEP_VALUE 100000000
	#define SYSTEM_INIT
#elif SYSTEM == ALTERA_NIOS
	#define SLEEP_VALUE 10000000
	#define SYSTEM_INIT
#elif SYSTEM == ALTERA_ARM_SOC
	#include "AlteraInitSystem.h"
	#define SLEEP_VALUE 100000000
	#define SYSTEM_INIT AlteraInitSystem()
#elif SYSTEM == UBOOT
	#define SLEEP_VALUE 10000000
	#define SYSTEM_INIT
#endif

int main()
{
	
	int i;

	SYSTEM_INIT;
	
    EN_PRINTF("\n\r\n\r\n\r\n\r");

	EN_PRINTF("== Enclustra Hello World Example ==\r\n\r\n");
	
    for (i=0; i<20; i++){
    	EN_PRINTF("Hello World %d\n\r", i);
		Sleep(SLEEP_VALUE);
    }

    EN_PRINTF("\n\rGoodbye...\n\r");

	while (1);
    return 0;
}
