
	#ifndef _SPI_REGISTER_H_
	#define _SPI_REGISTER_H_

	 #define SPCR       *((volatile u8*)0x2D)
	 #define SPSR       *((volatile u8*)0x2E)
	 #define SPDR       *((volatile u8*)0x2F)

	void __vector_12(void) __attribute__((signal));//transfer complete//



	#endif
