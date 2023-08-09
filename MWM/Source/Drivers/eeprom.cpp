//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1395/10/19
Programmer : Mohammad Lotfi
Site : http://www.mahsen.ir
Tel : +989124662703
*/
//************************************************************* Warning *****************************************************************//
/*
none
*/
//************************************************************* Wizard ******************************************************************//
#include "Wizards.cpp"
//************************************************************ defineds ******************************************************************//
/*
none
*/
//************************************************************ includes ******************************************************************//
#include "eeprom.hpp"
#include "taskmanager.hpp"
//************************************************************ variables *****************************************************************//
/*
none
*/
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
/**
 * @brief 		پيکره بندي اوليه اين ماژول
*/
void __init_EEPROM(void)
{

}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
bool EEPROM_WriteData(volatile U32 Address, U8* Data, U16 Length)
{

	__disable_irq();

	FLASH_Status status = FLASH_COMPLETE;
	Address += 0x08080000;

	for(U16 Index=RESET; Index<Length; Index++)
	{
		DATA_EEPROM_Unlock();  //Unprotect the EEPROM to allow writing
		if((Length - Index) < 4)
		{
			status = DATA_EEPROM_ProgramByte(Address, Data[Index]);
		}
		else
		{
			U32 Word = (Data[Index+3] << 24) | (Data[Index+2] << 16) | (Data[Index+1] << 8) | (Data[Index+0] << 0);
			
			status = DATA_EEPROM_ProgramWord(Address, Word);
			
			Address += 4;
			Index += 3;
		}
		DATA_EEPROM_Lock();  // Reprotect the EEPROM

		if((status != FLASH_COMPLETE))
		{
			__enable_irq();
			return false;
		}
	}

	__enable_irq();
	return true;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
bool EEPROM_ReadData(U32 Address, U8* Data, U16 Length)
{

	__disable_irq();
		
	Address += 0x08080000;
	
	for(U16 Index=RESET; Index<Length; Index++)
	{
		Data[Index] = *(__IO uint32_t*)(Address + Index);
	}
	
	__enable_irq();
	return true;
}
//*************************************************************** tasks *******************************************************************//
/*
none
*/
//************************************************************** vectors ******************************************************************//
/*
none
*/
//****************************************************************************************************************************************//









