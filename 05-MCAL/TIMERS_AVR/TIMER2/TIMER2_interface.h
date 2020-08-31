

	#ifndef _TIMER2_INTERFACE_H_
	#define _TIMER2_INTERFACE_H_
	
		#define OVER_FLOW     					  1 
	#define FAST_PWM        				  0 
	#define CTC        					      2 
	#define TIMER2_PRE_8                      0
	#define TIMER2_PRE_32                     4
	#define TIMER2_PRE_64                     1
	#define TIMER2_PRE_128                    5
	#define TIMER2_PRE_256                    2
	#define TIMER2_PRE_1024                   3
	#define TIMER2_PRE_SCALLER           TIMER2_PRE_256
	#define TIMER2_MODE     			    OVER_FLOW
	
	
	
	
	void TIMER2_VidInit(void);
	void TIMER2_SetCallBack(void (*LocalPointerTimer2)(void));
	void TIMER2_VidSetDutyCycle(u8 LOC_u8OcrValue);
	#endif
