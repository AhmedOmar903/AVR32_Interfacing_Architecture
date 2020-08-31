#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "TIMER1_interface.h"
#include "LCD_interface.h"
#include "GIE_interface.h"
#include "TIMER_register.h"
#include "ADC_interface.h"
#include "main.h"
#include "avr/delay.h"
#include <math.h>

/*

location 2 conncetion between line of the start and location 3   -------
                                                   ------
location 3 is the end of first wave drawn at bit 9 |
                                                   |----										   
location 4 THE LINE THAT CONNECT BETWEEN THE END OF FIRST WAVE AND THE START OF THE SECAND   * IN LINE 1
                                                                                             *
                                                                                             *                                  
location 5 to draw on the bits before first wave start and secand wave start  ---- in line 1
location 6 to draw X axis line 2
*/

void main(void){
    u16 Freq=0;
	u8 Veff=0;
    f32 Ton,Ttotal,Dudty=0,ANALOG=0,Duty_square;
       ADC_VidInit(); 
       LCD_VidInit(PORTC,PORTD);
    	GIE_VidEnable();
	DIO_VidSetPinDirection(PORTD,PIN6,INPUT);//TIMER1 ICP//
	DIO_VidSetPinDirection(PORTB,PIN3,OUTPUT);// FOR TIMER0 A PWM//
	TIMER1_SetCallBackIcp(TIMER1_VidIsrIcp); //ICP inerrupt//
	TIMER1_SetCallBack(TIMER1_VidIsrOverFlow);// over flow interrupt//
	TIMER1_VidInit();//init timer1//
	TIMER_VidInit();//init timer0//
	while(1){
       if(flag==3){
    	    Ton=(snap2-snap1);
		    Ttotal=snap3-snap1;
			Dudty= (Ton/Ttotal)*100;
		    Freq=1/(Ttotal*0.0000005);
		    Duty_square=sqrt((Ton/Ttotal));
		    Veff=5*(Duty_square);
			LCD_VidDisplayNumber(Ton,Ttotal,Dudty,Freq,Veff);
		   _delay_ms(3000);
			LCD_VidDisplay(Dudty,Veff);
			 _delay_ms(1000);

		    ANALOG=ADC_VidGetReadingPooling(ADC0);
		    ANALOG*=0.25;
		    TIMER0_VidSetDutyCycle(ANALOG);
    	             flag=0;
	       }
      }
}
void TIMER1_VidIsrIcp(void){
	if(flag==0){
		snap1=ICR1;
		over_flow=0;
		TIMER1_VidSenceControlIcp(FALLING);
		flag=1;
	}
	else if(flag==1){
        snap2=ICR1+(over_flow*65536);
        TIMER1_VidSenceControlIcp(RISING);
        flag=2;
	}
	else if(flag==2){
        snap3=ICR1+(over_flow*65536);
        over_flow=0;
        flag=3;
	}
}
void TIMER1_VidIsrOverFlow(void)
{
	over_flow++;
}



void LCD_VidDisplayNumber(f32 LOC_f32Ton,f32 LOC_f32Ttotal,f32 LOC_f32Duty,u16 LOC_u16freq,u8 LOC_u8Veff){
	u8 i=0;
	u8 value_array[]={LOC_u16freq,LOC_f32Duty,LOC_f32Ton,LOC_f32Ttotal,LOC_u8Veff};
	u8 character_array[][6]={"F=","D=","On=","HZ T=","V="};
	u8 index[][2]={
		{2,1},
		{2,7},
		{1,8},
		{2,14}
		};
	 LCD_VidWriteCommand(PORTC,PORTD,CLR);
	for(i=0;i<5;i++){
		LCD_VidWriteString(PORTC,PORTD,character_array[i]);
	    LCD_VidWriteNumber(PORTC,PORTD,value_array[i]);
		LCD_VidSetDdram(PORTC,PORTD,index[i][0],index[i][1]);
	}
	
}


void LCD_VidCheckVolt(u8 LOC_u8Ton,u8 LOC_u8Toff,u8 LOC_u8Vertical,u8 LOC_u8Veff){

u8 volt_array[]={1,2,3,4};

/*



1                                   volt4
2                          volt3    *********     
3                 volt2     *******          
       volt 1    *******              
4       ******
this function is used to rearrange the places of the TON_width,vertical,Toff
according to the the quantity of the Veff 

*/

u8 i=0,row=0;
u8 index[][9]={
   //0 1 2  3  4  5  6  7  8//
	{4,5,4,11,19,27,44,27,36},	
	{3,4,5,12,20,28,43,28,35},
	{2,3,6,13,21,29,42,29,34},	
	{1,2,7,14,22,30,41,30,33}	
	};
for(row=0;row<4;row++){
	if(LOC_u8Veff==volt_array[row]){
			 animation[index[row][0]]=LOC_u8Ton;
			 i=index[row][1];
			 while(i<8){
			 animation[i]=LOC_u8Vertical;
			 animation[i+index[row][2]]=LOC_u8Vertical; //index 9,10,11//
			 i++;
			 }
			 animation[index[row][3]]=LOC_u8Toff;
			 animation[index[row][4]]=0b00011111;
			 animation[index[row][5]]=0b00011111;
			 animation[index[row][6]]=0b00011111;
			 for(i=25;i<index[row][7];i++){
			 animation[i]=0b00010000;
			 }
			 for(i=index[row][8];i<40;i++){
			 animation[i]=0b00010000;    //36,37,38,39//
			 }
			 break;
	     } 
}

LCD_VidWriteCommand(PORTC,PORTD,64);
 for(i=0;i<56;i++){
    LCD_VidWriteData(PORTC,PORTD,animation[i]);
    }

 }

void LCD_VidCheckDuty(u8 LOC_u8Duty,u8*LOC_u8Pointer1stStart,u8*LOC_u8Pointer2ndStart,u8*LOC_u8PointerRowSize){
	
/*
	
this function is used to select the LCD bit number or the place which the square wave 
is going to start according to the Duty Cycle
*/
	
	
	u8 start[]={16,8,15,7,14,6,13,5,12,4,11,3,10,2,9,1};	
	u8 i=0,x=5,y=10;
	while(i<16){
		
		if(LOC_u8Duty<=x ||LOC_u8Duty<=y){
			*LOC_u8Pointer1stStart=start[i];
	        *LOC_u8Pointer2ndStart=start[i+1];
            *LOC_u8PointerRowSize=start[i];
			break;
		}
		x+=10;
		y+=10;
		i+=2;
	}
}


void LCD_vidDraw(u8 first_wave_start,u8 Secand_wave_start,u8 ROW_size){
	

	u8 i=0,j;

  for(i=0;i<16;i++){
		LCD_VidSetDdram(PORTC,PORTD,2,i+1);
		LCD_VidWriteData(PORTC,PORTD,6);    //X Axis// 
		}
		
 for(i=16;i>ROW_size;i--){
	LCD_VidSetDdram(PORTC,PORTD,1,i);
	LCD_VidWriteData(PORTC,PORTD,5);
	LCD_VidSetDdram(PORTC,PORTD,1,i-8);
	LCD_VidWriteData(PORTC,PORTD,5);
   }

u8 ARRAY_WAVE[]={first_wave_start,Secand_wave_start,first_wave_end,secand_wave_end};
i=10;
for(j=0;j<2;j++){
	LCD_VidSetDdram(PORTC,PORTD,1,ARRAY_WAVE[j]);
	LCD_VidWriteData(PORTC,PORTD,0);   //ton         the size of ton from right         ---//
	LCD_VidSetDdram(PORTC,PORTD,2,ARRAY_WAVE[j]);
	LCD_VidWriteData(PORTC,PORTD,1);//        ---  toff  wave row 2 goes to  left               //
	LCD_VidSetDdram(PORTC,PORTD,1,ARRAY_WAVE[j+2]);
	LCD_VidWriteData(PORTC,PORTD,4);// row 1  col 1  *//
	LCD_VidSetDdram(PORTC,PORTD,2,ARRAY_WAVE[j+2]);
	LCD_VidWriteData(PORTC,PORTD,3);// row2 col 2  *----  //
	   for(;i<ARRAY_WAVE[j];i++){
	      LCD_VidSetDdram(PORTC,PORTD,2,i);
	      LCD_VidWriteData(PORTC,PORTD,2);
        }
	   i=2;
 }
		
}

void LCD_VidDisplay(u8 LOC_u8DutyCycle,u8 LOC_u8Veff){

u8 x=0,y=0,z=0;
LCD_VidWriteCommand(PORTC,PORTD,CLR);
   
if( (LOC_u8DutyCycle>0 && LOC_u8DutyCycle<=5)||(LOC_u8DutyCycle>10 && LOC_u8DutyCycle<=15)||(LOC_u8DutyCycle>20 && LOC_u8DutyCycle<=25)||(LOC_u8DutyCycle>30 && LOC_u8DutyCycle<=35)||(LOC_u8DutyCycle>40 && LOC_u8DutyCycle<=45)||(LOC_u8DutyCycle>50 && LOC_u8DutyCycle<=55)||(LOC_u8DutyCycle>60 && LOC_u8DutyCycle<=65)||(LOC_u8DutyCycle>70 && LOC_u8DutyCycle<=75)||(LOC_u8DutyCycle>80 && LOC_u8DutyCycle<=85)||(LOC_u8DutyCycle>90 && LOC_u8DutyCycle<=95) ){

	   	  Ton_WIDTH=0b00000111;//row 3ard--//
      Vertical_line=0b00000100;//col tool  *//
            Ton_END=0b00011100;//--toff row 3ard//
     }
else {
	      Ton_WIDTH=0b00011111;
      Vertical_line=0b00010000;
            Ton_END=0b00010000;
}


LCD_VidAnimationDelete();
LCD_VidCheckVolt(Ton_WIDTH,Ton_END,Vertical_line,LOC_u8Veff); 

LCD_VidCheckDuty(LOC_u8DutyCycle,&first_wave_start,&Secand_wave_start,&ROW_size); 
 
LCD_vidDraw(first_wave_start,Secand_wave_start,ROW_size);

 
}

void LCD_VidAnimationDelete(void){
	u8 i=0;
	
	for(i=0;i<48;i++){
		
		animation[i]=0x00;
	}
	animation[8] =0b00011111;
	animation[16]=0b00011111;
	animation[24]=0b00011111;

}
