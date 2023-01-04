 /**********************************************************************
 *
 *    Filename:       UserParms.h
 *
 *  In this file are grouped all the parameters that the user is likely 
 *  to change for the use of specific devices
 *  Other parameters are related to HW configuration and control loops
 *  are not likely to be changed by the average user.
 *
 **********************************************************************/
#ifndef UserParms_H
#define UserParms_H

// Oscillator Parameters
#define PLLIN          10000000  // External Crystal or Clock Frequency (Hz), here 10Mhz
#define DESIREDMIPS	   40000000  // Enter desired MIPS
#define DPLL (unsigned int)(2.0*DESIREDMIPS/PLLIN) // PLL ratio (2.0*4)
#define FOSC           (PLLIN*DPLL) // Clock frequency [Hz] (80Meg)
#define DFCY           (FOSC/2)  // Instruction cycle frequency (Hz) (40Meg)
#define DTCY           (1.0/DFCY) // Instruction cycle period (sec)

//Variable oscillator for CAN module




#endif
