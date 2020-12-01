#ifndef __CAN_PROTO_PROTO_H_
#define __CAN_PROTO_PROTO_H_

#define MIN(a,b) ((a>b)?b:a)

#include "ecan.h"

// Incoiming commands are formatted as follows
// For 29 bit Id
//   29  28-25  24 -  8   7-0
//  ----  ---- ---- ----- --- ---     --- 
// | R/W | B  | FF | FF  | C |  PAYLOAD  |
//  ----  ---- ---- ----- --- ---     ---
// R/W command R(1) or W(0) ( 1 bit)
// B Board address          ( 4 bit)
// FF FF unused             (16 bit)
// C   command code         ( 8 bit)
// PAYLOAD variable lenght
//
// the board address represents a sort of virtual memory address area
// each board owns a block of the virtual memory separated from other boards 
// of the same kind, the EMS is a 'master' that knows all the adresses of the 
// areas of the connected boards and writes commands and read back the answers 
// in the 'slaves' memories.
// interslave communication is possible but not implemented.
// FOC boards 'send out' messages marked with its own address and gets command 
// marked with the same address.


// position of the bit get/set
#define CAN_PROTO_CMDGET_SET (0x10000000)
#define CAN_PROTO_CMDNUM_MASK (0xff)

// defines the fixed part (unused) of the id command
#define CAN_PROTO_CMDVALUE_UNUSED 0x00FFFF00

// define the masks for acceptance of the fixed part incoming commands
// make accept any R/W and any command code, 
#define CAN_PROTO_CMDUNUSED_MASK 0x00FFFF00

// mask for board address filtering/acceptance
// the board address is filtered using the Board Address variable 
#define CAN_PROTO_CMDBOARDADD_MASK 0x0F000000
// number of position to shift the board address in orteder to fit in the id
#define CAN_PROTO_CMDBOARDADD_SHIFT 24


// outgoing messages are formatted as follows
// For 29 bit Id
//  ----  ---- ---- ----- --- ---     --- 
// | 0  | B  | FF | FF  | C |  PAYLOAD  |
//  ----  ---- ---- ----- --- ---     ---
// 0 default                ( 1 bit)
// B Board address          ( 4 bit)
// FF FF unused             (16 bit)
// C   command code         ( 8 bit)
// PAYLOAD variable lenght

// outgoing periodical status message Id. dimension 11 or 29 bit
#define CAN_PROTO_TX_CMDVALUE_UNUSED 0x00FFFF00



// outgoing rensponse messages Id. 
#define CAN_PROTO_CMD_RESPONSE			      0xfe
// outgoing error message (for example unknown command or wrong params)
#define CAN_PROTO_CMD_ERROR					  0xff

//
//  CAN error codes definition
//

// the command has a wrong number of parameters
#define CAN_PROTO_ERROR_INCORRECT_NUMBER_OF_PARAMETERS 0x01
// the message is unknown by the parser
#define CAN_PROTO_ERROR_UNKNOWN_COMMAND                0x02
// trying to write a read only parameter
#define CAN_PROTO_ERROR_WRITE_READ_ONLY_DATA           0x03
// command parameter out of range
#define CAN_PROTO_ERROR_PARAM_OUT_OF_RANGE             0x04
// command not yet implemented
#define CAN_PROTO_ERROR_COMMAND_NOT_INPLEMENTED        0x05
// trying to read a write only parameter
#define CAN_PROTO_ERROR_READ_WRITE_ONLY_DATA           0x06



// utility macros for CAN ID management
#define CAN_PROTO_ID_MAKE_TX(bid,cmd)  (ECAN_ID_29 | CAN_PROTO_CMDVALUE_UNUSED | (((unsigned long)(bid)) << CAN_PROTO_CMDBOARDADD_SHIFT) | cmd )
#define CAN_PROTO_ID_MAKE_RX(bid)  (ECAN_ID_29 | CAN_PROTO_CMDVALUE_UNUSED | (((unsigned long)(bid)) << CAN_PROTO_CMDBOARDADD_SHIFT))
#define CAN_PROTO_ID_RX_MASK (CAN_PROTO_CMDVALUE_UNUSED | CAN_PROTO_CMDBOARDADD_MASK)

#define CAN_PROTO_ID_ISEXTENDED(rxid) (!!(rxid & ECAN_ID_29))
#define CAN_PROTO_ID_ISGET(rxid) (!!(rxid & CAN_PROTO_CMDGET_SET))
#define CAN_PROTO_ID_CMD(rxid) (rxid & CAN_PROTO_CMDNUM_MASK)

extern void CanProtoSendResponse(unsigned char bid, unsigned char len, tCanData *errordata);
extern void CanProtoTxAck(unsigned char bid);
extern void CanProtoTxErrorCode(unsigned char bid, unsigned char len, tCanData *errordata);
extern void CanProtoInit(unsigned char bid);
#endif
