
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

typedef enum{

	NOK,
	OK

}CONFIG_ERROR_STATUS;


CONFIG_ERROR_STATUS User_Pass(void);
void LCD_VidUserNameCheck(void);
void LCD_VidPasswordCheck(void);
void Intializtion(void);
void main(void);
void START(void);
void HOME_PAGE(void);
void servo(u8 angle);
void TEMP(u16 voltage);
void LDR(u16 VALUE);

#endif
