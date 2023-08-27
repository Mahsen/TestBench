#ifndef __EEPROM_HPP
#define __EEPROM_HPP
//----------------------------------------------------------
#include "defines.h"
#include "stm32l1xx_flash.h"
#include "addresseeprom.cpp"
//----------------------------------------------------------
void __init_EEPROM(void);
//----------------------------------------------------------		
bool EEPROM_WriteData(volatile U32 Address, U8* Data, U16 Length);
bool EEPROM_ReadData(U32 Address, U8* Data, U16 Length);
//----------------------------------------------------------
#endif
