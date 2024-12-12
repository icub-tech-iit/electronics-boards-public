/** \file SystemMonitor.h
 * \brief Header file for System Monitor functions.
 * \author Gian Köppel
 * \date 03.07.15
 */

#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "StandardIncludes.h"

//-------------------------------------------------------------------------------------------------
// Function declarations
//-------------------------------------------------------------------------------------------------

/**
 * \brief Initialise the system monitor,
 *
 * @return	Result code
 */
EN_RESULT SystemMonitor_Initialise();

/**
 * \brief Read a raw value from the system monitor
 *
 * @param[in] channel		Channel Index (0-6)
 * @param[out] pValue		Pointer to variable to receive raw value
 * @return					Result code
 */
EN_RESULT SystemMonitor_ReadValue(uint16_t channel, uint16_t* pValue);

/**
 * \brief Read a voltage in millivolt from the system monitor
 *
 * @param[in] channel		Channel Index (0-6)
 * @param[out] pVoltage		Pointer to variable to receive voltage
 * @param[in] RUpper		Voltage divider upper resistor (0 if no divider is used) in milliohms
 * @param[in] RLower		Voltage divider lower resistor (1 if no divider is used) in milliohms
 * @return					Result code
 */
EN_RESULT SystemMonitor_ReadVoltage(uint16_t channel, int* pVoltage, int RUpper, int RLower);

/**
 * \brief Read a current in millivolt from the system monitor
 *
 * @param[in] channel		Channel Index (0-6)
 * @param[out] pCurrent		Pointer to variable to receive voltage
 * @param[in] RShunt		Shunt resistor value in milliohms
 * @param[in] vRef			Reference Voltage of INA199A2 current sensor
 * @return					Result code
 */
EN_RESULT SystemMonitor_ReadCurrent(uint16_t channel, int* pCurrent, int RShunt, int vRef);
