#ifndef _TIMER1_INTERFACE_H_
#define _TIMER1_INTERFACE_H_

#define PIN0     					      0
#define PIN1     					      1
#define PIN2     					      2
#define PIN3     					      3
#define PIN4     					      4
#define PIN5     					      5
#define PIN6     					      6
#define PIN7     					      7
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
#define TIMER1_MODE     			    OVER_FLOW
#define TIMER1_PRE_SCALLER     		   TIMER1_PRE_1024
#define SELECT_CHANNEL     			    CHANNEL_A



void TIMER1_VidInit(void);
void TIMER1_VidSetDutyCycle(u16 LOC_u16OcrValue);
void TIMER1_SetCallBackIcp(void (*LocalPointerTimer1)(void));
void TIMER1_SetCallBack(void (*LocalPointerTimer1)(void));
void TIMER1_VidSenceControlIcp(u8 LOC_u8EdgeType);





#endif
