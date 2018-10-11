 #ifndef __GLOBAL_STATE_MACHINE_h__
 #define __GLOBAL_STATE_MACHINE_h__
 
typedef enum {
	e_GStateBeforeInit,
	 e_GStateInit,
	 e_GStateSteady,
	 e_GStateSetting,
	 e_GStateIdle,
	 e_GStateInvalid
 } eGlobalState;


 void GSM_RunOne();
 
 void GSM_PushCmd(eGlobalState cmd);

 #endif // __GLOBAL_STATE_MACHINE_h__
