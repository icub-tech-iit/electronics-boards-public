/*********************************************************************************
author:JENVRIN Julien
company: Italian Institute of Technology
Date: 19/09/2014
program name: CAN_JOG.c
content: All functions to use the CAN connector on JOG_BOARD
**********************************************************************************/
#include <ecan.h>
#include <dma.h>
#include <p33FJ128MC804.h>
#include "UserParms.h"

/* CAN Baud Rate Configuration */
#define FCAN DFCY // see UserParms.h = 40MHz
#define BITRATE 1000000
#define NTQ 20 //20 time quanta in a bit time
#define BRP_VAL ((FCAN/(2*NTQ*BITRATE))-1)

void CAN1_clock_config(void)
{
	C1CTRL1bits.WIN=0;
	/* Set the ECAN module for Configuration Mode before writing into the Baud
	Rate Control Registers*/
	C1CTRL1bits.REQOP = 4;
	/* Wait for the ECAN module to enter into Configuration Mode */
	while(C1CTRL1bits.OPMODE != 4);
	C1FCTRLbits.DMABS = 0b110;	//set 32 words memory BUFFER to receive/transmit
	
	/* Phase Segment 1 time is 8 TQ */
	C1CFG2bits.SEG1PH = 0x7;
	/* Phase Segment 2 time is set to be programmable */
	C1CFG2bits.SEG2PHTS = 0x1;
	/* Phase Segment 2 time is 6 TQ */
	C1CFG2bits.SEG2PH = 0x5;
	/* Propagation Segment time is 5 TQ */
	C1CFG2bits.PRSEG = 0x4;
	/* Bus line is sampled three times at the sample point */
	C1CFG2bits.SAM = 0x1;
	/* Synchronization Jump Width set to 4 TQ */
	C1CFG1bits.SJW = 0x3;
	/* Baud Rate Prescaler bits set to 1:1, i.e., TQ = (2*1*1)/ FCAN */
	C1CFG1bits.BRP = BRP_VAL ;
	
	CAN1SetOperationMode(CAN_IDLE_CON & CAN_REQ_OPERMODE_NOR & CAN_CAPTURE_DISABLE & CAN_SFR_BUFFER_WIN, CAN_DO_NOT_CMP_DATABYTES);
	
	C1TR01CONbits.TXEN0 = 1; /* ECAN1, Buffer 0 is a Transmit Buffer */
	C1TR01CONbits.TXEN1 = 1; /* ECAN1, Buffer 1 is a Receive Buffer */
	
	C1TR01CONbits.TX0PRI = 0b11; /* Message Buffer 0 Priority Level */
	
	ConfigIntCAN1(CAN_INVALID_MESSAGE_INT_DIS & CAN_WAKEUP_INT_DIS & CAN_ERR_INT_DIS & CAN_FIFO_INT_DIS & CAN_RXBUF_OVERFLOW_INT_DIS & CAN_RXBUF_INT_DIS & CAN_TXBUF_INT_DIS, CAN_INT_PRI_7 & CAN_INT_DISABLE);
	/* Enable ECAN1 interrupt */
//	IEC2bits.C1IE = 1;
	/* Enable transmit interrupt */
	C1INTEbits.TBIE = 1;

	/* Put the ECAN Module into Normal Mode Operating Mode*/
	C1CTRL1bits.REQOP = 0;
	/* Wait for the ECAN module to enter into Normal Operating Mode */
	while(C1CTRL1bits.OPMODE != 0);
		
}

void CAN1_reset_interrupt_flags(void)
{
	C1INTF = 0;
	_C1IF = 0;
	_C1TXIF = 0;
	_C1RXIF = 0;
	_C1IE = 1;
	_C1TXIE = 0;
	_C1RXIE = 0;
	C1INTE = 0x00FF;
	C1RXFUL1 = 0;
	C1RXFUL2 = 0;
	C1RXOVF1 = 0;
	C1RXOVF2 = 0;
}



//void ECANDma0Init(void)
//// DMA Initialization for ECAN1 Transmission
//{
//  // clear the collission flags
//  DMACS0 = 0;	
//  // setup channel 1 for peripheral indirect addressing mode
//  // normal operation, word operation and select as Tx to peripheral
//  DMA0CON = 0x2020; 
//  // setup the address of the peripheral ECAN1 (C1TXD)
//  DMA0PAD=0x0442;
//  // Set the data block transfer size of 8 
//  DMA0CNT=0x0007;
//  // automatic DMA Tx initiation by DMA request
//  DMA0REQ=0x0046;	
//  // DPSRAM TX start adddress offset value
//  DMA0STA=__builtin_dmaoffset(ecan1MsgBufTx); 
//  // enable the channel
//  DMA0CONbits.CHEN=1;	 
//}
//

