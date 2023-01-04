/*********************************************************************************
author:JENVRIN Julien
company: Italian Institute of Technology
Date: 12/11/2013
program name: MC_PWM_JOG.c
content: All functions use to control Motor with PWM
*************************************************************************************/
#include "pwm.h"	//pwm12.h

void setup_MC_PWM(void)
{
	/*Registro P1TCON : PWM Time Base Control Register*/
		//This register is used for the selection of Time Base mode, time base input clock prescaler, 
		//time base output postscaler, and for enabling the time base timer.
		P1TCONbits.PTEN=0;				//PTEN: PWM Time Base Timer Enable bit - At the end just turn ON the module with PTEN=1
		P1TCONbits.PTSIDL=1;			//PTSIDL: PWM Time Base Stop in Idle Mode bit
		P1TCONbits.PTOPS=0b000;			//PTOPS<3:0>: PWM Time Base Output Postscale Select bits (0b111=1:16, ..., 0b000=1:1)
		P1TCONbits.PTCKPS=0b00;			//PTCKPS<1:0>: PWM Time Base Input Clock Prescale Select bits (0b00=1:1, 0b01=1:4, 0b10=1:16, 0b11=1:64)
		P1TCONbits.PTMOD=0b00;			//PTMOD<1:0>: PWM Time Base Mode Select bits - 0b00=Free Running Mode - Count Upward until it gets P1TPER value and reset
		
	/*Registro P1TMR: PWM Time Base Register*/
		//The time base count value and the time base count direction status are obtained in this register.
		P1TMRbits.PTMR=0x0;				//PTMR<14:0>: PWM Time Base Register Count Value bits
	
	/*P1TPER: PWM Time Base Period Register*/
		//The PWM time base value is written into this register, which determines the PWM operating frequency.
		P1TPER=0xFFFF;		//PTMR<14:0>: PWM Time Base Register Count Value bits
	
	/*P1SECMP: Special Event Compare Register*/
		//This register provides the compare value at which the analog-to-digital conversions are to
		//be synchronized with the PWM time base.
	//NOT VERY IMPORTANT CAN BE LEFT WITHOUT SETTINGS - SEEE LATER COULD BE USEFUl TO CHECK VALUES INSIDE
	
	/*PWM1CON1: PWM Control Register 1*/
		//Selection of either Independent or Complementary mode for each PWM I/O pair is performed in this register.
		PWM1CON1bits.PMOD1=0;			//PMOD4:PMOD1: PWM I/O Pair Mode bits - 1=pair are independant Output Mode, 0=Complementary Mode
		PWM1CON1bits.PEN1L=0;				//_PEN1L	//PEN4H=0,PEN4L=0,PEN3H=0,PEN3L=0,PEN3H=0,PEN3L=0,PEN1H=1,PEN1L=1
		PWM1CON1bits.PEN1H=0;				//_PEN1H	//make switch in between PEN1L and PEN1H to go fprward or backward
		
	/*PWM1CON2: PWM Control Register 2*/
		PWM1CON2bits.SEVOPS=0b1111;		//SEVOPS<3:0>: PWM Special Event Trigger Output Postscale Select bits
		PWM1CON2bits.IUE=1;				//IUE: Immediate Update Enable bit
		PWM1CON2bits.OSYNC=0;			//OSYNC: Output Override Synchronization bit
		PWM1CON2bits.UDIS=0;			//UDIS: PWM Update Disable bit

	/*P1DTCON1: Dead Time Control Register 1*/
		//The dead time value and clock period prescaler for Dead Time Unit A and Dead Time Unit
		//B can be selected using this register.
		P1DTCON1bits.DTAPS=0b11;
		P1DTCON1bits.DTA=0b111111;
		P1DTCON1bits.DTBPS=0b00;
		P1DTCON1bits.DTB=0b000000;
	
	/*P1DTCON2: Dead Time Control Register 2*/
		//Dead time insertions from Dead Time Unit A = 0 or Dead Time Unit B = 1 for each of the PWM
		//outputs can be selected using this register.
		P1DTCON2bits.DTS1A=1;
		P1DTCON2bits.DTS1I=1;
	
	/*P1FLTACON: Fault A Control Register Dead Time Control Register 1*/
		P1FLTACONbits.FAOV1H=0;
		P1FLTACONbits.FAOV1L=0;
		P1FLTACONbits.FLTAM=1;
		P1FLTACONbits.FAEN1=0;	//1
	
	/*P1FLTBCON: Fault B Control Register Dead Time Control Register 2*/
	
	/*PxOVDCON: Override Control Register*/
		//This register is used for enabling the output override feature and for PWM output pin control selection.
		P1OVDCONbits.POVD1H=1;	//1
		P1OVDCONbits.POVD1L=1;	//1
		
	/*P1DC1: PWM Duty Cycle Register 1*/
		//The 16-bit PWM duty cycle value for the PWM output pair 1
		P1DC1=0x0000;
	
	/*P1DC2: PWM Duty Cycle Register 2 - The 16-bit PWM duty cycle value for the PWM output pair 2*/
	/*P1DC3: PWM Duty Cycle Register 3 - The 16-bit PWM duty cycle value for the PWM output pair 3*/
	/*P1DC4: PWM Duty Cycle Register 4 - The 16-bit PWM duty cycle value for the PWM output pair 4*/

	/*PWM1Key: PWM Unlock Register*/
		//This register enables the user to unlock the PWMxCON1, PxFLTACON and PxFLTBCON registers for write access.

	/*FPOR: POR Device Configuration Register*/
		//3 device Configuration bits can be used to set up the initial Reset states and polarity of the PWM I/O pins

	/*FOSCSEL: Oscillator Source Selection Register*/
		//one device Configuration bit in this register can be used to set up the write-protect feature of the PWM Configuration registers.


	/*START MODULE*/
	//P1TCONbits.PTEN=1;	//add this to the function in order to launch it when needed but not otherwise
}
