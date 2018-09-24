 #ifndef __GLOBAL_STATE_MACHINE_h__
 #define __GLOBAL_STATE_MACHINE_h__
 
typedef enum {
	 e_GStateInit,
	 e_GStateSteady,
	 e_GStateIdle,
	 e_GStateInvalid
 } eGlobalState;
 
 void GSM_RunOne();
 
 void GSM_SwitchState(eGlobalState state);
 
 #endif // __GLOBAL_STATE_MACHINE_h__
