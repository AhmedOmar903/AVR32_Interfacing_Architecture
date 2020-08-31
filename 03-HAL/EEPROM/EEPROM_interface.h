#ifndef _EEPROM_INTERFACE_H_
#define _EEPROM_INTERFACE_H_


void EEPROM_VidIntialization(void);
void EEPROM_VidWriteDataByte(u16 LOC_u16Adress,u8 LOC_u8Data);
u8 EEPROM_u8ReadDataByte(u16 LOC_u16Adress);


#endif
