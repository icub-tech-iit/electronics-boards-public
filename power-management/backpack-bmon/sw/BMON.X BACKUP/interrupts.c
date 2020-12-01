/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <xc.h>         /* XC8 General Include File */

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/
extern char timer_100us;
extern int adc_buffer;

void interrupt isr(void)
{
    if(PIR1bits.TMR1IF){		// Interrupt Timer1
	timer_100us=1;
	//TMR1H=0xF8;   // 50uS
	//TMR1L=0x72;   // 50uS
        TMR1H=0xF0;
	TMR1L=0xA2;
        PIR1bits.TMR1IF = 0;            //clear timer1 int flag bit
        //RA2=RA2^1;            // Test preciso
    }

    if(PIR1bits.ADIF){                  // Interrupt ADC
        adc_buffer = (ADRESH<<2) + (ADRESL>>6);
        PIR1bits.ADIF = 0;              //clear timer1 int flag bit
        //RC4=RC4^1;
    }
}



