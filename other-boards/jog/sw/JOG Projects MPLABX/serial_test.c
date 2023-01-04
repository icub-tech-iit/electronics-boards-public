/*********************************************************************************
author:JENVRIN Julien
company: Italian Institute of Technology
Date: 21/06/2013
program name: serial _test
content: project which has the goal to test thee serial communication on the dsPic33F128MC804 but which can be set up for another kind of device
*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <ecan.h>
#include <uart.h>
#include <p33FJ128MC804.h>
#include <libpic30.h>
#include <dsp.h>
#include <libq.h>
#include <timer.h>
#include <adc.h>

//typedef unsigned short WORD;

//#extern 
//#include "C_Goldelox\Include\Goldelox_Compound4DRoutines.inc"

#include "UserParms.h"
#include "UART_JOG.h"
#include "conf.h"
//definition for varible used for testing purposes
#define UART
//#define OSC_TEST
//#define UART_TEST
//#define SCREEN
//#define ADC_TEST_1_CANAL
//#define ADC_TEST_6_CANALS
#define MENU_SELECTION
//#define BUTTON
extern int txt_MoveCursor();
extern int putstr();


//
// Configuration bits
//
// no Boot sector and write protection disabled
_FBS(BSS_NO_FLASH & BWRP_WRPROTECT_OFF);
// no secure sector and write protection disaabled
_FSS(RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF);
// Code protection disabled
_FGS(GSS_OFF); 
// Clock switching disabled Fail safe Clock Monitor disabled
// Starts from safe internal fast RC
_FOSCSEL(IESO_OFF & FNOSC_FRCPLL); 
// Clock switching enabled and clock monitor disabled, EC external clock, OSCOUT as IOPIN
_FOSC(FCKSM_CSECMD & POSCMD_EC & OSCIOFNC_ON & IOL1WAY_OFF);
// Turn off Watchdog Timer
_FWDT(FWDTEN_OFF);
//_FWDT(WDT_ON & WDTPSA_512 & WDTPSB_1); // WD enabled 1:512*16
// PWM mode is Port registers PWM high & low active high
// alternate I2C mapped to SDA1/SCL1
// FPOR power on reset 128ms
_FPOR(PWMPIN_ON & HPOL_ON & LPOL_ON & FPWRT_PWR128);
// Use PGC3/PGD3 for programming and debugging
_FICD(ICS_PGD1 & JTAGEN_OFF); //IMPORTANTISSIMO SE JTAGEN_ON ADC NON FUNZICA

void oscConfig(void)
{	
	if(OSCCONbits.COSC == 0b011)
	{
	// already running on PLL (set by bootloader)
	// TODO decide wheter to trust the bootloader or
	// to switch back to EC or FRC and reconfigure
		return;
	}
	// dPLL derived in UserParms.h
	PLLFBD = (int)(DPLL * 4 - 2);
	// N1=2
	CLKDIVbits.PLLPOST = 0;
	// N2=2
	CLKDIVbits.PLLPRE = 0;
	PLLFBD = 0x1E;
	__builtin_write_OSCCONH(0x03);    // Initiate Clock Switch to Primary Oscillator (EC) with PLL (NOSC=0b011)
	__builtin_write_OSCCONL(0x01);    // Start clock switching
	
	while(OSCCONbits.COSC != 0b011);  // Wait for PLL to lock
	while(OSCCONbits.LOCK != 1);
}


/*********************************************************************
					Main App
**********************************************************************/
	
int main(void)
{	
	oscConfig();
	SetupPorts();
	wait_s(3); //demanding time for being sure that the screen responds to commands
	
#ifdef OSC_TEST
	{
		while(1)
		{
			wait_ms(1000);	
			PORTBbits.RB7=!PORTBbits.RB7;
		}
	}
#endif

#ifdef  UART_TEST
	{
		//int i=0;
		//unsigned char buf[10]={0};
		//char ReceivedChar;
		//unsigned char byte = 'C';
		//unsigned char Txdata[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','O','P','Q','R','U','\0'};
		char Txdata[] = {0xFF,0xCC,0x00,0x00,0x00,0x00,0x00,0x23,0x1B,0x10,'\0'};
		Clear_Read_Buffer();
		wait_ms(1);
		gfx_Cls();
		while(ACK_4DSYSTEMS()!=1);
		sendB(Txdata,10);
		while(ACK_4DSYSTEMS()!=1);		
	}	
#endif
		
#ifdef SCREEN
	{
		init_screen();
		init_syntax();
		//WRITE_STHG();
		//splash_screen_selection();
		MENU0();
	}
#endif	

#ifdef ADC_TEST_1_CANAL
	{

		char ADCValue[5];
		TRISA=0x00FF;
    
  
	    AD1CON1 = 0x0000; // SAMP bit = 0 ends sampling ...
		AD1PCFGL = 0xFF00; // AN0 = analog
		// and starts converting
		AD1CHS0 = 0x0004; // Connect AN0 as CH0 input ..
		AD1CSSL = 0;
		AD1CON3 = 0x002; // Manual Sample, Tad = internal 2 Tcy
		AD1CON2 = 0;
		AD1CON1bits.ADON = 1; // turn ADC ON
		/*           TEST CHARACTER ON SCREEN
		txt_MoveCursor(4,0);
		char saucisse[4]="AB";
			putstr(saucisse);
			END OF CHARATER ON SCREEN TEST*/
		while (1) // repeat continuously
		{
			AD1CON1bits.SAMP = 1; // start sampling ...
			wait_us(100);
			AD1CON1bits.SAMP = 0; // start Converting
			while (!AD1CON1bits.DONE);// conversion done?
			sprintf(ADCValue,"%d",ADC1BUF0);
		//	itoa (ADC1BUF0,ADCValue,16); // from int to char in hexadecimal
			txt_MoveCursor(5,0);
			putstr("       ");
			txt_MoveCursor(5,0);
			putstr(ADCValue);
		} // repeat
    return 0;
		
	}
#endif

#ifdef ADC_TEST_6_CANALS
	{
		init_screen();
		char ADCValue[5];
		int select=0;
		int AN_select[6]={0,1,4,5,6,7};
		TRISA |=0x03;  //turn AN module for AN0, AN1 resp. RA0, RA1
		TRISB |=0x0C;  //turn AN module for AN4, AN5 resp. RB2, RB3
		TRISC |=0x03;  //turn AN module for AN6, AN7 resp. RC0, RC1
      
	    AD1CON1 = 0x0000; // SAMP bit = 0 ends sampling ... and TURN OFF AN Module
		AD1PCFGL = 0xFF0C; // zero to turn analog pins - AN0,AN1,AN4-7 = analog
		AD1CSSL = 0;
		AD1CON3 = 0x002; // Manual Sample, Tad = internal 2 Tcy
		AD1CON2 = 0;
		
		while (1) // repeat continuously
		{
			AD1CHS0 = AN_select[select];
			AD1CON1bits.ADON = 1;
			AD1CON1bits.SAMP = 1; // start sampling ...
			wait_us(100);
			AD1CON1bits.SAMP = 0; // start Converting
			while (!AD1CON1bits.DONE);// conversion done?
			sprintf(ADCValue,"%d",ADC1BUF0);
		//	itoa (ADC1BUF0,ADCValue,16); // from int to char in hexadecimal
			txt_MoveCursor(select,0);
			putstr(ADCValue);
			AD1CON1bits.ADON = 0;
			select+=1;
			select=select%6;
		} // repeat
    return 0;
		
	}
#endif

#ifdef BUTTON
	{
		int J1_button, J2_button, button_touch1, button_touch2;
		while(1)
		{
			
			
			button_touch1 = PORTB;
			
			button_touch2 = PORTA;
		}


	}
#endif

#ifdef MENU_SELECTION
	{
		char* MENU[5]={"ROIE/L","MOTOR","AEA","CAN","ADC"};
		char ADCValue[5];
		int i;
		TRISB |=0x0008;
	    init_screen();
		init_syntax();
//  		for(i=0;i<5;i++)
//  		{
//	  		txt_MoveCursor(i,0);
//  			putstr(MENU[i]);
//  		}
		splash_screen_selection(*MENU,5);
	    AD1CON1 = 0x0000; // SAMP bit = 0 ends sampling ...
		AD1PCFGL = 0xFF00; // AN0 = analog
		// and starts converting
		AD1CHS0 = 0x0005; // Connect AN0 as CH0 input ..
		AD1CSSL = 0;
		AD1CON3 = 0x002; // Manual Sample, Tad = internal 2 Tcy
		AD1CON2 = 0;
		AD1CON1bits.ADON = 1; // turn ADC ON
		/*           TEST CHARACTER ON SCREEN
		txt_MoveCursor(4,0);
		char saucisse[4]="AB";
			putstr(saucisse);
			END OF CHARATER ON SCREEN TEST*/
		while (1) // repeat continuously
		{
			AD1CON1bits.SAMP = 1; // start sampling ...
			wait_us(100);
			AD1CON1bits.SAMP = 0; // start Converting
			while (!AD1CON1bits.DONE);// conversion done?
			sprintf(ADCValue,"%d",ADC1BUF0);
		//	itoa (ADC1BUF0,ADCValue,16); // from int to char in hexadecimal
			txt_MoveCursor(5,0);
			putstr("       ");
			txt_MoveCursor(5,0);
			putstr(ADCValue);
		} // repeat
    return 0;



	}
#endif


#ifdef UART
	{		
    	CloseUART1();
	}
#endif
	return 0;		
}
