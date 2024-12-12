/** \file CurrentMonitor.c
 * \brief Implementation file for module-independent current monitor functions.
 * \author Garry Jeromson
 * \date 02.07.15
 */


//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "CurrentMonitor.h"
#include "I2cInterface.h"
#include "UtilityFunctions.h"


//-------------------------------------------------------------------------------------------------
// Constants
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// I2C addresses
//-------------------------------------------------------------------------------------------------

/// Current sensor device address
#define CURRENT_MONITOR_DEVICE_ADDRESS 0x4F

/// Config register address
#define CURRENT_MONITOR_REGISTER_ADDRESS_CONFIG 0x00

/// VSense register address
#define CURRENT_MONITOR_REGISTER_ADDRESS_VSENS 0x01

/// VBus register address
#define CURRENT_MONITOR_REGISTER_ADDRESS_VBUS 0x02

/// Power register address
#define CURRENT_MONITOR_REGISTER_ADDRESS_POWER 0x03

/// Current register address
#define CURRENT_MONITOR_REGISTER_ADDRESS_CURRENT 0x04

/// Calibration register address
#define CURRENT_MONITOR_REGISTER_ADDRESS_CALIBRATION 0x05


//-------------------------------------------------------------------------------------------------
// Current monitor function definitions
//-------------------------------------------------------------------------------------------------


EN_RESULT CurrentMonitor_Initialise()
{
	// configuration for Mars Starter
	// one ADC bit is 10 uV for the VShunt measurement
	EN_RETURN_IF_FAILED(CurrentMonitor_WriteConfig(0x019F));

	// configuration for Mars Starter with 0.01R shunt
	return CurrentMonitor_WriteCalibration(0x1000);
}



EN_RESULT CurrentMonitor_ReadConfig(uint16_t* pConfig)
{
	uint16_t tempValue;
    return I2cRead(CURRENT_MONITOR_DEVICE_ADDRESS,
                   CURRENT_MONITOR_REGISTER_ADDRESS_CONFIG,
                   EI2cSubAddressMode_OneByte,
                   2,
                   (uint8_t*)&tempValue);
    *pConfig = ChangeByteOrder(tempValue);
}

EN_RESULT CurrentMonitor_ReadVSense(uint16_t* pVSense)
{
	uint16_t tempValue;
	EN_RETURN_IF_FAILED(I2cRead(CURRENT_MONITOR_DEVICE_ADDRESS,
                   CURRENT_MONITOR_REGISTER_ADDRESS_VSENS,
                   EI2cSubAddressMode_OneByte,
                   2,
                   (uint8_t*)&tempValue));

	// uV. One ADC bit is 10 micro volt
    *pVSense = ChangeByteOrder(tempValue)*10; // in micro volt
    return EN_SUCCESS;
}

EN_RESULT CurrentMonitor_ReadVBus(uint16_t* pValue)
{
    uint16_t tempValue;
    EN_RETURN_IF_FAILED(I2cRead(CURRENT_MONITOR_DEVICE_ADDRESS,
                                CURRENT_MONITOR_REGISTER_ADDRESS_VBUS,
                                EI2cSubAddressMode_OneByte,
                                2,
                                (uint8_t*)&tempValue));

    // mV. Calculate /2 to cut off the last bit
    *pValue = ChangeByteOrder(tempValue) / 2;

    return EN_SUCCESS;
}

EN_RESULT CurrentMonitor_ReadPower(uint16_t* pValue)
{
    uint16_t tempValue;
    EN_RETURN_IF_FAILED(I2cRead(CURRENT_MONITOR_DEVICE_ADDRESS,
                                CURRENT_MONITOR_REGISTER_ADDRESS_POWER,
                                EI2cSubAddressMode_OneByte,
                                2,
                                (uint8_t*)&tempValue));

    // mW. Calculate *20 because the Power LSB is 20*Current LSB
    *pValue = ChangeByteOrder(tempValue) * 20;

    return EN_SUCCESS;
}

EN_RESULT CurrentMonitor_ReadCurrent(uint16_t* pValue)
{
	uint16_t tempValue;
	EN_RETURN_IF_FAILED(I2cRead(CURRENT_MONITOR_DEVICE_ADDRESS,
                   CURRENT_MONITOR_REGISTER_ADDRESS_CURRENT,
                   EI2cSubAddressMode_OneByte,
                   2,
                   (uint8_t*)&tempValue));

    *pValue = ChangeByteOrder(tempValue);
    return EN_SUCCESS;
}

EN_RESULT CurrentMonitor_ReadCalibration(uint16_t* pValue)
{
	uint16_t tempValue;
	EN_RETURN_IF_FAILED(I2cRead(CURRENT_MONITOR_DEVICE_ADDRESS,
                   CURRENT_MONITOR_REGISTER_ADDRESS_CALIBRATION,
                   EI2cSubAddressMode_OneByte,
                   2,
                   (uint8_t*)&tempValue));
	*pValue = ChangeByteOrder(tempValue);
    return EN_SUCCESS;
}

EN_RESULT CurrentMonitor_WriteConfig(uint16_t value)
{
	uint16_t tempValue = ChangeByteOrder(value);
    return I2cWrite(CURRENT_MONITOR_DEVICE_ADDRESS,
                    CURRENT_MONITOR_REGISTER_ADDRESS_CONFIG,
                    EI2cSubAddressMode_OneByte,
                    (uint8_t*)&tempValue,
                    2);
}

EN_RESULT CurrentMonitor_WriteCalibration(uint16_t value)
{
	uint16_t tempValue = ChangeByteOrder(value);
    return I2cWrite(CURRENT_MONITOR_DEVICE_ADDRESS,
                    CURRENT_MONITOR_REGISTER_ADDRESS_CALIBRATION,
                    EI2cSubAddressMode_OneByte,
                    (uint8_t*)&tempValue,
                    2);
}
