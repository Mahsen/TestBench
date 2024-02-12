/************************************************** Description *******************************************************/
/*
    File : ui.cpp
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
#include "ui.hpp"
#include "uart.hpp"
#include "TaskManager.hpp"
#include "testbench.hpp"
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
/*
    Nothing
*/
/************************************************** Variables *********************************************************/
static U64 UI_Task_STAK[4096/8];
void Address_UI_Task(void)
{
	UI.Task();
}
/************************************************** Opjects ***********************************************************/
class_UI UI;
/*--------------------------------------------------------------------------------------------------------------------*/
void class_UI::Init(Media* _Media) {
	MyMedia = _Media;
	if(MyMedia) {
		MyMedia->Open();
		TaskManager_Add("UI", &Address_UI_Task, 0, &UI_Task_STAK, sizeof(UI_Task_STAK));
	}
}
/************************************************** Functions *********************************************************/
/*
    Nothing
*/
/************************************************** Tasks *************************************************************/
void class_UI::Task() {
	uint8_t Message[1024];
	uint32_t Length;
	char StrID[16];
	while(true) {		
		if(MyMedia->Receive(Message, &Length)) {	
			sprintf(StrID, "FIND=ID%s\r\n", TestBench.GetID());
			if(strcmp((char*)Message, StrID) == NULL) {
				MyMedia->Send((U8*)"OK\r\n", 4);
			}
			else if(TestBench.Pars(Message, &Length)) {
				MyMedia->Send(Message, Length);
			}
			memset(Message, 0, sizeof(Message));
			MyMedia->Clear();
		}
		TaskManager_Delay(500 MSec);
	}
}
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
