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
#include <spi.h>
#include <uart.h>
#include <p33FJ128MC804.h>
#include <libpic30.h>
#include <dsp.h>
#include <libq.h>
#include <timer.h>
#include <adc.h>
#include <pwm.h>
#include <qei.h>
//#include <pmp.h>

//typedef unsigned short WORD;


#include "C_Goldelox\Include\Goldelox_const4D.h"

#include "UserParms.h"
#include "UART_JOG.h"
#include "conf.h"
#include "SPI_JOG.h"
//#include "MC_PWM_JOG.h"
//#include "QEI_JOG.h"
//#include "HALL_JOG.h"

//definition for varible used for testing purposes
//#define OSC_TEST
//#define UART_TEST
//#define SCREEN
//#define SCREEN_TEST
//#define ADC_TEST
#ifdef ADC_TEST
//	#define ADC_TEST_1_CANAL
	#define ADC_TEST_6_CANALS
#endif

//#define MENU_SELECTION
//#define BUTTON
#define SPI_TEST
//#define MOTOR_AND_ENCODER_TEST
//#define QEI_TEST
//#define HALL_TEST

extern int txt_MoveCursor();
extern int putstr();
extern int gfx_Cls();

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
// PWM mode is Port registers PWM high & low active Low
// alternate I2C mapped to SDA1/SCL1
// FPOR power on reset 128ms
_FPOR(PWMPIN_OFF & HPOL_OFF & LPOL_OFF & FPWRT_PWR128);
// Use PGC3/PGD3 for programming and debugging
_FICD(ICS_PGD1 & JTAGEN_OFF); //IMPORTANTISSIMO SE JTAGEN_ON ADC NON FUNZICA

//GLOBALE VARIABLES FOR HALL SENSOR
int HALL[6]={4,2,3,0,5,1};
int sens = 0;
int where_is_rotor;
int where_was_rotor;
int poleAB;
int poleBC;
int poleCA;

//interrupt use for the change on pin for the HALL sensor
void __attribute__ ((__interrupt__)) _CNInterrupt(void)
{
	IFS1bits.CNIF = 0; // Clear CN interrupt
	where_is_rotor = _RC6*4+_RB9*2+_RB8-1;
	if(where_is_rotor==where_was_rotor)
	{
		sens = 0;
	}
	if (where_is_rotor == 6)
	{
		basic_screen_tool(2,WHITE);
			txt_MoveCursor(5,0);
			putstr("ER. HAL 6");
			wait_s(10); 
	}
	if (where_is_rotor == -1)
	{
		basic_screen_tool(2,WHITE);
			txt_MoveCursor(5,0);
			putstr("ER. HAL -1");
			wait_s(10); 
	}
	else
	{
		if(where_was_rotor == 0)
		{
			if(HALL[where_is_rotor]==1)
			{
				sens = 2; //clockwise
			}
			if(HALL[where_is_rotor]==5)
			{
				sens = 1; //counterclockwise
			}
		}
		if (where_was_rotor == 5)
		{
			if(HALL[where_is_rotor]==0)
			{
				sens = 2; //clockwise
			}
			if(HALL[where_is_rotor]==4)
			{
				sens = 1; //counterclockwise
			}
		}	
		else		
		{
			if(HALL[where_is_rotor]==(where_was_rotor-1))
			{
				sens = 1; //counterclockwise
			}
			if(HALL[where_is_rotor]==(where_was_rotor + 1))
			{
				sens = 2; //clockwise
			}
		}
	}		
	where_was_rotor=HALL[where_is_rotor];	
}	

//unsigned int RX_data[3];
void __attribute__ ((__interrupt__)) _SPI1Interrupt(void)
{
	//CloseSPI1();
	IFS0bits.SPI1IF = 0;
//	RX_data[i] = ReadSPI1();
}

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
	char* MENU[6]={"ROIE/L","MOTOR","AEA","CAN","ADC","HALL"};
	
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
		while(ACK_4DSYSTEMS()!=1);
		sendB(Txdata,10);
		while(ACK_4DSYSTEMS()!=1);		
	}	
#endif


#ifdef SCREEN_TEST
	{
		init_screen();
		
		/*BASIC SCREEN SAVER*/
//		init_basic_syntax();
//		MENU0();
		
		/*ADVANCED SCREEN SAVER*/
		init_char_size(2);
		init_color(BLUE);
		//WRITE_STHG();
		splash_screen_selection(&MENU,5);
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
		init_char_size(2);
		init_color(GREEN);
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
			putstr("   ");
			AD1CON1bits.ADON = 0;
			select+=1;
			select=select%6;
		} // repeat
    return 0;
		
	}
#endif

#ifdef BUTTON
	{
		init_screen();
		init_char_size(2);
		init_color(BLUE);
		int J1_button, J2_button, button_touch1, button_touch2;
		TRISB |= 0x0010;
		CNEN1bits.CN1IE = 1; // Enable CN1 pin for interrupt detection
		_CN1PUE=1;
		_CNIP=5;
		IEC1bits.CNIE = 1; // Enable CN interrupts
		IFS1bits.CNIF = 0; // Reset CN interrupt
	}
#endif

#ifdef MENU_SELECTION
	{
		char* ADCValue[2];
		unsigned int ADC_V=530;
		unsigned int MENU_CHOICE;
		//char* MENU_SELECTION[5]={"ROIE/L","MOTOR","AEA","CAN","ADC"};
		char* MENU_RO[5]={"NOT YET","NOT YET","NOT YET","NOT YET","NOT YET"};
		char* MENU_MOT[5]={"NOT YET","NOT YET","NOT YET","NOT YET","NOT YET"};
		char* MENU_AEA[5]={"ENC. VALUES"};
		char* MENU_CAN[5]={"NOT YET","NOT YET","NOT YET","NOT YET","NOT YET"};
		char* MENU_ADC[5]={"NOT YET","NOT YET","NOT YET","NOT YET","NOT YET"};
		int select=0;
		//int select=0;
		TRISB |=0x0008;
		MENU_CHOICE=&MENU;
		
		/*INIT MENU_SELECTION*/
		init_screen();
	    init_char_size(2);
		init_color(WHITE);
		splash_screen_selection(MENU_CHOICE,5);
		
		/*INIT ADC*/
	    AD1CON1 = 0x0000; // SAMP bit = 0 ends sampling ...
		AD1PCFGL = 0xFFDF; // AN0 = analog
		// and starts converting
		AD1CHS0 = 0x0005; // Connect AN5 on CH0 input ..
		AD1CSSL = 0;
		AD1CON3 = 0x002; // Manual Sample, Tad = internal 2 Tcy
		AD1CON2 = 0;
		AD1CON1bits.ADON = 1; // turn ADC ON
		
		
		/*provare di avere un MENU_SELCT*/
		init_color(RED);
		txt_MoveCursor(select,0);
		putstr(MENU[select]);
		while (1) // repeat continuously
		{
			//if(check_state_buttons()!=
			AD1CON1bits.SAMP = 1; // start sampling ...
			wait_us(100);
			AD1CON1bits.SAMP = 0; // start Converting
			while (!AD1CON1bits.DONE);// conversion done?
			ADC_V = ADC1BUF0;
			if (ADC_V > 750 || ADC_V < 250)
			{
				if (ADC_V > 750)
				{
					init_color(WHITE);
					txt_MoveCursor(select,0);
					putstr(MENU[select]);
					if (select==0)
					{
						init_color(WHITE);
						txt_MoveCursor(select,0);
						putstr(MENU[select]);
						select=4;
					}
					else select-=1;	
				}
				if (ADC_V <250)
				{
					init_color(WHITE);
					txt_MoveCursor(select,0);
					putstr(MENU[select]);
					select+=1;
					select%=5;	
				}
				init_color(RED);	
				txt_MoveCursor(select,0);
				putstr(MENU[select]);
				wait_ms(100);
			}	
			else
			{
				wait_ms(100);
			}
		}	
    return 0;
	}
#endif

#ifdef SPI_TEST
	{
		int i=0;
		unsigned int RX_Data[2]={0,0};
		char Data_AEA[7]={0};
		//int RX_data[3];
		
		/*SCREEN AS TOOL*/
		init_screen();
		init_color(RED);
		init_char_size(2);
		txt_MoveCursor(5,0);
		
		/*SPIEN*/
		PORTBbits.RB11=1;
		
		//wait_us(50);
		while(1)
		{
			/*Try to fill this following lines into a function receive_SPI(RX_Data[])*/
			SPI1STATbits.SPIEN = 1;
			PORTBbits.RB11=0;
			WriteSPI1(0x0000);// Write data even if not transmitted anything just in order to say OK start opening reception and transmition

			while(DataRdySPI1()==0);	//wait for data reception
			RX_Data[0] = ReadSPI1();
			wait_us(10);
			if (DataRdySPI1()==0)		//receive other bits? (lat 2 bits - if nothing means 0 received)
			{
				RX_Data[1] = ReadSPI1();
				if (RX_Data[1]==0xFFFF)
					RX_Data[1]=0;
			}
			
			PORTBbits.RB11=1;
			SPI1STATbits.SPIEN = 0;
			wait_ms(10);
			Nop();
			/*Check bits for integrity value - int CheckSPIdatas(RX_Data) if OK do print*/
			if ((RX_Data[0]&&0x0006!=0x2)||(RX_Data[0]&&0x0006!=0x4))
			{
				RX_Data[0]=RX_Data[0]>>4;
				RX_Data[0]&=0x0FFF;
				
				/*Try to put this part of code into function print_receive_value_SPI()*/
				sprintf(Data_AEA,"%d",RX_Data[0]);
				txt_MoveCursor(5,0);
				putstr(Data_AEA);
				putstr("   ");
			}
		}
	}
#endif

#ifdef MOTOR_AND_ENCODER_TEST
	{
		/*DISPLAY STUFFS ON SCRREEN*/
		basic_screen_tool(2,WHITE);
		
		/*START MODULE*/	
		P1TCONbits.PTEN=1;		
		/*MOT_ENABLE*/	
		PORTCbits.RC2=1;
		
		/*PWM*/
		while(1)
		{
			//P1DC1+=0x100;		
		}
	}
#endif

#ifdef QEI_TEST
	{
		//DISPLAY STUFFS ON SCRREEN
		basic_screen_tool(2,WHITE);
		
		char DATA2SCREEN[7]={0};	
		unsigned int pos_value;
		int i =0;
		while (1)
		{
			pos_value = ReadQEI1();
			//Try to put this part of code
			sprintf(DATA2SCREEN,"%d",pos_value);
			txt_MoveCursor(0,0);
			putstr(DATA2SCREEN);
			putstr("   ");
//			if (i==0)
//			{
//				i=1;
//				/*START MODULE PWM CONTROL*/	
//				P1TCONbits.PTEN=1;		
//				/*ENABLE OUTPUT FOR THE POWER H-BRIDGE*/	
//				PORTCbits.RC2=1;
//				P1DC1+=0x100;  
//	    	}
		 }   	 	
	    CloseQEI1();
	    return 0;
	}
#endif

#ifdef HALL_TEST
	{
		#define screen_debug
		//DISPLAY STUFFS ON SCRREEN
		basic_screen_tool(2,WHITE);
		//_PMPEN=1;
		char DATA2SCREEN[7]={0};
		_RP22R = 0b00000;
		//pins selection of the HALL connector
		_TRISC6 = 1;	//pole AB - CN18
		_TRISB9 = 1;	//pole BC - CN21
		_TRISB8 = 1;	//pole CA - CN22
		CNEN2 = 0x0064;	//CN Enable registry 2 from CN30 to CN16
		wait_ms(1);
		poleAB = _RC6;
		poleBC = _RB9;
		poleCA = _RB8;
		where_was_rotor = poleAB*4+poleBC*2+poleCA-1;
		where_is_rotor = where_was_rotor;
		
		//enable interrupts for CN
		IFS1bits.CNIF = 0;
		IEC1bits.CNIE=1;	
		
		//INVITATION MESSAGE FOR ENTERING IN THIS MODE
		txt_MoveCursor(0,0);
		putstr("WELCOME 2");
		txt_MoveCursor(1,0);
		putstr("HALL SENS.");
	
		#ifdef screen_debug
		txt_MoveCursor(2,0);
		putstr("AB");
		sprintf(DATA2SCREEN,"%d",poleAB);
		txt_MoveCursor(2,4);
		putstr(DATA2SCREEN);
		txt_MoveCursor(3,0);
		putstr("BC");
		sprintf(DATA2SCREEN,"%d",poleBC);
		txt_MoveCursor(3,4);
		putstr(DATA2SCREEN);
		txt_MoveCursor(4,0);
		putstr("CA");
		sprintf(DATA2SCREEN,"%d",poleCA);
		txt_MoveCursor(4,4);
		putstr(DATA2SCREEN);
		#endif
		
		while(1)
		{
			if(_RC6 != poleAB)
			{
				poleAB = _RC6;
				#ifdef screen_debug
				sprintf(DATA2SCREEN,"%d",poleAB);
				txt_MoveCursor(2,4);
				putstr(DATA2SCREEN);
				#endif
			}
			if(_RB9 != poleBC)
			{
				poleBC = _RB9;
				#ifdef screen_debug
				sprintf(DATA2SCREEN,"%d",poleBC);
				txt_MoveCursor(3,4);
				putstr(DATA2SCREEN);
				#endif
			}
			if(_RB8 != poleCA)
			{
				poleCA = _RB8;
				#ifdef screen_debug
				sprintf(DATA2SCREEN,"%d",poleCA);
				txt_MoveCursor(4,4);
				putstr(DATA2SCREEN);
				#endif
			}
			
			if (sens == 0)
			{
				txt_MoveCursor(6,0);
				putstr("STOP");
				continue;
			}
			if (sens == 1)
			{
				txt_MoveCursor(6,0);
				putstr("CCLOCLWISE");
				continue;		
			}
			if (sens == 2)
			{
				txt_MoveCursor(6,0);
				putstr("CLOCLWISE");
				continue;	
			}
		}
	}
#endif

#ifdef UART_TEST
	{		
    	CloseUART1();
	}
#endif

#ifdef SPI_TEST
	{
		CloseSPI1();
	}
#endif
	
}
