#include "STD_TYPES.h"
#include "I2C_interface.h"

void EEPROM_VidIntialization(void){
	
	I2C_VidInitialMaster();
}
void EEPROM_VidWriteDataByte(u16 LOC_u16Adress,u8 LOC_u8Data){
	
	I2C_ERROR_STATUS STATE=NOK;
	
	STATE=I2C_u8MasterStartCondition();//START CONDITION//
	if(STATE==OK){
		STATE=I2C_u8MasterSendAddressWrite(0x50|( ( LOC_u16Adress&0x0700 )>>8 ) );// send address  MSB //
		if(STATE==OK){
			STATE=I2C_u8MasterSendData((u8)LOC_u16Adress);// send address take LSB //
			if(STATE==OK){
				STATE=I2C_u8MasterSendData(LOC_u8Data);// send DATA//
				if(STATE==OK){
				  I2C_u8MasterStopCondition();//STOP CONDITION//
				}
			}
		}
		
	}

}
u8 EEPROM_u8ReadDataByte(u16 LOC_u16Adress){

u8 LOC_u8Data=0;	
	
I2C_ERROR_STATUS STATE=NOK;
	
	STATE=I2C_u8MasterStartCondition();//START CONDITION//
	if(STATE==OK){
		STATE=I2C_u8MasterSendAddressWrite(0x50|( ( LOC_u16Adress&0x0700 )>>8 ) );// send address  MSB //
		if(STATE==OK){
			STATE=I2C_u8MasterSendData((u8)LOC_u16Adress);// send address take LSB //
			if(STATE==OK){
				STATE=I2C_u8MasterRepeatedStart();
				if(STATE==OK){
			       STATE=I2C_u8MasterSendAddressRead(0x50|( ( LOC_u16Adress&0x0700 )>>8 ) );
				   if(STATE==OK){
					  STATE=I2C_u8MasterReciveData(&LOC_u8Data);  
					  if(STATE==OK){
						  I2C_u8MasterStopCondition();
					  }
				   }
		   }
		}	
	}	
  }
  return   LOC_u8Data;

}