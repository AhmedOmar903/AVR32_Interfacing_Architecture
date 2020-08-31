/*
 * intialization.c
 *
 *  Created on: Aug 3, 2020
 *      Author: Ramadona
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD_interface.h"
#include"GIE_interface.h"
#include"UART_interface.h"
#include"TIMER1_interface.h"
#include"ADC_interface.h"
#include"functions.h"
#define  ADCSRA        *((volatile u8*)0x26)


void ISR_VidAdcInterrupt(u16 value);
void ISR_VidUartInterrupt(u8 LOC_u8Data);

void Intializtion(void){
	DIO_VidSetPinDirection(PORTD,PIN0,INPUT);//rx//
	DIO_VidSetPinDirection(PORTD,PIN1,OUTPUT);// tx//
	DIO_VidSetPinDirection(PORTD,PIN4,OUTPUT);//ocr1 servo//
	DIO_VidSetPinDirection(PORTA,PIN7,OUTPUT);//buzzer//
	DIO_VidSetPinDirection(PORTA,PIN6,OUTPUT);//LED//


	LCD_VidInit();//LCD INIT//
	GIE_VidEnable();//global interrupt INIT//
	UART_VidSetCallBackReceive(ISR_VidUartInterrupt);//set call back UART INIT//
	ADC_SetCallBack(ISR_VidAdcInterrupt);//set call back ADC INIT//
	UART_VidInit();//UART INIT//
	TIMER1_VidInit();//TIMER1  INIT FOR SERVO MOTOR//
	ADC_VidInit();//ADC INIT//
	CLR_BIT(ADCSRA,PIN7); //DISABLE ADC//

}
