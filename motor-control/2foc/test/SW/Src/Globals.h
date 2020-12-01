
//
// * L O T S *  of DECLARATIONS of Global variables
//
#ifdef __GLOBALS_H
#error DONOTDOTHIS
#endif

#define __GLOBALS_H


#include "faults.h"
#include "park.h"

//
// ADC (ia, ic, VDCLink)
//

	

//
// PARK-CLARKE related
//
tParkParm ParkParm;


tSysError SysError;

//
// CAN command variables 
//

//
// System  related 
//
// Machine status
tSysStatus SysStatus;
// Led multiplexing status, init as all LED off
// unsigned short LED_status = 0x00;
volatile tLED_status LED_status = {0x00};

// VDCLink in 100mV units
unsigned int vdc;


// Variables for GULP!ing
tGulp Gulp;
// define the contents of the periodic message used as an index for PeriodicData
unsigned char PeriodicMessageContents[4] = {0,0,0,0};

// a new set of variables are requested for Gulp!ing
// if this is 1 we are waiting for FOC to fill new values
// Note that the main loop does not really wait, it just does not
// perform operations on the pending variables.
volatile int gulp_update_request = 1;



//
// DMA Space
//




//TODO: del me if we use really the parser, and we never switch to virtual can memory map
// the virtual memory addressed by can extended frames.

// Buffers used to store ADC Samples
SFRAC16 ADCBuffer[4] __attribute__((space(dma),aligned(16))); 	

//
// I2T related variables
//


//
// DS402 state machine as defined in 'CiA DSP 402 V 2.0' pag. 45
//
volatile tControlword DS402_Controlword = { .W[0]=0 };

// init state as NOT READY TO SWITCH ON:  
// DS402 State xxxx xxxx x0xx 0000 
volatile tStatusword  DS402_Statusword = { .W[0]=0 };


//TODO: 
//TODO: eliminare la variabile LOCALE position che non vuole dire nulla e fare funzionare 
//      il tutto in modo piu' charo senza magia nera utilizzando la variabile globale MeccanicalAngle
//TODO: 
//TODO: 
// volatile unsigned long Position = 0;

// updated each foc loop
volatile  long Current_position = 0;
// last foc cycle value
volatile  long Previous_position = 0;

// zero value
unsigned int Zero = 0;

//
// list of possible contents of the periodic message
// 

const unsigned int * PeriodicData[ELEMENTS_IN_PREIODIC_DATA_LIST]={
    //
    // Trasformation related
    //
/* 0 */  (unsigned int*) &Zero,
/* 1 */  (unsigned int*) &Zero,
/* 2 */  (unsigned int*) &Zero,
   //
/* 3 */  (unsigned int*) &Zero,
/* 4 */  (unsigned int*) &Zero,
  //
/* 5 */  (unsigned int*) &Zero,
/* 6 */  (unsigned int*) &Zero,
  //
/* 7 */  (unsigned int*) &Zero,
/* 8 */  (unsigned int*) &Zero,
  //
/* 9 */  (unsigned int*) &Zero,
/* A */  (unsigned int*) &Zero,
  //
/* B */  (unsigned int*) &Zero,
/* C */  (unsigned int*) &Zero,
/* D */  (unsigned int*) &Zero,
    //
    // PWM related
    //
/* E */  (unsigned int*) &PDC1,
/* F */  (unsigned int*) &PDC2,
/* 10 */ (unsigned int*) &PDC3,
   //
   // angle related
   //
/* 11 */ (unsigned int*) &Zero, 
/* 12 */ (unsigned int*) &Zero,
/* 13 */ (unsigned int*) &Zero,
/* 14 */ (unsigned int*) &Zero,
/* 15 */ (unsigned int*) &Zero, // position is 32bit wide
/* 16 */ (unsigned int*) &Zero,
  //
  // Velocity related
  //
/* 17 */ (unsigned int*) &Zero, 
  //
  // PID related
  //
/* 18 */ (unsigned int*) &Zero, 
/* 19 */ (unsigned int*) &Zero, 
/* 1A */ (unsigned int*) &Zero,
/* 1B */ (unsigned int*) &Zero,
/* 1C */ (unsigned int*) &Zero,

  //
  // Voltage related
  //
/* 1D */ (unsigned int*) &Zero,
/* 1E */ (unsigned int*) &Zero,
  //
  // system related
  //
/* 1F */ (unsigned int*) (((void*)(&SysStatus))+2),  // SysStatus is 32 bit wide
/* 20 */ (unsigned int*) ((void*)(&SysStatus)),
/* 21 */ (unsigned int*) &Zero,
/* 22 */ (unsigned int*) &DS402_Controlword,
/* 23 */ (unsigned int*) &DS402_Statusword,

/* 24 */ (unsigned int*) &Zero,
/* 25 */ (unsigned int*) &Zero,
/* 26 */ (unsigned int*) &Zero,
/* 27 */ (unsigned int*) &Zero
};

