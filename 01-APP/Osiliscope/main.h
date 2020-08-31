#define Ton_WIDTH                x
#define Vertical_line            y
#define Ton_END                  z
#define first_wave_start        col1
#define Secand_wave_start       col2
#define ROW_size                 p
#define first_wave_end           9
#define secand_wave_end          1
#define ICR1               *((volatile u16*)0x46)



void LCD_VidDisplay(u8 LOC_u8DutyCycle,u8 LOC_u8Veff);
void LCD_vidDraw(u8 first_wave_start,u8 Secand_wave_start,u8 ROW_size);
void LCD_VidCheckVolt(u8 LOC_u8Ton,u8 LOC_u8Toff,u8 LOC_u8Vertical,u8 LOC_u8Veff);
void LCD_VidCheckDuty(u8 LOC_u8Duty,u8*LOC_u8Pointer1stStart,u8*LOC_u8Pointer2ndStart,u8*LOC_u8PointerRowSize); 
void LCD_VidAnimationDelete(void);
void LCD_VidDisplayNumber(f32 LOC_f32Ton,f32 LOC_f32Ttotal,f32 LOC_f32Duty,u16 LOC_u16freq,u8 LOC_u8Veff);


void TIMER1_VidIsrOverFlow(void);
void TIMER1_VidIsrIcp(void);

 volatile u8  flag=0;
 volatile u8  over_flow=0;
 volatile u16 snap1=0;
 volatile u16 snap2=0;
 volatile u16 snap3=0;
 u8 col1,col2,p;
 
 
 u32 animation[]={
		 //changable//
		 
		 //     0   1    2    3   4     5    6   7 //
			 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //loc 0//
			 //     8     9    10  11   12   13    14  15//
			 0b00011111,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//loc1//
			 //     16  17    18   19    20  21    22   23//
			 0b00011111,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//loc2//
			 //    24     25   26   27   28   29   30   31//
			 0b00011111,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//loc3//
			//32    33  34   35    36   37   38  39//
			 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//loc4//
			//40   41    42  43    44   45   46  47//
			 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//loc5//
			            //fixed//
			 0b00011111,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000// loc 6 x axis//
 };

