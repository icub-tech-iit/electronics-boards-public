#include <p33FJ128MC802.h>

#include "ecan.h"

#include "system.h"
#include "Status.h"
#include "can_proto_parser.h"
#include "can_proto.h"
#include "test.h"

#define TEST_OVERCURR_NUM 20


int TestReadOvercurr()
{
	int i;
	int res = 0;

	for(i=0;i<TEST_OVERCURR_NUM;i++){
		res |= (PORTBbits.RB1)?1:0;
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	}

return res;
}

void TestTris(int command_get, int *command_ok, unsigned char *txlen, tCanData *txpayload, unsigned char rxlen, tCanData *rxpayload)
{
   *txlen = 0x1;

 	if(command_get)
        {
	
          

		
          txpayload->b[0] = 0;
 		 
          switch(rxpayload->b[0]){
			// molex P6 or P1
            case 6:
            case 1:

				switch(rxpayload->b[1]){
					case 3:
					// extif1/prog1/RA3
					txpayload->b[0] = TRISAbits.TRISA3?1:0;
					break;

					case 4:
					// hu1/RP3
					txpayload->b[0] = TRISBbits.TRISB3?1:0;
					break;

					case 5:
					// hv1/RP8
					txpayload->b[0] = TRISBbits.TRISB8?1:0;
					break;

					case 6:
					// hw1/RP9
					txpayload->b[0] = TRISBbits.TRISB9?1:0;
					break;

					default:
					//invalid PIN
					*command_ok = 0;
					 txpayload->b[0] = CAN_ERROR_PARAMETER_OUT_OF_RANGE;
					break;
				}

            break;
			
			// molex P5 or P2
		    case 5:
            case 2:
            	switch(rxpayload->b[1]){
					case 3:
					// SDO1/RA4
					txpayload->b[0] = TRISAbits.TRISA4?1:0;
					break;

					case 4:
					// indx1/SDI1
					txpayload->b[0] = TRISBbits.TRISB7?1:0;
					break;

					case 5:
					// QEB1/SS1/RP6
					txpayload->b[0] = TRISBbits.TRISB6?1:0;
					break;

					case 6:
					// QEA1/SCK1/RP5
					txpayload->b[0] = TRISBbits.TRISB5?1:0;
					break;

					default:	
					//invalid PIN
					*command_ok = 0;
					 txpayload->b[0] = CAN_ERROR_PARAMETER_OUT_OF_RANGE;
					break;
				}

			break;

			default:
				// invalid connector
				*command_ok = 0;
				txpayload->b[0] = CAN_ERROR_PARAMETER_OUT_OF_RANGE;
				break;

		  }
        
		
        }
        else  // command set
        {
          switch(rxpayload->b[0]){
			// molex P6 or P1
            case 6:
            case 1:

				switch(rxpayload->b[1]){
					case 3:
					// extif1/prog1/RA3
					TRISAbits.TRISA3 = rxpayload->b[2];
					break;

					case 4:
					// hu1/RP3
					TRISBbits.TRISB3 = rxpayload->b[2];
					break;

					case 5:
					// hv1/RP8
					TRISBbits.TRISB8 = rxpayload->b[2];
					break;

					case 6:
					// hw1/RP9
					TRISBbits.TRISB9 = rxpayload->b[2];
					break;

					default:
					// invalid PIN
					*command_ok = 0;
 					*txlen = 0x1;
					txpayload->b[0] = CAN_ERROR_PARAMETER_OUT_OF_RANGE;
					break;
				}

            break;
			
			// molex P5 or P2
		    case 5:
            case 2:
            	switch(rxpayload->b[1]){
					case 3:
					// SDO1/RA4
					TRISAbits.TRISA4 = rxpayload->b[2];
					break;

					case 4:
					// indx1/SDI1
					TRISBbits.TRISB7 = rxpayload->b[2];
					break;

					case 5:
					// QEB1/SS1/RP6
					TRISBbits.TRISB6 = rxpayload->b[2];
					break;

					case 6:
					// QEA1/SCK1/RP5
					TRISBbits.TRISB5 = rxpayload->b[2];
					break;

					default:
					// invalid PIN
					*command_ok = 0;
					 *txlen = 0x1;
					txpayload->b[0] = CAN_ERROR_PARAMETER_OUT_OF_RANGE;
					break;
				}

			break;
			default:
				// invalid connector
				*command_ok = 0;
 			
				txpayload->b[0] = CAN_ERROR_PARAMETER_OUT_OF_RANGE;
				break;

		  }
            
       } 
        
  }



void TestPort(int command_get, int *command_ok, unsigned char *txlen, tCanData *txpayload, unsigned char rxlen, tCanData *rxpayload)
{
    *txlen = 0x1;
 	if(command_get)
        {
		
          
	
          txpayload->b[0] = 0;
 		 
          switch(rxpayload->b[0]){
			// molex P6 or P1
            case 6:
            case 1:

				switch(rxpayload->b[1]){
					case 3:
					// extif1/prog1/RA3
					txpayload->b[0] = PORTAbits.RA3;
					break;

					case 4:
					// hu1/RP3
					txpayload->b[0] = PORTBbits.RB3;
					break;

					case 5:
					// hv1/RP8
					txpayload->b[0] = PORTBbits.RB8;
					break;

					case 6:
					// hw1/RP9
					txpayload->b[0] = PORTBbits.RB9;
					break;
				}

            break;
			
			// molex P5 or P2
		    case 5:
            case 2:
            	switch(rxpayload->b[1]){
					case 3:
					// SDO1/RA4
					txpayload->b[0] = PORTAbits.RA4;
					break;

					case 4:
					// indx1/SDI1
					txpayload->b[0] = PORTBbits.RB7;
					break;

					case 5:
					// QEB1/SS1/RP6
					txpayload->b[0] = PORTBbits.RB6;
					break;

					case 6:
					// QEA1/SCK1/RP5
					txpayload->b[0] = PORTBbits.RB5;
					break;
				}

			break;

		  }
        
		
        }
        else  // command set
        {
          switch(rxpayload->b[0]){
			// molex P6 or P1
            case 6:
            case 1:

				switch(rxpayload->b[1]){
					case 3:
					// extif1/prog1/RA3
					LATAbits.LATA3 = rxpayload->b[2];
					break;

					case 4:
					// hu1/RP3
					LATBbits.LATB3 = rxpayload->b[2];
					break;

					case 5:
					// hv1/RP8
					LATBbits.LATB8 = rxpayload->b[2];
					break;

					case 6:
					// hw1/RP9
					LATBbits.LATB9 = rxpayload->b[2];
					break;
				}

            break;
			
			// molex P5 or P2
		    case 5:
            case 2:
            	switch(rxpayload->b[1]){
					case 3:
					// SDO1/RA4   
					LATAbits.LATA4 = rxpayload->b[2];
					break;

					case 4:
					// indx1/SDI1
					LATBbits.LATB7 = rxpayload->b[2];
					break;

					case 5:
					// QEB1/SS1/RP6
					LATBbits.LATB6 = rxpayload->b[2];
					break;

					case 6:
					// QEA1/SCK1/RP5
					LATBbits.LATB5 = rxpayload->b[2];
					break;
				}

			break;

		  }
            
       } 
        
  }


