#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "avr/delay.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
/*u8 loc_u8DataPort=the port that connected from D0 to D7
u8   loc_u8ControlPort=the port that connected to RS&RW&EN
*/
void LCD_VidInit(u8 loc_u8DataPort,u8 loc_u8ControlPort){
	_delay_ms(50);
	DIO_VidSetPortDirection(loc_u8DataPort,255);
	DIO_VidSetPortDirection(loc_u8ControlPort,0b00000111);
	
	 LCD_VidWriteCommand(loc_u8DataPort,loc_u8ControlPort,FUNCTION_SET);    //function set  //
     _delay_ms(1);
	 LCD_VidWriteCommand(loc_u8DataPort,loc_u8ControlPort,DISPLAY_ON);    //display on    //
	 _delay_ms(1);
	 LCD_VidWriteCommand(loc_u8DataPort,loc_u8ControlPort,CLR );        //clear display //
	 _delay_ms(2);
	 
}
/*

loc_u8DataPort=the port that connected from D0 to D7
loc_u8ControlPort=the port that connected to RS&RW&EN
*/
void LCD_VidWriteCommand(u8 loc_u8DataPort,u8 loc_u8ControlPort,u8 loc_u8command){
	
	DIO_VidSetPinValue(loc_u8ControlPort,PIN0,LOW); //make the RS in command mode//
    DIO_VidSetPinValue(loc_u8ControlPort,PIN1,LOW);//make the RW in write mode//
    DIO_VidSetPortValue(loc_u8DataPort,loc_u8command);//take the data from D0 to D7//
	
	
    DIO_VidSetPinValue(loc_u8ControlPort,PIN2,HIGH); // EN raising edge//
	_delay_ms(1);
    DIO_VidSetPinValue(loc_u8ControlPort,PIN2,LOW);// EN falling edge//
    _delay_ms(1);	
}
void LCD_VidWriteData(u8 loc_u8DataPort,u8 loc_u8ControlPort,u8 loc_u8data){
	
	DIO_VidSetPinValue(loc_u8ControlPort,PIN0,HIGH); //make the RS in data mode//
    DIO_VidSetPinValue(loc_u8ControlPort,PIN1,LOW);//make the RW in write mode//
    DIO_VidSetPortValue(loc_u8DataPort,loc_u8data);//take the data from D0 to D7//
	
    DIO_VidSetPinValue(loc_u8ControlPort,PIN2,HIGH); // EN raising edge//
	_delay_ms(1);     
    DIO_VidSetPinValue(loc_u8ControlPort,PIN2,LOW);// EN falling edge//
    _delay_ms(1);	
}
void LCD_VidWriteString(u8 loc_u8DataPort,u8 loc_u8ControlPort,u8* loc_CharString){
	u8 i=0;
	for(i=0; loc_CharString[i]!=NULL;i++){
	LCD_VidWriteData(loc_u8DataPort,loc_u8ControlPort,loc_CharString[i]);
    }
}
void LCD_VidWriteNumber(u8 loc_u8DataPort,u8 loc_u8ControlPort,s32 loc_s32number){


 s32 x=loc_s32number;
 s32 y=0;
 s32 reversed=1;
 u8 negtive_flag=0;
     if(loc_s32number<0){
    	         x=(loc_s32number*-1);
    	         negtive_flag=1;
         }

     else if(x==0){
		         LCD_VidWriteData(loc_u8DataPort,loc_u8ControlPort,48);
			}
	 while(x>0){
		         reversed=(reversed*10)+(x%10);
				   x=x/10;
			   }
     if(loc_s32number<0){
			     x=(loc_s32number*-1);
     }
     else{
        	    x=loc_s32number;
         }
     while(x>0){
				y=reversed%10;
				if(negtive_flag==1){
				 LCD_VidWriteData(loc_u8DataPort,loc_u8ControlPort,'-');
				  negtive_flag=0;
								}
				LCD_VidWriteData(loc_u8DataPort,loc_u8ControlPort,y+48);
				reversed=reversed/10;
				x=x/10;
     }
}


void LCD_VidSetDdram(u8 loc_u8DataPort,u8 loc_u8ControlPort,u8 loc_u8row,u8 loc_u8col){
	if(1==loc_u8row){
		LCD_VidWriteCommand(loc_u8DataPort,loc_u8ControlPort,(127+loc_u8col));
	}
	else if(2==loc_u8row){

		LCD_VidWriteCommand(loc_u8DataPort,loc_u8ControlPort,(127+64+loc_u8col));
	}
}




