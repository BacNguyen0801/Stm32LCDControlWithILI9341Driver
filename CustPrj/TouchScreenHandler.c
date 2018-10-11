/*
 * TouchSreenHandler.c
 *
 *  Created on: Oct 5, 2018
 *      Author: BapCoi
 */

#include "TouchScreenHandler.h"
#include "ILI9341_Touchscreen.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

#define M_MaxTouchPointHandle 100
#define M_MinimumThresholdForTouchMove 100

uint16_t v_XYPosition[M_MaxTouchPointHandle][2];
uint16_t v_CurPositionIndex;
static e_TouchRegconized v_LastCommand;
static uint16_t v_LastTouchPosition[2];

void TSH_RunOne()
{
	/*Reset for next cmd*/
	v_CurPositionIndex = 0;
	while(TP_Touchpad_Pressed())
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_SET);
		if(TP_Read_Coordinates(v_XYPosition[v_CurPositionIndex]) == TOUCHPAD_DATA_OK)
		{
			/*No need to update*/
			if(v_CurPositionIndex != 0 &&
				v_XYPosition[v_CurPositionIndex-1][0] == v_XYPosition[v_CurPositionIndex][0] &&
				v_XYPosition[v_CurPositionIndex-1][1] == v_XYPosition[v_CurPositionIndex][1])
			{
				/*Do nothing*/
				++v_CurPositionIndex;
			}
			else
			{
				++v_CurPositionIndex;
				if(v_CurPositionIndex == M_MaxTouchPointHandle)
				{
					/*Enough sample, don't need to get more*/
					--v_CurPositionIndex;
				}
			}
		}
		else
		{
			break;
		}
	}
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_RESET);
	if(v_CurPositionIndex != 0)
	{
		uint8_t touchMoveCmdFlag = 0;
		uint16_t deltaX, deltaY;
		deltaX = v_XYPosition[v_CurPositionIndex-1][0] - v_XYPosition[0][0];
		deltaY = v_XYPosition[v_CurPositionIndex-1][1] - v_XYPosition[0][1];

		if(deltaX > deltaY)
		{
			if(deltaX > M_MinimumThresholdForTouchMove)
			{
				if(0 != (deltaX & 0x80))
				{
					v_LastCommand = e_TouchBottomToTop;
					touchMoveCmdFlag= 0x01;
				}
				else
				{
					v_LastCommand = e_TouchTopToBottom;
					touchMoveCmdFlag= 0x01;
				}
			}
		}
		else
		{
			if(deltaY > M_MinimumThresholdForTouchMove)
			{
				if(0 != (deltaY & 0x80))
				{
					v_LastCommand = e_TouchRightToLeft;
					touchMoveCmdFlag= 0x01;
				}
				else
				{
					v_LastCommand = e_TouchLeftToRight;
					touchMoveCmdFlag= 0x01;
				}
			}
		}
		if (0 == touchMoveCmdFlag)
		{
			v_LastCommand = e_TouchOnly;
			v_LastTouchPosition[0] = (v_XYPosition[v_CurPositionIndex-1][0]+v_XYPosition[0][0]) /2;
			v_LastTouchPosition[1] = (v_XYPosition[v_CurPositionIndex-1][1]+v_XYPosition[0][1]) /2;
		}

		char counter_buff[40];
		sprintf(counter_buff, "%.3d-%.3d-%.1d", v_XYPosition[v_CurPositionIndex-1][0], v_XYPosition[v_CurPositionIndex-1][1], v_LastCommand);
		ILI9341_Draw_Rectangle(0,100, 320, 20, BLACK);
		ILI9341_Draw_Text(counter_buff, 100,100,RED,2);
	}

}

e_TouchRegconized TSH_GetLastTouchCmd(uint16_t* pos)
{
	pos = v_LastTouchPosition;
	return v_LastCommand;
}

