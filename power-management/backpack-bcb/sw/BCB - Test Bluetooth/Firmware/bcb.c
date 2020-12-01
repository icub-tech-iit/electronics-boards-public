 /****************************************************
 *  BCB board - iCub Facility - 2013                 *
 *  Main program                                     *
 *                                                   *
 *  Written by Andrea Mura                           *
 *  <andrea.mura@iit.it>                             *
 ****************************************************/


// ----------------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdbool.h>
#include "STM32F10x.h"
#include "define.h"
#include "globals.h"
#include "gpio.h"
#include "adc.h"
#include "can.h"
#include "exti.h"
#include "timer.h"
#include "usart.h"
#include "bmon.h"

// ----------------------------------------------------------------------------
// Global variables
// ----------------------------------------------------------------------------
bool V12board           = 0;        // DCDC board control
bool V12board_F         = 0;        // fault
bool V12motor           = 0;        // DCDC motor control
bool V12motor_F         = 0;        // fault
bool HSM                = 0;
bool HSM_PG             = 0;
bool HSM_F              = 0;
bool DCrestart          = 0;
int DCDC_ctrl           = 0;
int DCDC_status         = 0;
int ext_status          = 0;

int filter_PB1          = 0;
int filter_PB2          = 0;
int filter_fault_gpio   = 0;
int timer_debounce      = 10;       // 10x (10ms timer) = 100ms
int timer_restart       = 100;		// 100x (10ms timer) = 1s

char timer_100us        = 0;
char timer_1ms          = 0;
char timer_10ms         = 0;
char timer_100ms        = 0;
char timer_1s           = 0;

bool sendBT             = 0;
bool can_led_active     = 0;
bool toggle             = 0;
bool togglex2           = 0;
bool fault              = 1;
bool jack               = 0;

bool PB1_debounce       = 0;
bool PB1_restart        = 0;
bool PB2_debounce       = 0;
bool PB2_restart        = 0;
bool int_fault          = 0;

uint8_t BMON_RX[6] = {0};
uint8_t pippo;

unsigned int ledExti=0;

// ----------------------------------------------------------------------------
// Local variables
// ----------------------------------------------------------------------------
int *adc_values;
int adc_val[1];
int VBATT;

char state_fsm			= START;
char state_fsm_prec	;
char timerFSM           = 0;        // timer macchina a stati finiti

int cont=0;
int rx=0;
uint8_t BT_RXmsg[256];
uint8_t rxlength;
int message=0;
char text[17];
unsigned int val_Tx = 0, val_Rx = 0;    // Globals used for display

unsigned int testCont1=0;
unsigned int testCont2=0x1fff;
unsigned int testCont3=0xffff;
unsigned char up=1;


// ----------------------------------------------------------------------------
// Initialize CAN interface
// ----------------------------------------------------------------------------
void CAN_init (void) {
    CAN_setup();																// setup CAN Controller     
    CAN_wrFilter (0x621, STANDARD_FORMAT);			// Enable reception of PC messages 

    // ! COMMENT LINE BELOW TO ENABLE DEVICE TO PARTICIPATE IN CAN NETWORK !    
    //CAN_testmode(CAN_BTR_SILM | CAN_BTR_LBKM);      // Loopback, Silent Mode (self-test)

    CAN_start ();																// start CAN Controller   
    CAN_waitReady ();														// wait till tx mbx is empty 
}


// ----------------------------------------------------------------------------
// Finite state machine - DCDC power management
// ----------------------------------------------------------------------------
void dcdc_management(void){
	
	if(V12board_F==0 && V12motor_F==0 && HSM_F==0){                                         // if BDC is ok...
		if(PB1_debounce){
			PB1_debounce=0;
			if(V12board)                            {state_fsm = OFF_BOARD_MOTORS;}         // if V12board is on, switch off
			else                                    {state_fsm = ON_BOARD;}                 // else if V12board is off, switch on
		}
		
		if(PB2_debounce){
			PB2_debounce=0;
			if      (V12motor)                      {state_fsm = ON_BOARD;}                 // if V12motor is on, switch off
			else if (!V12motor && V12board)         {state_fsm = ON_BOARD_MOTORS;}          // else if V12motor is off and V12board is on, switch on
		}	
	}
	else{																																			// else if BDC has fault...
		if(V12board_F==0 && (V12motor_F==1 || HSM_F==1)){
			if(PB1_debounce){
				PB1_debounce=0;
				if(V12board)                        {state_fsm = OFF_BOARD_MOTORS;}         // if V12board is on, switch off
				else                                {state_fsm = ON_BOARD;}                 // else if V12board is off, switch on
			}
			else{
				if(PB2_restart==0)                  {state_fsm = FAULT_MOTORS;}
				else{
					if(V12board)                    {state_fsm = ON_BOARD_MOTORS;}          // if V12board is on, switch off
					else                            {state_fsm = OFF_BOARD_MOTORS;}         // else if V12board is off, switch on
				}
			}
		}
		else if(V12board_F==1){
			if(PB1_restart==0){
				if(V12motor_F==1 || HSM_F==1)       {state_fsm = FAULT_BOARD_MOTORS;}
				else                                {state_fsm = FAULT_BOARD;}
			}
			else if(PB1_restart==1){
				state_fsm = ON_BOARD;
				//V12board_F=0;
			}
		}
	}
	
	
	
	
	switch(state_fsm){
	
		case START:                 // ----------------------------------------------------------- //
			timerFSM++;
			state_fsm_prec = START;
		
			if(timerFSM >= 10){
				state_fsm = READY;
			}
		break;
		
		case READY:                 // ----------------------------------------------------------- //
			timerFSM = 0;
						
		break;
		
		case OFF_BOARD_MOTORS:		// ----------------------------------------------------------- //
			V12board=0;             // switch off V12board
			V12motor=0;             // switch off V12motor
			HSM=0;                  // switch off HSM
			PB1_LED_RED;
			PB2_LED_RED;
		break;
		
		case ON_BOARD:              // ----------------------------------------------------------- //
			V12board=1;             // switch on V12board
			V12motor=0;             // switch off V12motor
			HSM=0;                  // switch off HSM
			PB1_LED_GREEN;
			PB2_LED_RED;
		break;
		
		case ON_BOARD_MOTORS:       // ----------------------------------------------------------- //
			V12board=1;             // switch on V12board
			V12motor=1;             // switch on V12motor
			HSM=1;                  // switch on HSM
            if(HSM_PG==0){
                if(toggle)  {PB2_LED_GREEN;}
                else        {PB2_LED_OFF;}
			}
            else{
                PB2_LED_GREEN;
            }
		break;
		
		case FAULT_BOARD:           // ----------------------------------------------------------- //
			V12board=0;             // switch off V12board
			V12motor=0;             // switch off V12motor
			HSM=0;                  // switch off HSM
			if(toggle)  {PB1_LED_RED;}
			else        {PB1_LED_OFF;}
			PB2_LED_RED;
		break;
			
		case FAULT_MOTORS:          // ----------------------------------------------------------- //
			//V12board=1;           // switch on V12board
			V12motor=0;             // switch off V12motor
			HSM=0;                  // switch off HSM
			if(toggle)  {PB2_LED_RED;}
			else        {PB2_LED_OFF;}
		break;
			
		case FAULT_BOARD_MOTORS:    // ----------------------------------------------------------- //
			V12board=0;             // switch off V12board
			V12motor=0;             // switch off V12motor
			HSM=0;                  // switch off HSM
			if(toggle)  {PB1_LED_RED;       PB2_LED_RED;}
			else        {PB1_LED_OFF;       PB2_LED_OFF;}
		break;
            
        case FAULT:                 // ----------------------------------------------------------- //
			//V12board=1;             // switch on V12board
			//V12motor=1;             // switch on V12motor
			//HSM=1;                  // switch on HSM
            PB1_LED_GREEN;
			if(toggle)  {PB2_LED_GREEN;}
			else        {PB2_LED_OFF;}
		break;
		
	
	}
	
	
	
    DCDC_ctrl = ((V12board		& 0x01) << 7) +
                ((V12motor		& 0x01)	<< 5) +
                ((HSM           & 0x01)	<< 3) +
                (((PB1_restart || PB2_restart) & 0x01)	<< 0);
    
    //ext_status = 
	
    if(DCrestart){
        PB1_restart=0;
        PB2_restart=0;
    }
}





// ----------------------------------------------------------------------------
// CAN messages management
// ----------------------------------------------------------------------------
void CANBUS(void){
    if (CAN_TxRdy) {		
            CAN_TxRdy = 0;
            CAN_TxMsg.id = 0x612;

            if(message==0){
                CAN_TxMsg.data[0] = 0x00;				//
                CAN_TxMsg.data[1] = DCDC_ctrl;
                message=1;
            }
            else if(message==1){
                CAN_TxMsg.data[0] = 0x01;				// Voltage message
                CAN_TxMsg.data[1] = DCDC_ctrl;
                message=2;
            }
            else if (message==2){
                CAN_TxMsg.data[0] = 0x02;				// Current message
                CAN_TxMsg.data[1] = DCDC_ctrl;
                message=0;
            }

            CAN_TxMsg.data[2] = ((VBATT>> 8) & 0xFF);
            CAN_TxMsg.data[3] = VBATT & 0xFF;
            CAN_TxMsg.data[4] = cont & 0xFF;
            CAN_TxMsg.data[5] = BMON_RX[2];
            CAN_TxMsg.data[6] = BMON_RX[3];
            //CAN_TxMsg.data[7] = BMON_RX[2];
            //CAN_TxMsg.data[8] = BMON_RX[3];
            //CAN_TxMsg.data[4] = V12board;
            //CAN_TxMsg.data[5] = V12motor;
            //CAN_TxMsg.data[6] = HSM;
            CAN_wrMsg (&CAN_TxMsg);
    }
    //else {CAN_LED_OFF;}


    if (CAN_RxRdy){                                 //rx msg on CAN Ctrl
            CAN_RxRdy = 0;
            DCDC_status = CAN_RxMsg.data[1];

            V12board_F  = (DCDC_status >> 6 ) & 0x01;
            V12motor_F  = (DCDC_status >> 4 ) & 0x01;
            HSM_PG      = (DCDC_status >> 2 ) & 0x01;
            HSM_F       = (DCDC_status >> 1 ) & 0x01;
            DCrestart   = (DCDC_status >> 0 ) & 0x01;
    }

    if(can_led_active>0){                           // blink can led
            if(toggle)  {CAN_LED_ON;}
            else        {CAN_LED_OFF;}
            can_led_active--;
    }
    else	{CAN_LED_OFF;}

}


// ----------------------------------------------------------------------------
// BMON messages management
// ----------------------------------------------------------------------------
void BMON(void){
    BMON_ReadRegister(0x5A, 0x00, BMON_RX, 6);       // SKIN address
    
}


// ----------------------------------------------------------------------------
// Bluetooth messages management
// ----------------------------------------------------------------------------
void Bluetooth(void){
    int ok=0;
    //rx=GetKey2();
    GetString2(BT_RXmsg, &rxlength);
    
    rx=BT_RXmsg[0];
    
    switch(BT_RXmsg[0]){
    
        case 0x72: // ---------------------- r=read register
            switch(BT_RXmsg[1]){
                
                case 0x01:  SendChar2(BMON_RX[0]);  SendChar2(BMON_RX[1]);              break;
                case 0x02:  SendChar2(BMON_RX[2]);  SendChar2(BMON_RX[3]);              break;
                case 0x03:  SendChar2(BMON_RX[4]);  SendChar2(BMON_RX[5]);              break;
                case 0x04:  SendChar2(DCDC_ctrl);                                       break;            
                case 0x05:  SendChar2(sendBT);                                          break;
                case 0x06:  SendChar2(up);                                              break;
                
            }
        break;
        
        case 0x77: // ---------------------- w=write register
            
            switch(BT_RXmsg[1]){
                
                case 0x01:  // 
                    switch(BT_RXmsg[2]){
                        case 0x00: PB1_LED_OFF;         ok=1; break;
                        case 0x01: PB1_LED_RED;         ok=1; break;
                        case 0x02: PB1_LED_GREEN;       ok=1; break;
                    }
                break;
                    
                case 0x02:
                    switch(BT_RXmsg[2]){
                        case 0x00: PB2_LED_OFF;         ok=1; break;
                        case 0x01: PB2_LED_RED;         ok=1; break;
                        case 0x02: PB2_LED_GREEN;       ok=1; break;
                    }
                break;
                
                case 0x03:
                    switch(BT_RXmsg[2]){
                        case 0x00: sendBT=0;            ok=1; break;
                        case 0x01: sendBT=1;            ok=1; break;
                    }
                break;
                    
                case 0x04:
                    DCDC_ctrl=BT_RXmsg[2];              ok=1;
                break;
                
                case 0x05:
                    switch(BT_RXmsg[2]){
                        case 0x00: up=0;                ok=1; break;
                        case 0x01: up=1;                ok=1; break;
                    }
                break;
                
            }
            
            if(ok==1 && rxlength>0)  {SendUart2(BT_RXmsg, rxlength); ok=0;}     // se il comando è stato recepito, rispondo con lo stesso messaggio ricevuto
            
        break;
        
        default: // ---------------------- echo
            if(rxlength>0)  {SendUart2(BT_RXmsg, rxlength);}
        break;
    
    }
    
    if(up)  {testCont1++;    testCont2++;     testCont3++;}
    else    {testCont1--;    testCont2--;     testCont3--;}
    
    BMON_RX[0]=testCont1>>8 & 0xFF;
    BMON_RX[1]=testCont1 & 0xFF;
    BMON_RX[2]=testCont2>>8 & 0xFF;
    BMON_RX[3]=testCont2 & 0xFF;
    BMON_RX[4]=testCont3>>8 & 0xFF;
    BMON_RX[5]=testCont3 & 0xFF;
    
    //if(rxlength>0)  {SendUart2(BT_RXmsg, rxlength);}
    
    if(sendBT){
        SendUart2(BMON_RX, sizeof(BMON_RX));
        SendChar2(DCDC_ctrl);
    }
    
    BT_RXmsg[0]=0;
}






// ----------------------------------------------------------------------------
// MAIN function
// ----------------------------------------------------------------------------
int main (void) {
	int i;
	
    BCB_GPIO_Init();			// Initialize GPIO
    EXTI_Init();			// Initialize interrupts
    TIM1_Init();			// Initialize Timer1
    TIM2_Init();			// Initialize Timer2
    TIM3_Init();			// Initialize Timer3
    TIM4_Init();			// Initialize Timer4
    ADC_Init();				// Initialize ADC
    CAN_init();				// Initialize CAN
    //USART1_Init();	// Initialize USART1
    USART2_Init();		// Initialize USART2
    BMON_Init();             // Initialize I2C for BMON reading 
    BT_ON;						// Switch on Bluetooth module
    FAULT_REM_ON;
	
    CAN_TxMsg.id = 0x612;
    for (i = 0; i < 8; i++) CAN_TxMsg.data[i] = 0;
    CAN_TxMsg.len = 8;
    CAN_TxMsg.format = STANDARD_FORMAT;
    CAN_TxMsg.type = DATA_FRAME;


    PB1_LED_RED;
    PB2_LED_RED;
    FAN1_ON;
    FAN2_ON;
    CAN_LED_OFF;
    //V12board=1;
    //PB1_LED_GREEN;
    //LED_BT_OFF;
	
  while (1) {
        if (timer_100us >= 1){      //----------------------------- 100us -----------------------------
            timer_100us=0;
            timer_1ms++;
        }
		
        if (timer_1ms >= 10){       //----------------------------- 1ms -------------------------------
            timer_1ms=0;
            timer_10ms++;

            ADC_StartCnv();                      // start A/D conversion 12bit
            adc_values = ADC_Conv();
            ADC_StopCnv();                       // stop A/D conversion

            VBATT=(*adc_values)*14.195;          // conversion in mV

            //dcdc_management();
            //CANBUS();

            //BMON();

            //SendChar2(cont);
            //SendChar2(cont);
            //rx=GetKey2();
        }
		
		
        if (timer_10ms >= 10){      //----------------------------- 10ms -----------------------------
            timer_10ms=0;
            timer_100ms++;
            //SendChar1(0x05);

            //dcdc_management();
            //CANBUS();
            //if((GPIOC->IDR & FAULT_GPIO) == 0 )   {LED_BT_ON;}
            //else                            {LED_BT_OFF;}
            
            if(sendBT){
                if(toggle)  {LED_BT_ON;}
                else        {LED_BT_OFF;}
            }
            else            {LED_BT_OFF;}
            
            
            if(int_fault){
                
                if( (!(GPIOC->IDR & FAULT_REM) == 0) && (
                    ( ((GPIOC->IDR & JACK)  == 0) && (!(GPIOC->IDR & FAULT_GPIO) == 0) ) ||
                    ( (!(GPIOC->IDR & JACK) == 0) && (GPIOC->IDR & FAULT_GPIO)  == 0)  )
                    ) {             // NO FAULT
                    if(filter_fault_gpio<timer_debounce){             
                        filter_fault_gpio++;                    
                    }
                    else if(filter_fault_gpio==timer_debounce){     // comando valido
                        //LED_BT_OFF;
                        filter_fault_gpio=0;
                        int_fault=0;
                    }
                }
                else{               // FAULT!!!!
                    if(filter_fault_gpio>-timer_debounce){             
                        filter_fault_gpio--;                    
                    }
                    else if(filter_fault_gpio==-timer_debounce){    // comando valido
                        //LED_BT_ON;
                        filter_fault_gpio=0;
                        int_fault=0;
                    }    
                }
            }

            

		}
		
		if (timer_100ms >= 10){		//----------------------------- 100ms -----------------------------
			timer_100ms=0;
			timer_1s++;
			
            toggle ^= 1;
            if(toggle)  {togglex2 ^=1;}
                    
			//CANBUS();
			//dcdc_management();
            
            Bluetooth();
            
            
	
		}
		
		if (timer_1s >= 5){		//----------------------------- 1s ---------------------------------
			timer_1s=0;
            
            //Bluetooth();
   
			cont++;
		}
		
	}
}
