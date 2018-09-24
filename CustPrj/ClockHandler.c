#include "CLockHandler.h"

#include "ILI9341_Touchscreen.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

/*Section: Local variables*/
static RTC_TimeTypeDef v_Time;
static RTC_DateTypeDef v_Date;

extern RTC_HandleTypeDef hrtc;
/*End Section*/

/*Section: local API*/
static void CH_ShowClock();
/*End section*/

/*Section: Function implementation*/
void CH_Init()
{
	CH_ShowClock();
}

void CH_RunOne()
{
	RTC_TimeTypeDef newTime;
	HAL_RTC_GetTime(&hrtc, &newTime, RTC_FORMAT_BIN);
	if(newTime.Seconds != v_Time.Seconds)
	{
		CH_ShowClock();
	}
}

void CH_ShowClock()
{
	uint8_t counter_buff[30];
	/*Get time*/
	HAL_RTC_GetDate(&hrtc, &v_Date, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc, &v_Time, RTC_FORMAT_BIN);

	/*Show time*/
	sprintf(counter_buff, "%02d:%02d", v_Time.Hours, v_Time.Minutes);
	ILI9341_Draw_Text(counter_buff, 10, 10, BLACK, 4, WHITE);
	sprintf(counter_buff, "%02d", v_Time.Seconds);
	ILI9341_Draw_Text(counter_buff, 130, 25, BLACK, 2, WHITE);
}

/*End section*/
