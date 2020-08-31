#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DOG_register.h"
void WATCH_VidEnable(void){
	//enable//
	CLR_BIT(WDTCR,4);
	SET_BIT(WDTCR,3);
	//prescaller 1s//
	SET_BIT(WDTCR,2);
	SET_BIT(WDTCR,1);
	CLR_BIT(WDTCR,0);
}
void WATCH_VidDisable(void){
	WDTCR=(1<<4)|(1<<3);
	WDTCR=0x00;
}
void WATCH_VidReresh(void){
	
	asm("WDR");
	
}