/*
 * main.c
 *
 *  Created on: Aug 18, 2020
 *      Author: Ahmed Ramadan
 */


#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"ADC_interface.h"
#include"LCD_interface.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "avr/delay.h"


void Init(void);
void Task1_Temp(void*PTR);
void Task2_LDR(void*Prt);



int main(void){

	Init();


  xTaskCreate(&Task1_Temp,NULL,300,NULL,2,NULL);
 xTaskCreate(&Task2_LDR,NULL,300,NULL,1,NULL);



	vTaskStartScheduler();

	return 0;
}






void Init(void){

	ADC_VidInit();
	LCD_VidInit();

	LCD_VidWriteCommand(CLR);
	LCD_VidWriteString("TEMP = ");
	LCD_VidSetDdram(1,11);
	LCD_VidWriteString("C");
	DIO_VidSetPinDirection(0,PIN3,OUTPUT);


}

void Task1_Temp(void*PTR){

u16 Analog=0;
	while(1){

		Analog=ADC_VidGetReadingPooling(ADC0);

		Analog=(Analog*5000UL)/(1024);
		Analog/=10;
		LCD_VidSetDdram(1,7);
		LCD_VidWriteNumber(Analog);


		vTaskDelay(200);

	}


}
void Task2_LDR(void*Prt){

	u16 Analog=0;
	while(1){

		//LCD_VidWriteCommand(CLR);
		//LCD_VidWriteString("LDR = ");
		Analog=ADC_VidGetReadingPooling(ADC1);
		Analog=(Analog*5000UL)/(Analog+1000);

		if(Analog>=2000){
			DIO_VidSetPinValue(0,3,LOW);
		}
		else{
			//DIO_VidTogBit(0,3);
			DIO_VidSetPinValue(0,3,HIGH);
		}

		vTaskDelay(300);

	}



}









