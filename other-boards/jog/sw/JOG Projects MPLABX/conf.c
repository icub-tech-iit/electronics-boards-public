/*********************************************************************************
author:JENVRIN Julien
company: Italian Institute of Technology
Date: 21/06/2013
program name: conf.c
substract: basic functions (time mainly) and pining for the different communication module used for the JOG_project
content: test the serial communication on the dsPic33F128MC804 but which can be set up for another kind of device
*************************************************************************************/

#include <p33FJ128MC804.h>
#include <stdlib.h>
#include <string.h>
#include <uart.h>
#include <spi.h>
#include <adc.h>
//#include <ecan.h>
//#include <pwm12.h>
#include "UART_JOG.h"
#include "SPI_JOG.h"
#include "MC_PWM_JOG.h"
#include "QEI_JOG.h"

typedef signed int SFRAC16;

// Buffers used to store ADC Samples
SFRAC16 ADCBuffer[15] __attribute__((space(dma),aligned(16))); 

#include "C_Goldelox\Include\Goldelox_const4D.h"
#include "C_Goldelox\Include\Goldelox_const4DSerial.h"
#include "C_Goldelox\Include\Goldelox_serial_4dlibrary.h"
#include "C_Goldelox\Include\Goldelox_Compound4DRoutines.inc"
//#include "C_Goldelox\Include\goldelox_types4d.h"



void wait_us(int number)
{	
	int nb_us=0;
	while (nb_us!=7*number)
	{
		nb_us++;
	}
}

void wait_ms(int number)
{	
	int nb_ms=0;
	while (nb_ms!=number)
	{
		wait_us(948);
		nb_ms++;
	}
}

void wait_s(int number)
{	
	int nb_s=0;
	while (nb_s!=number)
	{
		wait_ms(1000);
		nb_s++;
	}
}

void Setup_Pins_4_Push_Buttons(void)
{
	_TRISB2=1;
	_TRISB3=1;
	_TRISC0=1;
	_TRISC1=1;
	_TRISA7=1;
	_TRISA10=1;
}

void SetupPorts_SPI1(void)
{
  // SPI bus pin configuration:
  // Set RP12/RB12 as SPI Data OUTput MOSI as JOG-Board is the Master
  _TRISB12=0;
  RPOR6bits.RP12R = 0b00111;
  
  // Set RP13/RB13 as SPI Data INput MISO as JOG-Board is the Master
  _TRISB13=1;
  RPINR20bits.SDI1R = 13;  // or SDI1R=13;
  
  // Set RP11/RB11 as SPI_/CS
  _TRISB11=0;
  RPOR5bits.RP11R = 0b00000;  //no driven by module
  
  // Set RP10/RB10 as SPI_CLK
  _TRISB10=0;
  RPOR5bits.RP10R = 0b01000;
  SPI1STATbits.SPIEN = 0;	//CloseSPI1();

  IEC0bits.SPI1IE = 0;// Disable the Interrupt
  
  // SPI1CON1 Register Settings
  SPI1CON1bits.DISSCK = 0;	// Internal Serial Clock is Enabled
  SPI1CON1bits.DISSDO = 0;	// SDOx pin is controlled by the module
  SPI1CON1bits.MODE16 = 1;	// Communication is word-wide (16 bits
  SPI1CON1bits.CKE = 1;		// Serial output data changes on transition from Idle clock state to active clock state
  SPI1CON1bits.SSEN = 0;	// CS (called here SS) pin is controlled by the module
  SPI1CON1bits.CKP = 0;		// Idle state for clock is a low level, active state is a high level
  SPI1CON1bits.MSTEN = 1;	// Master mode Enabled
  SPI1CON1bits.SMP = 0;		// Input data is sampled at the end of data output time
  SPI1CON1bits.SPRE = 5;	// Secondary prescaler 3:1
  SPI1CON1bits.PPRE = 1;	// Primary prescaler 16:1
  
  // SPI1CON2 Register Settings
  SPI1CON2bits.FRMEN = 1;	// Framed mode Disabled - non CS used if 1
  SPI1CON2bits.SPIFSD = 0;	//1 = Frame sync pulse input (slave)
  SPI1CON2bits.FRMPOL = 0;	//1 = Frame sync pulse is active-high
  SPI1CON2bits.FRMDLY = 1;	//0 = Frame sync pulse precedes first bit clock
  // SPI1STAT Register Settings
  SPI1STATbits.SPISIDL = 1;	// Continue module operation in Idle mode
  SPI1STATbits.SPIROV = 0;	// No Receive Overflow has occurred
  
  //SPI1BUF = 0x0000;// Write data to be transmitted
  // Interrupt Controller Settings
  IFS0bits.SPI1IF = 0; // Clear the Interrupt Flag
  IEC0bits.SPI1IE = 1;// Enable the Interrupt
  //SPI1STATbits.SPIEN = 1;// Enable SPI module
  
}

void Setup_Pins_4_CAN_module(void)
// config dsPIC pins for CAN usage
{
  // CAN bus pin configuration:
  // Set RPX as output CANTX (valid for both HW revisions)
  RPOR2bits.RP5R = 0b10000;		//0b10000 means C1TX;

  // CAN Rx
  // Connect ECAN1 Receive to RPx
  RPINR26bits.C1RXR = 6;		//where 6 represents RPX in my case RP6
  //RP6 should also be overwritten as input
	_TRISB6=1;

  // CAN_EN pin as output
  _TRISB7=0;
	PORTBbits.RB7=1; //enable CAN communication on transceiver

}


void SetupPorts_UART1(void)
// config dsPIC for UART usage
{
	/* Holds the value of baud register   */
	unsigned int baudvalue;   
	/* Holds the value of uart config reg */
	unsigned int U1MODEvalue;
	/* Holds the information regarding uart	TX & RX interrupt modes */   
	unsigned int U1STAvalue;
	
	// UART bus pin configuration:
	
		// UART TX
		// Set RPX as output U1TX
	RPOR10bits.RP20R = 0b00011;		//in mycase TX is pin RP20;
	//make sure that the pin RP20(=RC4) is set as output
	_TRISC4=0;		//0=output
	
		// UART RX
		// Connect U1RX Receive to RPx
	_U1RXR = 19;		//in my case RX is pin RP19
	//make sure that the pin RP19(=RC3) is set as input
	_TRISC3=1;		//1=input
	CloseUART1();
	U1STAbits.UTXEN = 0;
	
	
	/* Configure uart1 receive and transmit interrupt */
//	ConfigIntUART1(UART_RX_INT_EN & UART_RX_INT_PR6 & UART_TX_INT_EN & UART_TX_INT_PR2);

/*************************************
//has been replaced by uart.c functions, UMODEValue	
	// configure U1MODE
	U1MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	//U2MODEbits.notimplemented;	// Bit14
	U1MODEbits.USIDL = 0;	// Bit13 Continue in Idle
	U1MODEbits.IREN = 0;	// Bit12 No IR translation
	U1MODEbits.RTSMD = 0;	// Bit11 Flow Mode
	//U2MODEbits.notimplemented;	// Bit10
	U1MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
	U1MODEbits.WAKE = 0;	// Bit7 No Wake up (since we don't sleep here)
	U1MODEbits.LPBACK = 0;	// Bit6 No Loop Back
	U1MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')
	U1MODEbits.URXINV = 0;	// Bit4 IdleState = 1  (for dsPIC)
	U1MODEbits.BRGH = 0;	// Bit3 16 clocks per bit period
	U1MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
	U1MODEbits.STSEL = 0;	// Bit0 One Stop Bit 
	**************************************/
	U1MODEvalue=UART_DIS & UART_IDLE_STOP & UART_IrDA_DISABLE & UART_MODE_FLOW &
	UART_UEN_00 & UART_DIS_WAKE & UART_UXRX_IDLE_ONE &
	UART_DIS_LOOPBACK & UART_DIS_ABAUD &
	UART_BRGH_SIXTEEN & UART_NO_PAR_8BIT & UART_1STOPBIT;

/*****************************************	U1STAValue
	// Load a value into Baud Rate Generator.  Example is for 9600.
	// See section 19.3.1 of datasheet.
	//  U1BRG = (Fcy / (16 * BaudRate)) - 1
	//  U1BRG = (40M / (16 * 9600)) - 1
	//  U1BRG = 259.4 //Round to 259
	
	//U1BRG = 21; //20.7 for 115200bps   //42.4 for 57600  //64.1 for 38400    //129.2 for 19200

	// Load all values in for U1STA SFR
	U1STAbits.UTXISEL1 = 0;	//Bit15 Int when Char is transferred (1/2 config!)
	U1STAbits.UTXINV = 0;	//Bit14 N/A, IRDA config
	U1STAbits.UTXISEL0 = 1;	//Bit13 Other half of Bit15
	//U2STAbits.notimplemented = 0;	//Bit12
	U1STAbits.UTXBRK = 0;	//Bit11 Disabled
	U1STAbits.UTXEN = 0;	//Bit10 TX pins controlled by periph
	U1STAbits.UTXBF = 0;	//Bit9 *Read Only Bit*
	U1STAbits.TRMT = 0;	//Bit8 *Read Only bit*
	U1STAbits.URXISEL = 0;	//Bits6,7 Int. on character received
	U1STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
	U1STAbits.RIDLE = 0;	//Bit4 *Read Only Bit*
	U1STAbits.PERR = 0;		//Bit3 *Read Only Bit*
	U1STAbits.FERR = 0;		//Bit2 *Read Only Bit*
	U1STAbits.OERR = 0;		//Bit1 *Read Only Bit*
	U1STAbits.URXDA = 0;	//Bit0 *Read Only Bit*

**************************************************/
	U1STAvalue = 0X0000 & UART_INT_TX_BUF_EMPTY & UART_TX_DISABLE & UART_INT_RX_CHAR &
	UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR & UART_SYNC_BREAK_DISABLED & UART_IrDA_POL_INV_ZERO;
	baudvalue = 21; //259 to get 9600 as baudrate //20.7 for 115200bps   //42.4 for 57600  //64.1 for 38400    //129.2 for 19200
	OpenUART1(U1MODEvalue, U1STAvalue, baudvalue);
	
//	ConfigIntUART1 (UART_RX_INT_EN & UART_TX_INT_EN);
	U1MODEbits.UARTEN = 1;	// And turn the peripheral on

	U1STAbits.UTXEN = 1;	// I think I have the thing working now.
//	wait_us(104);		//wait at least 104usec (1/9600 s)before sending first char
	wait_ms(1);
}


void SetupPorts_ADC1(void)
{
	AD1CON1 = 4;
	AD1CON1bits.SSRC=7;
	AD1CON2 = 0x0000;
	AD1CON3 = 0x1F02;
	
	/*timer3
	T3CON=0x0030;
	T3CONbits.TON=1;
	end timer3*/
	
	_TRISA0=1;
	_TRISA1=1;
	_TRISB2=1;
	_TRISB3=1;
	_TRISC0=1;
	_TRISC1=1;
	AD1PCFGL = 0b11110011;
	//AD1CON1 = 0x00E0; // ASAM bit = 1 implies sampling ..
	// starts immediately after last
	// conversion is done
	AD1CHS0= 0x0001; // Connect RB7/AN7 as CH0 input ..
	// in this example RB7/AN7 is the input

	AD1CSSL = 0;
	//AD1CON3 = 0x002; // Sample time manual, Tad = internal 2 Tcy
	//AD1CON2 = 0;
//	AD1CON1bits.ADON = 1; // turn ADC ON
  
  
//	  
//	  // 10 bits
//	  AD1CON1bits.AD12B = 0;
//	   // Samples multiple channels simultaneous
//	  AD1CON1bits.SIMSAM =0; 
//	  // Sampling begins immediately after last conversion completes. 
//	  // SAMP bit is auto set
//	  AD1CON1bits.ASAM = 1;  
//	  // PWM triggered conversion
//	  AD1CON1bits.SSRC = 0; 
//	  // Signed fractional (DOUT = sddd dddd dd00 0000)
//	  AD1CON1bits.FORM = 0;   
//	  
//	  //VREF-=AVSS VREF+=AVDD
//	  AD1CON2bits.VCFG=4;
//	  // Samples CH0, CH1, CH2, CH3 simultaneously (when CHPS = 1x)
//	  AD1CON2bits.CHPS = 0;  
//	  // Interrupt after every conversion!
//	  AD1CON2bits.SMPI = 0;
//	    // Do not scan!
//	  AD1CON2bits.CSCNA = 0;
//	  AD1CON2bits.BUFM=1;
//	  AD1CON2bits.BUFS=1;
//	  
//	  
//	  // A/D Conversion Clock (TAD). must be >= 76ns.
//	  // 40Mhz clk = 25 ns (TCY).
//	  // TAD = TCY * (ADCS+1)
//	  // TAD = 25*5 = 125 ns
//	  // Conversion time = TAD*12 = 1.5us 
//	  // time to conv 4 ch = 1.5*4 = 6 us
//	  // TODO: il valore di conversione ha influenza sul ritardo con cui parte il calcolo della SVG 
//	  // 1.5 us + tempo di calcolo deve essere < di TPWM/2  
//	  // AM portato a 4. Empiricamente si vede meno rumore su DCLink.
//	  // Su lettura di corrente sembra migliorare leggermente
//	  AD1CON3bits.ADCS = 10;   // AD1CON3bits.ADCS = 2; 
//	  AD1CON3bits.ADRC = 1; 
//	
//	  // One sample per cycle on each ch
//	  AD1CON4 = 0;
//	    
//	  // ADCHS: ADC Input Channel Select Register
//	  AD1CHS0 = 0;	
//	  // CH0 is unused. connect to a dummy AN
//	  AD1CHS0bits.CH0SA = 4;
//	  //inpout scan input
//	  //AD1CSSHbits=0x0000;
//	  AD1CSSLbits.CSS4 = 1;
//	  AD1CON1bits.ADON = 1;

}

//	
//	#if 0
//	void SetupPorts_ADC1(void)
//	{
//		CloseADC1();
//		
//		unsigned int channel123 = ADC_CH123_NEG_SAMPLEA_VREFN & ADC_CH123_NEG_SAMPLEB_VREFN &
//		ADC_CH123_POS_SAMPLEA_0_1_2 & ADC_CH123_POS_SAMPLEB_3_4_5;
//		unsigned int channel0 =  ADC_CH0_POS_SAMPLEA_AN6 & ADC_CH0_NEG_SAMPLEA_VREFN;//ADC_CH0_POS_SAMPLEA_AN6 & ADC_CH0_NEG_SAMPLEA_VREFN & ADC_CH0_POS_SAMPLEB_AN7 & ADC_CH0_NEG_SAMPLEB_VREFN;
//	   
//		SetChanADC1(channel123, channel0);
//		
//		//This contains the parameters to be configured in the ADxCON1 register
//		unsigned int config1 = ADC_MODULE_ON & ADC_IDLE_STOP & ADC_ADDMABM_ORDER & 
//		ADC_AD12B_10BIT & ADC_FORMAT_FRACT & ADC_CLK_MANUAL & ADC_AUTO_SAMPLING_OFF &
//		ADC_SIMULTANEOUS;
//		unsigned int config2 = ADC_VREF_AVDD_AVSS & ADC_SCAN_OFF & ADC_SELECT_CHAN_0 &
//		ADC_DMA_ADD_INC_1 & ADC_ALT_BUF_OFF & ADC_ALT_INPUT_OFF;
//		unsigned int config3 = ADC_CONV_CLK_SYSTEM & ADC_SAMPLE_TIME_4 & ADC_CONV_CLK_256Tcy; 
//		unsigned int config4 = ADC_DMA_BUF_LOC_1;
//		unsigned int configport_h = ENABLE_ALL_DIG_16_31;
//		unsigned int configport_l = ENABLE_AN0_ANA & ENABLE_AN1_ANA & ENABLE_AN4_ANA &
//		ENABLE_AN5_ANA & ENABLE_AN6_ANA & ENABLE_AN7_ANA;
//		unsigned int configscan_h = SCAN_NONE_16_31;
//		unsigned int configscan_l = SKIP_SCAN_AN0 & SKIP_SCAN_AN1 & SKIP_SCAN_AN2 & SKIP_SCAN_AN3 & SKIP_SCAN_AN4 & 
//		SKIP_SCAN_AN5 & SKIP_SCAN_AN7 & SKIP_SCAN_AN8 & SKIP_SCAN_AN9 & SKIP_SCAN_AN10 & SKIP_SCAN_AN11 &
//		SKIP_SCAN_AN12 & SKIP_SCAN_AN13 & SKIP_SCAN_AN14 & SKIP_SCAN_AN15;
//		
//		OpenADC1(config1, config2,	config3, config4, configport_l,	configport_h, configscan_h,	configscan_l);
//	
//	}
//	
//	#endif


void SetupDMA0(void)
{
	// DMA configurations for ADC
  DMA0CON = 0;
  // Configure DMA for Peripheral indirect mode
  DMA0CONbits.AMODE = 2;

  // Continuous, Ping-Pong modes disabled
  DMA0CONbits.MODE = 0;

  // trasfer block unit is a WORD
  DMA0CONbits.SIZE = 0;

  // set DMA source register	
  DMA0PAD=(int)&ADC1BUF0;
  // number of words to transfer
  // do 4 transfers
  DMA0CNT = 0;
  // attach DMA0 transfer to ADC
  DMA0REQ = 13;

  // set address of dma buffer    
  DMA0STA = __builtin_dmaoffset(ADCBuffer);

	// DMA enable
  DMA0CONbits.CHEN = 1;


}


void ON_OFF_SCREEN(void)
{
	_TRISC5=0;
	PORTCbits.RC5=0;
	wait_ms(500);
	PORTCbits.RC5=1;
	//wait_ms(1);
}


void SetupPorts(void)
{
	//
//  init dsPic ports and peripheral mapping
//
  // set everything as output
  LATA  = 0x0000;
  TRISA = 0x0000;
  
  LATB  = 0x0000;
  TRISB = 0x0000;
  
  LATC  = 0x0000;
  TRISC = 0x0000;

 
  // default all pins to DIGITAL
  //  AD1PCFGL = 0xffff; 

  // CAN
  //#define CAN
	OSCCONbits.IOLOCK=0;
  Setup_Pins_4_CAN_module();
  
  // UART
  //#define UART
  SetupPorts_UART1();
  // ENABLE_SCREEN
  ON_OFF_SCREEN();
  // DMA
  //SetupDMA0();
  // ADC
 // SetupPorts_ADC1(); //to comment until get work by taking piece of code from jug_test.c
  //SPI
  SetupPorts_SPI1();
  
	/*set the MC_motor module and pin FaultA*/
	_FLTA1R = 4;		// Connect /FLTA pin to RP4
	_TRISB4 = 1;		//1=input //make sure that the pin RP4(=RB4) is set as input
	_TRISC2 = 0;
	setup_MC_PWM();
	
	/*set pins for QEI interface - ROIE/L and MOTOR phases*/
	_TRISC7=1;
	_INDX1R=23;	//C7=RP23
	_TRISC8=1;
	_QEB1R=24;	//C8=RP24
	_TRISC9=1;
	_QEA1R=25;	//C9=RP25
	setup_QEI_JOG();
}

/*This function Clear the Screen and disable the Screen saver mode that is to say NO SCROLLING MENU*/
void init_screen(void)
{
	Clear_Read_Buffer();
	wait_ms(10);
	gfx_Cls();
	SSTimeout();
	wait_ms(10);
}

void init_basic_syntax(void)
{
	txt_Width(2);
	txt_Height(2);
	//txt_Bold(1);
	txt_FGcolour(WHITE);


}
void init_char_size(int size)
{
	txt_Width(size);
	txt_Height(size);
	//txt_Bold(1);
}

void init_color(WORD color)
{
	txt_FGcolour(color);
}

void basic_screen_tool(int char_size,WORD font_color)
{
	init_screen();
	wait_ms(10);
	txt_Width(char_size);
	wait_ms(10);
	txt_Height(char_size);
	wait_ms(10);
	txt_FGcolour(font_color);
	wait_ms(10);	
	txt_MoveCursor(0,0);
	wait_ms(10);
}




void splash_screen_selection(unsigned char** member,int length)
{
	int i;
	for (i=0;i<length;i++)
	{
		txt_MoveCursor(i,0);
		putstr(member[i]);
	}
	
}

void return_2_root_menu(void)
{
	int i;
	for(i=0;i<3;i++)
	{
	basic_screen_tool(2,YELLOW);
	txt_MoveCursor(2,0);
	putstr("BACK TO");
	txt_MoveCursor(3,0);
	putstr("ROOT MENU");
	wait_ms(500);
	gfx_Cls();
	wait_ms(500);
	}
}

