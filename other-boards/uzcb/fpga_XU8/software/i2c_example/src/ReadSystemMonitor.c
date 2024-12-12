/** \file ReadSystemMonitor.c
 * \brief Implementation file for Read System Monitor function.
 * \author Diana Ungureanu
 * \date 05.11.15
 */

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "ReadSystemMonitor.h"
#include "SystemMonitor.h"
#include "I2cInterface.h"
#include "UtilityFunctions.h" 
#include "SystemController.h" 

//-------------------------------------------------------------------------------------------------
// Function definitions
//-------------------------------------------------------------------------------------------------
#ifdef TARGET_BASEBOARD

	#if TARGET_BASEBOARD == MARS_PM3
	
		EN_RESULT ReadSystemMonitor()
		{
			/// A little bit of left padding for when we're printing strings.
			char LEFT_PADDING[] = "   ";
	
			// Read and display values from the current monitor
			EN_PRINTF("\r\nSystem Monitor:\r\n");
		
			// Perform any required initialisation.
			EN_RETURN_IF_FAILED(SystemMonitor_Initialise());
		
			// Get the voltage reading.
		
			struct VoltageReadingSysMon voltReading[7] = {
				{"VCC_MAIN", {47000000, 10000000}},
				{"VCC_5V",   {22000000, 10000000}},
				{"VCC_3V3",  {10000000, 22000000}},
				{"VCC_IO",   {10000000, 22000000}},
				{"VCC_1V2",  {10000000, 1}},
				{"VMON_P41", {10000000, 1}},
				{"VCC_OUT",  {10000000, 1}}
			};
		
			int vBus;
			int i;
		
			for (i = 0; i < 7; i++)
			{
				EN_RETURN_IF_FAILED(SystemMonitor_ReadVoltage(i, &vBus, voltReading[i].VoltageDivResistors[0], voltReading[i].VoltageDivResistors[1]));
				EN_PRINTF("%s%-15s%s%d mV\r\n", LEFT_PADDING, voltReading[i].VoltageLabel, "Voltage = ", vBus);
			}
		
			return EN_SUCCESS;
		}
	
	#elif TARGET_BASEBOARD == MARS_EB1
	
		EN_RESULT ReadSystemMonitor()
		{
			/// A little bit of left padding for when we're printing strings.
			char LEFT_PADDING[] = "   ";
	
			// Read and display values from the current monitor
			EN_PRINTF("\r\nSystem Monitor:\r\n");
		
			// Perform any required initialisation.
			EN_RETURN_IF_FAILED(SystemMonitor_Initialise());
		
			// Get the voltage reading.
		
			//Measure the voltages for DA branch on the multiplexers
			SystemController_SetVmonSel(0);
		
			struct VoltageReadingSysMon voltReadingSel0[7] = {
				{"VCC_MAIN",    {47000000, 10000000}},
				{"VCC_3V3_MOD", {10000000, 22000000}},
				{"VCC_OUT",     {10000000, 47000000}},
				{"VCC_2V5",     {10000000, 47000000}},
				{"VCC_5V",      {22000000, 10000000}},
				{"VMON_CS_MOD", {0, 1}},
				{"VREF_CS",     {0, 1}}
			};
		
			int vBus;
			int cBus;
			int vRef;
			int i;
			int Rshunt;
		
			Rshunt = 10;
		
			//Read Current Sense VREF Voltage
			EN_RETURN_IF_FAILED(SystemMonitor_ReadVoltage(6, &vRef, voltReadingSel0[6].VoltageDivResistors[0], voltReadingSel0[6].VoltageDivResistors[1]));
		
			for (i = 0; i < 7; i++)
			{
				if(i== 5)
				{
					EN_RETURN_IF_FAILED(SystemMonitor_ReadCurrent(i, &cBus, Rshunt, vRef));
					EN_PRINTF("%s%-15s%s%d mA\r\n", LEFT_PADDING, voltReadingSel0[i].VoltageLabel, "Current = ", cBus);
				}
				else {
					EN_RETURN_IF_FAILED(SystemMonitor_ReadVoltage(i, &vBus, voltReadingSel0[i].VoltageDivResistors[0], voltReadingSel0[i].VoltageDivResistors[1]));
					EN_PRINTF("%s%-15s%s%d mV\r\n", LEFT_PADDING, voltReadingSel0[i].VoltageLabel, "Voltage = ", vBus);
				}
			}
		
			SystemController_SetVmonSel(1);
			struct VoltageReadingSysMon voltReadingSel1[4] = {
				{"VCC_P41",  {0, 1}},
				{"VCC_P42",  {0, 1}},
				{"VCC_P94",  {0, 1}},
				{"VCC_P198", {0, 1}}
			};
		
			for (i = 0; i < 4; i++)
			{
				EN_RETURN_IF_FAILED(SystemMonitor_ReadVoltage(i, &vBus, voltReadingSel1[i].VoltageDivResistors[0], voltReadingSel1[i].VoltageDivResistors[1]));
				EN_PRINTF("%s%-15s%s%d mV\r\n", LEFT_PADDING, voltReadingSel1[i].VoltageLabel, "Voltage = ", vBus);
		
			}
		
			SystemController_SetVmonSel(0);
		
			return EN_SUCCESS;
		}
	
	#elif TARGET_BASEBOARD == MARS_STA
	
		EN_RESULT ReadSystemMonitor()
		{
			return EN_SUCCESS;
		}
	
	#elif TARGET_BASEBOARD == MERCURY_STARTER
	
		EN_RESULT ReadSystemMonitor()
		{
			return EN_SUCCESS;
		}
	
	#elif TARGET_BASEBOARD == MERCURY_PE1
	
		EN_RESULT ReadSystemMonitor()
		{
			/// A little bit of left padding for when we're printing strings.
			char LEFT_PADDING[] = "   ";
	
			// Read and display values from the current monitor
			EN_PRINTF("\r\nSystem Monitor:\r\n");
		
			// Perform any required initialisation.
			EN_RETURN_IF_FAILED(SystemMonitor_Initialise());
		
			// Get the voltage reading.
		
			//Measure the voltages for DA branch on the multiplexers
			SystemController_SetVmonSel(0);
		
			struct VoltageReadingSysMon voltReadingSel0[7] = {
				{"VMON_12V",    {47000000, 10000000}},
				{"VMON_3V3",    {10000000, 22000000}},
				{"VMON_OUT_A",  {10000000, 47000000}},
				{"VMON_OUT_B",  {10000000, 47000000}},
				{"VMON_CS_MOD", {0, 1}},
				{"VMON_CS_3V3", {0, 1}},
				{"VMON_5V",     {22000000, 10000000}}
			};
		
			int vBus;
			int cBus;
			int vRef;
			int i;
			int Rshunt;
		
			Rshunt = 10;
		
			//Read Current Sense VREF Voltage
			//EN_RETURN_IF_FAILED(SystemMonitor_ReadVoltage(6, &vRef, voltReading[6].VoltageDivResistors[0], voltReading[6].VoltageDivResistors[1]));
			vRef = 0;
		
			for (i = 0; i < 7; i++)
			{
				if(i ==4 || i== 5)
				{
					EN_RETURN_IF_FAILED(SystemMonitor_ReadCurrent(i, &cBus, Rshunt, vRef));
					EN_PRINTF("%s%-15s%s%d mA\r\n", LEFT_PADDING, voltReadingSel0[i].VoltageLabel, "Current = ", cBus);
				}
				else {
					EN_RETURN_IF_FAILED(SystemMonitor_ReadVoltage(i, &vBus, voltReadingSel0[i].VoltageDivResistors[0], voltReadingSel0[i].VoltageDivResistors[1]));
					EN_PRINTF("%s%-15s%s%d mV\r\n", LEFT_PADDING, voltReadingSel0[i].VoltageLabel, "Voltage = ", vBus);
				}
			}
		
			return EN_SUCCESS;
		}
	
	#endif
#else
	#if TARGET_MODULE==COSMOS_XZQ10

		EN_RESULT ReadSystemMonitor()
		{
			/// A little bit of left padding for when we're printing strings.
			char LEFT_PADDING[] = "   ";
	
			// Read and display values from the current monitor
			EN_PRINTF("\r\nSystem Monitor:\r\n");
		
			// Perform any required initialisation.
			EN_RETURN_IF_FAILED(SystemMonitor_Initialise());
		
			// Get the voltage reading.
				
			struct VoltageReadingSysMon voltReadingSel0[7] = {
				{"VCC_MAIN",                       {47000000, 10000000}},
				{"VCC_3V3",                        {10000000, 20000000}},
				{"VCC_5V",                         {22000000, 10000000}},
				{"VCC_2V5",                        {10000000, 47000000}},
				{"VCC_2V0 (1.8V for FBG packages)",{0, 1}},
				{"VCC_DDR3",                       {0, 1}},
				{"VCC_1V2",                        {0, 1}}
			};
		
			int vBus;
			int i;
		
			for (i = 0; i < 7; i++)
			{
				EN_RETURN_IF_FAILED(SystemMonitor_ReadVoltage(i, &vBus, voltReadingSel0[i].VoltageDivResistors[0], voltReadingSel0[i].VoltageDivResistors[1]));
				EN_PRINTF("%s%-15s%s%d mV\r\n", LEFT_PADDING, voltReadingSel0[i].VoltageLabel, "Voltage = ", vBus);
			}
		
			return EN_SUCCESS;
		}


	#else
		EN_RESULT ReadSystemMonitor()
		{
			return EN_SUCCESS;
		}
	#endif

#endif