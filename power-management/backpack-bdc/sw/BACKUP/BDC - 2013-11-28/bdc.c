 /****************************************************
 *  BDC board - iCub Facility - 2013                 *
 *  Main program                                     *
 *                                                   *
 *  Written by Andrea Mura                           *
 *  <andrea.mura@iit.it>                             *
 ****************************************************/


// ----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------

#include <stdio.h>
#include "STM32F10x.h"
#include "define.h"
#include "globals.h"
#include "gpio.h"
#include "adc.h"
#include "can.h"
#include "exti.h"
#include "timer.h"

// ----------------------------------------------------------------------------
// Global variables
// ----------------------------------------------------------------------------
int V_VBATT			= 0;
int V_V12board	= 0;
int V_V12motor	= 0;
int I_V12board	= 0;
int I_V12motor	= 0;
int I_HSM				= 0;
int DCDC_status	= 0;
int HSM_PG			= 0;
int HSM_F				= 0;

int ledDir = 0;
int ledDir1 = 0;

// ----------------------------------------------------------------------------
// Local variables
// ----------------------------------------------------------------------------
int *adc_values;			// contains all ADC channels conversion

int V12board=0;
int V12motor=0;
int HSM=0;

int message=0;

unsigned int ledExti    = 0;
//int hsm_fault=0;
//int hsm_pg=0;
int cont=0;
int rx=0;
int prova=0;

int adc_val[6];


// ----------------------------------------------------------------------------
// Initialize CAN interface
// ----------------------------------------------------------------------------
void CAN_init (void) {
  CAN_setup();																// setup CAN Controller     
  CAN_wrFilter (0x602, STANDARD_FORMAT);			// Enable reception of PC messages 
	CAN_wrFilter (0x612, STANDARD_FORMAT);			// Enable reception of BCB messages 
	
  // ! COMMENT LINE BELOW TO ENABLE DEVICE TO PARTICIPATE IN CAN NETWORK !    
  //CAN_testmode(CAN_BTR_SILM | CAN_BTR_LBKM);      // Loopback, Silent Mode (self-test)

  CAN_start ();																// start CAN Controller   
  CAN_waitReady ();														// wait till tx mbx is empty 
}




// ----------------------------------------------------------------------------
// MAIN function
// ----------------------------------------------------------------------------
int main (void) {
	int a;
	int b;
	int i;
	
	GPIO_Init();
	EXTI_Init();
	ADC_Init();
	TIM1_Init();
	
	//TIM2_Init();
	//USART2_Init();
	
	CAN_init();
	
	CAN_TxMsg.id = 0x621;
  for (i = 0; i < 8; i++) CAN_TxMsg.data[i] = 0x0;
  CAN_TxMsg.len = 8;
  CAN_TxMsg.format = STANDARD_FORMAT;
  CAN_TxMsg.type = DATA_FRAME;
	  
  while (1) {
		
		ADC_StartCnv();                      // start A/D conversion 12bit
		adc_values	= ADC_Conv();
		ADC_StopCnv();                       // stop A/D conversion
		
		V_VBATT			=*adc_values;
		V_V12board	=*(adc_values+1);
		V_V12motor	=*(adc_values+2);
		I_V12board	=*(adc_values+3);
		I_V12motor	=*(adc_values+4);
		I_HSM				=*(adc_values+5);
		
		//hsm_fault=!((GPIOB->IDR & HSM_nFLT) >> 1);
		//hsm_pg=!((GPIOB->IDR & HSM_nPG) >> 2);
		
		//if((GPIOB->IDR & HSM_nFLT)==0)	{V48motor_FLT_ON;		HSM_F=1;}
		//else														{V48motor_FLT_OFF;	HSM_F=0;}
		
		//if((GPIOB->IDR & HSM_nPG)==0)		{V48motor_PG_ON;		HSM_PG=1;}
		//else														{V48motor_PG_OFF;		HSM_PG=0;}
		
		
		if(V12board)	{EN_V12board_ON;}
		else					{EN_V12board_OFF;}
		
		if(V12motor)	{EN_V12motor_ON;}
		else					{EN_V12motor_OFF;}
		
		if(HSM)				{HSM_EN_ON;}
		else					{HSM_EN_OFF;}
		
		
		DCDC_status =	((V12board	& 0x01) << 7)	+
									((V12motor	& 0x01)	<< 5)	+
									((HSM				& 0x01)	<< 3) +
									((HSM_PG		& 0x01)	<< 2) +
									((HSM_F			& 0x01) << 1);
				
		/*if (CAN_TxRdy) {
			//if(ledDir) {CAN_LED_ON;}
			//else {CAN_LED_OFF;}
			
			CAN_LED_ON;
			
			CAN_TxRdy = 0;
			
			if(message==0){
				CAN_TxMsg.id = 0x621;
				CAN_TxMsg.data[0] = 0x01;				// Voltage message
				CAN_TxMsg.data[1] = DCDC_status;
				CAN_TxMsg.data[2] = ((V_VBATT>> 8) & 0x0F);
				CAN_TxMsg.data[3] = V_VBATT & 0xFF;
				CAN_TxMsg.data[4] = ((V_V12board>> 8) & 0x0F);
				CAN_TxMsg.data[5] = V_V12board & 0xFF;
				CAN_TxMsg.data[6] = ((V_V12motor>> 8) & 0x0F);
				CAN_TxMsg.data[7] = V_V12motor & 0xFF;
				CAN_wrMsg (&CAN_TxMsg);
				message=1;
			}
			else if(message==1){
				CAN_TxMsg.id = 0x621;
				CAN_TxMsg.data[0] = 0x02;				// Current message
				CAN_TxMsg.data[1] = DCDC_status;
				CAN_TxMsg.data[2] = ((I_V12board>> 8) & 0x0F);
				CAN_TxMsg.data[3] = I_V12board & 0xFF;
				CAN_TxMsg.data[4] = ((I_V12motor>> 8) & 0x0F);
				CAN_TxMsg.data[5] = I_V12motor & 0xFF;
				CAN_TxMsg.data[6] = ((I_HSM>> 8) & 0x0F);
				CAN_TxMsg.data[7] = I_HSM & 0xFF;
				CAN_wrMsg (&CAN_TxMsg);
				message=0;
			}
			
		}
		else {CAN_LED_OFF;}*/
		
		if (CAN_RxRdy) {							//rx msg on CAN Ctrl
			CAN_LED_ON;
			if (CAN_TxRdy) {
				int ctrl = CAN_RxMsg.data[0];
				switch (ctrl){
				case 0x01:	CAN_TxMsg.id = 0x621;
										CAN_TxMsg.data[0] = 0x81;				// Voltage message
										CAN_TxMsg.data[1] = DCDC_status;
										CAN_TxMsg.data[2] = ((V_VBATT>> 8) & 0x0F);
										CAN_TxMsg.data[3] = V_VBATT & 0xFF;
										CAN_TxMsg.data[4] = ((V_V12board>> 8) & 0x0F);
										CAN_TxMsg.data[5] = V_V12board & 0xFF;
										CAN_TxMsg.data[6] = ((V_V12motor>> 8) & 0x0F);
										CAN_TxMsg.data[7] = V_V12motor & 0xFF;
										CAN_wrMsg (&CAN_TxMsg);
										LED1_ON;
										break;
				case 0x02:	CAN_TxMsg.id = 0x621;
										CAN_TxMsg.data[0] = 0x82;				// Current message
										CAN_TxMsg.data[1] = DCDC_status;
										CAN_TxMsg.data[2] = ((I_V12board>> 8) & 0x0F);
										CAN_TxMsg.data[3] = I_V12board & 0xFF;
										CAN_TxMsg.data[4] = ((I_V12motor>> 8) & 0x0F);
										CAN_TxMsg.data[5] = I_V12motor & 0xFF;
										CAN_TxMsg.data[6] = ((I_HSM>> 8) & 0x0F);
										CAN_TxMsg.data[7] = I_HSM & 0xFF;
										CAN_wrMsg (&CAN_TxMsg);
										LED1_ON;
										break;
				default:		CAN_TxMsg.id = 0x621;
										CAN_TxMsg.data[0] = 0xAA;				// Voltage message
										CAN_TxMsg.data[1] = CAN_RxMsg.data[0];
										CAN_TxMsg.data[2] = CAN_RxMsg.data[1];
										CAN_TxMsg.data[3] = CAN_RxMsg.data[2];
										CAN_TxMsg.data[4] = CAN_RxMsg.data[3];
										CAN_TxMsg.data[5] = CAN_RxMsg.data[4];
										CAN_TxMsg.data[6] = CAN_RxMsg.data[5];
										CAN_TxMsg.data[7] = CAN_RxMsg.data[6];
										CAN_wrMsg (&CAN_TxMsg);
										LED1_ON;
										break;
				}
				CAN_TxRdy = 0;
			}
			
      CAN_RxRdy = 0;
      V12board	= CAN_RxMsg.data[4];
			V12motor	= CAN_RxMsg.data[5];
			HSM			 	= CAN_RxMsg.data[6];
    }
		else {CAN_LED_OFF;	LED1_OFF;}
		
		for(b = 0; b <= 0x00F; b++){
					
			for(a = 0; a <= 0x0FFF; a++);
			
		} 
		CAN_LED_OFF;
		LED1_OFF;
		
	}
}
