/** \file SystemMonitor.c
 * \brief Implementation file for System Monitor functions.
 * \author Gian Köppel
 * \date 03.07.15
 */

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "SystemMonitor.h"
#include "I2cInterface.h"
#include "UtilityFunctions.h"
#include "TimerInterface.h"

//-------------------------------------------------------------------------------------------------
// Directives, typedefs and constants
//-------------------------------------------------------------------------------------------------

#define SYSTEM_MONITOR_DEVICE_ADDRESS 0x2F

//-------------------------------------------------------------------------------------------------
// Register addresses
//-------------------------------------------------------------------------------------------------

// Configuration Register
#define SYSTEM_MONITOR_REGISTER_ADDRESS_CONFIG 0x00

// Interrupt Status Register 1
#define SYSTEM_MONITOR_REGISTER_ADDRESS_INTR_STATUS_1 0x01

// Interrupt Status Register 2
#define SYSTEM_MONITOR_REGISTER_ADDRESS_INTR_STATUS_2 0x02

// Interrupt Mask Register 1
#define SYSTEM_MONITOR_REGISTER_ADDRESS_INTR_MASK_1 0x03

// Interrupt Mask Register 2
#define SYSTEM_MONITOR_REGISTER_ADDRESS_INTR_MASK_2 0x04

// Fan Divisor / RTS_OUT / OS Register
#define SYSTEM_MONITOR_REGISTER_ADDRESS_FAN_DIV 0x05

// OS Configuration/Temperature Resolution Register
#define SYSTEM_MONITOR_REGISTER_ADDRESS_OS_CONFIG 0x06

// Conversion Rate Register
#define SYSTEM_MONITOR_REGISTER_ADDRESS_CONV_RATE 0x07

// Channel Disable Register
#define SYSTEM_MONITOR_REGISTER_ADDRESS_CHAN_DISABLE 0x08

// Value RAM Base Address
#define SYSTEM_MONITOR_REGISTER_ADDRESS_VALUE_BASE 0x20

//-------------------------------------------------------------------------------------------------
// Function definitions
//-------------------------------------------------------------------------------------------------

EN_RESULT SystemMonitor_Initialise()
{
    uint8_t Value = 0;

	// Write interrupt mask register 1
	Value = 0xFF;
	EN_RETURN_IF_FAILED(I2cWrite(SYSTEM_MONITOR_DEVICE_ADDRESS,
								SYSTEM_MONITOR_REGISTER_ADDRESS_INTR_MASK_1,
								EI2cSubAddressMode_OneByte,
								&Value,
								1));

	// Write interrupt mask register 1
	Value = 0xFF;
	EN_RETURN_IF_FAILED(I2cWrite(SYSTEM_MONITOR_DEVICE_ADDRESS,
								SYSTEM_MONITOR_REGISTER_ADDRESS_INTR_MASK_2,
								EI2cSubAddressMode_OneByte,
								&Value,
								1));

	// Set temp to 11 bit
	Value = 0x09;
	EN_RETURN_IF_FAILED(I2cWrite(SYSTEM_MONITOR_DEVICE_ADDRESS,
								SYSTEM_MONITOR_REGISTER_ADDRESS_OS_CONFIG,
								EI2cSubAddressMode_OneByte,
								&Value,
								1));

	// Set continuous conversion
	Value = 0x01;
	EN_RETURN_IF_FAILED(I2cWrite(SYSTEM_MONITOR_DEVICE_ADDRESS,
								SYSTEM_MONITOR_REGISTER_ADDRESS_CONV_RATE,
								EI2cSubAddressMode_OneByte,
								&Value,
								1));

	// Start monitoring process
	Value = 0x01;
	EN_RETURN_IF_FAILED(I2cWrite(SYSTEM_MONITOR_DEVICE_ADDRESS,
								SYSTEM_MONITOR_REGISTER_ADDRESS_CONFIG,
								EI2cSubAddressMode_OneByte,
								&Value,
								1));

	// Wait until the system monitor is ready
	SleepMilliseconds(500);

	return EN_SUCCESS;
}

EN_RESULT SystemMonitor_ReadValue(uint16_t channel, uint16_t* pValue)
{
	EN_RETURN_IF_FAILED(I2cRead(SYSTEM_MONITOR_DEVICE_ADDRESS,
								SYSTEM_MONITOR_REGISTER_ADDRESS_VALUE_BASE+channel,
								EI2cSubAddressMode_OneByte,
								2,
								(uint8_t*)pValue));

	return EN_SUCCESS;
}

EN_RESULT SystemMonitor_ReadVoltage(uint16_t channel, int* pVoltage, int RUpper, int RLower)
{
	uint16_t tempValue;
	EN_RETURN_IF_FAILED(I2cRead(SYSTEM_MONITOR_DEVICE_ADDRESS,
								SYSTEM_MONITOR_REGISTER_ADDRESS_VALUE_BASE+channel,
								EI2cSubAddressMode_OneByte,
								2,
								(uint8_t*)&tempValue));

	// Convert value to voltage
	tempValue = (tempValue << 8) | (tempValue >> 8);
	tempValue = tempValue >> 6;

	if ( RLower != 1 )
	{
		*pVoltage = (tempValue * 2.5 * (RUpper + RLower) / RLower);
	} else {
		//no divider to ground - the voltage is more or less the same (depending on the current through RUpper resistor)
		*pVoltage = (tempValue * 2.5 );
	}


	return EN_SUCCESS;
}

EN_RESULT SystemMonitor_ReadCurrent(uint16_t channel, int* pCurrent, int RShunt, int vRef)
{
	uint16_t tempValue = 0;
	EN_RETURN_IF_FAILED(I2cRead(SYSTEM_MONITOR_DEVICE_ADDRESS,
								SYSTEM_MONITOR_REGISTER_ADDRESS_VALUE_BASE+channel,
								EI2cSubAddressMode_OneByte,
								2,
								(uint8_t*)&tempValue));

	// Convert value to voltage
	tempValue = (tempValue << 8) | (tempValue >> 8);
	tempValue = tempValue >> 6;

	*pCurrent = (((tempValue * 2.5) - vRef) / (100 * (0.001 * RShunt)));

	return EN_SUCCESS;
}

