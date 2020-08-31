

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GIE_register.h"
#include "GIE_interface.h"




void GIE_VidEnable(void){
		
	  SET_BIT(SREG,PIN7);
	}
void GIE_VidDisable(void){
		CLR_BIT(SREG,PIN7);
	}

