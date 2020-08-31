
	#include "STD_TYPES.h"
	#include "BIT_MATH.h"
	#include "TIMER1_register.h"
	#include "TIMER1_interface.h"

	// Icp mode//
	static void (*GlobalPointerIcpTimer1)(u16 GLOBAL_u16Icr1Adress)=NULL;

	void TIMER1_SetCallBackIcp(void (*LocalPointerIcpTimer1)(u16 LOC_u16Icr1Adress)){

	  if(LocalPointerIcpTimer1!=NULL){


		  GlobalPointerIcpTimer1=LocalPointerIcpTimer1;
	  }

	}
	// any mode//

	static void (*GlobalPointerTimer1)(void)=NULL;

	void TIMER1_SetCallBack(void (*LocalPointerTimer1)(void)){

	  if(LocalPointerTimer1!=NULL){


		  GlobalPointerTimer1=LocalPointerTimer1;
	  }

	}




	void TIMER1_VidInit(void){
		
	#if TIMER1_PRE_SCALLER==TIMER1_PRE_8 

	CLR_BIT(TCCR1B,PIN0);// CS10//
	SET_BIT(TCCR1B,PIN1);// CS11//
	CLR_BIT(TCCR1B,PIN2);// CS12//
	#elif TIMER1_PRE_SCALLER==TIMER1_PRE_64 

	SET_BIT(TCCR1B,PIN0);// CS10//
	SET_BIT(TCCR1B,PIN1);// CS11//
	CLR_BIT(TCCR1B,PIN2);// CS12//
	#elif TIMER1_PRE_SCALLER==TIMER1_PRE_256 

	CLR_BIT(TCCR1B,PIN0);// CS10//
	CLR_BIT(TCCR1B,PIN1);// CS11//
	SET_BIT(TCCR1B,PIN2);// CS12//
	#elif TIMER1_PRE_SCALLER==TIMER1_PRE_1024 

	SET_BIT(TCCR1B,PIN0);// CS10//
	CLR_BIT(TCCR1B,PIN1);// CS11//
	SET_BIT(TCCR1B,PIN2);// CS12//

	#endif	
		
		

	#if TIMER1_MODE==OVER_FLOW
	CLR_BIT(TCCR1A,PIN1);//WGM11//
	CLR_BIT(TCCR1A,PIN0);//WGM10//
	CLR_BIT(TCCR1B,PIN3);//WGM12//
	CLR_BIT(TCCR1B,PIN4);//WGM13//
	SET_BIT(TIMSK,PIN2);// ENABLE THE OVER FLOW INTERRUPT//

	SET_BIT(TCCR1B,PIN6);//ICP 1 =1 rising  zero=falling//
	SET_BIT(TIMSK,PIN5);// ENABLE THE ICU INTERRUPT//

	#if SELECT_CHANNEL==CHANNEL_A

	CLR_BIT(TCCR1A,PIN7);
	CLR_BIT(TCCR1A,PIN6);

	#elif SELECT_CHANNEL==CHANNEL_B

	CLR_BIT(TCCR1A,PIN5);
	CLR_BIT(TCCR1A,PIN4);

	#endif
	//fast pwm ***************//
	#elif TIMER1_MODE==ICU  
	SET_BIT(TCCR1A,PIN1);//WGM11//
	CLR_BIT(TCCR1A,PIN0);//WGM10//
	SET_BIT(TCCR1B,PIN3);//WGM12//
	SET_BIT(TCCR1B,PIN4);//WGM13//
	/*SET_BIT(TCCR1B,PIN6);//ices1 =1 rising  zero=falling//
	SET_BIT(TIMSK,PIN5);// ENABLE THE ICU INTERRUPT//*/
	ICR1=625;
	#if SELECT_CHANNEL==CHANNEL_A
	SET_BIT(TCCR1A,PIN7);
	CLR_BIT(TCCR1A,PIN6);
	#elif SELECT_CHANNEL==CHANNEL_B // non inverting mode//
	SET_BIT(TCCR1A,PIN5);
	CLR_BIT(TCCR1A,PIN4);

	#endif

	//CTC ***************//
	#elif TIMER1_MODE==CTC// OCR1A//
	CLR_BIT(TCCR1A,PIN1);//WGM11//
	CLR_BIT(TCCR1A,PIN0);//WGM10//
	SET_BIT(TCCR1B,PIN3);//WGM12//
	CLR_BIT(TCCR1B,PIN4);//WGM13//
	SET_BIT(TIMSK,PIN3);// ENABLE THE CTC INTERRUPT B//
	SET_BIT(TIMSK,PIN4);// ENABLE THE CTC FLOW INTERRUPTA//
	#if SELECT_CHANNEL==CHANNEL_A
	CLR_BIT(TCCR1A,PIN7);  //ctc non inverting mode //
	CLR_BIT(TCCR1A,PIN6);
	#elif SELECT_CHANNEL==CHANNEL_B
	CLR_BIT(TCCR1A,PIN5);//ctc non inverting mode //
	CLR_BIT(TCCR1A,PIN4);
	#endif

	#elif TIMER1_MODE==FAST_PWM_8  
	CLR_BIT(TCCR1A,PIN1);//WGM11//
	SET_BIT(TCCR1A,PIN0);//WGM10//
	SET_BIT(TCCR1B,PIN3);//WGM12//
	CLR_BIT(TCCR1B,PIN4);//WGM13//
	#if SELECT_CHANNEL==CHANNEL_A
	SET_BIT(TCCR1A,PIN7);
	CLR_BIT(TCCR1A,PIN6);
	#elif SELECT_CHANNEL==CHANNEL_B // non inverting mode//
	SET_BIT(TCCR1A,PIN5);
	CLR_BIT(TCCR1A,PIN4);

	#endif





	#endif	
		
		
	   


	}

	void TIMER1_VidSenceControlIcp(u8 LOC_u8EdgeType){


	switch(LOC_u8EdgeType){

	case 0:       CLR_BIT(TCCR1B,PIN6);        break;

	case 1:       SET_BIT(TCCR1B,PIN6);      break;

	   }
	}



void TIMER1_VidSetDutyCycle(u16 LOC_u16OcrValue){

		OCR1B=LOC_u16OcrValue;

	}
	//timer1 event capture//
	void __vector_6(void){

		if(GlobalPointerIcpTimer1!=NULL){

			GlobalPointerIcpTimer1(ICR1);
					}
	}

	//timer1 overflow//	
	void __vector_9(void){
		
		if(GlobalPointerTimer1!=NULL){

					GlobalPointerTimer1();
				}
		
	}

	/*channel B  pinD4
	 * channel A  pinD5
	 *
	 * */



