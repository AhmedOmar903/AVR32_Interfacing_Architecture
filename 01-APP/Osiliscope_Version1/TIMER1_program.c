#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER1_interface.h"
#include "TIMER1_config.h"
#include "TIMER1_private.h"



void TIMERONE_VidInitializtaion(void)
{
	TCCR1A=TIMERONE_TCCRA_CONFIG;
	TCCR1B=TIMERONE_TCCRB_CONFIG;
	TIMSK=TIMERONE_MODE;

	#if TIMERONE_MODE == FAST_PWM
		ICR1=(			(8000000)	/	(	(	FREQUANCY	)	*		(	PWM_PRESCALLER	)	)			);
		
		TCCR1A=		CHANNEL			|			TIMERONE_TCCRA_CONFIG		;
	#endif
	
	TCCR1B|=TIMERONE_PRESCALLER; // Configure Timer One Prescaller
}


void TIMERONE_VoidSetThePreLoad(u16 NumberOfCounts)
{
	TCNT1=NumberOfCounts;
}


void TIMERONE_VidSetDutyCycle(u16 DUTYCYCLE)
{
	#if CHANNEL== CHANNEL_A
		OCR1A=DUTYCYCLE;
	#else	
		OCR1B=DUTYCYCLE;
	#endif
}






void TIMERONEICU_VidSenceControl(u8 LOC_u8EdgeType)
{
	if(			LOC_u8EdgeType			)  SET_BIT(TCCR1B,PIN6);      //Rising
	else								   CLR_BIT(TCCR1B,PIN6);	//Falling
}













void TIMERONE_VoidSetCAllBackInputCaptureUnit(void	(*LocalInputCaptureUnitPointerToFunction)(u16 ICR_Value))
{
		InputCaptureUnitPointerToFunction=LocalInputCaptureUnitPointerToFunction;
}





void TIMERONE_VoidSetCallBackOverFlow(void (*LocalTimerOneOverFlowPointerFunction)(void))
{
	TimerOneOverFlowPointerFunction=LocalTimerOneOverFlowPointerFunction;
}






//timer1 event capture//
void __vector_6(void)
{
	InputCaptureUnitPointerToFunction(ICR1);
}

//timer1 overflow//	
void __vector_9(void)
{	
	TimerOneOverFlowPointerFunction();	
}










