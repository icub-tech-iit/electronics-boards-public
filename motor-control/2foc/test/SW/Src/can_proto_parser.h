
#ifndef __PARSER_H
#define __PARSER_H

#include "ecan.h"

#include "Status.h"
#include "DSP.h"
#include "DS402.h"
#include "system.h"

extern char TWOFOC_FW_VERSION[];
extern char TWOFOC_HW_VERSION[];


//
//  CAN commands definition
//
// Swititch control mode on the fly.

// Get the extended status word from the TLE5012 encoder.
// This command may cause the CAN to stall for several microseconds and
// it may cause the FOC loop to get an older encoder value for 1 cycle.
// Please use with care.




// Set/Get periodice command contents
#define CAN_CMD_PERIODIC_COMMAND_CONTENTS 0x12

// get firmware version
#define CAN_CMD_FW_VERSION                0x14
// get hardware version
#define CAN_CMD_HW_VERSION                0x15
// get silicon version
#define CAN_CMD_SILICON_VERSION           0x16
// get fault informations
#define CAN_CMD_FAULT_INFO                0x17

// test firmware commands

#define CAN_CMD_GPIO_PORT				  0x30
#define CAN_CMD_GPIO_DIR				  0x31
#define CAN_CMD_LED					      0x32
#define CAN_CMD_OVERCURRENT				  0x33
#define CAN_CMD_READ_VDC				  0x34
#define CAN_CMD_READ_I					  0x35
#define CAN_CMD_TEST_PWM_PDN			  0x36
#define CAN_CMD_TEST_PWM_CYCLE 			  0x37
#define CAN_CMD_TEST_PWM_CURRENT		  0x38      
#define CAN_CMD_TEST_PWM_PROTECTION		  0x39  
#define CAN_CMD_TEST_PWM_CURRENT_WIRED	  0x40  
//
//  CAN error codes definition
//
// the command has a wrong number of parameters
#define CAN_ERROR_INCORRECT_NUMBER_OF_PARAMETERS 0x01
// the message is unknown by the parser
#define CAN_ERROR_UNKNOWN_COMMAND                0x02
// Trying to read write only data
#define CAN_ERROR_WRITE_ONLY_DATA                0x03
// Trying to write read only data
#define CAN_ERROR_READ_ONLY_DATA                 0x04
// DS402 invalid status change request
#define CAN_DS402_INVALID_STATUS_CHANGE          0x05
// DS402 invalid status change request
#define CAN_ERROR_PARAMETER_OUT_OF_RANGE         0x06
// the message is invalid in current state
#define CAN_ERROR_COMMAND_IN_INVALID_STATE       0x07





extern tSysStatus SysStatus;
extern fractional sorgente[];
extern fractional destinazione[];
extern unsigned char PeriodicMessageContents[4];


extern volatile tControlword DS402_Controlword;
extern volatile tStatusword  DS402_Statusword;


extern void CanProtoParserParse(unsigned long rxid, unsigned char rxlen, tCanData *rxpayload);
extern void CanProtoParserInit(unsigned char bid);

#endif
