#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_register.h"
#include "TIMER_interface.h"

static void (*GLOBAL_VidPointer)(void);
void TIMER_VidSetCallBack(void(*LOCAL_VidPointer)(void)){
	
	if(LOCAL_VidPointer!=NULL){
		GLOBAL_VidPointer=LOCAL_VidPointer;
	}
}


void TIMER_VidInit(void){
	
	//SELECT PRE_SCALLER //
#if TIMER0_PRE_SCALLER==TIMER0_PRE_8
	CLR_BIT(TCCR0,PIN2);
	SET_BIT(TCCR0,PIN1);
	CLR_BIT(TCCR0,PIN0);
#elif TIMER0_PRE_SCALLER==TIMER0_PRE_64
	CLR_BIT(TCCR0,PIN2);
	SET_BIT(TCCR0,PIN1);
	SET_BIT(TCCR0,PIN0);
#elif TIMER0_PRE_SCALLER==TIMER0_PRE_256
	SET_BIT(TCCR0,PIN2);
	CLR_BIT(TCCR0,PIN1);
	CLR_BIT(TCCR0,PIN0);
#elif TIMER0_PRE_SCALLER==TIMER0_PRE_1024
	SET_BIT(TCCR0,PIN2);
	CLR_BIT(TCCR0,PIN1);
	SET_BIT(TCCR0,PIN0);

#endif

	
//SELECT TIMER0 MODE //
#if  TIMER0_MODE==TIMER0_OVER_FLOW
	//interrupt enable overflow//
	SET_BIT(TIMSK,PIN0);
	CLR_BIT(TIMSK,PIN1);
    //set for normal mode//
	CLR_BIT(TCCR0,PIN6);
	CLR_BIT(TCCR0,PIN3);
  //set for normal mode oco//
    CLR_BIT(TCCR0,PIN5);
	CLR_BIT(TCCR0,PIN4);

#elif TIMER0_MODE==TIMER0_CTC
  //interrupt enable CTC//
	SET_BIT(TIMSK,PIN1);
	CLR_BIT(TIMSK,PIN0);
	//set for CTC mode//
	CLR_BIT(TCCR0,PIN6);
	SET_BIT(TCCR0,PIN3);
  //set for normal mode oco//
	CLR_BIT(TCCR0,PIN5);
	CLR_BIT(TCCR0,PIN4);
	OCR0=125;
#elif TIMER0_MODE==TIMER0_FAST_PWM
	//interrupt Disable //
	CLR_BIT(TIMSK,PIN0);
	CLR_BIT(TIMSK,PIN1);
   //SELECT fast_PWM mode//
	SET_BIT(TCCR0,PIN6);
	SET_BIT(TCCR0,PIN3);
  //SELECT Non inverted mode//
	CLR_BIT(TCCR0,PIN4);
	SET_BIT(TCCR0,PIN5);
	OCR0=120;//ton will 128 mean the duty cyle equal 50% //

#endif

}


void TIMER0_VidSetDutyCycle(u8 LOC_u8Volt){
//pinB 3//


    OCR0=LOC_u8Volt;
	//take the volt//

}
//OVER_FLOW//
void __vector_11(void){
	if(GLOBAL_VidPointer!=NULL){
		
		  GLOBAL_VidPointer();
	}	
}
//CTC//
void __vector_10(void){
	if(GLOBAL_VidPointer!=NULL){
		
		GLOBAL_VidPointer();
	}	
}
