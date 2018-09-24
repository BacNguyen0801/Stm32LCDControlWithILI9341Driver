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
			GSM_SwitchState(e_GStateSteady)
			break;
		}
		
		case e_GStateSteady:
		{
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