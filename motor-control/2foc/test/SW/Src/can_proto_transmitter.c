#include <p33FJ128MC802.h>
#include <string.h>

#include "can_proto.h"
#include "UserParms.h"
#include "can_proto_transmitter.h"
#include "system.h"
#include "faults.h"

static unsigned char canprototransmitter_bid;
extern volatile int gulp_update_request ;
extern tGulp Gulp;

void CanProtoTransmitterInit(unsigned char bid)
{
	canprototransmitter_bid = bid;
}

void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt(void)
// The periodic CAN transmission buffer is filled and the trasmission is started
{
  static unsigned int state_cnt = 0;
  unsigned long txid;
  unsigned int len;
  static tCanData candata = {{0}};
  // CAN TX buffer for period gulp messages (not status)
  // This needs to be static because it might be not initialized 
  // in this function when gulp vars are not updated
  
  // clear INT flag
  IFS1bits.T4IF = 0; 


  if( 0 == gulp_update_request)
  {  
    //--> sta roba serve per vedere le commutazioni delle sonde di hall
    //if (gulp2 != ((PORTB & 0b011100000) >> 5) )
    //{
    //gulp2 =((PORTB & 0b011100000) >> 5);
    //gulp1 = ParkParm.qAngle;

    candata.w[0] = Gulp.W[0];
    candata.w[1] = Gulp.W[1];
	candata.w[2] = Gulp.W[2];
    candata.w[3] = Gulp.W[3];
    
    // we got values and we buffered them. Now we can request 
    // to the FOC loop to provide new values again
    gulp_update_request = 1;
  } 

  // send TX data buffer to the CAN HW 
  //sendECAN(&CANTxMessage);	

	txid = CAN_PROTO_ID_MAKE_TX(canprototransmitter_bid,CAN_CMD_PERIODIC);
	
	ECANSend(txid, 8, &candata);

  // every CAN_STATE_PER gulp messages send out a status message 
  if(state_cnt++ == CAN_STATUS_MSG_PERIOD)
  {
    int sz1,sz2;
    // reset counter for next status message
    state_cnt = 0;
    
    // Copy the status structure in the CAN TX buffer
    
  
    sz1 = MIN(4,sizeof(SysStatus));
    sz2 = MIN(4,sizeof(SysError));
   
    memcpy(candata.b, SysStatus.b, sz1);
    memcpy(candata.b+4, SysError.b, sz2 );
    len = 4 + sz2;

    // 
    // Set the CAN message lenght to the size in bytes of the structure.
    // note that there could be some unused (thus randomic) bits 
    
	// Send the TX buffer to the CAN HW    
	txid = CAN_PROTO_ID_MAKE_TX(canprototransmitter_bid,CAN_CMD_BOARD_STATUS);
	
	ECANSend(txid, len, &candata);
  }
}
