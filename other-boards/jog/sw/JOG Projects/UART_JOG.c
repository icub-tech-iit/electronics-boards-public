/*********************************************************************************
author:JENVRIN Julien
company: Italian Institute of Technology
Date: 21/06/2013
program name: UART_JOG.c
content: All functions use to dialog with the SCREEN from 4DSYSTEMS via UART - used in Goldelox_Compound4DRoutiines.inc
*************************************************************************************/

#include <p33FJ128MC804.h>
#include <stdlib.h>
#include <string.h>
#include <uart.h>
#include "conf.h"

/*This function clear the reception buffer*/
void Clear_Read_Buffer(void)
{
	unsigned int RX_data;
	while(DataRdyUART1()==1)
	{
		RX_data=ReadUART1();
	}

}
/*This function wait for the ACK of the 4DSYSTEMS screens*/
int ACK_4DSYSTEMS(void)
{
	//TestACK
	unsigned char RX_data;
	//wait_ms(60);
	if(DataRdyUART1() == 1)
	{
		RX_data = (unsigned char)ReadUART1();
		if (RX_data==0x06)
		{
			return 1;
		}
		else 
		{
			return 0;
		}
	}
	else
		return 0;

}
/*This function send 1 char on serial line 1*/
void send_byte_serial(char byte)
{	
	int i,j;
	//U1TXREG = byte;
	//if(U1)
	int check;
	for(j=0;j<4;j++)
	{
		for(i=0;i<4;i++)
		{
			check=byte+i+j;
			U1TXREG = byte+i+j;
			while(_U1TXIF!=1) //wait till the byte has been sent
			{;}	
			_U1TXIF=0;
		}	
	}
}

/*This function is designed to send char after char from a buffer of length_buffer size*/
/*This function works on serial line 1*/
void sendB(unsigned char* buffer,int length_buffer)
{
	int i=0;
	//char check;
	while(i<length_buffer)
	{
		//check=buffer[i];
		U1TXREG = buffer[i];
     	while(_U1TXIF!=1);
     	_U1TXIF=0;
     	i++;
    }
    while(BusyUART1());
}

	
