
	
	#include "STD_TYPES.h"
	#include "BIT_MATH.h"
	#include "TIMER2_register.h"
	#include "TIMER2_interface.h"


	static void (*GlobalPointerTimer2)(void)=NULL;

	void TIMER2_SetCallBack(void (*LocalPointerTimer2)(void)){

	  if(LocalPointerTimer2!=NULL){


		  GlobalPointerTimer2=LocalPointerTimer2;
	  }

	}

	void TIMER2_VidInit(void){

	SET_BIT(ASSR,PIN3);


		//SELECT PRE_SCALLER //
	#if TIMER2_PRE_SCALLER==TIMER2_PRE_8
		CLR_BIT(TCCR2,PIN0);
		SET_BIT(TCCR2,PIN1);
		CLR_BIT(TCCR2,PIN2);
	#elif TIMER2_PRE_SCALLER==TIMER2_PRE_32
		SET_BIT(TCCR2,PIN0);
		SET_BIT(TCCR2,PIN1);
		CLR_BIT(TCCR2,PIN2);	
	#elif TIMER2_PRE_SCALLER==TIMER2_PRE_64
		CLR_BIT(TCCR2,PIN0);
		CLR_BIT(TCCR2,PIN1);
		SET_BIT(TCCR2,PIN2);
	#elif TIMER2_PRE_SCALLER==TIMER2_PRE_128
		SET_BIT(TCCR2,PIN0);
		CLR_BIT(TCCR2,PIN1);
		SET_BIT(TCCR2,PIN2);
	#elif TIMER2_PRE_SCALLER==TIMER2_PRE_256
		CLR_BIT(TCCR2,PIN0);
		SET_BIT(TCCR2,PIN1);
		SET_BIT(TCCR2,PIN2);
	#elif TIMER2_PRE_SCALLER==TIMER2_PRE_1024
		SET_BIT(TCCR2,PIN0);
		SET_BIT(TCCR2,PIN1);
		SET_BIT(TCCR2,PIN2);

	#endif




	#if TIMER2_MODE==OVER_FLOW
	CLR_BIT(TCCR2,PIN3);//WGM21//
	CLR_BIT(TCCR2,PIN6);//WGM20//
	CLR_BIT(TCCR2,PIN5);// OC DISCONNECT//
	CLR_BIT(TCCR2,PIN4);

	#elif TIMER2_MODE==CTC
	SET_BIT(TCCR2,PIN3);//WGM21//
	CLR_BIT(TCCR2,PIN6);//WGM20//
	CLR_BIT(TCCR2,PIN5);// OC DISCONNECT//
	CLR_BIT(TCCR2,PIN4);
	#elif TIMER2_MODE==FAST_PWM  
	SET_BIT(TCCR2,PIN3);//WGM21//
	SET_BIT(TCCR2,PIN6);//WGM20//
	SET_BIT(TCCR2,PIN5); //NON INVEERTING//
	CLR_BIT(TCCR2,PIN4);

	#endif

	}


	void TIMER2_VidSetDutyCycle(u8 LOC_u8OcrValue){

		OCR2=LOC_u8OcrValue;

	}
	//ctc//
	void __vector_4(void){
		
		if(GlobalPointerTimer2!=NULL){

				GlobalPointerTimer2();
			}

	}
	//over/
	void __vector_5(void){
		
		if(GlobalPointerTimer2!=NULL){

			GlobalPointerTimer2();
		}

	}

