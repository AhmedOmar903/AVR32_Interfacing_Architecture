/*
 * main.c
 *
 *  Created on: Apr 30, 2021
 *      Author: Ramadona
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"
#include "OSILLOSCOPE_interface.h"
#include "LCD_interface.h"
#include "avr/delay.h"


void OSILLISCOPE_VoidInitialization(void);
u8 OSILLISCOPE_VoidWriteTheSignalSpecsOnTheLCD(void);

void OSILLISCOPE_VoidDrawSquareWave(u8 Copy_DutyCycle);

void main(void)
{

	u8 DutyCycle=0;

	OSILLISCOPE_VoidInitialization();



	while(1)
	{



		DutyCycle=OSILLISCOPE_VoidWriteTheSignalSpecsOnTheLCD();
		LCD_VidWriteCommand(CLR);
		OSILLISCOPE_VoidDrawSquareWave(DutyCycle);
		_delay_ms(3000);


	}



}


void OSILLISCOPE_VoidDrawSquareWave(u8 Copy_DutyCycle)
{
	u8 FirstOnTimeEnds,FirstOffTimeEnds,Repeated=0,Flag=1;

	if(			Copy_DutyCycle			>=0 			&& 		Copy_DutyCycle   <=25			)
	{
		FirstOnTimeEnds=1;
		FirstOffTimeEnds=7;
	}
	else if(			Copy_DutyCycle			>25 			&& 		Copy_DutyCycle   <=50			)
	{
		FirstOnTimeEnds=3;
		FirstOffTimeEnds=7;
	}
	else if(			Copy_DutyCycle			>50 			&& 		Copy_DutyCycle   <=75			)
	{
		FirstOnTimeEnds=5;
		FirstOffTimeEnds=7;
	}
	else
	{
		Flag=0;
		for(	u8 i=1;					i<=	16;			i++				)			// TON Loc=0
		{
			LCD_VidSetDdram(1,i);
			LCD_VidWriteData(0);
		}
	}

	if(					Flag						)
	{

		for(u8 j=0;			j<2;				j++)
		{

			for(	u8 i=1;					i<=	FirstOnTimeEnds;			i++				)			// TON Loc=0
			{
				LCD_VidSetDdram(1,i+Repeated);
				LCD_VidWriteData(0);
			}
			LCD_VidSetDdram(1,FirstOnTimeEnds+Repeated+1);
			LCD_VidWriteData(1);			// TON Ends  With Drawing on X and Y  Loc=1
			LCD_VidSetDdram(2,FirstOnTimeEnds+Repeated+1);
			LCD_VidWriteData(2);
	/*********************************************************************************************************************/
			for(	u8 i=FirstOnTimeEnds+2;					i<=	FirstOffTimeEnds;			i++				)			// TON Loc=0
			{
				LCD_VidSetDdram(2,i+Repeated);
				LCD_VidWriteData(3);
			}
			LCD_VidSetDdram(2,8+Repeated);
			LCD_VidWriteData(4);
			LCD_VidSetDdram(1,8+Repeated);
			LCD_VidWriteData(5);
			Repeated=8;
		}
	}

}


u8 OSILLISCOPE_VoidWriteTheSignalSpecsOnTheLCD(void)
{
	u32 Frequancy=0,DutyCycle=0;
	u16 Period=0;

	LCD_VidWriteCommand(CLR);
	Period=ADC_VidGetReadingPooling(ADC0);
	TIMER0_VidSetDutyCycle(Period*0.25);
	OSCILLISCOPE_VoidGetTheReadingsOfTheSignalSyncrounase(&Frequancy,&DutyCycle);
	LCD_VidWriteString("F=");
	LCD_VidWriteNumber(Frequancy);
	LCD_VidWriteString(" D=");
	LCD_VidWriteNumber(DutyCycle);
	_delay_ms(3000);
	return DutyCycle;
}


void OSILLISCOPE_VoidInitialization(void)
{
	u8 ARRAY[][8]=
	{
		{0, 0, 31, 0, 0, 0, 0, 0}, 			// First Row X AXIS LOC=0
		{0, 0, 31, 1, 1, 1, 1, 1}, 		   //  First Row X AXIS LOC=1 With Drawing on X and Y
		{1, 1, 1, 1, 1, 1, 0, 0},		  //   Secand ROW Y AXIS LOC=2 Drawing On Y

		{0, 0, 0, 0, 0, 31, 0, 0}, 	   //  Secand ROW X AXIS LOC=3
		{1, 1, 1, 1, 1, 31, 0, 0},   // Secand ROW Y AXIS LOC=4  With Drawing on X And Y
		{0, 0, 1, 1, 1, 1, 1, 1}	// FIRST ROW Y AXIS LOC=5   Drawing On y
	};


	GIE_VidEnable();
	TIMER_VidInit();
	OSCILLISCOPE_VoidInitialization();
	DIO_VidSetPinDirection(PORTB,PIN3,OUTPUT); // FAST_PWM_Timer0
	DIO_VidSetPinDirection(PORTA,PIN0,INPUT); // ADC
	ADC_VidInit();
	LCD_VidInit();

	LCD_VidWriteCommand(64);//Set DDRAM

	for(u8 i=0;			i<6;		i++)
	{
		for(u8 j=0;			j<8;		j++)
		{
			LCD_VidWriteData(ARRAY[i][j]);
		}
	}
}











