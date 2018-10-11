#include "SettingControl.h"
#include "TouchScreenHandler.h"
#include "ILI9341_Touchscreen.h"
#include "ILI9341_STM32_Driver.h"
#include "GlobalStateMachine.h"
#include "ILI9341_GFX.h"

static void SC_InitScreen();
static uint8_t s_FirstTimeActiveSetting = 0x00;

#define M_XPosClockSetting 10
#define M_YPosClockSetting 10
#define M_WIDTH_ClockSetting 150
#define M_HIEGHT_ClockSetting 20

#define M_XPosColorSetting 10
#define M_YPosColorSetting 40
#define M_WIDTH_ColorSetting 150
#define M_HIEGHT_ColorSetting 20

void SC_DisplayScreen()
{
	if(s_FirstTimeActiveSetting == 0x00)
	{
		SC_InitScreen();
		s_FirstTimeActiveSetting = 0x01;
	}
	else
	{

		/*Check touch command*/
		TSH_RunOne();

		/*Get command from touch screen module*/
		uint16_t* pos;
		e_TouchRegconized touchCmd = TSH_GetLastTouchCmd(pos);
		switch(touchCmd)
		{
		case e_TouchLeftToRight:
		{
			/*Go to setting page*/
			GSM_PushCmd(e_GStateInit);
			break;
		}
		case e_TouchOnly:
		{
//			if(pos[1] >= M_XPosClockSetting && pos[1] <= (M_XPosClockSetting + M_WIDTH_ClockSetting) &&
//			   pos[0] >= M_YPosClockSetting && pos[0] <= (M_YPosClockSetting + M_HIEGHT_ClockSetting))
			if(1)
			{
				ILI9341_Draw_Rectangle(M_XPosClockSetting, M_YPosClockSetting, M_WIDTH_ClockSetting, M_HIEGHT_ClockSetting, RED);
				ILI9341_Draw_Text("Clicked", M_XPosClockSetting + 2, M_YPosClockSetting + 2, WHITE, 2);
			}
			else if(pos[1] >= M_XPosColorSetting && pos[1] <= (M_XPosColorSetting + M_WIDTH_ColorSetting) &&
			   pos[0] >= M_YPosColorSetting && pos[0] <= (M_YPosColorSetting + M_HIEGHT_ColorSetting))
			{
				ILI9341_Draw_Rectangle(M_XPosColorSetting,M_YPosColorSetting, M_WIDTH_ColorSetting, M_HIEGHT_ColorSetting, RED);
				ILI9341_Draw_Text("Clicked", M_XPosColorSetting + 2, M_YPosColorSetting + 2, WHITE, 2);
			}
			break;
		}
		default:
		{
			/*Do nothing*/
			break;
		}
		}
	}
}


void SC_InitScreen()
{
	ILI9341_Clear(BLACK);

	/*Draw first button: Clock*/
	ILI9341_Draw_Rectangle(M_XPosClockSetting, M_YPosClockSetting, M_WIDTH_ClockSetting, M_HIEGHT_ClockSetting, RED);
	ILI9341_Draw_Text("Change clock", M_XPosClockSetting + 2, M_YPosClockSetting + 2, WHITE, 2);

	/*Draw second button: Color*/
	ILI9341_Draw_Rectangle(M_XPosColorSetting,M_YPosColorSetting, M_WIDTH_ColorSetting, M_HIEGHT_ColorSetting, RED);
	ILI9341_Draw_Text("Change color", M_XPosColorSetting + 2, M_YPosColorSetting + 2, WHITE, 2);
}
