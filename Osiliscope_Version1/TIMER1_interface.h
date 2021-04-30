#ifndef _TIMER1_INTERFACE_H_
#define _TIMER1_INTERFACE_H_

#define FALLING       			          0
#define RISING       			          1

void TIMERONE_VidInitializtaion(void);
void TIMERONE_VidSetDutyCycle(u16 DUTYCYCLE);
void TIMERONEICU_VidSenceControl(u8 LOC_u8EdgeType);
void TIMERONE_VoidSetThePreLoad(u16 NumberOfCounts);
void TIMERONE_VoidSetCAllBackInputCaptureUnit(void	(*LocalInputCaptureUnitPointerToFunction)(u16 ICR_Value));

void TIMERONE_VoidSetCallBackOverFlow(void (*LocalTimerOneOverFlowPointerFunction)(void));

#endif
