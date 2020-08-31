/*
 * main.c
 *
 *  Created on: Aug 3, 2020
 *      Author: Ramadona
 */


#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD_interface.h"
#include"functions.h"
extern u8 USER_NAME_ARRAY[5];
extern u8 PASSWORD_array[5];
extern u8 index_pass;
extern u8 index_name;
extern u8 flag;


void main(void){


	Intializtion();
	START();

	while(1){

	}

}

void START(void){

	u8 i=0;
// start function//
    LCD_VidWriteCommand(CLR);
	LCD_VidWriteString("ENTER USER NAME : ");
	LCD_VidSetDdram(2,1);
	index_pass=0;//user name array index//
	index_name=0;//password array index//
	flag=0;//flag to check the position in ISR //
	for(i=0;i<6;i++){

		USER_NAME_ARRAY[i]=0;
	    PASSWORD_array[i]=0;
	}
}

