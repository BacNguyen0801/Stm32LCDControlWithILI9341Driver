#ifndef __BACKGROUND_HANDLER__h_
#define __BACKGROUND_HANDLER__h_

#include "stm32f1xx_hal.h"

typedef enum {
	e_BG_Num0,
	e_BG_MaxNum
} eBackgroundIndex;


void BGH_SetBackground(eBackgroundIndex index);

void BGH_Draw();

void BGH_FillBackground(uint16_t x, uint16_t y, uint16_t Width, uint16_t Height);

void BGH_Init();

#endif
