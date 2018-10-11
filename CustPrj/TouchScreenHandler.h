/*
 * TouchSreenHandler.h
 *
 *  Created on: Oct 5, 2018
 *      Author: BapCoi
 */

#ifndef TOUCHSCREENHANDLER_H_
#define TOUCHSCREENHANDLER_H_

#include "stm32f1xx_hal.h"

typedef enum
{
	e_TouchLeftToRight,
	e_TouchRightToLeft,
	e_TouchTopToBottom,
	e_TouchBottomToTop,
	e_TouchOnly,
	e_Invalid
} e_TouchRegconized;

void TSH_RunOne();

e_TouchRegconized TSH_GetLastTouchCmd();

#endif /* TOUCHSCREENHANDLER_H_ */
