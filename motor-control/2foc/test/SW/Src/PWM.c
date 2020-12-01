//   
//  PWM related rouines:
//  
//  Initialization, control and fault management 
//  
// 

#include <libpic30.h>

#include "PWM.h"
#include "UserParms.h"
#include "status.h"
#include "system.h"
#include "adc.h"


/* nominal R is (22||22) + (22||22) = 22 ohm
 * with 36V VDC I = 1.63 Amps
 */
#define PWM_TEST_IL_THRESH 1875  /*( 1430.0 / 0.76277 )*/
#define PWM_TEST_IH_THRESH 2399 /*(1830.0 / 0.76277)*/

// 22ohm wire resistor 450 mA
//#define PWM_TEST_IL_THRESH_WIRE 458  /*( 350.0 / 0.76277 )*/
//#define PWM_TEST_IH_THRESH_WIRE 721 /*(600.0 / 0.76277)*/

#define PWM_TEST_IH_THRESH_WIRE 15732  /*( 12000.0 / 0.76277 )*/
#define PWM_TEST_IL_THRESH_WIRE 10488 /*(8000.0 / 0.76277)*/


#define PWM_TEST_VDCL_THRESH 345
#define PWM_TEST_VDCH_THRESH 375


#define PWM_TEST_VDCL_THRESH_WIRE 185
#define PWM_TEST_VDCH_THRESH_WIRE 215

extern tSysStatus SysStatus;

typedef struct tPwmState{
	int e;
	int l;
} tPwmState;

tPwmState pwmstate;

void SetupPWM(void)
// init for a center aligned pwm with sincronized ADC 
{
  // OpenMCPWM1(LOOPINTCY/2, LOOPINTCY/2 -80,0x8002, 0x0077, 0);
  // Motor PWM
  PDC1 = 0;
  PDC2 = 0;
  PDC3 = 0;

  // Center aligned PWM.
  // Note: The PWM period is set to dLoopInTcy/2 but since it counts up and 
  // and then down => the interrupt flag is set to 1 at zero => actual 
  // interrupt period is dLoopInTcy
  PTPER = LOOPINTCY/2;    // Setup PWM period to Loop Time defined in parms.h 
  PWMCON1 = 0x0077;       // Enable PWM 1,2,3 pairs (L+H) for complementary mode
  DTCON1 = (0x40 | (DDEADTIME/2)); // Dead time
  DTCON2 = 0;

    
  // Set PWM for center aligned operation
  PTCON = 0x2;         
	
  // SEVTCMP: Special Event Compare Count Register 
  // Phase of ADC capture set relative to PWM cycle: 80 offset and counting down
  // to avoid ripple on the current measurement
  SEVTCMP = PTPER - 80;
  SEVTCMPbits.SEVTDIR = 1;	

  // Connect and enable PWM pads to PWM module

// TODO: sei proprio uno ZOZZONE.
//   il commento era gia scritto bastava spostarlo o cancellarlo
}

void PWMDisable()
//Called on fault. All pins are disconnected from PWM module
//and forced to low state.
{
  // Pin override register
  P1OVDCON = 0x0000;

  // disable PWM generation
  PTCONbits.PTEN = 0;

  // Signal PWM disable on sys status
  SysStatus.PWM_is_disabled= 1;
}

void PWMEnable()
// TODO: metti un commento, please
{
  PDC1 = 0;
  PDC2 = 0;
  PDC3 = 0;
  PTMR = 0;
  // TODO: vedi sopra
  P1OVDCON = 0x3f00;
	
  // allows driver boost capacitors to charge
  __delay32(8);

  // clear fault flag before start fault mechanism
  IFS3bits.FLTA1IF = 0;
  
  // Enable PWM generation
  PTCONbits.PTEN = 1;
  // PWM fault configuration
  // pin pair 1,2 and 3 are controlled by Fault Input A

  FLTACON = 7;

 SysStatus.PWM_is_disabled= 0;
}



int PWMTestPinPDN(int pin)
{
	int tmp;
	int i;

	unsigned int mask;
	unsigned int hval;

	hval = (1<<pin);
	mask = ~hval;

	__builtin_disi(0x3fff);

	// drive PIN high 
	LATB = LATB | hval; 

	for(i=0;i<10;i++){
		asm("nop");
		asm("nop");
	}

	// put PIN in HI-Z
	TRISB = TRISB | hval;

	for(i=0;i<10;i++){
		asm("nop");
		asm("nop");
	}

	// read back PIN status
	tmp = PORTB & hval;

	// restore PIN in push-pull low drive.
	LATB = LATB & mask; 
	TRISB = TRISB & mask;


	__builtin_disi(0x0);

	// no PDN on ZH
	if(tmp) 
		return -1;

	return 0;
}

void PWMManualMode()
{
	// disable PWM generation
	PWMDisable();

	// force PWM override to all off.
	P1OVDCON = 0x0000;



    // preload LATB register
	LATBbits.LATB15 = 0; //XL
	LATBbits.LATB14 = 0; //XH
	LATBbits.LATB13 = 0; //YL
	LATBbits.LATB12 = 0; //YH
	LATBbits.LATB11 = 0; //ZL
	LATBbits.LATB10 = 0; //ZH

	//detach PWM modue. PWMPINS are now controlled as GPIO
	PWMCON1 = 0; 

	// reload (just to be paranoid) LATB register
	LATBbits.LATB15 = 0; //XL
	LATBbits.LATB14 = 0; //XH
	LATBbits.LATB13 = 0; //YL
	LATBbits.LATB12 = 0; //YH
	LATBbits.LATB11 = 0; //ZL
	LATBbits.LATB10 = 0; //ZH

	TRISBbits.TRISB15 = 0; //XL
	TRISBbits.TRISB14 = 0; //XH
	TRISBbits.TRISB13 = 0; //YL
	TRISBbits.TRISB12 = 0; //YH
	TRISBbits.TRISB11 = 0; //ZL
	TRISBbits.TRISB10 = 0; //ZH
}

void PWMEnableMos(tPWMMOS m, int e)
{
	

	if(e) e = 1;
	
	switch(m){
		case PWMMOS_XL:
			LATBbits.LATB15 = e; //XL
		break;
	
		case PWMMOS_XH:
			LATBbits.LATB14 = e; //XH
		break;

		case PWMMOS_YL:
			LATBbits.LATB13 = e; //YL
		break;

		case PWMMOS_YH:
			LATBbits.LATB12 = e; //YH
		break;

		case PWMMOS_ZL:
			LATBbits.LATB11 = e; //ZL
		break;

		case PWMMOS_ZH:
			LATBbits.LATB10 = e; //ZH
		break;
	}
}

int PWMTestPDN()
{

	PWMManualMode();
	

	//// PWM pins now in GPIO mode, start test ///


	//--- test ZH ----/
	if(PWMTestPinPDN(10))
		return 1;

	//--- test ZL ----/
	if(PWMTestPinPDN(11))
		return 2;

	
	//--- test YH ----/
	if(PWMTestPinPDN(12))
		return 3;
	
	//--- test YL ----/
	if(PWMTestPinPDN(13))
		return 4;
	
	//--- test XH ----/
	if(PWMTestPinPDN(14))
		return 5;

	//--- test XL ----/
	if(PWMTestPinPDN(15))
		return 6;

	return 0;

	
}


void PWMGetState(int *e, int *l)
{
	*e = pwmstate.e;
	*l = pwmstate.l;
}

void PWMCycle(int e, int l)
{


	pwmstate.e = e;
    pwmstate.l = l;
	if(e){
		SetupPWM();

		if(l || (!(1 & e))){
			// force PWM override to all HS. (low side only)
			P1OVDCONbits.POUT1H = 0;
			P1OVDCONbits.POVD1H = 0;

		}else{
			P1OVDCONbits.POVD1H = 1;
		}

		if(l || (!(2 & e))){
			P1OVDCONbits.POUT2H = 0;
			P1OVDCONbits.POVD2H = 0;
			
		}else{
			P1OVDCONbits.POVD2H = 1;  		
		}
			
		if(l || (!(4 & e))){
			P1OVDCONbits.POUT3H = 0;
			P1OVDCONbits.POVD3H = 0;

		}else{
			P1OVDCONbits.POVD3H = 1;
		}	
	    


		PDC1 = 1000;
  		PDC2 = 1000;
  		PDC3 = 1000;
		
		if( e & 1){
		    P1OVDCONbits.POVD1L = 1;
		}else{
			P1OVDCONbits.POUT1L = 0;
			P1OVDCONbits.POVD1L = 0;
		}
	
		if( e & 2){
			P1OVDCONbits.POVD2L = 1;
		}else{
			P1OVDCONbits.POUT2L = 0;
			P1OVDCONbits.POVD2L = 0;
		}
	
	 	if( e & 4){
	  		P1OVDCONbits.POVD3L = 1;
		}else{
			P1OVDCONbits.POUT3L = 0;
			P1OVDCONbits.POVD3L = 0;
		}
  
  		// clear fault flag before start fault mechanism
  		IFS3bits.FLTA1IF = 0;
  
		  // Enable PWM generation
		PTCONbits.PTEN = 1;
		FLTACON = 7;
		
	  	SysStatus.PWM_is_disabled= 0;


	}else{
		PDC1 = 0;
		PDC2 = 0;
		PDC3 = 0;
		PWMDisable();
	}
	
}

void PWMWait()
{
	int i;
	for(i=0;i<100;i++){
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	}
}


void PWMChargeBoot(tPWMMOS m)
{
	int i;
	
	for(i=0;i<2;i++){
		
		switch(m){
			case PWMMOS_XL:
			case PWMMOS_XH:
			
				PWMEnableMos(PWMMOS_XH,0);
				PWMEnableMos(PWMMOS_XL,1);
		
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");
		
				PWMEnableMos(PWMMOS_XL,0);


			
			break;
	
			case PWMMOS_YL:
			case PWMMOS_YH:

				PWMEnableMos(PWMMOS_YH,0);
				PWMEnableMos(PWMMOS_YL,1);
				
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");
				
				PWMEnableMos(PWMMOS_YL,0);
			
			break;
	
			case PWMMOS_ZL:
			case PWMMOS_ZH:
			
				PWMEnableMos(PWMMOS_ZH,0);
				PWMEnableMos(PWMMOS_ZL,1);

				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");

				PWMEnableMos(PWMMOS_ZL,0);
			
			break;
		}
	
	}	
}

void PWMTestProtection()
{
	int i;

	SetupPWM();
	PWMEnable();

	/* x phase not used . all off */
	P1OVDCONbits.POUT1H = 0;
	P1OVDCONbits.POVD1H = 0;
	P1OVDCONbits.POUT1L = 0;
	P1OVDCONbits.POVD1L = 0;
	
	/* y phase low side always on */
	P1OVDCONbits.POUT2H = 0;
	P1OVDCONbits.POVD2H = 0;
	P1OVDCONbits.POUT2L = 1;
	P1OVDCONbits.POVD2L = 0;
	/* z phase run */

    /* disable int */
    __builtin_disi(0x3fff);
	PDC3 = 50000;

	for(i=0;i<220;i++){
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	}
	PWMDisable();
   /* re enable int*/
    __builtin_disi(0x0);
  
}

#define PWM_BOOT_TIME 3
#define ADC_NUM_MEAN 20

void PWMTestCurrentMosPair(int mosl, int mosh, int *i1_, int *i2_)
{						
	long i1,i2;
	int i,j;
	int tmp1,tmp2;

	i1 = i2 = 0;
													/* test YL XH  - read allegro X*/		
	PWMEnableMos(mosl,1); 	                                         		//         |          |          |
													//         |          |          |
	for(i=0;i<ADC_NUM_MEAN;i++){	  				//		- X        - O        - O	
	 										//         |          |          |
													//         |          |          |
		PWMChargeBoot(mosh);					//         |          |          |
		PWMEnableMos(mosh,1);					//		- O	       - X        - O	
													//         |          |          |
		for(j=0;j<PWM_BOOT_TIME;j++){		        //         |          |          |
			PWMWait();	
		}
				
		ADCReadFast(&tmp1, &tmp2);		    	
	
		i1 += tmp1;
		i2 += tmp2;
     			
	    PWMEnableMos(mosh,0);
        
        for(j=0;j<4000;j++){
    		asm("nop");
    		asm("nop");
    		asm("nop");
    		asm("nop");
    		asm("nop");
    		asm("nop");
    		asm("nop");
    		asm("nop");
    	}
	}
									
	 PWMEnableMos(mosl,0);			
	 PWMEnableMos(mosh,0);
        		

	i1/=ADC_NUM_MEAN;
	i2/=ADC_NUM_MEAN;

	*i1_ = i1;
	*i2_ = i2;

    
	for(i=0;i<20000;i++){
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	}


	//////////////////////////////////////
}

int PWMTestCurrent(int wired,int *resI1, int *resI2, int th, int tl)
{
	unsigned int vdc;
	long io1,io2;
	int i1,i2;
	int tmp1,tmp2;
	int i,j;
//	int th;
//	int tl;
	*resI1 = *resI2 = 0;

	/*if(wired){
		tl = PWM_TEST_IL_THRESH_WIRE;
		th = PWM_TEST_IH_THRESH_WIRE;
	}else{
		tl = PWM_TEST_IL_THRESH;
		th = PWM_TEST_IH_THRESH;
	}
*/
	PWMManualMode();

	/* read VDC */
	ADCRead(&vdc, &i1, &i2);		

	if(wired){
		if(vdc < PWM_TEST_VDCL_THRESH_WIRE){
			return 1;
		}else if(vdc > PWM_TEST_VDCH_THRESH_WIRE){
			return 2;
		}
	}else{

		if(vdc < PWM_TEST_VDCL_THRESH){
			return 1;
		}else if(vdc > PWM_TEST_VDCH_THRESH){
			return 2;
		}
	}

	/* read offset */
	io1 = io2  = 0;
	for(i=0;i<ADC_NUM_MEAN;i++){
		ADCReadFast(&tmp1, &tmp2);
		io1 += tmp1;
		io2 += tmp2;
	}
	io1 = io1/ADC_NUM_MEAN;
	io2 = io2/ADC_NUM_MEAN;


	/* test YL XH  - read allegro X*/		
         
	//         |          |          |
	//         |          |          |
    //		- X        - O        - O	
	//         |          |          |
	//         |          |          |
	//         |          |          |
	//		- O	       - X        - O	
	//         |          |          |
	//         |          |          |
		
	PWMTestCurrentMosPair(PWMMOS_YL, PWMMOS_XH, &i1, &i2);

	i1 = -(i1-io1); 
	*resI1 = i1;
	
	if ( i1 < tl){
		return 10;
	}else if( i1 > th){
		return 11;		
	}

	/* test XL YH - read allegro X*/
	//         |          |          |
	//		- O        - X        - O
	//         |          |          |						
	//         |          |          |
	//         |          |          |						
	//		- X	       - O        - O
	//         |          |          |
    //         |          |          |						
	
	PWMTestCurrentMosPair(PWMMOS_XL, PWMMOS_YH, &i1, &i2);
		
	i1 = i1-io1;

	*resI1 = i1;

	if (i1 <  tl){
		return 12;
	}else if(i1 > th){
		return 13;
	}

	/* test ZL YH - read allegro Z*/
    //         |          |          |
	//		- O        - X        - O
	//         |          |          |
	//         |          |          |
	//         |          |          |
	//         |          |          |
    //		- O	       - O        - X
    //         |          |          |
		

	PWMTestCurrentMosPair(PWMMOS_ZL, PWMMOS_YH, &i1, &i2);

	i2 = i2-io2;

	*resI2 = i2;
	if (i2 <  tl){
		return 14;
	}else if( i2 > th){
		return 15;
	}

	/* test YL ZH - read allegro Z*/
	//         |          |          |
	//         |          |          |	
	//		- O        - O        - X
	//         |          |          |
	//         |          |          |
	//         |          |          |
	//         |          |          |
	//		- O	       - X        - O	
	//         |          |          |

	PWMTestCurrentMosPair(PWMMOS_YL, PWMMOS_ZH, &i1, &i2);

    
    i2 = -(i2-io2); 

	*resI2 = i2;

	if ( i2 <  tl){
		return 16;
	}else if( i2 > th){
		return 17;
	}

	/* test XL ZH - read allegro X,Z*/

	//         |          |          |
	//		- O        - O        - X
	//         |          |          |
	//         |          |          |
	//         |          |          |
	//         |          |          |			
	//		- X	       - O        - O
	//         |          |          |					

	PWMTestCurrentMosPair(PWMMOS_XL, PWMMOS_ZH, &i1, &i2);			

	i1 = i1-io1;
	*resI1 = i1;

	if ( i1 <  tl){
		return 18;
	}else if(i1 > th){
		return 19;
	}	

	i2 = -(i2-io2);
	*resI2 = i2;

	if (i2 <  tl){
		return 20;
	}else if(i2 > th){
		return 21;
	}

	/* test ZL XH - read allegro X,Z*/
    //         |          |          |
	//		- X        - O        - O
	//         |          |          |
	//         |          |          |	
	//         |          |          |
	//         |          |          |
	//		- O	       - O        - X
	//         |          |          |
					
	PWMTestCurrentMosPair(PWMMOS_ZL, PWMMOS_XH, &i1, &i2);


	i1 = -(i1-io1);
	*resI1 = i1;

	if (i1 <  tl){
		return 22;
	}else if(i1 > th){
		return 23;
	}	
	
	i2 = (i2-io2); 
	*resI2 = i2;

	if ( i2 <  tl){
		return 24;
	}else if(i2 > th){
		return 25;
	}	

	return 0;

}