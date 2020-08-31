/*
 * ISR.c
 *
 *  Created on: Aug 3, 2020
 *      Author: Ramadona
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD_interface.h"
#include"ADC_interface.h"
#include"functions.h"

#define  ADCSRA        *((volatile u8*)0x26)

u8 flag=0;
u8 USER_NAME_ARRAY[5];
u8 PASSWORD_array[5];
u8 index_name=0,index_pass=0;
u8 axis=0,place=0;


void ISR_VidUartInterrupt(u8 LOC_u8Data){

	/* if the user press enter and the flag is equal to zero the compiler will jump into check username funtion
	   else if flag is equal to 1 jump to check PASSWORD

	*/
if(LOC_u8Data=='p'){

	switch(flag){

	case 0:LCD_VidUserNameCheck();  break;
	case 1:LCD_VidPasswordCheck();  break;
   }
}
/*if the flag is equal to zero  or one and the received data not equal to enter so the compiler will upload
 the arrays with the received data according to the flag
*/
 else if(flag==0 && LOC_u8Data!='p'){
	   LCD_VidWriteData(LOC_u8Data);
	   USER_NAME_ARRAY[index_name]=LOC_u8Data;
	   index_name++;
     }
else if(flag==1 && LOC_u8Data!='p'){
	   LCD_VidWriteData(LOC_u8Data);
	   PASSWORD_array[index_pass]=LOC_u8Data;
	   index_pass++;
   }
/*
 * if the flag is equal to 2 that mean the user enter the correct username and password,
 * that mean the compiler will be at home page function after that if the axis is equal  to zero
 * thats mean the next received data is to choose the between temp fun or LDR FUN OR DOOR FUN
 * once enter the any function the axis will be one
 * */
else if(flag==2 && LOC_u8Data!='p'){
	if(axis==0&&(LOC_u8Data=='1'||LOC_u8Data=='2'||LOC_u8Data=='3'||LOC_u8Data=='4')){
		switch(LOC_u8Data){
		         case '1':axis=1; place=1; servo('C');  break;//send close order to servo motor//
		         case '2':SET_BIT(ADCSRA,PIN7); //ENABLE ADC//
		                  ADC_VidGetReadingInterrupt(ADC0);//channel 1 for temp//
		                  LCD_VidWriteCommand(CLR);
		        	      axis=1; place=2; TEMP(15); break;
		         case '3':SET_BIT(ADCSRA,PIN7); //ENABLE ADC//
		                  ADC_VidGetReadingInterrupt(ADC1);//channel 1 for temp//
		                  LCD_VidWriteCommand(CLR);
		        	      axis=1; place=3; LDR(1); break;
		         case '4': main(); break;//back to main //

		         default:  HOME_PAGE();break;
		 }
	}
	else{

		/* place =1 (servo)    place =2 (TEMP)           place =3 (LDR)
 		 * if the variable place is equal to one that mean the next data will be the angle of the servo motor
		 * else if place =2 or 3 is used to go back from temp or LDR function to HOME_PAGE function
		 * */
		switch(place){
				case 1:  servo(LOC_u8Data); break;//angle//
				case 2:  TEMP(LOC_u8Data); break;//back//
				case 3:  LDR(LOC_u8Data); break;//back//

		}

	}

 }


}
void ISR_VidAdcInterrupt(u16 value){
/*
 * if the place is equal to 2 so calculate the temp
 * else calculate the light intenisty
 * */
u16 ANALOG=0;
if(place==2){
		ANALOG=(value*5000UL)/1024;
		ANALOG=(ANALOG/10);
		TEMP(ANALOG);
  }
else{
	ANALOG=(value*5000UL)/(value+1000);
	LDR(ANALOG);
}

}
