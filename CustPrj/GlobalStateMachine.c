#include "GlobalStateMachine.h"
#include "BackgroundHandler.h"
#include "ClockHandler.h"
#include "SettingControl.h"
#include "TouchScreenHandler.h"

/*Local function*/
static void GSM_StateStateHandling();
static void GSM_Init();
static void GSM_ProcessNewCommand();

/*Local variables*/
static eGlobalState v_State = e_GStateBeforeInit;
static uint32_t v_TickCnt = 0;

/*Section: Function implementation*/
void GSM_RunOne()
{
	switch(v_State)
	{
		case e_GStateBeforeInit:
		{
			v_TickCnt = HAL_GetTick();
			v_State = e_GStateInit;
			break;
		}
		case e_GStateInit:
		{
			v_TickCnt = HAL_GetTick() - v_TickCnt;
			if(v_TickCnt > 100)
			{
				GSM_Init();
				v_State = e_GStateSteady;
			}
			break;
		}
		
		case e_GStateSteady:
		{
			GSM_StateStateHandling();
			break;
		}
		
		case e_GStateSetting:
		{
			SC_DisplayScreen();
			break;
		}

		default:
			break;
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

	/*Check touch command*/
	TSH_RunOne();

	/*Process command*/
	GSM_ProcessNewCommand();
}

void GSM_PushCmd(eGlobalState state)
{
	if (v_State == e_GStateIdle)
	{
		/*Not handle on invalid case*/
		return;
	}
	v_State = state;
}

void GSM_ProcessNewCommand()
{
	/*Get command from TSH module*/\
	uint16_t* pos;
	e_TouchRegconized touchCmd = TSH_GetLastTouchCmd(pos);
	switch(touchCmd)
	{
	case e_TouchRightToLeft:
	{
		/*Go to setting page*/
		v_State = e_GStateSetting;
	} break;
	default:
	{
		/*Do nothing*/
		break;
	}
	}
}
/*End section*/
