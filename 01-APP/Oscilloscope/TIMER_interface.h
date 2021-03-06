
	#ifndef _TIMER_INTERFACE_H_
	#define _TIMER_INTERFACE_H_
	
	
	#define TIMER0_OVER_FLOW			      0
	#define TIMER0_CTC      			      1
	#define TIMER0_FAST_PWM 			      2
	#define TIMER0_PRE_8                      0
	#define TIMER0_PRE_64                     1
	#define TIMER0_PRE_256                    2
	#define TIMER0_PRE_1024                   3
	#define TIMER0_PRE_SCALLER           TIMER0_PRE_64
	#define TIMER0_MODE                  TIMER0_FAST_PWM


	void TIMER_VidInit(void);
	void TIMER_VidSetCallBack(void(*LOCAL_VidPointer)(void));//over flow take the adress of tcnt0//
	void TIMER0_VidSetDutyCycle(u8 LOC_u8Volt);
	void TIMER0_VidChangeFrequancy(u8 LOC_u8PreScaller);





	#endif
