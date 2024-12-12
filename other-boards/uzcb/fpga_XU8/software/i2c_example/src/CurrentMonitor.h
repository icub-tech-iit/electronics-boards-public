/** \file CurrentMonitor.h
 * \brief Interface functions for I2C current monitor devices.
 * \author Christoph Glattfelder
 * \author Garry Jeromson
 * \date 18.06.15
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
 * \brief Initialise the current monitor.
 *
 * @return 			Result code
 */
EN_RESULT CurrentMonitor_Initialise();


/**
 * \brief Write to the current monitor configuration register.
 *
 * @param value		The value to write to the register
 * @return			Result code
 */
EN_RESULT CurrentMonitor_WriteConfig(uint16_t value);


/**
 * \brief Write to the current monitor calibration register.
 * @param value		Write value
 * @return			Result code
 */
EN_RESULT CurrentMonitor_WriteCalibration(uint16_t value);


/**
 * \brief Read the current monitor configuration register
 *
 * @param[out] pValue	Read value
 * @return				Result code
 */
EN_RESULT CurrentMonitor_ReadConfig(uint16_t* pValue);


/**
 * \brief Read the current monitor VSense register.
 *
 * @param[out] pValue	Read value
 * @return				Result code
 */
EN_RESULT CurrentMonitor_ReadVSense(uint16_t* pValue);


/**
 * \brief Read the current monitor VBus register.
 *
 * @param[out] pValue	Read value
 * @return				Result code
 */
EN_RESULT CurrentMonitor_ReadVBus(uint16_t* pValue);


/**
 * \brief Read the current monitor power register.
 *
 * @param[out] pValue	Read value
 * @return				Result code
 */
EN_RESULT CurrentMonitor_ReadPower(uint16_t* pValue);


/**
 * \brief Read the current monitor current register.
 *
 * @param[out] pValue	Read value
 * @return				Result code
 */
EN_RESULT CurrentMonitor_ReadCurrent(uint16_t* pValue);


/**
 * \brief Read the calibration register value.
 *
 * @param[out] pValue 	Read value
 * @return				Result code
 */
EN_RESULT CurrentMonitor_ReadCalibration(uint16_t* pValue);
