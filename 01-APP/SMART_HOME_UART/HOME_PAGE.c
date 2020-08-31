#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD_interface.h"
#include"functions.h"
#include"TIMER1_interface.h"
#include"ADC_interface.h"
#include "avr/delay.h"

#define  ADCSRA        *((volatile u8*)0x26)

extern u8 USER_NAME_ARRAY[5];
extern u8 PASSWORD_array[5];
extern u8 flag;
extern u8 index_pass;
extern u8 axis;


u8 i=0;
u8 ARRAY[]={'A','H','M','E','D'};
u8 pass[]={'1','2','3'};

CONFIG_ERROR_STATUS User_Pass(void){

/* This Function is Used To Give the FeedBack About The Username And The PasswordBy Using Enum*/
CONFIG_ERROR_STATUS state=NOK;
if(flag==0){
	 for(i=0;i<5;i++){
			if(USER_NAME_ARRAY[i]== ARRAY[i]){
				 state=OK;
			}
			else{
				state=NOK;
				break;
			}
	  }
}
else if(flag==1){
	 for(i=0;i<3;i++){
			if(PASSWORD_array[i]== pass[i]){
				 state=OK;
			}
			else{
				state=NOK;
				break;
			}
	  }
}
 return state;

}

void LCD_VidUserNameCheck(void){
	CONFIG_ERROR_STATUS state=NOK;
 state=User_Pass();
 /*
  * SO If The FeedBack Is OK Then Change The Flag To 1 Inorder To Check The Password
  * Else Jump To Start Function
  * */
 switch(state){
 case OK:
		LCD_VidWriteCommand(CLR);
		LCD_VidWriteString("ENTER PASSWORD:");
		LCD_VidSetDdram(2,1);
	    flag=1; break;

 default:
	    LCD_VidWriteCommand(CLR);
	    LCD_VidWriteString("WRONG USER NAME ");
	    _delay_ms(1000);
	    START();
	    break;
   }

}

void LCD_VidPasswordCheck(void){
static u8 counter=0;
counter++;
CONFIG_ERROR_STATUS state=0;
 state=User_Pass();
 /*
   * SO If The FeedBack Is OK Jump To Home_Page Function
   * Then Change The Flag To 2 Inorder To Be Able To choose Between The Functions
   * Else Check If The Counter Is Less Than 2 If Right Type Try again
   * Else If The Counter Is More Than 2 Type No More Tries Then Go Back To Start
   * */
 switch(state){

 case OK:
         HOME_PAGE();
         flag=2;
         counter=0;
	 break;

default:
	 if(counter>2){
		LCD_VidWriteCommand(CLR);
		LCD_VidWriteString("NO MORE TRIES");
		counter=0;
		_delay_ms(1000);
		START();
	  }
	 else{
	  LCD_VidWriteCommand(CLR);
	  LCD_VidWriteString("TRY Again");
   	  _delay_ms(1000);
	   LCD_VidWriteCommand(CLR);
	   LCD_VidWriteString("ENTER PASSWORD:");
	   LCD_VidSetDdram(2,1);
	   index_pass=0;
	 }
	break;
 }
}

void HOME_PAGE(void)
{

	LCD_VidWriteCommand(CLR);
	LCD_VidWriteString("1-DOOR");
	LCD_VidSetDdram(1,11);
	LCD_VidWriteString("2-TEMP");
	LCD_VidSetDdram(2,1);
	LCD_VidWriteString("3-LDR");
	LCD_VidSetDdram(2,10);
	LCD_VidWriteString("4-BACK");
}

void servo(u8 angle){

	/*
	 * Check If The Received Data From The ISR IS equal To "C" OR "O" (closed || Opened)
	 * else Go Back to The Home_Page
	 * */

	LCD_VidWriteCommand(CLR);
	LCD_VidSetDdram(2,10);
	LCD_VidWriteString("BACK");
	LCD_VidSetDdram(1,1);
	LCD_VidWriteString("DOOR : ");
	if(angle=='C'){
	LCD_VidWriteString("CLOSED");
	TIMER1_VidSetDutyCycle(40);
	}
	else if(angle=='O'){
		LCD_VidWriteString("OPEN");
		TIMER1_VidSetDutyCycle(75);
	}
	else{
		HOME_PAGE();
		axis=0;
	}
}

void TEMP(u16 voltage){


	LCD_VidSetDdram(2,10);
	LCD_VidWriteString("BACK");
	LCD_VidSetDdram(1,1);
	LCD_VidWriteString("TEMP : ");
	LCD_VidSetDdram(1,9);
	LCD_VidWriteNumber(voltage);
	LCD_VidWriteData('C');

	/*
	 * Check If The Received Data From The ISR IS equal To "B" That Mean Go Back to The Home_Page
	 * And Set The Axis To Zero To be Able To Choose Between Functions Again and Turn Off The Buzzer
	 * Also Disable The ADC To Disallow Any Conflict Between The Functions
	 *
	 * Else Check The Value If More Than 38 C Turn on The Buzzer Else Turn Off
	 *
	 * */


switch(voltage){
	case'B':
		CLR_BIT(ADCSRA,PIN7); //DISABLE ADC//
		axis=0;
		DIO_VidSetPinValue(PORTA,PIN7,LOW);
		HOME_PAGE();
		break;

	default:
		   if(voltage>38){
				 DIO_VidSetPinValue(PORTA,PIN7,HIGH);
			}
			else{
				 DIO_VidSetPinValue(PORTA,PIN7,LOW);
			}
		break;

	}
}


void LDR(u16 VALUE){

	LCD_VidSetDdram(2,10);
	LCD_VidWriteString("BACK");
	LCD_VidSetDdram(1,1);
	LCD_VidWriteString("LDR : ");

	/*
		 * Check If The Received Data From The ISR IS equal To "B" That Mean Go Back to The Home_Page
		 * And Set The Axis To Zero To be Able To Choose Between Functions Again and Turn Off The LED
		 * Also Disable The ADC To Disallow Any Conflict Between The Functions
		 *
		 * Else Check The Value If More Than 2000 mA Turn Off The LED Else Turn On
		 *
		 * */


  if(VALUE=='B'){
	    CLR_BIT(ADCSRA,PIN7); //DISABLE ADC//
		axis=0;
		DIO_VidSetPinValue(PORTA,PIN6,LOW);//LED//
		HOME_PAGE();
	}

else if( VALUE>2000){

	     DIO_VidSetPinValue(PORTA,PIN6,LOW);
		 LCD_VidSetDdram(1,7);
		 LCD_VidWriteString("OFF");
}
else{
     DIO_VidSetPinValue(PORTA,PIN6,HIGH);
	 LCD_VidSetDdram(1,7);
	 LCD_VidWriteString(" ON");
}


}
