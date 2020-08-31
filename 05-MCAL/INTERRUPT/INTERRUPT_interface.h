
	#ifndef _INTERRUPT_INTERFACE_H_
	#define _INTERRUPT_INTERFACE_H_
	
		#define FALLING             0
	#define RISING              1
	#define IOC                 2
	#define LOW_level           3
	#define SENCE_MODE       FALLING
	
	

	#define EXIT0              0  // D2 //
	#define EXIT1              1  // D3 //
	#define EXIT2              2  // B2 //

	void INTERRIPT_SetCallBack(void (*LOCAL_Pointer)(void));


	void INTERRUPT_VidIntial(u8 loc_u8ExitNum);
	void INTERRUPT_VidEnable(u8 loc_u8ExitNum);
	void INTERRUPT_VidDisable(u8 loc_u8ExitNum);
	#endif

	//set the port direction ask about setcallback//
