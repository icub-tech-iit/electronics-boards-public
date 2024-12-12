/** \file I2cExample.c
 * \brief This file contains a few generic examples for reading from I2C devices on Enclustra
 * modules and base boards.
 *
 * \author Garry Jeromson
 * \date 17.08.15
 *
 * Copyright (c) 2015 Enclustra GmbH, Switzerland.
 * All rights reserved.
 */

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "I2cInterface.h"
#include "InterruptController.h"
#include "CurrentMonitor.h"
#include "ModuleEeprom.h"
#include "RealtimeClock.h"
#include "SystemMonitor.h"
#include "TimerInterface.h"
#include "GlobalVariables.h"
#include "I2cExampleDefines.h"
#include "ReadSystemMonitor.h"

#if SYSTEM == ALTERA_ARM_SOC
	#include "BootInterface.h"
#endif

//-------------------------------------------------------------------------------------------------
// File scope variables
//-------------------------------------------------------------------------------------------------

/// A little bit of left padding for when we're printing strings.
char LEFT_PADDING[] = "   ";


//-------------------------------------------------------------------------------------------------
// Function definitions
//-------------------------------------------------------------------------------------------------

/**
 * \brief Perform required initialisation of the system resources used by the application.
 */

EN_RESULT InitaliseSystem()
{

	EN_RETURN_IF_FAILED(InitialiseTimer());

	EN_RETURN_IF_FAILED(InitialiseI2cInterface());

	EN_RETURN_IF_FAILED(SetupInterruptSystem());

	return EN_SUCCESS;
}

/**
 * \brief Perform required boot initialisation
 */

#if SYSTEM == ALTERA_ARM_SOC

	EN_RESULT InitaliseSystemBoot()
	{

		EN_RETURN_IF_FAILED(InitialiseBoot());

		return EN_SUCCESS;
	}

#else

	EN_RESULT InitaliseSystemBoot()
	{

		return EN_SUCCESS;
	}

#endif

/**
 * \brief Read the module EEPROM and print the module configuration details.
 *
 * Enclustra modules all carry an EEPROM, which contains information such as module type, serial
 * number, MAC address, and information on the module configuration properties. This function
 * demonstrates how to read these properties.
 *
 * Some of the properties, such as the memory size or number of Ethernet ports, may be useful in
 * other parts of application code - in general, when a property is required in to be used
 * across multiple .c files, it should be declared once in GlobalVariables.h with the keyword
 * extern, and then defined once in a single .c file. In this example, g_
 */
EN_RESULT ReadEeprom()
{
    EN_PRINTF("EEPROM:\r\n");

    // Initialise the EEPROM.
    EN_RETURN_IF_FAILED(Eeprom_Initialise());

    // Read the EEPROM.
    EN_RETURN_IF_FAILED(Eeprom_Read());

    // After reading the EEPROM, the information is stored in its own translation unit - we can
    // query it using the EEPROM API functions.
    uint32_t serialNumber;
    ProductNumberInfo_t productNumberInfo;
    uint8_t macAddress[6];
    EN_RETURN_IF_FAILED(Eeprom_GetModuleInfo(&serialNumber, &productNumberInfo, (uint64_t*)&macAddress));

    EN_PRINTF("%s%-30s%s\r\n", LEFT_PADDING, "Module type", CONFIG_MODULE_NAME);
    EN_PRINTF("%s%-30s%d\r\n", LEFT_PADDING, "Revision", productNumberInfo.revisionNumber);
    EN_PRINTF("%s%-30s%d\r\n", LEFT_PADDING, "Serial number", serialNumber);
    EN_PRINTF("%s%-30s%02X:%02X:%02X:%02X:%02X:%02X\r\n",
              LEFT_PADDING,
              "MAC Address 0",
              macAddress[5],
              macAddress[4],
              macAddress[3],
              macAddress[2],
              macAddress[1],
              macAddress[0]);

    // Print the module configuration data.
    Eeprom_PrintModuleConfig();

/*	Info:
	//
    // Module specific-code to evaluate specific properties should be inserted below. Properties
    // can be retrieved by index - the indices themselves are defined for ease of use in
    // ModuleConfigConstants.h. The example below shows property retrieval for the Mercury ZX1
    // module.

    // Get the number of Gigabit Ethernet ports
    uint32_t gigabitEthernetPortCount = 0;
    Eeprom_GetModuleConfigPropertyValue(MERCURY_ZX1_CONFIG_PROPERTY_INDEX_GIGABIT_ETHERNET_PORT_COUNT,
                                        &gigabitEthernetPortCount);

    // Check if an RTC is present.
    uint32_t rtcEquipped = 0;
    Eeprom_GetModuleConfigPropertyValue(MERCURY_ZX1_CONFIG_PROPERTY_INDEX_REAL_TIME_CLOCK_EQUIPPED, &rtcEquipped);

    // Get the size of the DDR3L PS memory.
    uint32_t g_ddr3lPsSizeMb = 0;
    Eeprom_GetModuleConfigPropertyValue(MERCURY_ZX1_CONFIG_PROPERTY_INDEX_DDR3L_RAM_PS_SIZE_MB, &g_ddr3lPsSizeMb);
*/

    return EN_SUCCESS;
}


/**
* \brief Read and display values from the current monitor.
*/

// For system boards TARGET_BASEBOARD is not defined
#ifdef TARGET_BASEBOARD
	#if TARGET_BASEBOARD == MARS_STA

		EN_RESULT ReadCurrentMonitor()
		{
			// Read and display values from the current monitor
			EN_PRINTF("\r\nCurrent Monitor:\r\n");

			// Perform any required initialisation.
			EN_RETURN_IF_FAILED(CurrentMonitor_Initialise());

			// Get the VBus reading.
			uint16_t vBus;
			EN_RETURN_IF_FAILED(CurrentMonitor_ReadVBus(&vBus));
			EN_PRINTF("%s%s %d mV\r\n", LEFT_PADDING, "Voltage = ", vBus);

			// Get the current reading.
			uint16_t current;
			EN_RETURN_IF_FAILED(CurrentMonitor_ReadCurrent(&current));
			EN_PRINTF("%s%s %d mA\r\n", LEFT_PADDING, "Current = ", current);

			// Get the power reading.
			uint16_t power;
			EN_RETURN_IF_FAILED(CurrentMonitor_ReadPower(&power));
			EN_PRINTF("%s%s %d mW\r\n", LEFT_PADDING, "Power   = ", power);

			return EN_SUCCESS;
		}

	#else

		EN_RESULT ReadCurrentMonitor()
		{
			return EN_SUCCESS;
		}

	#endif

#else

	EN_RESULT ReadCurrentMonitor()
	{
		return EN_SUCCESS;
	}

#endif

/**
 * \brief Demonstrates how to set and read the real-time clock.
 */
#if (TARGET_MODULE==MARS_AX3) || (TARGET_MODULE==MERCURY_KX2) || (TARGET_MODULE==MERCURY_XU1) || (TARGET_MODULE==MARS_XU3) || (TARGET_MODULE==MERCURY_XU5) || (TARGET_MODULE==MERCURY_XU7) || (TARGET_MODULE==MERCURY_XU8)
// no RTC on AX3/KX2/XU1/XU3/XU5/XU7/XU8

EN_RESULT ReadRealtimeClock()
	{
		return EN_SUCCESS;
	}
#else
	
EN_RESULT ReadRealtimeClock()
{
	 EN_PRINTF("\r\nReal Time Clock:\r\n");

    // Initialise the RTC.
    EN_RETURN_IF_FAILED(Rtc_Initialise());

    // Set the time and date, then wait a bit.
    EN_RETURN_IF_FAILED(Rtc_SetTime(11, 22, 32));
    EN_RETURN_IF_FAILED(Rtc_SetDate(22, 11, 10));
    SleepMilliseconds(1000);

    // Read back the time.
    int hour, minute, seconds;
    EN_RETURN_IF_FAILED(Rtc_ReadTime((int*)&hour, (int*)&minute, (int*)&seconds));

    // Read back the date.
    int year, month, day;
    EN_RETURN_IF_FAILED(Rtc_ReadDate((int*)&day, (int*)&month, (int*)&year));

    // Print time and date
    EN_PRINTF("%sTime: %d:%d:%d\r\n", LEFT_PADDING, hour, minute, seconds);
    EN_PRINTF("%sDate: %d.%d.%d\r\n", LEFT_PADDING, day, month, year);

	int temperature;
    if (!EN_FAILED(Rtc_ReadTemperature((int*)&temperature)) )
    {
    	EN_PRINTF("%sTemperature: %d Celsius\r\n", LEFT_PADDING, temperature);
    }

    return EN_SUCCESS;

}
#endif


int main()
{

	InitaliseSystemBoot();

	EN_PRINTF("\r\n\r\n\r\n== Enclustra I2C test ==\r\n\r\n");

    if (EN_FAILED(InitaliseSystem()))
    {
        EN_PRINTF("Error: System initialization failed\r\n");
        return -1;
    }

    if (EN_FAILED(ReadEeprom()))
    {
        EN_PRINTF("Error: EEPROM read failed\r\n");
        return -1;
    }

    if (EN_FAILED(ReadRealtimeClock()))
    {
        EN_PRINTF("Error: Real-time clock read failed\r\n");
        return -1;
    }

	//Depending on the Base Board capabilities
    if (EN_FAILED(ReadCurrentMonitor()))
    {
        EN_PRINTF("Error: Current monitor read failed\r\n");
        return -1;
    }


	//Depending on the Base Board capabilities
    if (EN_FAILED(ReadSystemMonitor()))
    {
        EN_PRINTF("Error: System monitor read failed\r\n");
        return -1;
    }

    EN_PRINTF("\r\n\r\n== End of test ==\r\n");

	while (1);
    return 0;
}
