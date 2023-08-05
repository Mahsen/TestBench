/************************************************** Description *******************************************************/
/*
    File : testbench.cpp
    Programmer : Mohammad Lotfi
    Used : Nothing
    Design Pattern : Nothing
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2023/8/5
*/
/************************************************** Warnings **********************************************************/
/*
    Nothing
*/
/************************************************** Wizards ***********************************************************/
/*
    Nothing
*/
/************************************************** Includes **********************************************************/
#include "testbench.hpp"
#include "media.hpp"
#include "uart.hpp"
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
/*
    Nothing
*/
/************************************************** Variables *********************************************************/
/*
    Nothing
*/
/************************************************** Opjects ***********************************************************/
class_TestBench TestBench;
/*--------------------------------------------------------------------------------------------------------------------*/
bool class_TestBench::Add(uint8_t *Command, void (*Handle)(uint8_t *Data)) {	
	Test* _Test = new Test(Command, Handle);
	if(_Test) {
		if(Tests_Count < (sizeof(Tests)/4)) {
			Tests[Tests_Count++] = _Test;		
			return true;
		}
	}	
	return false;
}
/*--------------------------------------------------------------------------------------------------------------------*/
bool class_TestBench::Pars(uint8_t *Message, uint32_t *Length) {
	Parmeters.Message.Set(Message);
	if(Detach()) {
		if(!Execute()) {
			Parmeters.Data.Set((uint8_t*)"NoCommand");
		}
		if(Attach()) {
			strcpy((char*)Message, (char*)Parmeters.Message.Get());
			*Length = Parmeters.Message.Length();
			return true;
		}
	}
	return false;
}
/*--------------------------------------------------------------------------------------------------------------------*/
bool class_TestBench::Execute() {
	
	for(uint8_t Index=RESET; Index<Tests_Count; Index++) {
		if(strcmp((char*)Tests[Index]->_Command, (char*)Parmeters.Command.Get()) == NULL) {
			Tests[Index]->_Handle(Parmeters.Data.Get());
			return true;
		}
	}
	return false;
}
/************************************************** Functions *********************************************************/
/*
    Nothing
*/
/************************************************** Tasks *************************************************************/
/*
    Nothing
*/
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
