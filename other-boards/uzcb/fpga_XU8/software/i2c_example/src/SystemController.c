/** \file SystemController.c
 * \brief Implementation file for System Controller functions.
 * \author Diana Ungureanu
 * \date 05.11.15
 */

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "I2cInterface.h"
#include "TimerInterface.h"
#include "UtilityFunctions.h" 
 
//-------------------------------------------------------------------------------------------------
// Directives, typedefs and constants
//-------------------------------------------------------------------------------------------------

#define SYSTEM_CONTROLLER_DEVICE_ADDRESS 0x0D
 
//-------------------------------------------------------------------------------------------------
// Register addresses
//------------------------------------------------------------------------------------------------- 
 
#define SYSTEM_CONTROLLER_REGISTER_ADDRESS_VMON_SEL    20
#define SYSTEM_CONTROLLER_REGISTER_ADDRESS_VMON_SEL_EN 21
 
 
//-------------------------------------------------------------------------------------------------
// Function definitions
//-------------------------------------------------------------------------------------------------

EN_RESULT SystemController_SetVmonSel(int set_bit)
{

	uint8_t tempValue = 0;
	EN_RETURN_IF_FAILED(I2cRead(SYSTEM_CONTROLLER_DEVICE_ADDRESS,
			SYSTEM_CONTROLLER_REGISTER_ADDRESS_VMON_SEL,
			EI2cSubAddressMode_OneByte,
			1,
			(uint8_t*)&tempValue));

	//Set/Reset Bit 2 of Register 20 --> set Vmon_Sel to 1/0
	if (set_bit) {
		tempValue |= (1 << 2);
	}
	else {
		tempValue &= ~(1 << 2);
	}

	EN_RETURN_IF_FAILED(I2cWrite(SYSTEM_CONTROLLER_DEVICE_ADDRESS,
    		SYSTEM_CONTROLLER_REGISTER_ADDRESS_VMON_SEL,
    		EI2cSubAddressMode_OneByte,
    		&tempValue,
    		1));

    tempValue = 0;
	EN_RETURN_IF_FAILED(I2cRead(SYSTEM_CONTROLLER_DEVICE_ADDRESS,
			SYSTEM_CONTROLLER_REGISTER_ADDRESS_VMON_SEL_EN,
			EI2cSubAddressMode_OneByte,
			1,
			(uint8_t*)&tempValue));

	//Set Bit 2 of Register 21 --> set Vmon_Sel Enable to 1
	tempValue |= (1 << 2);

    EN_RETURN_IF_FAILED(I2cWrite(SYSTEM_CONTROLLER_DEVICE_ADDRESS,
    		SYSTEM_CONTROLLER_REGISTER_ADDRESS_VMON_SEL_EN,
    		EI2cSubAddressMode_OneByte,
    		&tempValue,
    		1));

	SleepMilliseconds(750);

}
