#include "GlobalStateMachine.h"
#include "BackgroundHandler.h"
#include "ClockHandler.h"

/*Local function*/
static void GSM_StateStateHandling();
static void GSM_Init();

/*Local variables*/
static eGlobalState v_State = e_GStateInit;

/*Section: Function implementation*/
void GSM_RunOne()
{
	switch(v_State)
	{
		case e_GStateInit:
		{
			GSM_Init();
			GSM_SwitchState(e_GStateSteady);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
			break;
		}
		
		case e_GStateSteady:
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
			GSM_StateStateHandling();
			break;
		}
		
		default:
			break;
	}
}

void GSM_SwitchState(eGlobalState state)
{
	if(e_GStateInvalid > state)
	{
		v_State = state;
	}
}

void GSM_Init()
{
	/*Init ILI9341 driver*/
	ILI9341_Init();
	/* Init Background */
	BGH_Init();
	/* Init clock */
	CH_Init();
}

void GSM_StateStateHandling()
{
	/*Handle clock*/
	CH_RunOne();
}
/*End section*/
