

	#include "STD_TYPES.h"
	#include "BIT_MATH.h"
	#include "DIO_interface.h"
	#include "KEYPAD_interface.h"
	#include "avr/delay.h"


	void KEYPAD_VidInit(u8 loc_u8portname){
		
		DIO_VidSetPortDirection(loc_u8portname,0b00001111);
		DIO_VidSetPortValue(loc_u8portname,0xFF);
		
	}
	u8 GET_u8PressedKey(u8 loc_u8portname){
		u8 col,row;
		u8 key_out=0;
		u32 arr[][4]={
				{1,2,3,4},
				{5,6,7,8},
				{9,'+','-','='},
				{'>','<',15,16}
		};
		for(col=0;col<4;col++){
				DIO_VidSetPinValue(loc_u8portname,col,LOW);
				for(row=4;row<8;row++){
				 if(DIO_u8GetPinValue(loc_u8portname,row)==0){
					 key_out=arr[row-4][col];
					 while(0==DIO_u8GetPinValue(loc_u8portname,row)){

					 }
					 _delay_ms(30);
				 }

				}
				
				DIO_VidSetPinValue(loc_u8portname,col,HIGH);
			}
		return key_out;
	}
