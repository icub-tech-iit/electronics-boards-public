//
// HW/FW Fault conditions handlers
//

#include "Faults.h"
#include <timer.h>
#include <string.h> // memset

void FaultReset(void)
// called when receiving shutdown cmd and
// going to readytoswitchon
{
	LED_status.RedBlinkRate = BLINKRATE_OFF;
	memset(SysError.b,0,sizeof(SysError));
	
}

void FaultConditionsHandler(void)
// General pourpouse fault handler (for Overload, Exernal, Encoder, DCLink, Spped, CAN, )
// TODO: all faluts handlers
{
  // TODO: To be fully completed

  // Disable PWM
  PWMDisable();


  // turn on Red Led
  LED_status.RedBlinkRate=BLINKRATE_FAST;
  LED_status.GreenBlinkRate=BLINKRATE_OFF;

}

void __attribute__((__interrupt__,no_auto_psv)) _FLTA1Interrupt(void) 
// Interrupt handler for OVERCURRENT fault.
// HW will automatically stop PWM generation.
// We need to set SW flag here in order to update SW state information 
{


  // signal overcurrent
  SysError.OverCurrentFailure = 1;

  // call fault handler
  FaultConditionsHandler();

  // clear irq flag
  IFS3bits.FLTA1IF = 0;
}


void FaultExternalTriggered()
// External fault interrupt handler
{
  SysError.ExternalFaultAsserted = 1;
  // call generic handler
  FaultConditionsHandler();
}


