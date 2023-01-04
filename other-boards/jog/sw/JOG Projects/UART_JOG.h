/*********************************************************************************
author:JENVRIN Julien
company: Italian Institute of Technology
Date: 21/06/2013
program name: UART_JOG.h
content: prototypes of the UART_JOG.c file
*************************************************************************************/

//#ifndef _UART_JOG_H_
//#define _UART_JOG_H_

void Clear_Read_Buffer(void);
int ACK_4DSYSTEMS(void);
void send_byte_serial(unsigned char byte);
void sendB(unsigned char* buffer,int length_buffer);


