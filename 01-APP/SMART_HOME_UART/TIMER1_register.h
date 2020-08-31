
	#ifndef _TIMER1_REGISTER_H_
	#define _TIMER1_REGISTER_H_

	#define TCCR1A      *((volatile u8*)0x4F)
	#define TCCR1B      *((volatile u8*)0x4E)
	#define TIMSK       *((volatile u8*)0x59)
	// CTC//
	#define OCR1AH      *((volatile u8*)0x4B)//channel A//
	#define OCR1AL      *((volatile u8*)0x4A)
	#define OCR1A       *((volatile u16*)0x4A)//read the channel 1A//
	#define OCR1BH      *((volatile u8*)0x49)//channel B//
	#define OCR1BL      *((volatile u8*)0x48)
	#define OCR1B       *((volatile u16*)0x48)//read the channel 1B//
	// fast pmw//
	#define ICR1H       *((volatile u8*)0x47)
	#define ICR1L       *((volatile u8*)0x46)
	#define ICR1        *((volatile u16*)0x46)//REGISTAR READ THE DATA FROM HIGH AND LOW//
	#define TCNT1H      *((volatile u8*)0x4D)
	#define TCNT1L      *((volatile u8*)0x4C)
	#define TCNT1       *((volatile u16*)0x4C) //REGISTAR READ THE DATA FROM HIGH AND LOW//



	void __vector_6(void)__attribute__((signal));//timer1 event capture//

	void __vector_9(void)__attribute__((signal));//timer1 overflow//



	#endif



