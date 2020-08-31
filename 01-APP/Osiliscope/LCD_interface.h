#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_

//SET CGRAM LOCATION _ ZERO 0b01000000  ||64 //
//the LCD COMMANDS//
#define CLR              0b00000001
#define FUNCTION_SET     0b00111000
#define DISPLAY_ON       0b00001100
#define RETURN_HOME      0b00000010
#define SHIFT_LEFT       0b00011000
#define SHIFT_RIGHT      0b00011100
#define CRUSER_ON        0b00001111
#define CRUSER_LEFT      0b00010000
#define CRUSER_RIGHT     0b00010100
// LCD FUNCTIONS//
void LCD_VidInit(u8 loc_u8DataPort,u8 loc_u8ControlPort);
void LCD_VidWriteCommand(u8 loc_u8DataPort,u8 loc_u8ControlPort,u8 loc_u8command);
void LCD_VidWriteData(u8 loc_u8DataPort,u8 loc_u8ControlPort,u8 loc_u8data);
void LCD_VidWriteString(u8 loc_u8DataPort,u8 loc_u8ControlPort,u8* loc_CharString);
void LCD_VidWriteNumber(u8 loc_u8DataPort,u8 loc_u8ControlPort,s32 loc_s32number);
void LCD_VidSetDdram(u8 loc_u8DataPort,u8 loc_u8ControlPort,u8 loc_u8row,u8 loc_u8col);
//              //
#endif
