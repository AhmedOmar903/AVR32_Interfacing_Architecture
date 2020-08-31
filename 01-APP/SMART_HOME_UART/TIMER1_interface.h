
	#ifndef _TIMER1_INTERFACE_H_
	#define _TIMER1_INTERFACE_H_
	#define CHANNEL_A     					  1
	#define CHANNEL_B     					  0 
	#define OVER_FLOW     					  1 
	#define ICU        					      0 
	#define CTC        					      2 
	#define FAST_PWM_8        				  3 
	#define TIMER1_PRE_8        			  0 
	#define TIMER1_PRE_64        			  1 
	#define TIMER1_PRE_256       			  2 
	#define TIMER1_PRE_1024        			  3 
	#define FALLING       			          0
	#define RISING       			          1
	#define TIMER1_MODE     			    ICU
	#define TIMER1_PRE_SCALLER     		   TIMER1_PRE_256
	#define SELECT_CHANNEL     			    CHANNEL_B
	

	void TIMER1_VidInit(void);
	void TIMER1_VidSetDutyCycle(u16 LOC_u16OcrValue);
	void TIMER1_SetCallBackIcp(void (*LocalPointerIcpTimer1)(u16 LOC_u16Icr1Adress));
	void TIMER1_SetCallBack(void (*LocalPointerTimer1)(void));
	void TIMER1_VidSenceControlIcp(u8 LOC_u8EdgeType);

	#endif
