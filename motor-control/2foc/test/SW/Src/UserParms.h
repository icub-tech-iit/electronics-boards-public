 /**********************************************************************
 *
 *    Filename:       UserParms.h
 *
 *    Tools used:     MPLAB IDE -> 8.30
 *                    C30 -> 3.12
 *
 *  In this file are grouped all the parameters that the user is likely 
 *  to change when a new motor, encoder or load are connected.
 *  Other parameters are related to HW configuration and control loops
 *  are not likely to be changed by the average user.
 *
 **********************************************************************/

#ifndef UserParms_H
#define UserParms_H


#define FIRMWARE_REVISION_STRING "2.0"

// HW revision 3 or previous
// #define HARDWARE_REVISION_3
// HW revision 4 or successive
#define HARDWARE_REVISION_4


#ifdef HARDWARE_REVISION_4
#define HARDWARE_REVISION_STRING "4.0"
#elif defined HARDWARE_REVISION_3
#define HARDWARE_REVISION_STRING "3.0"
#else
#define HARDWARE_REVISION_STRING "???"
#endif



// Enables output on pin RA3 (extfault) (P1.5) for debug pourpouses
#define PIN_RA3_IS_DEBUG
//#define PIN_RA3_IS_EXTERNAL_FAULT


//
// DC-Link parameters
// 

#define     DQKA       Q15(1.0)  // Ia 
#ifdef SAMPLE_IA_IB 
  #define   DQKB       Q15(-1.0) // Ib is sampled . 
#else
  #define   DQKB       Q15(-1.0) // Ib is calculated from Ia and Ic. 
    // due to optimizations in algo inverted sign is required !!!!!
#endif
#define     DQKC       Q15(1.0)  // Ic

// Enable/Disable Overcurrent protection
#define ENABLE_OVER_CURRENT_PROTECTION 

// Undervoltage and Overvoltage values in 100mV units.
// The undervoltage protection will trigger if the VDCLink drops below this value. 
#define UNDERVOLTAGE_THRESHOLD 100
// The overvoltage detection will trigger if the VDCLink rise above this value. 
#define OVERVOLTAGE_THRESHOLD  600





// PWM and Control Timing Parameters
#define PWMFREQUENCY   20000     // PWM Frequency in Hertz
#define DEADTIMESEC	   0.00000015 // Deadtime in seconds (0.15 uSec)
// this forces the 2foc interrupt to delay PWM registers update when it is 
// about to do it very close to the PWM hardware register buffering.
// The number represent the estimated clock cycles taken by SVgen to
// update those registers. The call to SVgen is thus delayed if the
// algo foresee that the HW will shadows register during SVGen (in the
// next PWMSAFETIME clock cycles)
#define PWMSAFETIME 50 // svgen takes 34 cycles. be conservative

//
// CAN communication parameters
//
// Data rate of outgoing messages in 0.1 millisecond units
#define CAN_OUTPUT_DATARATE (float)2.0
// every CAN_STATE_PER messages a status message is generated
#define CAN_STATUS_MSG_PERIOD 1000
// Enable ack. for CAN set commands
// #define CAN_ACK_EACH_COMMAND

// Enable accept all commands (including setpoints) when in switch off state
//#define CAN_CMD_ALWAYS_ACCEPT

// Oscillator Parameters
#define PLLIN          10000000  // External Crystal or Clock Frequency (Hz)
#define DESIREDMIPS	   40000000  // Enter desired MIPS

// number of elements in the list of possible contents of periodic message
#define ELEMENTS_IN_PREIODIC_DATA_LIST 0x28

#endif
