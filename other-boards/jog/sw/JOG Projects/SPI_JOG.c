/*********************************************************************************
author:JENVRIN Julien
company: Italian Institute of Technology
Date: 12/11/2013
program name: SPI_JOG.c
content: All functions use to dialog in SPI with AS5045 - AEA
*************************************************************************************/

#include <p33FJ128MC804.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <spi.h>
#include "conf.h"  //wait(ms, us , s) routines inside

extern int txt_MoveCursor();
extern int putstr();

/*This function receive X char on SPI MISO*/

int receive_SPI(unsigned int* RX_Data)
{	
	SPI1STATbits.SPIEN = 1;
	PORTBbits.RB11=0;
	WriteSPI1(0x0000);// Write data even if not transmitted anything just in order to say OK start opening reception and transmition

	while(DataRdySPI1()==0);	//wait for data reception
	RX_Data[0] = ReadSPI1();
	wait_us(15);
	if (DataRdySPI1()==0)		//receive other bits? (lat 2 bits - if nothing means 0 received)
	{
		RX_Data[1] = ReadSPI1();
	}
	
	PORTBbits.RB11=1;
	SPI1STATbits.SPIEN = 1;

	Nop();
	RX_Data[0]=RX_Data[0]>>4;
	RX_Data[0]&=0x0FFF;
	return 0;
}

//This function is designed to send char after char from a buffer of length_buffer size
//This function works on serial line 1
void print_receive_value_SPI(unsigned int* RX_Data)
{
	char Data_AEA[7]={0};
	sprintf(Data_AEA,"%s",(const char *)RX_Data);
	txt_MoveCursor(5,0);
	putstr(Data_AEA);
}
