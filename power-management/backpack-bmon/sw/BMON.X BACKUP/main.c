/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <pic16f1824.h>
#include <xc.h>                 /* XC8 General Include File */

#include <stdint.h>             /* For uint8_t definition */
#include <stdbool.h>            /* For true/false definition */

#include "system.h"             /* System functions/params */
#include "user.h"               /* User functions/params */
#include "configuration_bits.h" /* Configuration bits */
#include "i2c.h"                /* i2c */
//#include <plib/i2c.h>

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

#define LED0 RA2        // DL1 red
#define LED1 RA4        // DL2 green
#define LED2 RC5        // DL3 green
#define LED3 RC4        // DL4 green

#define VBATTMON RC3    // input battery voltage
#define IBATTMON RC2    // input battery current

#define BUTTON RA0      // push button

#define ON  1
#define OFF 0

char timer_100us=0;
char timer_1ms=0;
char timer_10ms=0;
char timer_100ms=0;
char timer_1s=0;

char cont=0;

char toggle=0;
char timer_blink=0;
char blink_ds=10;

int adc_buffer;
int VTH[7]={0x0253, 0x0279, 0x0293, 0x02C3, 0x02E8, 0x030D, 0x0333};
// VTH = {32V, 34V, 36V, 38V, 40V, 42V, 44V}

//int VTH0=0x0279;        /* Voltage threshold 0 -> 34V */
//int VTH1=0x0293;        /* Voltage threshold 1 -> 36V */
//int VTH2=0x02C3;        /* Voltage threshold 2 -> 38V */
//int VTH3=0x02E8;        /* Voltage threshold 2 -> 40V */
//int VTH4=0x030D;        /* Voltage threshold 2 -> 42V */

int read_adc(char input);       /* read the ADC */
void readButton(void);          /* read the test button */
void displayCharge(void);       /* display status charge with leds */
void lightupLed(char lightup);  /* lightup/blink led  */
//void blinkLed(char blink);      /* blink led  */
void blink();                   /* blink timer */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    I2cInitMaster();
    
    while(1)
    {
        if (timer_100us >= 1){      /* ------------- ciclo 100us ------------ */
            timer_100us=0;
            timer_1ms++;
            //LED0=LED0^1;
        }

        if (timer_1ms >= 10){        /* ------------- ciclo 1ms -------------- */
            timer_1ms=0;
            timer_10ms++;
            I2cStart();
            I2cWriteMaster(ADRESH);
            I2cWriteMaster(ADRESL>>6);
            //I2cWriteMaster(BUTTON);
            //I2cWriteMaster(toggle);
            I2cStop();
            //LED1=LED1^1;
        }

        if (timer_10ms >= 10){      /* ------------- ciclo 10ms ------------- */
            timer_10ms=0;
            timer_100ms++;
            //LED1=LED1^1;
        }

        if (timer_100ms >= 10){     /* ------------- ciclo 100ms ------------ */
            timer_100ms=0;
            timer_1s++;
            
            blink(blink_ds);

            if(!PIR1bits.ADIF)  {read_adc(VBATTMON);}
            displayCharge();
            readButton();
            cont++;
            //LED2=LED2^1;
        }

        if (timer_1s >= 10){     /* ---------------- ciclo 1s --------------- */
            timer_1s=0;
            //LED3=LED3^1;
        }
    }
}


int read_adc(char input){
    if      (input==VBATTMON)   {ADCON0bits.CHS=0b00111;}   // AN7
    else if (input==IBATTMON)   {ADCON0bits.CHS=0b00110;}   // AN6
    ADCON0bits.GO_nDONE=1;      // Start conversion
}

void readButton(void){
    if(BUTTON==1){
        //LED0=LED0^1;
    }
}

void displayCharge(void){
    if(adc_buffer < VTH[0]){
        blink_ds=1;
        lightupLed(0b00010001);     /* light up LED0 */
    }
    else if(adc_buffer < VTH[1]){
        blink_ds=2;
        lightupLed(0b00010001);     /* light up LED0 */
    }
    else if(adc_buffer < VTH[2]){
        lightupLed(0b00000001);     /* light up LED0 */
    }
    else if(adc_buffer < VTH[3]){
        lightupLed(0b00000011);     /* light up LED1 */
    }
    else if(adc_buffer < VTH[4]){
        lightupLed(0b00000111);     /* light up LED2 */
    }
    else if(adc_buffer < VTH[5]){
        lightupLed(0b00001111);     /* light up LED3 */
    }
    else if(adc_buffer < VTH[6]){
        blink_ds=2;
        lightupLed(0b00011111);     /* light up LED3 */
    }
    else{
        blink_ds=1;
        lightupLed(0b00011111);     /* light up LED3 */
    }
}

void lightupLed(char lightup){
    /* lightup<7:4> blink, lightup<3:0> light up */
    char blink = toggle & (lightup>>4 & 0x01);
    LED0 = (!(lightup    & 0x01)) || blink;
    LED1 = (!(lightup>>1 & 0x01)) || blink;
    LED2 = (!(lightup>>2 & 0x01)) || blink;
    LED3 = (!(lightup>>3 & 0x01)) || blink;
}

/*void blinkLed(char blink){
    LED0 = !(blink    & 0x01);
    LED1 = !(blink>>1 & 0x01);
    LED2 = !(blink>>2 & 0x01);
    LED3 = !(blink>>3 & 0x01);
}*/

void blink(){
    timer_blink++;
    if(timer_blink >= blink_ds){
        toggle = toggle^1;
        timer_blink=0;
    }
}