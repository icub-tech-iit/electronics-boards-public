/** \file RealtimeClock.h
 * \brief Header file for RTC functions.
 * \author Garry Jeromson
 * \date 02.07.15
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
 * \brief Initialise the real-time clock.
 *
 * @return	Result code
 */
EN_RESULT Rtc_Initialise();


/**
 * \brief Read the time from the real-time clock.
 *
 * @param[out] pHour		Pointer to variable to receive hour value
 * @param[out] pMinutes		Pointer to variable to receive minutes value
 * @param[out] pSeconds		Pointer to variable to receive seconds value
 * @return					Result code
 */
EN_RESULT Rtc_ReadTime(int* pHour, int* pMinutes, int* pSeconds);


/**
 * \brief Set the RTC time.
 *
 * @param hour		Hour
 * @param minutes	Minutes
 * @param seconds	Seconds
 * @return			Result code
 */
EN_RESULT Rtc_SetTime(int hour, int minutes, int seconds);


/**
 * \brief Read the date from the RTC.
 *
 * @param[out] pDay		Pointer to variable to receive day value
 * @param[out] pMonth	Pointer to variable to receive month value
 * @param[out] pYear	Pointer to variable to receive year value
 * @return				Result code
 */
EN_RESULT Rtc_ReadDate(int* pDay, int* pMonth, int* pYear);


/**
 * \brief Set the date in the RTC.
 *
 * @param day		Day
 * @param month		Month
 * @param year		Year
 * @return			Result code
 */
EN_RESULT Rtc_SetDate(int day, int month, int year);


/**
 * \brief Read the temperature in degrees Celsius from the RTC.
 *
 * @param[out] pTemperature		Pointer to variable to receive temperature value
 * @return						Result code
 */
EN_RESULT Rtc_ReadTemperature(int* pTemperature);
