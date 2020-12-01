//   
//  ADC related rouines:
//  Measure Current & VDC-Link
//
//  Initialization, control and fault management 
//

#include <p33FJ128MC802.h>
#include <libpic30.h> /*__delay32 */

#include "ADC.h"
#include "Status.h"
#include "system.h"
#include "faults.h"



#define ADC_VDCLINK_ALLEGRO_MIN_THRESHOLD 120

void ADCInterruptAndDMAEnable(void)
// Enable DMA interrupt, arm DMA for transfer
{
  //Clear the DMA interrupt flag bit
  IFS0bits.DMA0IF = 0; 
  //Set the DMA interrupt enable bit
  IEC0bits.DMA0IE = 1; 
  // amplifiers holding
  AD1CON1bits.SAMP = 1;
  // no valid result is present
  AD1CON1bits.DONE = 0;
  // Clear the A/D interrupt flag bit
  IFS0bits.AD1IF = 0; 
  // Turn on DMA
  DMA0CONbits.CHEN = 1;
  // Turn on A/D module
  AD1CON1bits.ADON = 1;
}

void ADCInterruptAndDMADisable(void)
// Disable DMA interrupt, disarm DMA
{
  // Turn off DMA
  DMA0CONbits.CHEN = 0;
  // Turn off A/D module
  AD1CON1bits.ADON = 0;
  // reset the DMA interrupt enable bit
  IEC0bits.DMA0IE = 0; 
}

SFRAC16 ADCGetVDCLink()
// This quickly returns VDCLink SFRAC value.
{
  return  (ADCBuffer[2]);
}

unsigned int ADCTo10bit(SFRAC16 adc)
{
  unsigned int tmp;
 //convert to full scale unsigned int
  tmp = adc;
  tmp -= 1<<15;

  // convert to 10 bit unsigned int and mult by 10
  tmp = tmp >> 6;


  return tmp;

}

unsigned int ADCVDCLinkTo100mV(SFRAC16 vadc)
// This return VDC link value in 100mV units.
// It can be used for CAN information message
// or maybe to implement VDClink voltage protection.
// However AdcGetVDCLink() function is faster, so 
// consider using it for voltage protection stuff.
{
  
  double tmp2;
  unsigned int tmp;

  tmp = vadc;

  // convert to 10 bit unsigned int and mult by 10
  tmp = tmp >> 5;
  tmp *= 5;

  tmp2 = tmp;

  // VonAdcPads = VDC * 0.04592 (from input resistor scaling 100K, 4.7K)
  // AdcReadVal = VDC * 0.04592 / 3.3 * 1024 = 14.249115
  // VDC = AdcReadVal / 14.249115
  // TODO: ....e poi, una divisione con un finto float????
  //   forse sarà il caso di farla in FIXED 1.15 !!!

  tmp2 /= 14.249115; 
  tmp = tmp2 ;
  return (tmp);
}



void ADCConfigPWMandDMAMode()
// Confure ADC regisaters for PWM sync and DMA transfer
{
  // zero configuration 
  AD1CON1 = 0;
  AD1CON2 = 0;
  AD1CON3 = 0;
  
  // 10 bits
  AD1CON1bits.AD12B = 0;
  
  // A/D Conversion Clock (TAD). must be >= 75ns.
  // 40Mhz clk = 25 ns (TCY).
  // TAD = TCY * (ADCS+1)
  // TAD = 25*3 = 75 ns
  // Conversion time = TAD*12 = 900ns 
// TODO: il valore di conversione ha influenza sul ritardo con cui parte il calcolo della SVG 
// 0.9ns + tempo di calcolo deve essere < di TPWM/2  
  // AM portato a 4. Empiricamente si vede meno rumore su DCLink.
  // Su lettura di corrente sembra migliorare leggermente
  AD1CON3bits.ADCS = 4;   // AD1CON3bits.ADCS = 2;  

  // Samples CH0, CH1, CH2, CH3 simultaneously (when CHPS = 1x)
  AD1CON2bits.CHPS = 2;  

  // Samples multiple channels simultaneous
  AD1CON1bits.SIMSAM = 1; 

  // Sampling begins immediately after last conversion completes. 
  // SAMP bit is auto set
  AD1CON1bits.ASAM = 1;  

  // PWM triggered conversion
  AD1CON1bits.SSRC = 3; 

  // Signed fractional (DOUT = sddd dddd dd00 0000)
  AD1CON1bits.FORM = 3;    

  // Interrupt after every conversion!
  AD1CON2bits.SMPI = 0;
   
  // One sample per cycle on each ch
  AD1CON4 = 0;
    
  // Do not scan!
  AD1CON2bits.CSCNA = 0;

  // ADCHS: ADC Input Channel Select Register
  AD1CHS0 = 0;
	
  // CH0 is unused. connect to a dummy AN
  AD1CHS0bits.CH0SA = 3;
  // CH1 positive input is AN0, CH2 positive input is AN1, CH3 positive input is AN2
  AD1CHS123bits.CH123SA = 0;

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
  DMA0CNT = 3;
  // attach DMA0 transfer to ADC
  DMA0REQ = 13;

  // set address of dma buffer    
  DMA0STA = __builtin_dmaoffset(ADCBuffer);
}
//int adc_dbg[2];
void ADCConfigureRegistersForSyncRead()
// Configure ADC registers for calibration without PWM sync and DMA
{
  // zero configuration 
  AD1CON1 = 0;
  AD1CON2 = 0;
  AD1CON3 = 0;
    
  // A/D Conversion Clock Select bits = 21 * Tcy
  AD1CON3bits.ADCS = 7; //adc_dbg[0];

	// not used in man mode
  AD1CON3bits.SAMC = 0;


  // sample only from ch0 
  AD1CON2bits.CHPS = 0;  

  // Samples multiple channels individually in sequence
  AD1CON1bits.SIMSAM = 0; 

  // Sampling begins immediately after last conversion completes. 
  // SAMP bit is auto set
  AD1CON1bits.ASAM = 0;  

  // sampling in manual mode
  AD1CON1bits.SSRC = 0; 

  // Signed fractional (DOUT = sddd dddd dd00 0000)
  AD1CON1bits.FORM = 3;    

  // Interrupt after every conversion!
  AD1CON2bits.SMPI = 0;
   
  // One sample per cycle on each ch
  AD1CON4 = 0;
    
  // Do not scan for calibration !
  AD1CON2bits.CSCNA = 0;

  // Channel 0 negative input is VREF-
  AD1CHS0 = 0; 	
}

int ADCReadFast(int *i1, int *i2)
{
  int TOT;
  long ADCVal1;
  long ADCVal2;
  
  ADCVal1 = 0;
  ADCVal2 = 0;

  ADCConfigureRegistersForSyncRead(); 
  AD1CON1bits.AD12B = 1;
  // Turn on ADC module
  AD1CON1bits.ADON = 1;
 	

// READ PH 0 /////////////////////////////////////////////////////////


 // Samples AN2 (Vdc)
    AD1CHS0bits.CH0SA = 0;

    AD1CON1bits.DONE = 0;
    // amplifiers holding
    AD1CON1bits.SAMP = 1;

    // TODO TRIM ME 
    __delay32(8000);

    // convert!
    AD1CON1bits.SAMP = 0;
    // don't mind about int generated

    // init time out timer
    TOT=0;
    // poll for end of conversion
    while( 0 == AD1CON1bits.DONE )
    {
      // Avoids polling lock
      if (ADC_CAL_TIMEOUT == ++TOT)
      {
        // offset correction error signaling 
   
        return -1;
      }
    }

    // accumuulate values
    // + 0x8000 to transform signed to unsigned
	ADCVal1 = ADC1BUF0;


// READ PH 1 /////////////////////////////////////////////////


 // Samples AN2 (Vdc)
    AD1CHS0bits.CH0SA = 1;

    AD1CON1bits.DONE = 0;
    // amplifiers holding
    AD1CON1bits.SAMP = 1;

    // TODO TRIM ME 
    __delay32(200);

    // convert!
    AD1CON1bits.SAMP = 0;
    // don't mind about int generated

    // init time out timer
    TOT=0;
    // poll for end of conversion
    while( 0 == AD1CON1bits.DONE )
    {
      // Avoids polling lock
      if (ADC_CAL_TIMEOUT == ++TOT)
      {
        // offset correction error signaling 
   
        return -1;
      }
    }

    // accumuulate values
    // + 0x8000 to transform signed to unsigned
	ADCVal2 = ADC1BUF0;


  

   
  // Turn off ADC module
  AD1CON1bits.ADON = 0;


  *i1 = /*(unsigned int)ADCTo10bit*/(ADCVal1);
  *i2 = /*(unsigned int)ADCTo10bit*/(ADCVal2);

  return 0;
}


int ADCRead(unsigned int *vdc, int *i1, int *i2)
{
// Calculate mean value of ADC_CAL_N_SAMPLES samples for iA, iB and Vdc and store in
// ADCVal1, ADCVal2 and ADCVdc
// DMA AND ADC isr are not enabled here!
 
  int i,TOT;
  long ADCVdc;
  long ADCVal1;
  long ADCVal2;
  unsigned int tmp;
 //static int curr;

  ADCVdc = 0;
  ADCVal1 = 0;
  ADCVal2 = 0;

  ADCConfigureRegistersForSyncRead(); 
  // Turn on ADC module
  AD1CON1bits.ADON = 1;
 	
  for(i=0;i<ADC_CAL_N_SAMPLES;i++)
  {

// READ VDC ///////////////////////////////////////////////////	
    // Samples AN2 (Vdc)
    AD1CHS0bits.CH0SA = 2;

    AD1CON1bits.DONE = 0;
    // amplifiers holding
    AD1CON1bits.SAMP = 1;

    // TODO TRIM ME 
    __delay32(1000);

    // convert!
    AD1CON1bits.SAMP = 0;
    // don't mind about int generated

    // init time out timer
    TOT=0;
    // poll for end of conversion
    while( 0 == AD1CON1bits.DONE )
    {
      // Avoids polling lock
      if (ADC_CAL_TIMEOUT == ++TOT)
      {
        // offset correction error signaling 
   
        return -1;
      }
    }

    // accumuulate values
    // + 0x8000 to transform signed to unsigned
	tmp = ADC1BUF0 + 0x8000 ;
    ADCVdc += tmp;
   /* if the measured VDCLINK is lower than this threshold
    * then we cannot be sure the Allegro are properly powered.
    * For this reason the ADC calibration is not reliable.
    */
     if(ADCVDCLinkTo100mV(tmp) < ADC_VDCLINK_ALLEGRO_MIN_THRESHOLD)
	   return -2;

// READ PH 0 /////////////////////////////////////////////////////////


 // Samples AN2 (Vdc)
    AD1CHS0bits.CH0SA = 0;

    AD1CON1bits.DONE = 0;
    // amplifiers holding
    AD1CON1bits.SAMP = 1;

    // TODO TRIM ME 
    __delay32(1000);

    // convert!
    AD1CON1bits.SAMP = 0;
    // don't mind about int generated

    // init time out timer
    TOT=0;
    // poll for end of conversion
    while( 0 == AD1CON1bits.DONE )
    {
      // Avoids polling lock
      if (ADC_CAL_TIMEOUT == ++TOT)
      {
        // offset correction error signaling 
   
        return -1;
      }
    }

    // accumuulate values
    // + 0x8000 to transform signed to unsigned
	ADCVal1 += ADC1BUF0;



// READ PH 1 /////////////////////////////////////////////////


 // Samples AN2 (Vdc)
    AD1CHS0bits.CH0SA = 1;

    AD1CON1bits.DONE = 0;
    // amplifiers holding
    AD1CON1bits.SAMP = 1;

    // TODO TRIM ME 
    __delay32(1000);

    // convert!
    AD1CON1bits.SAMP = 0;
    // don't mind about int generated

    // init time out timer
    TOT=0;
    // poll for end of conversion
    while( 0 == AD1CON1bits.DONE )
    {
      // Avoids polling lock
      if (ADC_CAL_TIMEOUT == ++TOT)
      {
        // offset correction error signaling 
   
        return -1;
      }
    }

    // accumuulate values
    // + 0x8000 to transform signed to unsigned
	ADCVal2 += ADC1BUF0;


  }

  // divide for number of samples in order to get mean
  ADCVal1 /= (long)ADC_CAL_N_SAMPLES;
  ADCVal2 /= (long)ADC_CAL_N_SAMPLES;
  ADCVdc /= (long)ADC_CAL_N_SAMPLES;
   
  // Turn off ADC module
  AD1CON1bits.ADON = 0;

  *vdc = (unsigned int)ADCVDCLinkTo100mV((SFRAC16)ADCVdc);

  *i1 = (unsigned int)ADCTo10bit(ADCVal1);
  *i2 = (unsigned int)ADCTo10bit(ADCVal2);

  return 0;
}
