/*********************************************************************************
author:JENVRIN Julien
company: Italian Institute of Technology
Date: 12/11/2013
program name: QEI_JOG.c
content: All functions use to configure and test QEI sensors - Quadrature Encoder Interface
*************************************************************************************/
#include <qei.h>

#include "conf.h"

extern void txt_MoveCursor(WORD , WORD );
extern void putstr();

void setup_QEI_JOG(void)
{
	/*QEIxCON: QEI Control Register*/
		//This register controls the QEI operation and provides status flags for the state of the QEI module.
		
		ConfigIntQEI1(QEI_INT_PRI_1 & QEI_INT_ENABLE);
	    POS1CNT  = 0x0001;
	    MAX1CNT = 0x7FFF;
	    OpenQEI1(QEI_EXT_CLK & QEI_INDEX_RESET_DISABLE & QEI_CLK_PRESCALE_256 & QEI_GATED_ACC_DISABLE & QEI_INPUTS_NOSWAP & QEI_MODE_x2_MATCH & QEI_DIR_SEL_CNTRL & QEI_IDLE_CON, POS_CNT_ERR_INT_ENABLE & QEI_QE_CLK_DIVIDE_1_1 & QEI_QE_OUT_ENABLE);
	    //QEICONbits.UPDN = 1;
    

}
void countdown(int timer_in_s)
{
	int i;
	txt_MoveCursor(6,0);
	putstr("");
	for(i=0;i<timer_in_s;i++)
	{
		wait_s(1);
		
	}
}
