/** \file SystemController.h
 * \brief Header file for System Controller functions.
 * \author Diana Ungureanu
 * \date 05.11.15
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
 * \brief Sets/Resets Vmon Sel register of System Controller on EB1/PE1 and sets output direction
 *
 * @return					Result code
 */
EN_RESULT SystemController_SetVmonSel(int set_bit);