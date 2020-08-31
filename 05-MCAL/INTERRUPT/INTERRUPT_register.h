

	#ifndef _INTERRUPT_REGISTER_H_
	#define _INTERRUPT_REGISTER_H_


	#define GICR    *((volatile u8*)0x5B)//to active the PIE  EXTI0=6,EXTI1=7,EXTI2=5//
	#define GIFR    *((volatile u8*)0x5A)//for put flag =0 by typing 1 on it when the PIE IS disabled//
	#define MCUCR   *((volatile u8*)0x55)// to active the sence control exti0 ,exti1//
	#define MCUCSR  *((volatile u8*)0x54)// to active the sence control exti2//

	void __vector_1( void )__attribute__((signal));
	void __vector_2( void )__attribute__((signal));
	void __vector_3( void )__attribute__((signal));
	#endif


