/*~|-_-|~**~-_-~**~-_-~**~-_-~**~-_-~**~-_-~**~-_-~*
 * Authors : JENVRIN Julien & Marco Maggiali
 * Company Name : Italian Institute of Technology
 * Starting Date: 03/02/2014
 * Program Name: JOG_MAIN
 * Description : project which has the goal to test thee serial communication on the dsPic33F128MC804 but which can be set up for another kind of device
 */

/* Firmware version 1.0 */
// 04-06-2015  
//
// Julien

/* Firmware version 1.1 */
// 05-06-2015  
//
//Maggia: few changes in the menus
//

/* Firmware version 1.2 */
// 09-06-2015  
//
//Maggia: solve some bugs in the menu
//

/* Firmware version 1.3 */
// 09-08-2015  
//
//Julien: add tense proximal joint
//

/* Firmware version 1.4 */
// 19-08-2015  
//
//Julien: brushless without hall sensor ready
//

/* Firmware version 1.5 */
// 09-10-2015  
//
//Julien: inconsistency in between Brushless w/o HS and w HS
//

/* Firmware version 1.6 */
// 21-01-2016  
//
//Julien: everything alright now
//

/* Firmware version 1.7
 * 29-02-2016
 * Author : Double Jay
 * adding features:
 * 	- new menu for BLESS_MOTOR WO HALL
 *  - selection of the tension needed to spin at a certain amount of rpm
 */

/* Firmware version 1.8
 * 03-08-2017
 * Author : Marco Maggiali
 * adding features:
 * 	- reading of the index and the PULSE PER REV
 */

#ifndef __dsPIC33F__
#define __dsPIC33F__
#endif


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



#include <dma.h>

#include "C_Goldelox\Include\Goldelox_const4D.h"

#include "UserParms.h"
#include "UART_JOG.h"
#include "conf.h"
#include "SPI_JOG.h"
#include "MC_PWM_JOG.h"
#include "QEI_JOG.h"
#include "CAN_JOG.h"
#include "ecan.h"
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


/* ECAN message buffer*/
/* CAN Message Buffer Configuration */
#define  ECAN1_MSG_BUF_LENGTH 	16
typedef unsigned int ECAN1MSGBUF [ECAN1_MSG_BUF_LENGTH][8];	
ECAN1MSGBUF  BufferA __attribute__((space(dma),aligned(ECAN1_MSG_BUF_LENGTH*16)));
ECAN1MSGBUF  BufferB __attribute__((space(dma),aligned(ECAN1_MSG_BUF_LENGTH*16)));
//unsigned int  __attribute__((space(dma),aligned(8*16)));
// ECAN1MSGBUF ecan1msgBuf __attribute__((space(dma),aligned(ECAN1_MSG_BUF_LENGTH*16)));
//unsigned int BufferB[8][8] __attribute__((space(dma),aligned(8*16)));

#define MAIN_MENU 0
#define MOTOR_MENU 1
#define SENSOR_MENU 2
#define SPI_MENU 3
#define QEI_MENU 4
#define HALL_MENU 5
#define ADC_MENU 6
#define ROIE_L_MENU 7
#define DC_M_MENU 8
#define BLESS_MENU 9
#define CAN_4_BLESS_MENU 10
#define BLESS_WO_HALL_RPM_MENU 11
#define DCM_TENS_PROX_MENU 12
#define DCM_MOVE_IT_MENU 13
#define QEI_ENC_MAN_MENU 14
#define BLESS_WO_HALL_TENSION_MENU 15
#define FIRMWARE_MENU 55

#define SPI 1
#define QEI 2
#define HALL_T 3
#define ADC 4
#define CAN_4_BLESS 5
#define CAN_4_BLESS_WO_HALL 6
#define DCM_TENS_PROX 7
#define QEI_ENC_MAN 8
#define BLESS_WO_HALL_RPM 9
#define BLESS_WO_HALL_TENSION 10

#define MOTOR_AND_ENCODER_TEST 55
#define OUT -1

//for CAN line
#define  dataarray 0x1820

extern void txt_MoveCursor();
extern void putstr();
extern void gfx_Cls();
extern void txt_FGcolour();


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
_FPOR(PWMPIN_ON & HPOL_OFF & LPOL_OFF & FPWRT_PWR128);
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
unsigned int encoder_count_cur;

//GLOBALE VARIABLE FOR MENU SELECTION
int select = 0;
int change_menu = 0;
int mode = 0;
int menu = -1;
//char* test="";
int test = -1;
int fois = 0;
int change = 1; //because when CN interrupt is launched the level is high on pin RA4
char DATA2SCREEN[7]={0};
float ratio = 0.0;
int x;

int ADC_DEFAULT=512;
float VOLT =0.0;
int HALF_RANGE;

/*commands send on CAN Line to move BLESS MOTORS*/
unsigned char get_firmware[8] =  		{0x5B,0x09,0x09,0x00,0x00,0x00,0x00,0x00};
unsigned char V3[8] =  					{0x77,0x00,0x00,0xE0,0x00,0x00,0x08,0x00};
unsigned char V1[8] = 			 		{0x77,0x02,0x00,0xE0,0x00,0x00,0x08,0x00};
unsigned char open_loop[8] =     		{0x09,0x50,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char PID_value[8] = 			{0x65,0x08,0x00,0x02,0x00,0x00,0x00,0x0A};
unsigned char TEST_value[8] = 			{0x09,0xB3,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char idle[8] =          		{0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char force_idle[8] =          	{0x09,0x09,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char set_PWM[8] = 		 		{0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char current_limit[8] = 		{0x48,0x00,0x14,0x00,0x00,0x00,0x00,0x00};
unsigned char mode_speed[8] =    		{0x09,0x0A,0x10,0x00,0x00,0x00,0x00,0x00};
unsigned char _6_round_per_min[8] =		{0x17,0x90,0xF7,0xD0,0x07,0x00,0x00,0x00};
unsigned char _3_round_per_min[8] =  	{0x17,0xC8,0xFB,0xD0,0x07,0x00,0x00,0x00};
unsigned char _1_round_per_min[8] =  	{0x17,0x98,0xFE,0xD0,0x07,0x00,0x00,0x00};
unsigned char round_per_min[8] =  		{0x17,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char O_round_per_min[8] =  	{0x17,0x68,0x01,0xD0,0x07,0x00,0x00,0x00};
unsigned char T_round_per_min[8] =  	{0x17,0x38,0x04,0xD0,0x07,0x00,0x00,0x00};
unsigned char S_round_per_min[8] =  	{0x17,0x70,0x08,0xD0,0x07,0x00,0x00,0x00};


//interrupt use for the change on pin for the HALL sensor
void __attribute__ ((interrupt,no_auto_psv)) _CNInterrupt(void)
{
	fois+=1;
    if(_RC7!=1)  // CHECK THE INDEX OF THE ENCODER 
	{
        encoder_count_cur =POS1CNT ;   
        POS1CNT=0;
        IFS1bits.CNIF = 0; // Clear CN interrupt
	}
    
	if(test == HALL_T)
	{
		where_is_rotor = _RC6*4+_RB9*2+_RB8-1;
		if(_RA3!=1)
		{
			Nop();
		}
		else if(where_is_rotor==where_was_rotor)
		{
			//sens = 0;
			//where_was_rotor=HALL[where_is_rotor];
		}
		else if (where_is_rotor == 6)
		{
			//gfx_Cls();
			basic_screen_tool(1,RED);
			txt_MoveCursor(0,0);
			putstr("ERROR HALL 6");
			txt_MoveCursor(2,0);
			putstr("1 1 1");
			txt_MoveCursor(3,0);
			putstr("detected");	
			for (x=5;x>0;x--)
			{
				txt_MoveCursor(4,0);
				putstr("wait ");
				sprintf(DATA2SCREEN,"%d",x);
				putstr(DATA2SCREEN);
				putstr("S");
				wait_s(1);	
			}

		txt_MoveCursor(2,0);
		putstr("                ");
		txt_MoveCursor(3,0);
		putstr("                ");
		txt_MoveCursor(4,0);
		putstr("                ");

    	txt_FGcolour(YELLOW);
		txt_MoveCursor(0,0);
		putstr("TURN MANUALLY THE ");
		txt_MoveCursor(1,0);
		putstr("MOTOR CW and CCW");
		txt_FGcolour(WHITE);
		wait_ms(20);
		txt_MoveCursor(3,0);
		putstr("AB");
		sprintf(DATA2SCREEN,"%d",poleAB);
		txt_MoveCursor(3,4);
		putstr(DATA2SCREEN);
		txt_MoveCursor(4,0);
		putstr("BC");
		sprintf(DATA2SCREEN,"%d",poleBC);
		txt_MoveCursor(4,4);
		putstr(DATA2SCREEN);
		txt_MoveCursor(5,0);
		putstr("CA");
		sprintf(DATA2SCREEN,"%d",poleCA);
		txt_MoveCursor(5,4);
		putstr(DATA2SCREEN);
		txt_FGcolour(YELLOW);
		wait_us(40);
		txt_MoveCursor(9,0);
		putstr("CLICK TO EXIT");
 
		}
		else if (where_is_rotor == -1)
		{
			basic_screen_tool(1,RED);
			txt_MoveCursor(4,0);
			putstr("ER. HAL -1");
			txt_MoveCursor(5,0);
			putstr("0 0 0");
			txt_MoveCursor(6,0);
			putstr("detected");
			wait_s(5); 
			txt_MoveCursor(0,0);
			putstr("            ");
			txt_MoveCursor(2,0);
			putstr("            ");
			txt_MoveCursor(3,0);
			putstr("            ");	
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
			where_was_rotor=HALL[where_is_rotor];
		}		
		
	}

	if (_RA3 != 1)
	{
		wait_ms(50);
		if(_RA3 != 1)
		{
			//change = 0;
			if(test == QEI || test == ADC || test == SPI || test == HALL_T || test == CAN_4_BLESS || test == BLESS_WO_HALL_TENSION || test == DCM_TENS_PROX || test == QEI_ENC_MAN || test == MOTOR_AND_ENCODER_TEST)
			{
				test = OUT;
				change_menu = 1;
				menu = MAIN_MENU;
				while(_RA3 != 1)
				{Nop();}
				wait_ms(100);
			}

			else if(menu == MAIN_MENU /*&& change ==0*/)
			{
				if (select == 1)
				{
					menu = MAIN_MENU;
				}
				else if (select == 2)
				{
					menu = MOTOR_MENU;
				}
				else if (select == 3)
				{
					menu = SENSOR_MENU;
				}
				//select = 0;
				//change = 1;
				change_menu = 1;
				while(_RA3 != 1)
				{Nop();}
				wait_ms(100);
			}

			else if(menu == MOTOR_MENU /*&& change ==0*/)
			{
				if (select == 1)
				{
					menu = BLESS_MENU;
				}
				else if (select == 2)
				{
					menu = DC_M_MENU;//DC_M_MENU;
				}
				else if (select == 3)
				{
					menu = MAIN_MENU;
				}
				//select =0;
				//change = 1;
				change_menu = 1;
				while(_RA3 != 1)
				{Nop();}
				wait_ms(100);
			}

			else if(menu == BLESS_MENU /*&& change ==0*/)
			{
				if (select == 1) // TEST 1 HALL test
				{
					menu = HALL_MENU;
				}
				else if (select == 2) // TEST 2 Motor with HALL sensors
				{
					menu = CAN_4_BLESS_MENU;
				}
				else if (select == 3) //TEST 3 -> motor without HALL
				{
					menu = BLESS_WO_HALL_RPM_MENU;
				}
				else if (select == 4) //EXIT
				{
					menu = MAIN_MENU;
				}
				//select = 0;
				//change = 1;
				change_menu = 1;
				while(_RA3 != 1)
				{Nop();}
				wait_ms(100);
			}
			
			else if(menu == DC_M_MENU /*&& change ==0*/)
			{
				if (select == 1) // MOVE IT
				{
					menu = DCM_MOVE_IT_MENU;
				}
				else if (select == 2) // ENCODER VALUES
				{
					menu = QEI_ENC_MAN_MENU;
				}
				else if (select == 3)
				{
					menu = DCM_TENS_PROX_MENU;
				}
				else if (select == 4) //TENS PROX JOINT
				{
					menu = MAIN_MENU;
				}
				//select = 0;
				//change = 1;
				change_menu = 1;
				while(_RA3 != 1)
				{Nop();}
				wait_ms(100);
			}
						
			else if(menu == SENSOR_MENU /*&& change ==0*/)
			{
				if (select == 1)
				{
					menu = SPI_MENU;//"SPI_TEST";
				}
				else if (select == 2)
				{
					menu = QEI_MENU;
				}
				else if (select == 3)
				{
					menu = HALL_MENU;
				}
				else if (select == 4)
				{
					menu = MAIN_MENU;
				}
				else if (select == 5)
				{
					menu = MAIN_MENU;
				}
				//select = 0;
				//change = 1;
				change_menu = 1;
				while(_RA3 != 1)
				{Nop();}
				wait_ms(100);
			}
			else if(menu == QEI_MENU /*&& change == 0*/)
			{		
				if (select == 0)
				{
					menu = QEI_ENC_MAN_MENU;
				}
				else if (select == 1)
				{
					menu = QEI_ENC_MAN_MENU;
				}
				else if (select == 2)
				{
					menu = MAIN_MENU;
				}
				//select = 0;
				//change = 1;
				change_menu = 1;
				while(_RA3 != 1)
				{Nop();}
				wait_ms(100);
				
			}
			else if (test == BLESS_WO_HALL_RPM)
			{
				test = OUT;
				change_menu = 1;
				menu = BLESS_WO_HALL_TENSION_MENU;
				while(_RA3 != 1)
				{Nop();}
				wait_ms(100);
			}	
		}
		if(_RA3==1)
		{
			IFS1bits.CNIF = 0; // Clear CN interrupt
			//wait_ms(250);
		}
	}
	else
	{
		IFS1bits.CNIF = 0; // Clear CN interrupt
		//wait_ms(250);
	}		
}	

//unsigned int RX_data[3];
void __attribute__ ((interrupt,no_auto_psv)) _SPI1Interrupt(void)
{
	//CloseSPI1();
	IFS0bits.SPI1IF = 0;
//	RX_data[i] = ReadSPI1();
}

void __attribute__ ((interrupt,no_auto_psv)) _QEI1Interrupt(void)
{
	
     if (QEI1CONbits.UPDN==1)
    {
       // POS1CNT = 0;
    }
    if (QEI1CONbits.INDX==1)
    {      
    }
    IFS3bits.QEI1IF = 0;    /* Clear QEI interrupt flag */ 
}

void __attribute__((__interrupt__,no_auto_psv)) _C1Interrupt(void)
{
	/* Only the Transmit Message, Receive 
	 * Message Events and Error flags are processed. You can
	 * check for the other events as well.*/
	
	_C1IF = 0;
	
	if(C1INTFbits.TBIF == 1)
	{
		/* Transmit done. Set the flag so that
		 * the main application loop knows that
		 * the message was transmitted */

		C1INTFbits.TBIF = 0;
	}
	

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

			wait_ms(1000);	
			PORTBbits.RB7=!PORTBbits.RB7;
            wait_ms(1000);	
            PORTBbits.RB7=!PORTBbits.RB7;
            wait_ms(1000);	


{
		//int i=0;
		//unsigned char buf[10]={0};
		//char ReceivedChar;
		//unsigned char byte = 'C';
		//unsigned char Txdata[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','O','P','Q','R','U','\0'};
//		char Txdata[] = {0xFF,0xCC,0x00,0x00,0x00,0x00,0x00,0x23,0x1B,0x10,'\0'};
		Clear_Read_Buffer();
		wait_ms(1);
		gfx_Cls();
		//while(ACK_4DSYSTEMS()!=1);
		//sendB(Txdata,10);
		//while(ACK_4DSYSTEMS()!=1);		
	}	

            
// CAN SETUP    /////////////////////////////////////////////////////////////

	//position of BufferA and B in RAM memory
	unsigned int sta_address0,stb_address0;
	sta_address0 = __builtin_dmaoffset(&BufferA);
	stb_address0 = __builtin_dmaoffset(&BufferB);

	// clocking and sampling init
	CAN1_clock_config();

	CAN1_reset_interrupt_flags();

	/*Initialisation DMA0 for ECAN1 module TX*/
	unsigned int config0, irq0, pad_address0, count0;


	config0 = DMA0_MODULE_OFF & DMA0_SIZE_WORD &
              DMA0_TO_PERIPHERAL & DMA0_INTERRUPT_BLOCK &
              DMA0_NORMAL & DMA0_PERIPHERAL_INDIRECT &
              DMA0_CONTINUOUS;
	irq0 = DMA0_AUTOMATIC;	//do when ask
	pad_address0 = 0x0442; //pad_address for ECAN1TX
	count0 = 3;
    
	OpenDMA0(config0, irq0, sta_address0, stb_address0, pad_address0, count0);

    DMA0REQ = 70; // Select ECAN1TX as DMA Request source
	//DMA0REQbits.FORCE = 1;
	_DMA0IE	= 0;	
   	_DMA0IF = 0;
    DMA0CONbits.CHEN = 1; // Enable DMA[/b]
		/*end of init DMA0*/

/////////////////////////////////////////////////////////////////////////////


	int color = RED;
	where_was_rotor = _RC6*4+_RB9*2+_RB8-1;
	wait_s(3); //demanding time for being sure that the screen responds to commands
	int set_once = 0;
		
	//MAIN MENU SELECTION
	unsigned char* MENU_MAIN[16]={"  ","UPDATE FIRMWARE","TEST MOTORS","TEST SENSORS","            ","             ","             ","use left joystick ","for select & click","               ", " "," "," ", " JOG FIRMWARE 1.8",  "2FOC FIRMWARE 1.6"," "};
	int MENU_MAIN_LGTH = 16;
	//MENU LEVEL -1
	unsigned char* MENU_SENSORS[14]={" ", "SPI","QEI","HALL","ADC CONV.","            EXIT","                  ","                  ","use left joystick ","for select & click","                  ","                  ","                  ","                  "};
	int MENU_SENSORS_LGTH = 14;
	unsigned char* MENU_MOTOR[13]={" ","BRUSHLESS MOTOR","DC MOTOR","            EXIT","","","                  ","use left joystick ","for select & click","                  ","                  ","                  ","                  "};
	int MENU_MOTOR_LGTH = 13;
//	unsigned char* MENU_UPDATE[2]={"LOAD FIRM.","            EXIT"};
//	int MENU_UPDATE_LGTH = 2;
	//MENU LEVEL -2
//	unsigned char* MENU_SPI[6] = {"AEA ENC.","            EXIT","","","use left joystick ","for select & click",};
//	int MENU_SPI_LGTH = 6;
	unsigned char* MENU_QEI[3] = {"ROIE/L","DC MOT. ENC.","            EXIT"};
	int MENU_QEI_LGTH = 3;
	unsigned char* MENU_BLESS[13] = {" ", "TEST1 HALL SENS","TEST2 MOVE IT", "TEST3 MOVE wo HALL", "            EXIT","","","use left joystick ","for select & click","                  ","                  ","                  ","                  "};
	int MENU_BLESS_LGTH = 13;
	unsigned char* MENU_DCM[12] = {" ", "MOVE IT","READ ENCODER","TENSE PROXIMAL JNT.","            EXIT","","","use left joystick ","for select & click","                  ","                  ","                  "};
	int MENU_DCM_LGTH = 12;
	unsigned char* MENU_BLESS_WO_HALL_RPM[13] = {" ", "Please use the", "left joystick", "to select the", "rotation desired", " ", " ", " ", " ", " ", " ", " ", "RIGHT CLICK 2 EXIT"};
	int MENU_BLESS_WO_HALL_RPM_LGTH = 13;
//	unsigned char* MENU_ADC[5]={"NOT YET","NOT YET","NOT YET","NOT YET","NOT YET"};
//	int MENU_ADC_LGTH = 5;
	unsigned char* MENU_BLESS_WO_HALL_TENSION[13] = {" ", "Please use the", "left joystick", "to select the", "rotation desired", " ", " ", " ", " ", " ", " ", " ", "RIGHT CLICK 2 EXIT"};
	int MENU_BLESS_WO_HALL_TENSION_LGTH = 13;
	unsigned char* MENU[16];		//it will be the replacement MENU NAME for any kind of MENU_...
	int MENU_LGTH;

	int i;
	int rpm_desired = 0;
	
//* ENABLE INTERRUPTS FOR BUTTONS AND ENCODER INDEX	
  
    //enable interrupts for CN29
	_TRISA3 =1;	//RA3 on CN29 so input mode
	CNEN2bits.CN29IE=1;	//CN29 Enable
    
    //enable interrupts for CN16
	_TRISC7 =1;	//RC7 on CN17 so input mode
	CNEN2bits.CN17IE=1;	//CN17 Enable
    
    
	//CNEN2 = 0x0000;
	IFS1bits.CNIF = 0;
	IEC1bits.CNIE=1;
	

	//#define HALL_MODE
	_RP22R = 0b00000;
	//pins selection of the HALL connector
	_TRISC6 = 1;	//pole AB - CN18
	_TRISB9 = 1;	//pole BC - CN21
	_TRISB8 = 1;	//pole CA - CN22


	//-----setup_PORTADC------
	 int ADC_V=530;
	/*INIT ADC*/
	_TRISB3=1; //RB3=AN5
    AD1CON1 = 0x0000; // SAMP bit = 0 ends sampling ...
	AD1PCFGL = 0xFFDF; // AN5 = analog
	// and starts converting
	AD1CHS0 = 0x0005; // Connect AN5 on CH0 input ..
	AD1CSSL = 0;
	AD1CON3 = 0x002; // Manual Sample, Tad = internal 2 Tcy
	AD1CON2 = 0;
	AD1CON1bits.ADON = 1; // turn ADC ON	
	//------end of setupPORTADC	-------

	_TRISC2=0;
	_RC2=1;
	PORTCbits.RC2=0;
	int forever =1;
	int display_menu = 1;
	menu = MAIN_MENU;
	
	while(forever)
	{
		/*INIT MENU_SELECTION*/
		basic_screen_tool(1, WHITE); // meaning - init_screen(); init_char_size(2); init_color(WHITE);

		while(display_menu)
		{
			if(menu == MAIN_MENU)
			{
				MENU_LGTH=MENU_MAIN_LGTH;
				basic_screen_tool(1,WHITE);
				for(i=0;i<MENU_LGTH;i++)
				{
					MENU[i] = MENU_MAIN[i];
					if (i == 4)
					{ 	
						//txt_FGcolour(YELLOW);
					}
					if ((i>4) && (i<=8))
					{	
						txt_MoveCursor(i,0);
						txt_FGcolour(WHITE);
						putstr(MENU[i]);
					}
					if (i>8)
					{
						txt_MoveCursor(i,0);
						txt_FGcolour(GRAY);
						putstr(MENU[i]);
					}			
				}
				txt_FGcolour(WHITE);
				splash_screen_selection(MENU,4);
				//	splash_screen_selection(MENU,MENU_LGTH);	
				change_menu = 0;
			}
					
			else if (menu == SENSOR_MENU)
			{	
				basic_screen_tool(1,WHITE);
				MENU_LGTH = MENU_SENSORS_LGTH;
				for (i = 0; i < MENU_LGTH; i++)
				{
					MENU[i] = MENU_SENSORS[i];
				}
				splash_screen_selection(MENU, MENU_LGTH);
				change_menu = 0;
			}
					
			else if (menu == QEI_MENU)
			{
				basic_screen_tool(1,WHITE);
				MENU_LGTH = MENU_QEI_LGTH;
				for (i = 0; i < MENU_LGTH; i++)
				{
					MENU[i] = MENU_QEI[i];
				}
				splash_screen_selection(MENU, MENU_LGTH);
				change_menu = 0;
			}
					
			else if (menu == MOTOR_MENU)
			{
				basic_screen_tool(1,WHITE);
				MENU_LGTH = MENU_MOTOR_LGTH;
				for (i = 0; i < MENU_LGTH; i++)
				{
					MENU[i] = MENU_MOTOR[i];
				}
				splash_screen_selection(MENU, MENU_LGTH);
				change_menu = 0;
			}
			
			else if (menu == BLESS_MENU)
			{
				basic_screen_tool(1,WHITE);
				MENU_LGTH = MENU_BLESS_LGTH;
				for (i = 0; i < MENU_LGTH; i++)
				{
					MENU[i] = MENU_BLESS[i];
				}
				splash_screen_selection(MENU,MENU_LGTH);
				change_menu = 0;
			}
			
			else if (menu == BLESS_WO_HALL_RPM_MENU)
			{
				basic_screen_tool(1,WHITE);
				MENU_LGTH=MENU_BLESS_WO_HALL_RPM_LGTH;
				for(i=0;i<MENU_LGTH;i++)
				{
					MENU[i]=MENU_BLESS_WO_HALL_RPM[i];
				}
				splash_screen_selection(MENU,MENU_LGTH);
				test = BLESS_WO_HALL_RPM;
				change_menu = 1;
				break;
			}

			else if (menu == BLESS_WO_HALL_TENSION_MENU)
			{
				basic_screen_tool(1,WHITE);
				MENU_LGTH=MENU_BLESS_WO_HALL_TENSION_LGTH;
				for(i=0;i<MENU_LGTH;i++)
				{
					MENU[i]=MENU_BLESS_WO_HALL_TENSION[i];
				}
				splash_screen_selection(MENU,MENU_LGTH);
				test = BLESS_WO_HALL_TENSION;
				change_menu = 1;
				break;
			}
	
			else if (menu == DC_M_MENU)
			{
				basic_screen_tool(1,WHITE);
				MENU_LGTH=MENU_DCM_LGTH;
				for(i=0;i<MENU_LGTH;i++)
				{
					MENU[i]=MENU_DCM[i];
				}
				splash_screen_selection(MENU,MENU_LGTH);
				change_menu = 0;
			}
			
			else if (menu == FIRMWARE_MENU)
			{
				basic_screen_tool(1,WHITE);
				change_menu = 0;
			}
			
			else if (menu == SPI_MENU)
			{
				basic_screen_tool(1,WHITE);
				test = SPI;
				break;
			}
			
			else if (menu == ROIE_L_MENU )
			{
				basic_screen_tool(1, WHITE);
				test = QEI;
				break;
			}
			
			else if (menu == HALL_MENU)
			{
				basic_screen_tool(1, WHITE);
				test = HALL_T;
				break;
			}
			else if (menu == DCM_TENS_PROX_MENU)
			{
				basic_screen_tool(1, WHITE);
				test = DCM_TENS_PROX;
				break;
			}
			else if (menu == CAN_4_BLESS_MENU)
			{
				basic_screen_tool(1, WHITE);
				test = CAN_4_BLESS;
				break;
			}
			else if (menu == DCM_MOVE_IT_MENU || menu == DC_M_MENU)
			{
				basic_screen_tool(1,WHITE);
				test = MOTOR_AND_ENCODER_TEST;
				break;
			}
			else if (menu == QEI_ENC_MAN_MENU)
			{
				basic_screen_tool(1,WHITE);
				test = QEI;
				break;
			}
			select=1;
		
			/*provare di avere un MENU_SELECT*/
			init_color(color);
			txt_MoveCursor(select,0);
			putstr(MENU[select]);
			//color+=0x0010;
	
	
			while (change_menu == 0) // repeat continuously
			{
				//if(check_state_buttons()!=
				AD1CON1bits.SAMP = 1; // start sampling ...
				wait_us(100);
				AD1CON1bits.SAMP = 0; // start Converting
				while (!AD1CON1bits.DONE);// conversion done?
				ADC_V = ADC1BUF0;
				if (ADC_V > 750 || ADC_V < 250)
				{
					wait_ms(100);
					if (ADC_V > 750)
					{
						init_color(WHITE);
						txt_MoveCursor(select,0);
						putstr(MENU[select]);
						if (select==0)
						{
							select=MENU_LGTH-1;
						}
						else select-=1;	
					}
					if (ADC_V <250)
					{
						init_color(WHITE);
						txt_MoveCursor(select,0);
						putstr(MENU[select]);
						select+=1;
	#warning "tapullo!!!"
						select%=6; //MENU_LGTH; The selection is not longer then 5 actually	
					}
					init_color(RED);	
					txt_MoveCursor(select,0);
					putstr(MENU[select]);
					//color+=0x0010;
					
				}	
				else
				{
					wait_ms(100);
				}
				//txt_MoveCursor(6,0);
				//sprintf(MENUX,"%d",menu);
				//putstr(MENUX);
			}// end while(change_menu == 0)
		}// end while(display_menu)

		/*enter in SPI test*/
		if (test == SPI)
		{
			unsigned int RX_Data[2]={0,0};
			char Data_AEA[7]={0};
			
			/*SCREEN AS TOOL*/
			init_screen();
			init_color(YELLOW);
			
			
			txt_MoveCursor(1,0);
			putstr("MOVE THE JOINT");
			txt_MoveCursor(2,0);
			putstr("by hand");
			
			txt_FGcolour(YELLOW);
			wait_us(40);
			txt_MoveCursor(10,0);
			putstr("CLICK TO EXIT");
	
			
			txt_FGcolour(WHITE);
			
			txt_MoveCursor(5,0);
			/*SPIEN*/
			PORTBbits.RB11=1;
			
			//
			while (1)
			{
				/*Try to fill this following lines into a function receive_SPI(RX_Data[])*/
				SPI1STATbits.SPIEN = 1;
				PORTBbits.RB11=0;
				WriteSPI1(0x0000);// Write data even if not transmitted anything just in order to say OK start opening reception and transmition
	
				while(DataRdySPI1()==0);	//wait for data reception
				RX_Data[0] = ReadSPI1();
				wait_us(15);
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
				if (test == OUT)
				{
					break;
				}
			}//end of while loop
		}//end of test SPI
	
	
		else if (test == QEI)
		{
			//DISPLAY STUFFS ON SCRREEN
			basic_screen_tool(1,YELLOW);
			_RC2=1;
			txt_MoveCursor(0,0);
			putstr("Move the motor \n up and down \n by hand");
			txt_MoveCursor(12,0);
			putstr("CLICK TO EXIT");
			txt_FGcolour(WHITE);
			txt_MoveCursor(5,0);
			putstr("Encoder:");
            txt_MoveCursor(6,0);
            txt_FGcolour(YELLOW);
            putstr("PULSE per REV");   
			unsigned int pos_value;
			unsigned int encoder_count;
			
//            int i =0;
			pos_value = 10;
			encoder_count =10;
			while (1)
			{
				if(pos_value!=ReadQEI1() || encoder_count!=encoder_count_cur)
				{
					pos_value = ReadQEI1();
                    
					//Try to put this part of code
					sprintf(DATA2SCREEN,"%d",pos_value);
					txt_FGcolour(WHITE);
					txt_MoveCursor(5,9);
                    putstr("      ");
                    txt_MoveCursor(5,9);
					putstr(DATA2SCREEN);
					putstr("   ");
                   
				}
                if(encoder_count!=encoder_count_cur)
                {
                    encoder_count=encoder_count_cur;
					sprintf(DATA2SCREEN,"%d",encoder_count);					
                    txt_FGcolour(GREEN);
                    txt_MoveCursor(7,9);
                    putstr("       ");
                    txt_MoveCursor(7,9);
                    putstr(DATA2SCREEN);
                } 
				if(test==OUT)
				{
					_RC2=0;
					_PEN1L=0;			
					_PEN1H=0;
					P1TCONbits.PTEN=0;
					//return_2_root_menu();
					break;
				}	
			 }//end of while loop	 	
		}//end of test QEI
	
	
		else if (test == MOTOR_AND_ENCODER_TEST)
		{
			/*DISPLAY STUFFS ON SCRREEN*/
			basic_screen_tool(1,YELLOW);
			_RC2=1;
			txt_MoveCursor(0,0);
			putstr("Move the joystick \n up and down");
			txt_MoveCursor(12,0);
			putstr("CLICK TO EXIT");
			txt_FGcolour(WHITE);
			txt_MoveCursor(4,0);
			putstr("Encoder:");
	 		txt_MoveCursor(7,0);
			putstr("Voltage:");
			unsigned int pos_value;
//			int i =0;
			pos_value = 10;
			//Make sure PWM to zero for side of the motor and deselection of 
			_PEN1L=0;
			_PEN1H=0;
			P1TCONbits.PTEN=1;
			
			AD1CON1bits.SAMP = 1; // start sampling ...
			wait_us(100);
			AD1CON1bits.SAMP = 0; // start Converting			
			while (!AD1CON1bits.DONE);// conversion done?
			ADC_DEFAULT = ADC1BUF0;
			if (ADC_DEFAULT >= 512)
			{
				HALF_RANGE = (1024-ADC_DEFAULT);
			}
			else
			{
				HALF_RANGE = ADC_DEFAULT;	
			}
			if (HALF_RANGE>480)
				HALF_RANGE=480;

			while (1)
			{
				if (pos_value != ReadQEI1())
				{
					pos_value = ReadQEI1();
					//Try to put this part of code
					sprintf(DATA2SCREEN,"%d",pos_value);
					txt_FGcolour(WHITE);
					txt_MoveCursor(4,9);
					putstr(DATA2SCREEN);
					putstr("   ");
				}	
				AD1CON1bits.SAMP = 1; // start sampling ...
				wait_us(100);
				AD1CON1bits.SAMP = 0; // start Converting
				while (!AD1CON1bits.DONE);// conversion done?
				//if(ADC_V!=ADC1BUF0)
				//{
				ADC_V = ADC1BUF0-ADC_DEFAULT;
							
				if (ADC_V>=0) 
				{
					if (ADC_V>HALF_RANGE) ADC_V=HALF_RANGE;
					
					VOLT=12.0/480*ADC_V;	
					sprintf(DATA2SCREEN,"%f",VOLT);
					txt_FGcolour(GREEN);
					txt_MoveCursor(7,8);
					putstr(DATA2SCREEN);
					putstr("  ");
					ratio = (ADC_V)/HALF_RANGE;
					P1DC1=0xFFFF-(ADC_V*136);
					_PEN1L=0;			
					_PEN1H=1;
				}
			    else
				{
					if (ADC_V<=-HALF_RANGE) ADC_V=HALF_RANGE;
					else ADC_V=-ADC_V;
					VOLT=12.0/480*ADC_V;
					sprintf(DATA2SCREEN,"-%f",VOLT);
					txt_FGcolour(GREEN);
					txt_MoveCursor(7,8);
					putstr(DATA2SCREEN);
					putstr("  ");
					ratio = (ADC_V)/HALF_RANGE;
					P1DC1=ADC_V*136;
					_PEN1L=1;			
					_PEN1H=0;
				}
				
				if(test==OUT)
				{
					_RC2=0;
					_PEN1L=0;			
					_PEN1H=0;
					P1TCONbits.PTEN=0;
					//return_2_root_menu();
					break;
				}	
			 }   	 	
		    //CloseQEI1();
		    //return 0;
	
		}
	
	
		else if (test == HALL_T)
		{
			#define screen_debug
			//DISPLAY STUFFS ON SCRREEN
			basic_screen_tool(1,YELLOW);
			//_PMPEN=1;2
	
			poleAB = _RC6;
			poleBC = _RB9;
			poleCA = _RB8;
			where_was_rotor = poleAB*4+poleBC*2+poleCA-1;
			where_is_rotor = where_was_rotor;
			unsigned error_hall=0;
			//enable interrupts for CN
			CNEN2 |= 0x0064;	//CN Enable registry 2 from CN30 to CN16
			IFS1bits.CNIF = 0;
			IEC1bits.CNIE=1;	
			
			//DA FARE LAMPEGGIARE "HALL MENU LOADING"
			
			//INVITATION MESSAGE FOR ENTERING IN THIS MODE
			txt_MoveCursor(0,0);
			putstr("TURN MANUALLY THE ");
			txt_MoveCursor(1,0);
			putstr("MOTOR CW and CCW");
			#ifdef screen_debug
			txt_FGcolour(WHITE);
			wait_ms(20);
			txt_MoveCursor(3,0);
			putstr("AB");
			sprintf(DATA2SCREEN,"%d",poleAB);
			txt_MoveCursor(3,4);
			putstr(DATA2SCREEN);
			txt_MoveCursor(4,0);
			putstr("BC");
			sprintf(DATA2SCREEN,"%d",poleBC);
			txt_MoveCursor(4,4);
			putstr(DATA2SCREEN);
			txt_MoveCursor(5,0);
			putstr("CA");
			sprintf(DATA2SCREEN,"%d",poleCA);
			txt_MoveCursor(5,4);
			putstr(DATA2SCREEN);
			txt_FGcolour(YELLOW);
			wait_us(40);
			txt_MoveCursor(11,0);
			putstr("CLICK TO EXIT");
			#endif
			if (((poleAB==1 && poleBC==1 && poleCA==1)) || (poleAB==0 && poleBC==0 && poleCA==0))
				{ //there is something not working
					txt_MoveCursor(3,0);
					txt_FGcolour(RED);
					putstr("ERROR \nThe hall sensors\nare not working");
					wait_ms(50);
					putstr("\nplease check the\nconnections");
					wait_ms(50);
					error_hall=1;
				}
			else error_hall = 0;
			while(1)
			{
				
	
				if (_RC6 != poleAB)
				{
					poleAB = _RC6;
					#ifdef screen_debug
					sprintf(DATA2SCREEN,"%d",poleAB);
					txt_MoveCursor(3,4);
					putstr(DATA2SCREEN);
					#endif
				}
				if (_RB9 != poleBC)
				{
					poleBC = _RB9;
					#ifdef screen_debug
					sprintf(DATA2SCREEN,"%d",poleBC);
					txt_MoveCursor(4,4);
					putstr(DATA2SCREEN);
					#endif
				}
				if (_RB8 != poleCA)
				{
					poleCA = _RB8;
					#ifdef screen_debug
					sprintf(DATA2SCREEN,"%d",poleCA);
					txt_MoveCursor(5,4);
					putstr(DATA2SCREEN);
					#endif
				}
				
				if (sens == 0)
				{
					txt_FGcolour(YELLOW);
			        wait_ms(20);
					txt_MoveCursor(9,0);
					if (error_hall==1) {}
					else putstr("PLEASE MOVE");
				//	continue;
				}
				if (sens == 1)
				{
					txt_FGcolour(YELLOW);
			        wait_ms(20);
					txt_MoveCursor(9,0);
					putstr("OK Rotation CCW  ");
				//	continue;		
				}
				if (sens == 2)
				{
					txt_FGcolour(YELLOW);
			        wait_ms(20);
	
					txt_MoveCursor(9,0);
					putstr("OK Rotation CW  ");
				//	continue;	
				}
				if (test == OUT)
				{
					//DA FARE: FUNCTION per fare lampeggiare "back to main menu"
					//return_2_root_menu();
					break;
	
				}
			}
		
		}
	
		else if (test==CAN_4_BLESS)
		{
			basic_screen_tool(1,YELLOW);
			txt_MoveCursor(1,0);
			putstr("Move the joystick\nup and down to\nrotate the motor");
		//	txt_MoveCursor(2,0);
		//	putstr("TEST");
			txt_MoveCursor(10,0);
			putstr("Click to exit");
			AD1CON1bits.SAMP = 1; // start sampling ...
			wait_us(100);
			AD1CON1bits.SAMP = 0; // start Converting			
			while (!AD1CON1bits.DONE);// conversion done?
			ADC_DEFAULT = ADC1BUF0;
			if (ADC_DEFAULT>=512)
			{
				HALF_RANGE=(1024-ADC_DEFAULT);
			}
			else
			{
				HALF_RANGE=ADC_DEFAULT;	
			}
			if (HALF_RANGE>480) HALF_RANGE=480; //limit to 480 to be sure to have enough span up and down 
	//		txt_MoveCursor(10,0);
	//		sprintf(DATA2SCREEN,"%d",HALF_RANGE);
	//		putstr(DATA2SCREEN);
			if (set_once == 0)
			{
				while (C1TR01CONbits.TXREQ0 == 1);
				CAN1SendMessage (get_firmware,3,0x1,0,0,BufferA[0],0);
				C1TR01CONbits.TXREQ0 = 1;
				while (C1TR01CONbits.TXREQ0 == 1);
				CAN1SendMessage (V1,7,0x1,0,0,BufferA[0],0);
				C1TR01CONbits.TXREQ0 = 1;
				while (C1TR01CONbits.TXREQ0 == 1);
				CAN1SendMessage (PID_value,8,0x1,0,0,BufferA[0],0);
				C1TR01CONbits.TXREQ0 = 1;
				while (C1TR01CONbits.TXREQ0 == 1);
				CAN1SendMessage (current_limit,5,0x1,0,0,BufferA[0],0);
				C1TR01CONbits.TXREQ0 = 1;
				while (C1TR01CONbits.TXREQ0 == 1);
				set_once=1;
			}
				
			int percent;
			int disection;
	//		unsigned char data[8]; 
	//		data[0] = 0x12;
	//		data[1] = 0x34;
	
			CAN1SendMessage (force_idle,2,0x1,0,0,BufferA[0],0);
			C1TR01CONbits.TXREQ0 = 1;
			while(C1TR01CONbits.TXREQ0 == 1);
			wait_ms(50);
	
			CAN1SendMessage (open_loop,2,0x1,0,0,BufferA[0],0);
			C1TR01CONbits.TXREQ0 = 1;
			while(C1TR01CONbits.TXREQ0 == 1);
			
			/*Start of getting value from the ADC of the joystick to control the motor PWM*/
			while(1)
			{		
				AD1CON1bits.SAMP = 1; // start sampling ...
				wait_us(100);
				AD1CON1bits.SAMP = 0; // start Converting
				while (!AD1CON1bits.DONE);// conversion done?
				ADC_V = ADC1BUF0-ADC_DEFAULT;
				if (ADC_V>=0) 
				{
					if (ADC_V>HALF_RANGE) ADC_V=HALF_RANGE;
					
			//		VOLT=12.0/470*ADC_V;	
			//		sprintf(DATA2SCREEN,"%f",VOLT);
			//		txt_FGcolour(GREEN);
			//		txt_MoveCursor(7,8);
			//		putstr(DATA2SCREEN);
			//		putstr("  ");
					ratio = (8.0*ADC_V)/HALF_RANGE;
					percent = ratio*12.5;// * 100.0;
					txt_MoveCursor(7,0);
					txt_FGcolour(BLUE);
					putstr("Percentage: ");
					sprintf(DATA2SCREEN,"%d",percent);		
					txt_MoveCursor(7,12);
					putstr(DATA2SCREEN);
					putstr("    ");
					disection=(int)((0x0FFF * ratio)/8);
					set_PWM[1]=(char)(disection>>8);
					set_PWM[0]=(char) (disection);
	
	//				sprintf(DATA2SCREEN,"%02x%02x",set_PWM[1],set_PWM[0]);				
	//				txt_MoveCursor(10,0);
	//				putstr(DATA2SCREEN);
	//				putstr("                       ");
					CAN1SendMessage (set_PWM,8,0x10F,0,0,BufferA[0],0);
					C1TR01CONbits.TXREQ0 = 1;
					while(C1TR01CONbits.TXREQ0 == 1);
				}
			    else
				{
					if (ADC_V <= -HALF_RANGE)
						ADC_V = HALF_RANGE;
					else
						ADC_V=-ADC_V;
	//				VOLT=12.0/470*ADC_V;
	//				sprintf(DATA2SCREEN,"-%f",VOLT);
	//				txt_FGcolour(GREEN);
	//				txt_MoveCursor(7,8);
	//				putstr(DATA2SCREEN);
	//				putstr("  ");
					ratio = (8.0*ADC_V)/HALF_RANGE;
					percent = ratio*12.5;// * 100.0;
					txt_FGcolour(BLUE);
					txt_MoveCursor(7,0);
					putstr("Percentage:-");
					sprintf(DATA2SCREEN,"%d",percent);			
					txt_MoveCursor(7,12);
					putstr(DATA2SCREEN);
					putstr("    ");
	
					disection = 0xF001 + (int)(0x0FFF - ((0x0FFF * ratio)/8));
					set_PWM[1] = (char)(disection>>8);
					set_PWM[1] = set_PWM[1];  //240?
					set_PWM[0] = (char)(disection);
						
	//				sprintf(DATA2SCREEN,"%02x%02x",set_PWM[1],set_PWM[0]);				
	//				txt_MoveCursor(10,0);
	//				putstr(DATA2SCREEN);
	//          	putstr("              ");
	
					CAN1SendMessage(set_PWM,8,0x10F,0,0,BufferA[0],0);
					C1TR01CONbits.TXREQ0 = 1;
					while(C1TR01CONbits.TXREQ0 == 1);
				}
				
				if(test==OUT)
				{
	//				set_PWM[0]=0;
	//				set_PWM[1]=0;
					CAN1SendMessage (force_idle,2,0x1,0,0,BufferA[0],0);
					C1TR01CONbits.TXREQ0 = 1;
					while(C1TR01CONbits.TXREQ0 == 1);
	//				set_once=0;
					break;
				}
			} //end of while(1)
		}// end test CAN_4_BLESS
	
		else if(test == BLESS_WO_HALL_RPM)
		{
			AD1CON1bits.SAMP = 1; // start sampling ...
			wait_us(100);
			AD1CON1bits.SAMP = 0; // start Converting			
			while (!AD1CON1bits.DONE);// conversion done?
			ADC_DEFAULT = ADC1BUF0;
			if (ADC_DEFAULT>=512)
			{
				HALF_RANGE=(1024-ADC_DEFAULT);
			}
			else
			{
				HALF_RANGE=ADC_DEFAULT;	
			}
			if (HALF_RANGE>480) HALF_RANGE=480;
			
			txt_MoveCursor(9,0);
			txt_FGcolour(YELLOW);
			putstr("Speed :     rpm");
			txt_MoveCursor(9,8);
			txt_FGcolour(RED);
			putstr("0 ");
	
			while(1)
			{		
				AD1CON1bits.SAMP = 1; // start sampling ...
				wait_us(100);
				AD1CON1bits.SAMP = 0; // start Converting
				while (!AD1CON1bits.DONE);// conversion done?
				
			    if((ADC1BUF0>1000))
				{
					switch(rpm_desired)
					{
						case 0 :
							rpm_desired = 1;
							txt_MoveCursor(9,8);
							putstr("1 ");
							break;
						case 1 :
							rpm_desired = 3;
							txt_MoveCursor(9,8);
							putstr("3 ");
							break;
						case 3 :
							rpm_desired = 6;
							txt_MoveCursor(9,8);
							putstr("6 ");
							break;
						case -6 :
							rpm_desired = -3;
							txt_MoveCursor(9,8);
							putstr("-3");
							break;
						case -3 :
							rpm_desired = -1;
							txt_MoveCursor(9,8);
							putstr("-1");
							break;
						case -1 :
							rpm_desired = 0;
							txt_MoveCursor(9,8);
							putstr("0 ");
							break;
						default:
							break;
					}
					do
					{
						AD1CON1bits.SAMP = 1; // start sampling ...
						wait_us(1000);
						AD1CON1bits.SAMP = 0; // start Converting			
						while (!AD1CON1bits.DONE);// conversion done?
					}while(ADC1BUF0>1000);
					
				}
				if(ADC1BUF0<100)
				{
					switch(rpm_desired)
					{
						case 0 :
							rpm_desired = -1;
							txt_MoveCursor(9,8);
							putstr("-1");
							break;
						case 1 :
							rpm_desired = 0;
							txt_MoveCursor(9,8);
							putstr("0 ");
							break;
						case 3 :
							rpm_desired = 1;
							txt_MoveCursor(9,8);
							putstr("1 ");
							break;
						case 6 :
							rpm_desired = 3;
							txt_MoveCursor(9,8);
							putstr("3 ");
							break;
						case -3 :
							rpm_desired = -6;
							txt_MoveCursor(9,8);
							putstr("-6");
							break;
						case -1 :
							rpm_desired = -3;
							txt_MoveCursor(9,8);
							putstr("-3");
							break;
						default:
							break;
					}
					do
					{
						AD1CON1bits.SAMP = 1; // start sampling ...
						wait_us(1000);
						AD1CON1bits.SAMP = 0; // start Converting			
						while (!AD1CON1bits.DONE);// conversion done?
					}while(ADC1BUF0<100);
					
				}
				else
				{
					wait_us(1000);
					txt_MoveCursor(9,8);
					sprintf(DATA2SCREEN,"%d",rpm_desired);
					putstr(DATA2SCREEN);
				}
				
				if(test == OUT)
				{
					if (rpm_desired == 0)
						menu = MAIN_MENU;
					break;
				}
			} //end of while(1)
		}//end of test BLESS_WO_HALL_RPM -> selection speed for BLESS_WO_HALL
	
		else if (test == BLESS_WO_HALL_TENSION)
		{
			float volt_desired = 0.0;
			unsigned char rpm_and_tension[8] = {0x17,0x00,0x00,0x00,0x00,0x00,0x00,0x00};		

			if (rpm_desired == 1)
			{
				rpm_and_tension[1] = 0x68;
				rpm_and_tension[2] = 0x01;
			}
			if (rpm_desired == 3)
			{
				rpm_and_tension[1] = 0x38;
				rpm_and_tension[2] = 0x04;
			}
			if (rpm_desired == 6)
			{
				rpm_and_tension[1] = 0x70;
				rpm_and_tension[2] = 0x08;
			}
			if (rpm_desired == -1)
			{
				rpm_and_tension[1] = 0x98;
				rpm_and_tension[2] = 0xFE;
			}
			if (rpm_desired == -3)
			{
				rpm_and_tension[1] = 0xC8;
				rpm_and_tension[2] = 0xFB;
			}
			if (rpm_desired == -6)
			{
				rpm_and_tension[1] = 0x90;
				rpm_and_tension[2] = 0xF7;
			}

			txt_MoveCursor(6,0);
			txt_FGcolour(BLUE);
			putstr("spin :       rpm");
			txt_MoveCursor(6,8);
			sprintf(DATA2SCREEN,"%d ",rpm_desired);		
			putstr(DATA2SCREEN);

			txt_MoveCursor(8,0);
			txt_FGcolour(RED);
			putstr("tension : ");
			txt_MoveCursor(8,8);
			sprintf(DATA2SCREEN,"%d ",volt_desired);		
			putstr(DATA2SCREEN);
			
			// send get_firmware message

			while(C1TR01CONbits.TXREQ0 == 1);
			CAN1SendMessage (get_firmware,3,0x1,0,0,BufferA[0],0);
			C1TR01CONbits.TXREQ0 = 1;
			while(C1TR01CONbits.TXREQ0 == 1);
			CAN1SendMessage (V3,7,0x1,0,0,BufferA[0],0);
			C1TR01CONbits.TXREQ0 = 1;
			while(C1TR01CONbits.TXREQ0 == 1);
			CAN1SendMessage (PID_value,8,0x1,0,0,BufferA[0],0);
			C1TR01CONbits.TXREQ0 = 1;
			while(C1TR01CONbits.TXREQ0 == 1);
			CAN1SendMessage (current_limit,5,0x1,0,0,BufferA[0],0);
			C1TR01CONbits.TXREQ0 = 1;
			while(C1TR01CONbits.TXREQ0 == 1);
			CAN1SendMessage (TEST_value,2,0x1,0,0,BufferA[0],0);
			C1TR01CONbits.TXREQ0 = 1;
			while(C1TR01CONbits.TXREQ0 == 1);	

			while(1)
			{	
				AD1CON1bits.SAMP = 1; // start sampling ...
				wait_us(100);
				AD1CON1bits.SAMP = 0; // start Converting
				while (!AD1CON1bits.DONE);// conversion done?
				if((ADC1BUF0>1000))
				{
					if (volt_desired < 10.0)
						volt_desired += 0.5;
					do
					{
						AD1CON1bits.SAMP = 1; // start sampling ...
						wait_us(1000);
						AD1CON1bits.SAMP = 0; // start Converting			
						while (!AD1CON1bits.DONE);// conversion done?
					}while(ADC1BUF0>1000);
	
				}
				if(ADC1BUF0<100)
				{
					if (volt_desired > 0.0)
						volt_desired -= 0.5;					
					do
					{
						AD1CON1bits.SAMP = 1; // start sampling ...
						wait_us(1000);
						AD1CON1bits.SAMP = 0; // start Converting			
						while (!AD1CON1bits.DONE);// conversion done?
					}while(ADC1BUF0<100);
					
				}

				sprintf(DATA2SCREEN,"%.1f  ",volt_desired);		
				txt_MoveCursor(8,8);
				putstr(DATA2SCREEN);
				int volt_des_hex = (int)((0x7FFF/48) * volt_desired);
				rpm_and_tension[3] = (char)volt_des_hex;
				//sprintf(DATA2SCREEN,"v in hex : 0x%x     ",volt_des_hex);		
				//txt_MoveCursor(8,0);
				//putstr(DATA2SCREEN);
				volt_des_hex = volt_des_hex>>8;
				rpm_and_tension[4] = (char)volt_des_hex;
				//sprintf(DATA2SCREEN,"v in hex : 0x%x     ",volt_des_hex);		
				//txt_MoveCursor(9,0);
				//putstr(DATA2SCREEN);
				//sprintf(DATA2SCREEN,"[4]=0x%x, [3]=0x%x  ",rpm_and_tension[4],rpm_and_tension[3]);
				//txt_MoveCursor(10,0);
				//putstr(DATA2SCREEN);


				CAN1SendMessage (rpm_and_tension,5,0x1,0,0,BufferA[0],0);
				C1TR01CONbits.TXREQ0 = 1;
				while(C1TR01CONbits.TXREQ0 == 1);
	
				if(test==OUT)
				{
					volt_desired = 0.0;
					rpm_desired = 0;
					CAN1SendMessage (round_per_min,5,0x1,0,0,BufferA[0],0);
					C1TR01CONbits.TXREQ0 = 1;
					while(C1TR01CONbits.TXREQ0 == 1);
					CAN1SendMessage (force_idle,2,0x1,0,0,BufferA[0],0);
					C1TR01CONbits.TXREQ0 = 1;
					while(C1TR01CONbits.TXREQ0 == 1);

					break;
				}
			}
		}	
		else if(test==DCM_TENS_PROX)
		{
			_RC2=1; // enable driving motor
			basic_screen_tool(1,YELLOW);
			txt_MoveCursor(1,0);
			putstr("Make sure the motor");
			txt_MoveCursor(2,0);
			putstr("is correctly plugged");
			txt_MoveCursor(3,0);
			putstr("Move the joystick");
			txt_MoveCursor(4,0);
			putstr("up or down to");
			txt_MoveCursor(5,0);
			putstr("block the prox");
			
			txt_FGcolour(WHITE);
			txt_MoveCursor(8,0);
			putstr("Voltage:");
			
			txt_FGcolour(YELLOW);
			txt_MoveCursor(11,0);
			putstr("Click to exit");
			wait_s(1);
			//Make sure PWM to zero for side of the motor and deselection of 
			_PEN1L=0;
			_PEN1H=0;
			P1TCONbits.PTEN=1;
			txt_FGcolour(RED);
			VOLT = 0.0;
			while(1)
			{
				AD1CON1bits.SAMP = 1; // start sampling ...
				wait_us(100);
				AD1CON1bits.SAMP = 0; // start Converting			
				while (!AD1CON1bits.DONE);// conversion done?
				ADC_V = ADC1BUF0;
				if(ADC_V>1000)
				{
					VOLT += 0.5;
					if (VOLT > 12.0)
					{
						VOLT = 12.0;
					}
					sprintf(DATA2SCREEN,"%.2f",VOLT);
					txt_FGcolour(GREEN);
					txt_MoveCursor(8,10);
					putstr(DATA2SCREEN);
					putstr("           ");
					if(VOLT>=0)
					{
						P1DC1=0XFFFF*VOLT/12;
						_PEN1L=1;			
						_PEN1H=0;
					}
					else 
					{
						P1DC1=0XFFFF+(0xFFFF*VOLT/12);
						_PEN1L=0;			
						_PEN1H=1;
					}
					while (ADC_V>600 || test ==OUT)
					{
						AD1CON1bits.SAMP = 1; // start sampling ...
						wait_us(100);
						AD1CON1bits.SAMP = 0; // start Converting			
						while (!AD1CON1bits.DONE);// conversion done?
						ADC_V = ADC1BUF0;
						if(test == OUT)
						{
							_RC2=0;
							_PEN1L=0;			
							_PEN1H=0;
							P1TCONbits.PTEN=0;
							break;
						}
					}
				}
				if(ADC_V<100)
				{
					VOLT = VOLT - 0.5;
					if (VOLT < -12.0)
					{
						VOLT = -12.0;
					}
					sprintf(DATA2SCREEN,"%.2f ",VOLT);
					txt_FGcolour(GREEN);
					txt_MoveCursor(8,10);
					putstr(DATA2SCREEN);
					putstr("         ");
					if(VOLT>=0)
					{
						P1DC1=0XFFFF*VOLT/12;
						_PEN1L=1;			
						_PEN1H=0;
					}
					else 
					{
						P1DC1=0XFFFF+(0xFFFF*VOLT/12);
						_PEN1L=0;			
						_PEN1H=1;
					}
					while(ADC_V<400 || test == OUT)
					{
						AD1CON1bits.SAMP = 1; // start sampling ...
						wait_us(100);
						AD1CON1bits.SAMP = 0; // start Converting			
						while (!AD1CON1bits.DONE);// conversion done?
						ADC_V = ADC1BUF0;
						if(test == OUT)
						{
							_RC2=0;
							_PEN1L=0;			
							_PEN1H=0;
							P1TCONbits.PTEN=0;
							break;
						}
					}
				}	
				if(test==OUT)
				{
					_RC2=0;
					_PEN1L=0;			
					_PEN1H=0;
					P1TCONbits.PTEN=0;
					break;
				}		
			}
		}
		else if(test==QEI_ENC_MAN)
		{
			//DISPLAY STUFFS ON SCRREEN
			basic_screen_tool(1,YELLOW);
			//_RC2=1;
			txt_MoveCursor(0,0);
			putstr("Spin the motor\n with a screw\n driver");
			txt_MoveCursor(12,0);
			putstr("CLICK TO EXIT");
			txt_FGcolour(WHITE);
			txt_MoveCursor(6,0);
			putstr("Encoder:");
			unsigned int pos_value;
			pos_value = 10; //because the first if in the while is dependent from pos_value different from 0;
				
			while (1)
			{
				if(pos_value!=ReadQEI1())
				{
					pos_value = ReadQEI1();
					//Try to put this part of code
					txt_MoveCursor(6,8);
					sprintf(DATA2SCREEN,"%d",pos_value);
					putstr("   ");
				}	
				if(test==OUT)
				{
					break;
				}	
			 }   	 	
		    //CloseQEI1();
		    //return 0;
	
		} //end while(1)
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
		
	} //end while (1)
} //end main()
