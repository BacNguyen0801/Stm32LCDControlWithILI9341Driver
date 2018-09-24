#include "BackgroundHander.h"

/*Section: user definition*/
#define BitMapPicture_0 
#define BitMapPicture_1 
#define BitMapPicture_2 
#define BitMapPicture_3 

#define LCD_WEIGH 320
#define LCD_HEIGHT 240
#define LCD_SIZE_OF_PIXEL 2
/*End section*/

/*Section: Local variables*/
static const uint16_t a_PictureBitMap[e_BG_MaxNum][LCD_WEIGH][LCD_HEIGHT*LCD_SIZE_OF_PIXEL] = {
	BitMapPicture_0,
	BitMapPicture_1,
	BitMapPicture_2,
	BitMapPicture_3
}

static eBackgroundIndex v_CurrentBGIndex;
/*End section*/

/*Section: Function implementation*/
void BGH_SetBackground(eBackgroundIndex index)
{
	if(index < e_BG_MaxNum)
	{
		v_CurrentBGIndex = index;
	}
	else
	{
		/*Do nothing*/
	}
}

void BGH_Draw()
{
	ILI9341_DrawBlock();
}

void BGH_FillBackground(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1)
{
	
}
/*End section*/