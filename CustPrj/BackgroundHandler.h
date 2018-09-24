#ifndef __BACKGROUND_HANDLER__h_
#define __BACKGROUND_HANDLER__h_

#include "stm32f1xx_hal.h"

typedef enum {
	e_BG_Num0,
	e_BG_MaxNum
} eBackgroundIndex;


void BGH_SetBackground(eBackgroundIndex index);

void BGH_Draw();

void BGH_FillBackground(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1);

void BGH_Init();

#endif
