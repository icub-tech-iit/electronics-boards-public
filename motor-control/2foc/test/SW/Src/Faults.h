//
// fault management 
//

#ifndef __FAULTS_H
#define __FAULTS_H

#include "System.h"
#include "PWM.h"
#include "Status.h"

//
// Flags for various Errors of the System
//
typedef union uSysError
{
  struct 
  {
    // an invalid value of HES has been detected
    unsigned HESInvalidValue:1;
    // an invalid sequence of HES activation has been detected
    unsigned HESInvalidSequence:1;
    // ADC calibration failure
    unsigned ADCCalFailure:1;
    // CAN
    unsigned CANFailure:1;                    //4
    // Overvoltage
    unsigned OverVoltageFailure:1;
    // Undervoltage
    unsigned UnderVoltageFailure:1;
    // OverCurrent
    unsigned OverCurrentFailure:1;
    // I2T protection
    unsigned I2TFailure:1;                      //8
    // External Fault
    unsigned ExternalFaultAsserted:1;           

    // EMUROM Fault
    unsigned EMUROMFault:1;
    // EMUROM CRC Fault
    unsigned EMUROMCRCFault:1;

    // Encoder Fault. 1 when homing with zero signal fail
    unsigned EncoderFault:1;                   //12

   // SPI reading has been interrupted before finishing by foc loop
   unsigned FirmwareSPITimingError:1;		

   unsigned AS5045CSumError:1;               
   unsigned AS5045CalcError:1;				 

   // this is true when the FOC loop tried to delay the PWM update (see below)
   // but the wait for the PWM counter timed out (PWM counter freezed?)
   unsigned FirmwarePWMFatalError:1;         //16
   // This should never happen, and that may indicate
   // a firmware BUG or abnormal firmware behaviour due to
   // unpredictable and exotic reasons (malfunctions, voodoo
   // magic, hardware bugs, gravity inversions, alien invasions, 
   // end of the world).
   // In any case please consider that this is certainly NOT due
   // to the firmware developer, but more likely it's electronic 
   // eng. full responsibility :-)

  // FOC loop was about to update the PDCs near the PDC shadow copy 
   // (pwm counter approaching 0) and the PDC write has thus been delayed 
   unsigned FirmwarePWMTimingErrorCount:8;   //24
  } ;//Flags; 
  // Permits to access the whole structure data in byte/word/array fashon 
  unsigned int W[2];
  unsigned char b[4];
}  __attribute__((__packed__)) tSysError;

extern void FaultConditionsHandler(void);
extern void FaultReset(void);
extern void FaultExternalTriggered();

extern volatile tLED_status LED_status;
extern tSysError SysError;

#endif
