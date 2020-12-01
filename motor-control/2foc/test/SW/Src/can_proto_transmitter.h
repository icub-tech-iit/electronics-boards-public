#ifndef __CANPROTOTRANSMITTER_H
#define __CANPROTOTRANSMITTER_H


// Periodic outgoing messages
#define CAN_CMD_PERIODIC                  0x81
// Board status
#define CAN_CMD_BOARD_STATUS              0x82
// Board status
#define CAN_CMD_BOARD_FAULT               0x83



extern void CanProtoTransmitterInit(unsigned char bid);
extern void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt(void);


#endif

