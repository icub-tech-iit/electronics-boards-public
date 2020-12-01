#include <p33FJ128MC802.h>
#include <string.h>

#include "ecan.h"
#include "UserParms.h"

#include "system.h"
#include "Status.h"
#include "DSP.h"
#include "can_proto_parser.h"
#include "can_proto.h"
#include "faults.h"
#include "test.h"
#include "adc.h"

#include <libpic30.h> 

static unsigned char canprotoparser_bid;

void CanProtoParserInit(unsigned char bid)
{
	canprotoparser_bid = bid;
}
//extern int adc_dbg[2];
void CanProtoParserParse(unsigned long rxid, unsigned char rxlen, tCanData *rxpayload)
// Parse CAN commands
{
  // Command Syntax ok  
  int command_ok;
  // Read/!write data command
  int command_get;
  unsigned int vdc;
  int i1,i2;

  unsigned char txlen = 0;

  tCanData txpayload;

  int res;


  // outgoing message (error, acknowledge or answer) 
  if(CAN_PROTO_ID_ISEXTENDED(rxid))
  {
    

    // you are innocent until counter-proof
    command_ok = 1;
    // if the command is a set or get request
    command_get = CAN_PROTO_ID_ISGET(rxid);

    // Less significant byte of Message Id represents the command number
    switch( CAN_PROTO_ID_CMD(rxid))
    {
		int e,l;

/*	case 0x99:	
		adc_dbg[0] = rxpayload->b[0];
		adc_dbg[1] = rxpayload->b[1];
break;*/
		case CAN_CMD_TEST_PWM_CYCLE:
	
		
		if(command_get)
        {
          // trying to read write only data
     	  PWMGetState(&e, &l);
          txlen=0x3;
          txpayload.b[0] = e;
          txpayload.b[1] = l;
		  txpayload.b[2] = SysError.OverCurrentFailure;
        }
        else
        {
          if (2 == rxlen)
          {
           e = l = 0;

           e = rxpayload->b[0];
           if(rxpayload->b[1]) l = 1;

		   PWMCycle(e,l);	
          }
          else
          {
            // incorrect number of parameters
            command_ok = 0;
            txlen=0x1;
            txpayload.b[0] = CAN_ERROR_INCORRECT_NUMBER_OF_PARAMETERS;
          }
        }
        break;


		case CAN_CMD_TEST_PWM_CURRENT:
	
		
		if(command_get)
        {
          if(4 == rxlen){
	        // trying to read write only data
	     	e = PWMTestCurrent(0,&i1,&i2, rxpayload->w[0], rxpayload->w[1]);
			
			if(e || SysError.OverCurrentFailure){
				txlen=0x6;
		        txpayload.b[0] = e;
				txpayload.b[1] = SysError.OverCurrentFailure;
				txpayload.w[1] = i1;
				txpayload.w[2] = i2;
			}else{
		        txlen=0x2;
		        txpayload.b[0] = e;
				txpayload.b[1] = SysError.OverCurrentFailure;
			}
          }else{
              // parameter out of range
              command_ok = 0;
              txlen=0x1;
              txpayload.b[0] = CAN_ERROR_PARAMETER_OUT_OF_RANGE;
          }
        }
        else
        {
        	// Error, trying to write a read-only parameter
	        command_ok = 0;
	        txlen=0x1;
	        txpayload.b[0] = CAN_PROTO_ERROR_WRITE_READ_ONLY_DATA;
        }
        break;

		case CAN_CMD_TEST_PWM_CURRENT_WIRED:
	
		
		if(command_get)
        {   
            if(4 == rxlen){
            
	          // trying to read write only data
              e = PWMTestCurrent(1, &i1, &i2, rxpayload->w[0], rxpayload->w[1]);
	        
			  if(e || SysError.OverCurrentFailure){
				txlen=0x6;
		        txpayload.b[0] = e;
				txpayload.b[1] = SysError.OverCurrentFailure;
				txpayload.w[1] = i1;
				txpayload.w[2] = i2;
			  }else{
		        txlen=0x2;
		        txpayload.b[0] = e;
				txpayload.b[1] = SysError.OverCurrentFailure;
			  }
            } else {
              // parameter out of range
              command_ok = 0;
              txlen=0x1;
              txpayload.b[0] = CAN_ERROR_PARAMETER_OUT_OF_RANGE;
            }
        }
        else
        {
        	// Error, trying to write a read-only parameter
	        command_ok = 0;
	        txlen=0x1;
	        txpayload.b[0] = CAN_PROTO_ERROR_WRITE_READ_ONLY_DATA;
        }
        break;

		case CAN_CMD_TEST_PWM_PROTECTION:
		
			if(command_get)
	        {
			  txpayload.b[0] = SysError.OverCurrentFailure; 
	
	          txlen = 0x1;
			 
	          //memcpy(txpayload.b, SIXSG_FW_VERSION, 8 );
	        }
	        else
	        {
	          txlen=0x0;
			  SysError.OverCurrentFailure = 0;
			  PWMTestProtection();
	        } 

	         
	    break;

		case CAN_CMD_TEST_PWM_PDN:
	
		
			if(command_get)
	        {
			  txpayload.b[0] = PWMTestPDN();
	
	          txlen = 0x1;
			 
	          //memcpy(txpayload.b, SIXSG_FW_VERSION, 8 );
	        }
	        else
	        {
	         // Error, trying to write a read-only parameter
	          command_ok = 0;
	          txlen=0x1;
	          txpayload.b[0] = CAN_PROTO_ERROR_WRITE_READ_ONLY_DATA;
	        } 

	         
	    break;

	    case CAN_CMD_READ_VDC:
	
	
			res = ADCRead(&vdc, &i1, &i2);
		
			if(command_get)
	        {
			  txpayload.w[0] = res;
			  txpayload.w[1] = vdc;
	
	          txlen = 0x4;
			 
	          //memcpy(txpayload.b, SIXSG_FW_VERSION, 8 );
	        }
	        else
	        {
	         // Error, trying to write a read-only parameter
	          command_ok = 0;
	          txlen=0x1;
	          txpayload.b[0] = CAN_PROTO_ERROR_WRITE_READ_ONLY_DATA;
	        } 

	         
	    break;
	
	
	    case CAN_CMD_READ_I:
	
	
			res = ADCRead(&vdc, &i1, &i2);

			if(command_get)
	        {
			  txpayload.w[0] = res;
			  txpayload.w[1] = ADCTo10bit(i1);
			  txpayload.w[2] = ADCTo10bit(i2);	

	          txlen = 0x6;
			 
	          //memcpy(txpayload.b, SIXSG_FW_VERSION, 8 );
	        }
	        else
	        {
	         // Error, trying to write a read-only parameter
	          command_ok = 0;
	          txlen=0x1;
	          txpayload.b[0] = CAN_PROTO_ERROR_WRITE_READ_ONLY_DATA;
	        } 

	
	    break;
	
		case CAN_CMD_OVERCURRENT:
			if(command_get)
	        {
			  
			  txpayload.w[0] = TestReadOvercurr();
	
	          txlen = 0x1;
			 
	          //memcpy(txpayload.b, SIXSG_FW_VERSION, 8 );
	        }
	        else
	        {
	         // Error, trying to write a read-only parameter
	          command_ok = 0;
	          txlen=0x1;
	          txpayload.b[0] = CAN_PROTO_ERROR_WRITE_READ_ONLY_DATA;
	        } 
		break;



  		case CAN_CMD_LED:
			if(command_get)
	        {
			  
			  txpayload.w[0] = (BLINKRATE_OFF != LED_status.GreenBlinkRate);
		      
			  if(BLINKRATE_OFF != LED_status.RedBlinkRate){
			  	txpayload.w[0] |=  1; 
	          }
	
	          txlen = 0x1;
			 
	          //memcpy(txpayload.b, SIXSG_FW_VERSION, 8 );
	        }
	        else
	        {
				LED_status.RedBlinkRate = LED_status.GreenBlinkRate = BLINKRATE_OFF;
	
	         	if(rxpayload->b[0] & 0x1)
					LED_status.RedBlinkRate = BLINKRATE_STILL;
	
				if(rxpayload->b[0] & 0x2)
					LED_status.GreenBlinkRate = BLINKRATE_STILL;
	
	        } 
		break;

	   case CAN_CMD_GPIO_PORT:
			TestPort(command_get, &command_ok, &txlen, &txpayload, rxlen, rxpayload);
	   break;

	   case CAN_CMD_GPIO_DIR:
			TestTris(command_get, &command_ok, &txlen, &txpayload, rxlen, rxpayload);

	   break;
// Get firmware version
      // example: 1FFFFFF3  
      case CAN_CMD_FW_VERSION:
        if(command_get)
        {
          txlen = MIN(8,strlen(TWOFOC_FW_VERSION));
          memcpy(txpayload.b, TWOFOC_FW_VERSION,  txlen);
        }
        else
        {
          // Error, trying to write a read-only parameter
          command_ok = 0;
          txlen=0x1;
         txpayload.b[0] = CAN_PROTO_ERROR_WRITE_READ_ONLY_DATA;
        } 
      break;

    
 

      case CAN_CMD_SILICON_VERSION:
        if(command_get)
        {
		  unsigned int devrev;
          txlen = 0x2;

		/* read silicon chip revision */
		 _memcpy_p2d16(&devrev, 0xff0002, sizeof(devrev));

		 txpayload.w[0] = devrev;
          //memcpy(txpayload.b, SIXSG_FW_VERSION, 8 );
        }
        else
        {
          // Error, trying to write a read-only parameter
          command_ok = 0;
          txlen=0x1;
         txpayload.b[0] = CAN_PROTO_ERROR_WRITE_READ_ONLY_DATA;
        } 
      break;

      // Get fault status
      // example: 1FFFFF17  
      case CAN_CMD_FAULT_INFO:
        if(command_get)
        {
          int sz1,sz2;
          sz1 = MIN(4,sizeof(SysStatus));
		  sz2 = MIN(4,sizeof(SysError));
          memcpy(txpayload.b, SysStatus.b, sz1);
		  memcpy(txpayload.b+4, SysError.b, sz2 );
          txlen = 4 + sz2;
          // 
         
        }
        else
        {
          // Error, trying to write a read-only parameter
          command_ok = 0;
          txlen=0x1;
         txpayload.b[0] = CAN_PROTO_ERROR_WRITE_READ_ONLY_DATA;
        } 
      break;

      // Get hardware version
      // example: 1FFFFFF4  
      case CAN_CMD_HW_VERSION:
        if(command_get)
        {
          txlen = MIN(8,strlen(TWOFOC_HW_VERSION));
          memcpy(txpayload.b, TWOFOC_HW_VERSION, txlen);
          // 
         
        }
        else
        {
          // Error, trying to write a read-only parameter
          command_ok = 0;
          txlen=0x1;
         txpayload.b[0] = CAN_PROTO_ERROR_WRITE_READ_ONLY_DATA;
        } 
      break;
      // swtitch running mode on the fly. TODO must be done when the FOC loop is not pumping current 
      // example: 1BFFFF01 01 
    
      case CAN_CMD_PERIODIC_COMMAND_CONTENTS:
        // define Periodic command contents 
        // 1BFFFFF12
        if(command_get)
        {	
          txlen=0x4;
          txpayload.b[0] = PeriodicMessageContents[0];
          txpayload.b[1] = PeriodicMessageContents[1];
          txpayload.b[2] = PeriodicMessageContents[2];
          txpayload.b[3] = PeriodicMessageContents[3];
        }
        else
        {
          if (4 == rxlen)
          {
            // check data to transmit if in the acceptable range 
            if ( (rxpayload->b[0] < ELEMENTS_IN_PREIODIC_DATA_LIST )
              && (rxpayload->b[1] < ELEMENTS_IN_PREIODIC_DATA_LIST )
              && (rxpayload->b[2] < ELEMENTS_IN_PREIODIC_DATA_LIST )
              && (rxpayload->b[3] < ELEMENTS_IN_PREIODIC_DATA_LIST ))
            {
              // set the data to transmit
              PeriodicMessageContents[0] = rxpayload->b[0];
              PeriodicMessageContents[1] = rxpayload->b[1];
              PeriodicMessageContents[2] = rxpayload->b[2];
              PeriodicMessageContents[3] = rxpayload->b[3];
            }
            else
            {
              // parameter out of range
              command_ok = 0;
              txlen=0x1;
              txpayload.b[0] = CAN_ERROR_PARAMETER_OUT_OF_RANGE;
            }
          }
          else
          {
            // incorrect number of parameters
            command_ok = 0;
            txlen=0x1;
            txpayload.b[0] = CAN_ERROR_INCORRECT_NUMBER_OF_PARAMETERS;
          }
        }
      break;

     

      default:

        // UNKNOWN command... TODO: Handle !
        // unknown or bad command
        command_ok = 0;
        txlen=0x1;
        txpayload.b[0] = CAN_ERROR_UNKNOWN_COMMAND;
      break;
    }

    // initialize the CAN send data struct
   
    // compose id
    if(command_ok)
    {

      if(command_get){
		CanProtoSendResponse(canprotoparser_bid, txlen, &txpayload);
	  }
#ifdef CAN_ACK_EACH_COMMAND 
	  else{
		CanProtoTxAck(bid);
	  }
#endif
    }
    else
    {
      CanProtoTxErrorCode(canprotoparser_bid, txlen, &txpayload);
    }

  }
  else
  {
    // the message is a 11 bit
//
// TODO: Questo codice serve per il loop di coppia, riceve i dati dsi coppia
//  da un eventuale sensore di forza/copppia.
//  derattizzare e defogliare a piacimento
//

// TODO: aggiungere il controllo della congruenza della lunghezza del messaggio 
// if (2 != len) ...

    // check for the F/T Sensor data
    // in calibrated sensors z axis torque is located in the 0x35B message ID (FTSens address 5)
    // at 3^rd position w[2]
    if(0x35B == rxid)
    {
    
    }
    else
    { 
      // discard further data from F/T Sens
    }
  }
}

