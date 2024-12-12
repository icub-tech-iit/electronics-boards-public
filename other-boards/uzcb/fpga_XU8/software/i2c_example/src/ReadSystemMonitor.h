/** \file ReadSystemMonitor.h
 * \brief Header file for Read System Monitor function.
 * \author Diana Ungureanu
 * \date 05.11.15
 */

#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "StandardIncludes.h"

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------

#define SYSTEM_CONTROLLER_DEVICE_ADDRESS 0x0D
#define SYSTEM_CONTROLLER_REGISTER_ADDRESS_VMON_SEL    20
#define SYSTEM_CONTROLLER_REGISTER_ADDRESS_VMON_SEL_EN 21


//-------------------------------------------------------------------------------------------------
// Function and variable declarations
//-------------------------------------------------------------------------------------------------


struct VoltageReadingSysMon {
	char* VoltageLabel;
	int VoltageDivResistors[2];
};


/**
 * \brief Reads and prints out the values from the system monitor
 *
 * The configuration printed depends on the base board (system monitor and/or current sense)
 * @return					Result code
 */
EN_RESULT ReadSystemMonitor();