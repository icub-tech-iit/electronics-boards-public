 /**********************************************************************
 *
 *  Filename:       2FOC.c
 *  Date:           15/11/08
 *  Revision:       P R E L I M I N A R Y 
 *
 *  Tools:          MPLAB IDE 8.63
 *                  C30  3.25
 *  
 ***********************************************************************
 *  2FOC PRODUCTION TEST FIRMWARE              
 ***********************************************************************
 *  ...creatively derived from 2FOC engineering R&D firmware
 ***********************************************************************
 */

#include <p33FJ128MC802.h>
#include <libq.h>
#include <timer.h>
#include <ecan.h>
#include <spi.h>
#include <math.h>
#include <dsp.h>
#include <libpic30.h>  //__delay32

#include "UserTypes.h"
#include "MeasCurr.h"
#include "UserParms.h"
#include "ecan.h"

#include "System.h"
#include "PWM.h"
#include "ADC.h"

#include "Status.h"

#include "DS402.h"
#include "can_proto.h"
#include "faults.h"


#define CAN_ID 0xd

char TWOFOC_FW_VERSION[] = FIRMWARE_REVISION_STRING;
char TWOFOC_HW_VERSION[] = HARDWARE_REVISION_STRING;

//
// Configuration bits
//
 
// no Boot sector and write protection disabled
_FBS (BSS_NO_FLASH & BWRP_WRPROTECT_OFF);

// no secure sector and write protection disaabled
_FSS (RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF);

// Code protection disabled
_FGS(GSS_OFF); 

// Clock switching disabled Fail safe Clock Monitor disabled
// Starts from safe internal fast RC
_FOSCSEL(IESO_OFF & FNOSC_FRC); 

// Clock switching enabled and clock monitor disabled, EC external clock, OSCOUT as IOPIN
_FOSC(FCKSM_CSECMD & POSCMD_EC & OSCIOFNC_ON)

// Turn off Watchdog Timer
_FWDT (FWDTEN_OFF);
//_FWDT(WDT_ON & WDTPSA_512 & WDTPSB_1); // WD enabled 1:512*16

// PWM mode is Port registers PWM high & low active high
// alternate I2C mapped to SDA1/SCL1
// FPOR power on reset 128ms
_FPOR (PWMPIN_ON & HPOL_ON & LPOL_ON & FPWRT_PWR128);

// Use PGC3/PGD3 for programming and debugging
_FICD (ICS_PGD3 & JTAGEN_OFF); // & COE_ON ); //BKBUG_OFF

//
// Tons of globals
//
#include "globals.h"



void __attribute__((__interrupt__,no_auto_psv)) _DMA0Interrupt(void)
//
// DMA0 IRQ Service Routine
// used for FOC loop 
//
{


  // This ISR is *very* high priority.
  // It might preempt lower priority ASM DSP code.
  // Above we make it sure that the preempted code can continue
  // safely when this ISR finishes. Here we ensure that THIS
  // ISR (that will use DSP ASM funtions) can work properly, and
  // so we set the CORCON register in proper way. 

  // multiplication are NOT unsigned
  CORCONbits.US  = 0;
  // enable saturation on DSP data write
  CORCONbits.SATDW = 1;
  // DISABLE saturation on accumulator A. Required by MeasCurr algo
  CORCONbits.SATA  = 0;

  // do not do super saturation (probably don't care because SATA = 0
  CORCONbits.ACCSAT  = 0;
  // program space not visible in data space
  CORCONbits.PSV  = 0;
  // conventional rounding mode
  CORCONbits.RND  = 1;

  // DSP multiplication are in fractional mode.
  CORCONbits.IF  = 0;
  // TODO: <--- move to ASM calls

  // read and compensate ADC offset by MeasCurrParm.Offseta, Offsetb, Offsetc
  // scale currents by MeasCurrParm.qKa, qKb, qKc
  // Calculate ParkParm.qIa, qIb, qIc


 //Clear the DMA0 Interrupt Flag
  IFS0bits.DMA0IF = 0;

}


/*
void DriveInit()
// Perform drive HW init
{



  // setup for a center aigned PWM
  SetupPWM();

  // setup and perform ADC offset calibration in MeasCurrParm.Offseta and Offsetb 
  ADCDoOffsetCalibration();

  // Enable DMA interrupt, arm DMA for transfer
  ADCConfigPWMandDMAMode();


  // setup Hw related parameters (current gain, ecc...)
  SetupHWParameters();

}


void DisableDrive()
// disable the drive functions:
// - disable and zero control reference and status
// - disable PWM generators
// - disable FOC loop
{
  // disable PWM
  PWMDisable();

  // Disable ADC IRQ and DMA
  ADCInterruptAndDMADisable();

}

*/


int main ( void )
// 
// drive functions are controlled according to DS402 standard (when possible)
// 
{

/*
 * MOVED OFF notreadytoswitchon to enable LED operation in notreadytoswitchon state
 */

  // Configure Oscillator Clock Source, PLL
  oscConfig();
 
  // set up port direction and peripheral pin mapping
  SetupPorts();
 

  // Interrupt Priority configuration
  InterruptPriorityConfig();

  // Setup timer for low frequency (LED) operations
  Timer1Config();

  // enable timer1 interrupt
  EnableIntT1;
 
// TODO: vedere se possibile verificare l'oscillatore e la verifica di porte di IO
  
  // signal NOT READY TO SWITCH ON status with green LED blinking ultrafast
  // LED blinking velocity
  LED_status.GreenBlinkRate=BLINKRATE_ULTRAFAST;
  LED_status.RedBlinkRate=BLINKRATE_ULTRAFAST;

  // Drive Init  
//  DriveInit();

  OverCurrentFaultEnable();
  CanProtoInit(CAN_ID);


  // Arm all the automation (PWM->ADC->DMA->FOC) but don't start yet!
//  ADCInterruptAndDMAEnable();
 
  // Starts to pump current!
//  PWMEnable();

  // should never arrive here!
  while(1);

asm("NOP");
asm("NOP");
asm("NOP");
asm("NOP");
asm("NOP");

}



