

	#include "STD_TYPES.h"
	#include "BIT_MATH.h"
	#include "INTERRUPT_interface.h"
	#include "INTERRUPT_register.h"

	static void(*GLOBAL_Pointer)(void)=NULL;
	void INTERRIPT_SetCallBack(void (*LOCAL_Pointer)(void)){
		if(LOCAL_Pointer!=NULL){
			GLOBAL_Pointer=LOCAL_Pointer;
			}
	}

	void INTERRUPT_VidIntial(u8 loc_u8ExitNum){
		//HERE WE SELECT THE MODE //
	switch(loc_u8ExitNum){
		case 0:
			  // set portD pin2 input High//
			#if SENCE_MODE == FALLING 
					  CLR_BIT(MCUCR,PIN0);
					  SET_BIT(MCUCR,PIN1);
			#elif SENCE_MODE == RISING
						  SET_BIT(MCUCR,PIN0);
						  SET_BIT(MCUCR,PIN1);
			#elif SENCE_MODE == IOC
						  SET_BIT(MCUCR,PIN0);
						  CLR_BIT(MCUCR,PIN1);

			#elif SENCE_MODE == LOW_level
						  CLR_BIT(MCUCR,PIN0);
						  CLR_BIT(MCUCR,PIN1);			  
			#else
			#error "  WRONG CHOICE "
			#endif	
			  break;
		case 1: 

				// set portD pin3 input High//
				#if SENCE_MODE == FALLING 
						  CLR_BIT(MCUCR,PIN2);
						  SET_BIT(MCUCR,PIN3);
				#elif SENCE_MODE == RISING
							  SET_BIT(MCUCR,PIN2);
							  SET_BIT(MCUCR,PIN3);
				#elif SENCE_MODE == IOC
							  SET_BIT(MCUCR,PIN2);
							  CLR_BIT(MCUCR,PIN3);

				#elif SENCE_MODE == LOW_level
							  CLR_BIT(MCUCR,PIN2);
							  CLR_BIT(MCUCR,PIN3);			  
				#else
				#error "  WRONG CHOICE "
				#endif	
				  break;
		case 2: 

				// set portB pin2 input High//
				CLR_BIT(GICR,PIN5); // cleand enable//
				SET_BIT(GIFR,PIN5);// cleaned the falg//
				#if SENCE_MODE == FALLING 
						  CLR_BIT(MCUCSR,PIN6);
				#elif SENCE_MODE == RISING
					   SET_BIT(MCUCSR,PIN6);
				#else
				#error "  WRONG CHOICE "
				#endif	
				  break;			
		
		 }

	}
	void INTERRUPT_VidEnable(u8 loc_u8ExitNum){
	  //HERE WE make the enable  //
	  switch(loc_u8ExitNum){
		 
			   case 0: SET_BIT(GICR,PIN6);  break;// EXTI0//
			   case 1: SET_BIT(GICR,PIN7);  break;// EXTI1//
			   case 2: SET_BIT(GICR,PIN5);  break;// EXTI2//
	  }
	}
	void INTERRUPT_VidDisable(u8 loc_u8ExitNum){
		
		switch(loc_u8ExitNum){
		 
			   case 0: CLR_BIT(GICR,PIN6);  break;// EXTI0//
			   case 1: CLR_BIT(GICR,PIN7);  break;// EXTI1//
			   case 2: CLR_BIT(GICR,PIN5);  break;// EXTI2//
	   }
		
	}


	void __vector_1(void){

		if(GLOBAL_Pointer!=NULL){
				GLOBAL_Pointer();
				}


	}
	void __vector_2(void){

		if(GLOBAL_Pointer!=NULL){
				GLOBAL_Pointer();
				}


	}
	void __vector_3(void){
		
		
		if(GLOBAL_Pointer!=NULL){
				GLOBAL_Pointer();
				}


	}








