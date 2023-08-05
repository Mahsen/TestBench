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
#include "media.hpp"
#include "uart.hpp"
#include "TaskManager.hpp"
#include "testbench.hpp"
/************************************************** Defineds **********************************************************/
#define UI_MEDIA_UART 5
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
class : Media
{
	public:
		virtual bool Open() {		
			Update(19200);
			return true;
		}
		virtual bool Update(uint32_t Speed) {
			UART_UpdateSetting(UI_MEDIA_UART, Speed, USART_WordLength_8b, USART_Parity_No, USART_StopBits_1, true);
			return true;
		}
		virtual bool Send(uint8_t *Message, uint32_t Length) {		
			UART_Send_String(UI_MEDIA_UART, Message, Length);
			return true;
		}
		virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
			if(UART_Read_State_FIFO(UI_MEDIA_UART).rxBusy()) {
				for(U32 Index=RESET; Index<100; Index++)
				{
					*Length = UART_Read_State_FIFO(UI_MEDIA_UART).rx_Length;	
					TaskManager_Delay(100 MSec);
					if(*Length == UART_Read_State_FIFO(UI_MEDIA_UART).rx_Length)
					{
						break;
					}
				}
				if(*Length) {
					*Length = UART_Receive_String_FIFO(UI_MEDIA_UART, Message, *Length);
					return true;
				}
			}
			return false;
		}
		virtual bool Clear() {		
			UART_Reset_Buffer_FIFO(UI_MEDIA_UART);
			return true;
		}
		virtual bool Reset() {		
			return false;
		}
		virtual bool Close() {		
			return false;
		}		
} InterfaceUI;
/*--------------------------------------------------------------------------------------------------------------------*/
void class_UI::Init() {
	InterfaceUI.Open();
	TaskManager_Add("UI", &Address_UI_Task, 0, &UI_Task_STAK, sizeof(UI_Task_STAK));
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
		sprintf(StrID, "FIND=ID%s\r\n", TestBench.GetID());
		if(InterfaceUI.Receive(Message, &Length)) {			
			if(strcmp((char*)Message, StrID) == NULL) {
				InterfaceUI.Send((U8*)"OK\r\n", 4);
			}
			else if(TestBench.Pars(Message, &Length)) {
				InterfaceUI.Send(Message, Length);
			}
		}
		TaskManager_Delay(500 MSec);
	}
}
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
