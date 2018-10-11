#include "CLockHandler.h"

#include "ILI9341_Touchscreen.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

#define SIZE_HOUR_ON_PIXEL 4
#define SIZE_MINUTE_ON_PIXEL 4
#define SIZE_SECOND_ON_PIXEL 2
#define SIZE_COLON_ON_PIXEL 3
#define SIZE_DEFAULT_FONT 6

#define M_GetColonPosition LEFT_ALIGNMENT + SIZE_HOUR_ON_PIXEL * SIZE_DEFAULT_FONT * 2
#define M_GetMinutePosition M_GetColonPosition + SIZE_COLON_ON_PIXEL * SIZE_DEFAULT_FONT
#define M_GetSecondPosition M_GetMinutePosition + SIZE_MINUTE_ON_PIXEL * SIZE_DEFAULT_FONT * 2

#define TOP_ALIGNMENT 10
#define LEFT_ALIGNMENT 10
#define RIGHT_ALIGNMENT 10
#define BOTTOM_ALIGNMENT 10

typedef enum
{
	e_ClockSetting,
	e_ClockSteady
} e_ClockState;

typedef enum
{
	e_ClockAlignTop,
	e_ClockAlignBottom,
	e_ClockAlignRight,
	e_ClockAlignLeft,
} e_ClockPosition;

/*Section: Local variables*/
static RTC_TimeTypeDef v_Time;
static e_ClockState v_ClockState = e_ClockSteady;
extern RTC_HandleTypeDef hrtc;
/*End Section*/

/*Section: local API*/
static void CH_UpdateHour();
static void CH_UpdateMinute();
static void CH_UpdateSecond();
static void CH_UpdateColon(uint8_t visible);
/*End section*/

/*Section: Function implementation*/
void CH_Init()
{
	v_ClockState = e_ClockSteady;
	v_Time.Hours = 0;
	v_Time.Minutes = 0;
	v_Time.Seconds = 0;
}

void CH_RunOne()
{
	switch(v_ClockState)
	{
		case e_ClockSteady:
		{
			RTC_TimeTypeDef newTime;
			HAL_RTC_GetTime(&hrtc, &newTime, RTC_FORMAT_BIN);
			if(newTime.Seconds != v_Time.Seconds)
			{
				v_Time.Seconds = newTime.Seconds; /*Update second*/
				CH_UpdateSecond();
				CH_UpdateColon(v_Time.Seconds % 2);
				if(newTime.Minutes != v_Time.Minutes)
				{
					v_Time.Minutes = newTime.Minutes; /*Update Minutes*/
					CH_UpdateMinute();
					if(newTime.Hours != v_Time.Hours)
					{
						v_Time.Hours = newTime.Hours; /*Update Hours*/
						CH_UpdateHour();
					}
				}
			}
			break;
		}
		case e_ClockSetting:
		{
			/*Setting time for clock*/
			break;
		}
		default:
			break;
	}

}

void CH_UpdateHour()
{
	uint8_t counter_buff[30];
	/*Show time*/
	sprintf(counter_buff, "%02d", v_Time.Hours);
	BGH_FillBackground(LEFT_ALIGNMENT, TOP_ALIGNMENT, 2 * SIZE_HOUR_ON_PIXEL * CHAR_WIDTH, SIZE_HOUR_ON_PIXEL *CHAR_HEIGHT );
	ILI9341_Draw_Text(counter_buff, TOP_ALIGNMENT, LEFT_ALIGNMENT, RED, SIZE_HOUR_ON_PIXEL);
}

void CH_UpdateMinute()
{
	uint8_t counter_buff[30];
	/*Show time*/
	sprintf(counter_buff, "%02d", v_Time.Minutes);


	ILI9341_Draw_Text(counter_buff, M_GetMinutePosition, TOP_ALIGNMENT, RED, SIZE_MINUTE_ON_PIXEL);
}

void CH_UpdateColon(uint8_t visible)
{
	uint8_t counter_buff[2];
	if(0x00== visible)
	{
		sprintf(counter_buff, ":");
		BGH_FillBackground(M_GetColonPosition, TOP_ALIGNMENT + (SIZE_MINUTE_ON_PIXEL - SIZE_COLON_ON_PIXEL) * SIZE_DEFAULT_FONT, SIZE_COLON_ON_PIXEL *CHAR_WIDTH, SIZE_COLON_ON_PIXEL *CHAR_HEIGHT );
		ILI9341_Draw_Text(counter_buff, M_GetColonPosition, TOP_ALIGNMENT + (SIZE_MINUTE_ON_PIXEL - SIZE_COLON_ON_PIXEL) * SIZE_DEFAULT_FONT, RED, SIZE_COLON_ON_PIXEL);
	}
	else
	{
		BGH_FillBackground(M_GetColonPosition, TOP_ALIGNMENT + (SIZE_MINUTE_ON_PIXEL - SIZE_COLON_ON_PIXEL) * SIZE_DEFAULT_FONT, SIZE_COLON_ON_PIXEL *CHAR_WIDTH, SIZE_COLON_ON_PIXEL *CHAR_HEIGHT );
	}
}

void CH_UpdateSecond()
{
	uint8_t counter_buff[30];
	/*Show time*/
	sprintf(counter_buff, "%02d", v_Time.Seconds);
	BGH_FillBackground(M_GetSecondPosition, TOP_ALIGNMENT + (SIZE_MINUTE_ON_PIXEL - SIZE_SECOND_ON_PIXEL) * SIZE_DEFAULT_FONT, 2 * SIZE_SECOND_ON_PIXEL *CHAR_WIDTH, SIZE_SECOND_ON_PIXEL *CHAR_HEIGHT );
	ILI9341_Draw_Text(counter_buff, M_GetSecondPosition, TOP_ALIGNMENT + (SIZE_MINUTE_ON_PIXEL - SIZE_SECOND_ON_PIXEL) * SIZE_DEFAULT_FONT, RED, SIZE_SECOND_ON_PIXEL);
}


/*End section*/
