#include <p33FJ128MC802.h>
#include "can_proto.h"
#include "can_proto_parser.h"
#include "can_proto_transmitter.h"
#include "ecan.h"

#ifndef NULL
#define NULL 0
#endif

void CanProtoTxErrorCode(unsigned char bid, unsigned char len, tCanData *errordata)
{
	unsigned long txid;

	txid = CAN_PROTO_ID_MAKE_TX(bid,CAN_PROTO_CMD_ERROR);
	
	ECANSend(txid, len, errordata); 
	
}

void CanProtoTxAck(unsigned char bid)
{
	unsigned long txid;

	txid = CAN_PROTO_ID_MAKE_TX(bid,CAN_PROTO_CMD_RESPONSE);
	
	ECANSend(txid, 0, NULL); 
}

void CanProtoSendResponse(unsigned char bid, unsigned char len, tCanData *respdata)
{
	unsigned long txid;

	txid = CAN_PROTO_ID_MAKE_TX(bid,CAN_PROTO_CMD_RESPONSE);
	
	ECANSend(txid, len, respdata); 
}

extern void initECAN();
// Initializes CAN for communication
void CanProtoInit(unsigned char bid)
{
  // Initialize the SW transmitter module
  CanProtoTransmitterInit(bid);
  // Initialize the SW parser module
  CanProtoParserInit(bid);
  // Initialize CAN driver and link to parser RX handler
  ECANInit(CanProtoParserParse);
  // Configure CAN RX filters
  ECANRxFilterAdd(CAN_PROTO_ID_MAKE_RX(bid),CAN_PROTO_ID_RX_MASK);

  // for strain RX
  ECANRxFilterAdd(0x35B, 0xfff);
	
  // Start CAN operation
  ECANStart(); 

//initECAN();
}
