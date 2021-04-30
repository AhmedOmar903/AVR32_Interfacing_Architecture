
	#ifndef _TIMER_REGISTER_H_
	#define _TIMER_REGISTER_H_

	#define OCR0      *((volatile u8*)0x5C)
	#define TIMSK     *((volatile u8*)0x59)
	#define TIFR      *((volatile u8*)0x58)
	#define TCCR0     *((volatile u8*)0x53)
	#define TCNT0     *((volatile u8*)0x52)


	void __vector_11(void)__attribute__((signal));//OVER_FLOW//
	void __vector_10(void)__attribute__((signal));//CTC//



	#endif
