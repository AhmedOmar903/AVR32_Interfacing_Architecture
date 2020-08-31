
	#ifndef _TIMER2_REGISTER_H_
	#define _TIMER2_REGISTER_H_

	#define TCCR2      *((volatile u8*)0x45)
	#define TCNT2      *((volatile u8*)0x44)
	#define OCR2       *((volatile u8*)0x43)
	#define ASSR       *((volatile u8*)0x42)
	#define TIMSK      *((volatile u8*)0x59)



	void __vector_4(void)__attribute__((signal)); //ctc//
	void __vector_5(void)__attribute__((signal)); //over_flow//



	#endif



