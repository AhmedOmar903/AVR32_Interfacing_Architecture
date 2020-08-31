
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_register.h"
#include "7SEGMENT_interface.h"


void SEGMENT_VidCommanAnodeCathode(u8 loc_u8port_name,u8 loc_u8data){


	u8 numbers[]={zero,one,two,three,four,five,six,seven,eight,nine,off};

#if SEG_TYPE==ANODE       //COMMAN ANODE //
	switch(loc_u8port_name){
		case 0 :PORTA=numbers[loc_u8data];break;
		case 1 :PORTB=numbers[loc_u8data];break;
		case 2 :PORTC=numbers[loc_u8data];break;
		case 3 :PORTD=numbers[loc_u8data];break;
		  }

#elif SEG_TYPE==CATHODE //COMMAN CATHODE//

		switch(loc_u8port_name){
		case 0 :PORTA=~numbers[loc_u8data];break;
		case 1 :PORTB=~numbers[loc_u8data];break;
		case 2 :PORTC=~numbers[loc_u8data];break;
		case 3 :PORTD=~numbers[loc_u8data];break;
			 }

#endif

}




                         

