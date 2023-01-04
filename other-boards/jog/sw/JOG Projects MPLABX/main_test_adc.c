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


#include "UserParms.h"
//#include "UART_JOG.h"
#include "UART_JOG.h"
//definition for varible used for testing purposes
//#define OSC_TEST
//#define UART_TEST
//#define SCREEN
//#define ADC_TEST
//#define UART
//#define BUTTON

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
_FICD(ICS_PGD1 & JTAGEN_OFF); // & COE_ON ); //BKBUG_OFF

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


void SetupPorts_ADC1(void)
{
<<<<<<< .mine
	//turn off the module ADC
=======
	TRISA=0x00FF;
	
>>>>>>> .r447
	AD1CON1 = 0;
	//select sample clock source
	AD1CON1bits.SSRC=0;
	//form of the result integer signed
	AD1CON1bits.FORM = 1;
	AD1CON2 = 0x0000;
<<<<<<< .mine
	AD1CON3 = 0x0002;
=======
	AD1CON2bits.VCFG=0b1;  //vref in an0 e an1
    AD1CON3bits.SAMC = 31;		// Auto Sample Time = 2*Tad
	AD1CON3bits.ADCS = 0x1f;		// ADC Conversion Clock Tad=Tcy*(ADCS+1)=
	AD1CON1bits.FORM = 0; 
>>>>>>> .r447
	AD1CSSL = 0;
<<<<<<< .mine

	AD1PCFGL = 0b11110011;
	AD1CHS0= 0x0101; //Connect RB7/AN7 as CH0 input ..
=======
			
    IFS0bits.AD1IF = 0; // reset ADC interrupt flag
    IEC0bits.AD1IE = 0;			// Disable A/D interrupt
  	//AD1CHS0/AD1CHS123: A/D Input Select Register
    AD1CHS0bits.CH0SA = 4;		// MUXA +ve input selection (AN0) for CH0
	AD1CHS0bits.CH0NA = 0;		// MUXA -ve input selection (Vref-) for CH0
 
 //       AD1CHS123bits.CH123SA = 0;	// MUXA +ve input selection (AN0) for CH1
 //		AD1CHS123bits.CH123NA = 0;	// MUXA -ve input selection (Vref-) for CH1
>>>>>>> .r447

//AD1PCFGH/AD1PCFGL: Port Configuration Register
	AD1PCFGL=0xffff;	// Set as digital
	AD1PCFGLbits.PCFG0 = 1;		// AN0 as Analog Input
//	AD1PCFGLbits.PCFG1 = 1;		// AN1 as Analog Input
	AD1PCFGLbits.PCFG4 = 1;		// AN4 as Analog Input
	AD1PCFGLbits.PCFG5 = 1;		// AN5 as Analog Input
    AD1CON1bits.ASAM = 1;
	AD1CON1bits.ADON = 1; // turn ADC ON
}

	int result[1024];


int main(void)
{	

	int i=0;
	oscConfig();
	SetupPorts_ADC1();
	TRISBbits.TRISB7=0;
 #ifdef OSC_TEST
	{
		while(1)
		{
			wait_ms(1000);	
			PORTBbits.RB7=!PORTBbits.RB7;
		}
	}
#endif   
	while(1)
		{

			//start sampling and holding the ADC inputs
		//	AD1CON1bits.DONE = 0;
		//	wait_s(1);
			
			/*//ConvertADC1();
			while( 0 == AD1CON1bits.DONE );
			for(i =0;i<15;i++)
			{
				result[i] = ReadADC1(i);
			}	*/
		//	AD1CON1bits.SAMP = 1;
			for (i=0;i<16;i++)
{ 
//			AD1CON1bits.SAMP = 1;
		    wait_ms(100);
  //         	AD1CON1bits.SAMP = 0;
			PORTBbits.RB7=!PORTBbits.RB7;
//			while (!AD1CON1bits.DONE);// conversion done?
//			result[i] = (int)ADC1BUF0; // yes then get ADC value
		
}

		}
}
