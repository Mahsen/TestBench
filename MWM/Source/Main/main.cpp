/************************************************** Description *******************************************************/
/*
    File : main.cpp
    Programmer : Mohammad Lotfi
    Used : tester board
    Design Pattern : Nothing
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2023/8/21
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
#include "rtc.hpp"
#include "wdt.hpp"
#include "ui.hpp"
#include "gpio.hpp"
#include "adc.hpp"
#include "pwm.hpp"
#include "TaskTimer.hpp"
#include "media.hpp"
#include "Wizards.cpp"
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
struct { // General
	struct { // Key
		struct_ValueBool A;
	} Key;
	struct { // LED
		struct_ValueBool A;
	} LED;
} General;
struct { // Test_56
	struct { // DigitalOutput
		struct_ValueBool Power_5v_En;
		struct_ValueBool Power_4v_En;
	} DigitalOutput;
	struct { // DigitalInput
		struct_ValueBool EventMic;
		struct_ValueBool EventLED;
	} DigitalInput;
	struct { // AnalogInput
		float Get_Power_to5v_Voltage(void)
		{
			return ((float)ADC_Read(TESTBENCH_TEST_ID56_ANALOG_INPUT_POWER_TO5V_VOLTAGE_CHANNEL) * 0.0008056640625);
		}
		float Get_Power_4v_Voltage(void)
		{
			return ((float)ADC_Read(TESTBENCH_TEST_ID56_ANALOG_INPUT_POWER_4V_VOLTAGE_CHANNEL) * 0.0008056640625);
		}
		float Get_RTC_Voltage(void)
		{
			return ((float)ADC_Read(TESTBENCH_TEST_ID56_ANALOG_INPUT_RTC_VOLTAGE_CHANNEL) * 0.0008056640625);
		}			
	} AnalogInput;
	class : Media // Interface
	{
		public:
			virtual bool Open() {		
				Update(19200);
				return true;
			}
			virtual bool Update(uint32_t Speed) {
				UART_UpdateSetting(TESTBENCH_TEST_ID56_MEDIA_UI_UART, Speed, USART_WordLength_8b, USART_Parity_No, USART_StopBits_1, true);
				return true;
			}
			virtual bool Send(uint8_t *Message, uint32_t Length) {		
				UART_Send_String(TESTBENCH_TEST_ID56_MEDIA_UI_UART, Message, Length);
				return true;
			}
			virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
				if(UART_Read_State_FIFO(TESTBENCH_TEST_ID56_MEDIA_UI_UART).rxBusy()) {
					for(U32 Index=RESET; Index<100; Index++)
					{
						*Length = UART_Read_State_FIFO(TESTBENCH_TEST_ID56_MEDIA_UI_UART).rx_Length;	
						TaskManager_Delay(100 MSec);
						if(*Length == UART_Read_State_FIFO(TESTBENCH_TEST_ID56_MEDIA_UI_UART).rx_Length)
						{
							break;
						}
					}
					if(*Length) {
						*Length = UART_Receive_String_FIFO(TESTBENCH_TEST_ID56_MEDIA_UI_UART, Message, *Length);
						return true;
					}
				}
				return false;
			}
			virtual bool Clear() {		
				UART_Reset_Buffer_FIFO(TESTBENCH_TEST_ID56_MEDIA_UI_UART);
				return true;
			}
			virtual bool Reset() {		
				return false;
			}
			virtual bool Close() {		
				return false;
			}		
	} Interface;
	class : Media // Meter
	{
		public:
			virtual bool Open() {		
				Update(TESTBENCH_TEST_ID56_MEDIA_METER_MEDIA_BOUDRATE);
				return true;
			}
			virtual bool Update(uint32_t Speed) {
				UART_UpdateSetting(TESTBENCH_TEST_ID56_MEDIA_METER_MEDIA_UART, Speed, USART_WordLength_8b, USART_Parity_No, USART_StopBits_1, true);
				return true;
			}
			virtual bool Send(uint8_t *Message, uint32_t Length) {		
				UART_Send_String(TESTBENCH_TEST_ID56_MEDIA_METER_MEDIA_UART, Message, Length);
				return true;
			}
			virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
				if(UART_Read_State_FIFO(TESTBENCH_TEST_ID56_MEDIA_METER_MEDIA_UART).rxBusy()) {
					for(U32 Index=RESET; Index<100; Index++)
					{
						*Length = UART_Read_State_FIFO(TESTBENCH_TEST_ID56_MEDIA_METER_MEDIA_UART).rx_Length;	
						TaskManager_Delay(100 MSec);
						if(*Length == UART_Read_State_FIFO(TESTBENCH_TEST_ID56_MEDIA_METER_MEDIA_UART).rx_Length)
						{
							break;
						}
					}
					if(*Length) {
						*Length = UART_Receive_String_FIFO(TESTBENCH_TEST_ID56_MEDIA_METER_MEDIA_UART, Message, *Length);
						return true;
					}
				}
				return false;
			}
			virtual bool Clear() {		
				UART_Reset_Buffer_FIFO(TESTBENCH_TEST_ID56_MEDIA_METER_MEDIA_UART);
				return true;
			}
			virtual bool Reset() {		
				return false;
			}
			virtual bool Close() {		
				return false;
			}		
	} Meter;
	class : Media // OP
	{
		public:
			virtual bool Open() {		
				Update(TESTBENCH_TEST_ID56_MEDIA_OP_MEDIA_BOUDRATE);
				return true;
			}
			virtual bool Update(uint32_t Speed) {
				UART_UpdateSetting(TESTBENCH_TEST_ID56_MEDIA_OP_MEDIA_UART, Speed, 0x2000, USART_Parity_Even, USART_StopBits_1, true);
				return true;
			}
			virtual bool Send(uint8_t *Message, uint32_t Length) {		
				UART_Send_String(TESTBENCH_TEST_ID56_MEDIA_OP_MEDIA_UART, Message, Length);
				return true;
			}
			virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
				if(UART_Read_State_FIFO(TESTBENCH_TEST_ID56_MEDIA_OP_MEDIA_UART).rxBusy()) {
					for(U32 Index=RESET; Index<100; Index++)
					{
						*Length = UART_Read_State_FIFO(TESTBENCH_TEST_ID56_MEDIA_OP_MEDIA_UART).rx_Length;	
						TaskManager_Delay(100 MSec);
						if(*Length == UART_Read_State_FIFO(TESTBENCH_TEST_ID56_MEDIA_OP_MEDIA_UART).rx_Length)
						{
							break;
						}
					}
					if(*Length) {
						*Length = UART_Receive_String_FIFO(TESTBENCH_TEST_ID56_MEDIA_OP_MEDIA_UART, Message, *Length);
						return true;
					}
				}
				return false;
			}
			virtual bool Clear() {		
				UART_Reset_Buffer_FIFO(TESTBENCH_TEST_ID56_MEDIA_OP_MEDIA_UART);
				return true;
			}
			virtual bool Reset() {		
				return false;
			}
			virtual bool Close() {		
				return false;
			}		
	} OP;
} Test_56;
struct { // Test_55
	struct { // DigitalOutput
		struct_ValueBool Power_12v_En;
		struct_ValueBool Power_5v_En;
		struct_ValueBool Power_3v3_En;
		struct_ValueBool Booster_En;
		struct_ValueBool Relay_Set;
		struct_ValueBool Relay_Reset;
		void Relay(bool Enable) {
			if(Enable) {
				Relay_Set.Enable();
			}
			else {
				Relay_Reset.Enable();
			}
			TaskManager_Delay(50 MSec);
			Relay_Set.Disable();
			Relay_Reset.Disable();
			TaskManager_Delay(50 MSec);
		}			
		struct_ValueBool MBUS_En;
		struct_ValueBool RS485_En;
	} DigitalOutput;
	struct { // DigitalInput
		struct_ValueBool Relay_Status;
	} DigitalInput;
	struct { // AnalogInput
		float Get_Power_12v_Voltage(void)
		{
			return ((float)ADC_Read(TESTBENCH_TEST_ID55_ANALOG_INPUT_POWER_12V_VOLTAGE_CHANNEL) * 0.0008056640625);
		}
		float Get_Power_5v_Voltage(void)
		{
			return ((float)ADC_Read(TESTBENCH_TEST_ID55_ANALOG_INPUT_POWER_5V_VOLTAGE_CHANNEL) * 0.0008056640625);
		}
		float Get_Power_4v_Voltage(void)
		{
			return ((float)ADC_Read(TESTBENCH_TEST_ID55_ANALOG_INPUT_POWER_4V_VOLTAGE_CHANNEL) * 0.0008056640625);
		}
		float Get_Power_3v3_Voltage(void)
		{
			return ((float)ADC_Read(TESTBENCH_TEST_ID55_ANALOG_INPUT_POWER_3V3_VOLTAGE_CHANNEL) * 0.0008056640625);
		}		
		float Get_Booster_Voltage(void)
		{
			return ((float)ADC_Read(TESTBENCH_TEST_ID55_ANALOG_INPUT_BOOSTER_VOLTAGE_CHANNEL) * 0.0008056640625);
		}			
	} AnalogInput;
	class : Media // Interface
	{
		public:
			virtual bool Open() {		
				Update(19200);
				return true;
			}
			virtual bool Update(uint32_t Speed) {
				UART_UpdateSetting(TESTBENCH_TEST_ID56_MEDIA_UI_UART, Speed, USART_WordLength_8b, USART_Parity_No, USART_StopBits_1, true);
				return true;
			}
			virtual bool Send(uint8_t *Message, uint32_t Length) {		
				UART_Send_String(TESTBENCH_TEST_ID56_MEDIA_UI_UART, Message, Length);
				return true;
			}
			virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
				if(UART_Read_State_FIFO(TESTBENCH_TEST_ID56_MEDIA_UI_UART).rxBusy()) {
					for(U32 Index=RESET; Index<100; Index++)
					{
						*Length = UART_Read_State_FIFO(TESTBENCH_TEST_ID56_MEDIA_UI_UART).rx_Length;	
						TaskManager_Delay(100 MSec);
						if(*Length == UART_Read_State_FIFO(TESTBENCH_TEST_ID56_MEDIA_UI_UART).rx_Length)
						{
							break;
						}
					}
					if(*Length) {
						*Length = UART_Receive_String_FIFO(TESTBENCH_TEST_ID56_MEDIA_UI_UART, Message, *Length);
						return true;
					}
				}
				*Length = RESET;
				return false;
			}
			virtual bool Clear() {		
				UART_Reset_Buffer_FIFO(TESTBENCH_TEST_ID56_MEDIA_UI_UART);
				return true;
			}
			virtual bool Reset() {		
				return false;
			}
			virtual bool Close() {		
				return false;
			}		
	} Interface;
	class : Media // MBUS_Master
	{
		public:
			virtual bool Open() {		
				Update(1200);
				return true;
			}
			virtual bool Update(uint32_t Speed) {
				UART_UpdateSetting(TESTBENCH_TEST_ID55_MBUS_MASTER_MEDIA_UART, Speed, USART_WordLength_8b, USART_Parity_No, USART_StopBits_1, true);
				return true;
			}
			virtual bool Send(uint8_t *Message, uint32_t Length) {		
				UART_Send_String(TESTBENCH_TEST_ID55_MBUS_MASTER_MEDIA_UART, Message, Length);
				return true;
			}
			virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
				if(UART_Read_State_FIFO(TESTBENCH_TEST_ID55_MBUS_MASTER_MEDIA_UART).rxBusy()) {
					for(U32 Index=RESET; Index<100; Index++)
					{
						*Length = UART_Read_State_FIFO(TESTBENCH_TEST_ID55_MBUS_MASTER_MEDIA_UART).rx_Length;	
						TaskManager_Delay(100 MSec);
						if(*Length == UART_Read_State_FIFO(TESTBENCH_TEST_ID55_MBUS_MASTER_MEDIA_UART).rx_Length)
						{
							break;
						}
					}
					if(*Length) {
						*Length = UART_Receive_String_FIFO(TESTBENCH_TEST_ID55_MBUS_MASTER_MEDIA_UART, Message, *Length);
						return true;
					}
				}
				*Length = RESET;
				return false;
			}
			virtual bool Clear() {		
				UART_Reset_Buffer_FIFO(TESTBENCH_TEST_ID55_MBUS_MASTER_MEDIA_UART);
				return true;
			}
			virtual bool Reset() {		
				return false;
			}
			virtual bool Close() {		
				return false;
			}		
	} MBUS_Master;
	class : Media // MBUS_Slave
	{
		public:
			virtual bool Open() {		
				Update(1200);
				return true;
			}
			virtual bool Update(uint32_t Speed) {
				UART_UpdateSetting(TESTBENCH_TEST_ID55_MBUS_SLAVE_MEDIA_UART, Speed, USART_WordLength_8b, USART_Parity_No, USART_StopBits_1, true);
				return true;
			}
			virtual bool Send(uint8_t *Message, uint32_t Length) {		
				UART_Send_String(TESTBENCH_TEST_ID55_MBUS_SLAVE_MEDIA_UART, Message, Length);
				return true;
			}
			virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
				if(UART_Read_State_FIFO(TESTBENCH_TEST_ID55_MBUS_SLAVE_MEDIA_UART).rxBusy()) {
					for(U32 Index=RESET; Index<100; Index++)
					{
						*Length = UART_Read_State_FIFO(TESTBENCH_TEST_ID55_MBUS_SLAVE_MEDIA_UART).rx_Length;	
						TaskManager_Delay(100 MSec);
						if(*Length == UART_Read_State_FIFO(TESTBENCH_TEST_ID55_MBUS_SLAVE_MEDIA_UART).rx_Length)
						{
							break;
						}
					}
					if(*Length) {
						*Length = UART_Receive_String_FIFO(TESTBENCH_TEST_ID55_MBUS_SLAVE_MEDIA_UART, Message, *Length);
						return true;
					}
				}
				*Length = RESET;
				return false;
			}
			virtual bool Clear() {		
				UART_Reset_Buffer_FIFO(TESTBENCH_TEST_ID55_MBUS_SLAVE_MEDIA_UART);
				return true;
			}
			virtual bool Reset() {		
				return false;
			}
			virtual bool Close() {		
				return false;
			}		
	} MBUS_Slave;
	class : Media // RS485_Master
	{
		public:
			virtual bool Open() {		
				Update(9600);
				return true;
			}
			virtual bool Update(uint32_t Speed) {
				UART_UpdateSetting(TESTBENCH_TEST_ID55_RS485_MASTER_MEDIA_UART, Speed, USART_WordLength_8b, USART_Parity_No, USART_StopBits_1, true);
				return true;
			}
			virtual bool Send(uint8_t *Message, uint32_t Length) {		
				UART_Send_String(TESTBENCH_TEST_ID55_RS485_MASTER_MEDIA_UART, Message, Length);
				return true;
			}
			virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
				if(UART_Read_State_FIFO(TESTBENCH_TEST_ID55_RS485_MASTER_MEDIA_UART).rxBusy()) {
					for(U32 Index=RESET; Index<100; Index++)
					{
						*Length = UART_Read_State_FIFO(TESTBENCH_TEST_ID55_RS485_MASTER_MEDIA_UART).rx_Length;	
						TaskManager_Delay(100 MSec);
						if(*Length == UART_Read_State_FIFO(TESTBENCH_TEST_ID55_RS485_MASTER_MEDIA_UART).rx_Length)
						{
							break;
						}
					}
					if(*Length) {
						*Length = UART_Receive_String_FIFO(TESTBENCH_TEST_ID55_RS485_MASTER_MEDIA_UART, Message, *Length);
						return true;
					}
				}
				*Length = RESET;
				return false;
			}
			virtual bool Clear() {		
				UART_Reset_Buffer_FIFO(TESTBENCH_TEST_ID55_RS485_MASTER_MEDIA_UART);
				return true;
			}
			virtual bool Reset() {		
				return false;
			}
			virtual bool Close() {		
				return false;
			}		
	} RS485_Master;
	class : Media // RS485_Slave
	{
		public:
			virtual bool Open() {		
				Update(9600);
				return true;
			}
			virtual bool Update(uint32_t Speed) {
				UART_UpdateSetting(TESTBENCH_TEST_ID55_RS485_SLAVE_MEDIA_UART, Speed, USART_WordLength_8b, USART_Parity_No, USART_StopBits_1, true);
				return true;
			}
			virtual bool Send(uint8_t *Message, uint32_t Length) {		
				UART_Send_String(TESTBENCH_TEST_ID55_RS485_SLAVE_MEDIA_UART, Message, Length);
				return true;
			}
			virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
				if(UART_Read_State_FIFO(TESTBENCH_TEST_ID55_RS485_SLAVE_MEDIA_UART).rxBusy()) {
					for(U32 Index=RESET; Index<100; Index++)
					{
						*Length = UART_Read_State_FIFO(TESTBENCH_TEST_ID55_RS485_SLAVE_MEDIA_UART).rx_Length;	
						TaskManager_Delay(100 MSec);
						if(*Length == UART_Read_State_FIFO(TESTBENCH_TEST_ID55_RS485_SLAVE_MEDIA_UART).rx_Length)
						{
							break;
						}
					}
					if(*Length) {
						*Length = UART_Receive_String_FIFO(TESTBENCH_TEST_ID55_RS485_SLAVE_MEDIA_UART, Message, *Length);
						return true;
					}
				}
				*Length = RESET;
				return false;
			}
			virtual bool Clear() {		
				UART_Reset_Buffer_FIFO(TESTBENCH_TEST_ID55_RS485_SLAVE_MEDIA_UART);
				return true;
			}
			virtual bool Reset() {		
				return false;
			}
			virtual bool Close() {		
				return false;
			}		
	} RS485_Slave;
} Test_55;
/************************************************** Functions *********************************************************/
bool TEST_GetID_MUTEX = false;
uint8_t* TEST_GetID() {
	GPIO_InitTypeDef  GPIO_InitStructure;
	U8 Buffer[2];
	static uint8_t Data[3];
	
	TASK_MANAGER_MUTEXWAIT(TEST_GetID_MUTEX);
	
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[TESTBENCH_GETID_SERIAL_1_PORT] | \
				GPIO_PORTCLOCK[TESTBENCH_GETID_SERIAL_2_PORT] | \
				GPIO_PORTCLOCK[TESTBENCH_GETID_LOAD_PORT] | \
				GPIO_PORTCLOCK[TESTBENCH_GETID_CLOCK_PORT], ENABLE);
	
	// Configure output TESTBENCH_SERIAL_1
	//{
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_GETID_SERIAL_1_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_SERIAL_1_PORT], &GPIO_InitStructure);
	//}

	// Configure output TESTBENCH_SERIAL_2
	//{
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_GETID_SERIAL_2_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_SERIAL_2_PORT], &GPIO_InitStructure);
	//}
	
	// Configure output TESTBENCH_LOAD
	//{
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_GETID_LOAD_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_LOAD_PORT], &GPIO_InitStructure);
	//}

	// Configure output TESTBENCH_CLOCK
	//{
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_GETID_CLOCK_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_CLOCK_PORT], &GPIO_InitStructure);
	//}

	GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_LOAD_PORT], (1 << TESTBENCH_GETID_LOAD_PIN));
	TaskManager_Delay(10 MSec);
	GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_LOAD_PORT], (1 << TESTBENCH_GETID_LOAD_PIN));
	TaskManager_Delay(100 MSec);
	
	TaskManager_Delay(20 MSec);
	GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_CLOCK_PORT], (1 << TESTBENCH_GETID_CLOCK_PIN));
	TaskManager_Delay(20 MSec);
	GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_CLOCK_PORT], (1 << TESTBENCH_GETID_CLOCK_PIN));
		
	GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_LOAD_PORT], (1 << TESTBENCH_GETID_LOAD_PIN));
	GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_CLOCK_PORT], (1 << TESTBENCH_GETID_CLOCK_PIN));
	TaskManager_Delay(2 MSec);	
	Buffer[0] = RESET;
	Buffer[1] = RESET;
	for(S8 Index=7; Index>=0; Index--)
	{
		if(GPIO_ReadInputDataBit((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_SERIAL_1_PORT], (1 << TESTBENCH_GETID_SERIAL_1_PIN)))
		{
			Buffer[0] |= (1 << Index);
		}
		if(GPIO_ReadInputDataBit((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_SERIAL_2_PORT], (1 << TESTBENCH_GETID_SERIAL_2_PIN)))
		{
			Buffer[1] |= (1 << Index);
		}
		
		TaskManager_Delay(20 MSec);
		GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_CLOCK_PORT], (1 << TESTBENCH_GETID_CLOCK_PIN));
		TaskManager_Delay(20 MSec);
		GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_CLOCK_PORT], (1 << TESTBENCH_GETID_CLOCK_PIN));
	}
	
	if(Buffer[0] == Buffer[1]) {
		sprintf((char*)Data, "%d", Buffer[0]);
		General.LED.A.Disable();
	} else {
		General.LED.A.Enable();
		Test_56.DigitalOutput.Power_4v_En.Disable();
		Test_56.DigitalOutput.Power_5v_En.Disable();
		Test_55.DigitalOutput.Power_12v_En.Disable();
		sprintf((char*)Data, "0");
	}
	
	TASK_MANAGER_MUTEXRELEASE(TEST_GetID_MUTEX);	
	
	return Data;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_HardwareVersion(uint8_t* Data) {
	sprintf((char*)Data, "%s", TESTBENCH_VERSION_HARDWARE);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_SoftwareVersion(U8* Data) {
	sprintf((char*)Data, "%s", TESTBENCH_VERSION_SOFTWARE);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_GetID(U8* Data) {
	strcpy((char*)Data, (char*)TEST_GetID());
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID56_Power_5v_On(U8* Data)
{
	TaskManager_Delay(200 MSec);
	float Value[2];
	Value[0] = Test_56.AnalogInput.Get_Power_to5v_Voltage();
	
	if(Value[0] >= 2.15) {
		Test_56.DigitalOutput.Power_5v_En.Enable();
		TaskManager_Delay(3 Sec);
		Value[1] = Test_56.AnalogInput.Get_Power_to5v_Voltage();
		if(Value[1] < (Value[0]-(Value[0]*0.3))) {
			Test_56.DigitalOutput.Power_5v_En.Disable();
			sprintf((char*)Data, "Short circuit");
		} else {
			sprintf((char*)Data, "OK");
		}			
	}
	else {
		sprintf((char*)Data, "Input under voltage");
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID56_CheckProgram_Test(U8* Data)
{
		U8 Buffer[256];
		uint32_t Length;
		
		Test_56.Meter.Update(9600);
		TaskManager_Delay(10 Sec);
		Test_56.Meter.Clear();
		Test_56.Meter.Send((U8*)"C00", 3);
		TaskManager_Delay(3 Sec);
		memset(Buffer, NULL, sizeof(Buffer));
		Length = Test_56.Meter.Receive(Buffer, &Length);

		if(Length)
		{
				sprintf((char*)Data, "%s", Buffer);
		}
		else
		{
				strcpy((char*)Data, "Error");
		}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID56_Power_4v_On(U8* Data)
{
	TaskManager_Delay(200 MSec);
	float Value[2];
	Test_56.DigitalOutput.Power_4v_En.Enable();
	TaskManager_Delay(10 Sec);
	Value[0] = Test_56.AnalogInput.Get_Power_4v_Voltage();
	
	if((Value[0] >= 1.75) && (Value[0] <= 1.85)) {
		sprintf((char*)Data, "OK");		
	}
	else {
		Test_56.DigitalOutput.Power_4v_En.Disable();
		sprintf((char*)Data, "Short circuit");
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID56_CheckModem(U8* Data)
{
	U8 Buffer[128];
	uint32_t Length;
	
	Test_56.Meter.Update(9600);
	Test_56.Meter.Clear();
	Test_56.Meter.Send((U8*)"R10", 3);
	TaskManager_Delay(2 Sec);
	Length = Test_56.Meter.Receive(Buffer, &Length);
	TaskManager_Delay(1 Sec);

	if(Length)
	{
			sprintf((char*)Data, "%s", Buffer);
	}
	else
	{
			strcpy((char*)Data, "Error");
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID56_RTC_Voltage(U8* Data)
{
	TaskManager_Delay(200 MSec);
	float Value[2];
	Value[0] = Test_56.AnalogInput.Get_RTC_Voltage();

	if((Value[0] >= 2.5) && (Value[0] <= 3.2))
	{
		sprintf((char*)Data, "OK");
	}
	else
	{
		sprintf((char*)Data, "Battery not valid");
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID56_CheckFlash(U8* Data)
{
		U8 Buffer[128];
		uint32_t Length;
		
		Test_56.Meter.Update(9600);
		Test_56.Meter.Clear();
		Test_56.Meter.Send((U8*)"R20", 3);
		TaskManager_Delay(10 Sec);
		Length = Test_56.Meter.Receive(Buffer, &Length);

		if(Length)
		{
				sprintf((char*)Data, "%s", Buffer);
		}
		else
		{
				strcpy((char*)Data, "Error");
		}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID56_CheckEEprom(U8* Data)
{
		U8 Buffer[128];
		uint32_t Length;
		
		Test_56.Meter.Update(9600);
		Test_56.Meter.Clear();
		Test_56.Meter.Send((U8*)"R30", 3);
		TaskManager_Delay(10 Sec);
		Length = Test_56.Meter.Receive(Buffer, &Length);

		if(Length)
		{
				sprintf((char*)Data, "%s", Buffer);
		}
		else
		{
				strcpy((char*)Data, "Error");
		}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID56_CheckOP(U8* Data)
{
	U8 Buffer[128];
	U8 Byte[2];
	uint32_t Length;
	bool Pass;
		
	///
	//{
	sprintf((char*)Data, "ERROR");


	Test_56.OP.Open();
	Test_56.OP.Clear();
					
	for(U16 Index=RESET; Index<sizeof(Buffer); Index++)
	{
		Buffer[Index] = Index;		
	}
	
	Test_56.OP.Send((U8*)Buffer, sizeof(Buffer));
	
	TaskManager_Delay(3 Sec);
	
	Pass = false;
	Length = sizeof(Buffer);
	memset((char*)Buffer, NULL, sizeof(Buffer));
	Test_56.OP.Receive((U8*)Buffer, &Length);
				
	if(Length)
	{
		Pass = true;
		for(U16 Index=RESET; Index<sizeof(Buffer); Index++)
		{
			Byte[0] = ((((U8)0xFF)-((U8)Index)) & 0x7F);
			if(Buffer[Index] != Byte[0])
			{
				Pass = false;
				break;
			}
		}
	}

	if(Pass)
	{
		sprintf((char*)Data, "OK");
	}
	//}
}
/*--------------------------------------------------------------------------------------------------------------------*/
U32 TEST_ID56_CheckBuzzer_EventMic_Count;

void TEST_ID56_CheckBuzzer_EventMic(void)
{
	TEST_ID56_CheckBuzzer_EventMic_Count++;
}
void TEST_ID56_CheckBuzzer(U8* Data)
{
		TEST_ID56_CheckBuzzer_EventMic_Count = RESET;
		U8 Buffer[128];
		uint32_t Length;
		
		Test_56.Meter.Update(9600);
		Test_56.Meter.Clear();
		Test_56.Meter.Send((U8*)"R40", 3);
		TaskManager_Delay(4 Sec);
		Length = Test_56.Meter.Receive(Buffer, &Length);

		if((Length) && (TEST_ID56_CheckBuzzer_EventMic_Count > 5000))
		{
				sprintf((char*)Data, "%s", Buffer);
		}
		else
		{
				strcpy((char*)Data, "Error");
		}
	
}
/*--------------------------------------------------------------------------------------------------------------------*/
U32 TEST_ID56_CheckBuzzer_EventLED_Count;

void TEST_ID56_CheckBuzzer_EventLED(void)
{
	TEST_ID56_CheckBuzzer_EventLED_Count++;
}
void TEST_ID56_CheckLED_Green(U8* Data)
{
		TEST_ID56_CheckBuzzer_EventLED_Count = RESET;
		U8 Buffer[128];
		uint32_t Length;
		
		Test_56.Meter.Update(9600);
		Test_56.Meter.Clear();
		Test_56.Meter.Send((U8*)"R50", 3);
		TaskManager_Delay(4 Sec);
		Length = Test_56.Meter.Receive(Buffer, &Length);

		if((Length) && (TEST_ID56_CheckBuzzer_EventLED_Count > 5000))
		{
				sprintf((char*)Data, "%s", Buffer);
		}
		else
		{
				strcpy((char*)Data, "Error");
		}
	
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID56_Power_4v_Off(U8* Data)
{
		TaskManager_Delay(1 Sec);
		Test_56.DigitalOutput.Power_4v_En.Disable();
		sprintf((char*)Data, "OK");
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID56_Power_5v_Off(U8* Data)
{
		TaskManager_Delay(1 Sec);
		Test_56.DigitalOutput.Power_5v_En.Disable();
		sprintf((char*)Data, "OK");
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID55_Power_12v_On(U8* Data)
{
	TaskManager_Delay(200 MSec);
	float Value[2];
	Value[0] = Test_55.AnalogInput.Get_Power_12v_Voltage();
	
	if(Value[0] >= 2.15) {
		Test_55.DigitalOutput.Power_12v_En.Enable();
		TaskManager_Delay(3 Sec);
		Value[1] = Test_55.AnalogInput.Get_Power_12v_Voltage();
		if(Value[1] < (Value[0]-(Value[0]*0.3))) {
			Test_55.DigitalOutput.Power_12v_En.Disable();
			sprintf((char*)Data, "Short circuit");
		} else {
			sprintf((char*)Data, "OK");
		}			
	}
	else {
		sprintf((char*)Data, "Input under voltage");
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID55_5v_Voltage(U8* Data)
{
	TaskManager_Delay(200 MSec);
	float Value[2];
	Value[0] = Test_55.AnalogInput.Get_Power_5v_Voltage();

	if((Value[0] >= 2.2) && (Value[0] <= 2.4))
	{
		sprintf((char*)Data, "OK");
	}
	else
	{
		Test_55.DigitalOutput.Power_12v_En.Disable();
		sprintf((char*)Data, "Fault voltage");
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID55_4v_Voltage(U8* Data)
{
	TaskManager_Delay(200 MSec);
	float Value[2];
	Value[0] = Test_55.AnalogInput.Get_Power_4v_Voltage();

	if((Value[0] >= 1.35) && (Value[0] <= 1.65))
	{
		sprintf((char*)Data, "OK");
	}
	else
	{
		Test_55.DigitalOutput.Power_12v_En.Disable();
		sprintf((char*)Data, "Fault voltage");
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID55_3v3_Voltage(U8* Data)
{
	TaskManager_Delay(200 MSec);
	float Value[2];
	Value[0] = Test_55.AnalogInput.Get_Power_3v3_Voltage();

	if((Value[0] >= 2.6) && (Value[0] <= 2.9))
	{
		sprintf((char*)Data, "OK");
	}
	else
	{
		Test_55.DigitalOutput.Power_12v_En.Disable();
		sprintf((char*)Data, "Fault voltage");
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID55_Booster_Voltage(U8* Data)
{
	TaskManager_Delay(200 MSec);
	float Value[2];
	
	Test_55.DigitalOutput.Power_3v3_En.Enable();
	Test_55.DigitalOutput.Booster_En.Enable();
	TaskManager_Delay(500 MSec);
	Value[0] = Test_55.AnalogInput.Get_Booster_Voltage();

	if((Value[0] >= 1.55) && (Value[0] <= 1.7))
	{
		sprintf((char*)Data, "OK");
	}
	else
	{		
		sprintf((char*)Data, "Fault voltage");
	}
	
	Test_55.DigitalOutput.Booster_En.Disable();
	Test_55.DigitalOutput.Power_3v3_En.Disable();
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID55_Relay(U8* Data)
{
	TaskManager_Delay(200 MSec);
	U8 Error = 0;
	
	Test_55.DigitalOutput.Power_3v3_En.Enable();
	Test_55.DigitalOutput.Relay(true);
	TaskManager_Delay(200 MSec);
	if(Test_55.DigitalInput.Relay_Status.Get() == false) {
		Error = 1;
	}
	Test_55.DigitalOutput.Relay(false);
	TaskManager_Delay(200 MSec);
	if(Test_55.DigitalInput.Relay_Status.Get() != false) {
		Error = 2;
	}
	Test_55.DigitalOutput.Power_3v3_En.Disable();
	if(Error == 0) {
		sprintf((char*)Data, "OK");
	}
	else {
		sprintf((char*)Data, "Relay Error : %d", Error);
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID55_RS485(U8* Data)
{
	TaskManager_Delay(200 MSec);
	U8 Error = 0;
	U8 Send[256];
	U8 Receive[256];
	uint32_t Length;
	
	Test_55.DigitalOutput.Power_5v_En.Enable();
	Test_55.DigitalOutput.RS485_En.Enable();
	Test_55.RS485_Master.Open();
	Test_55.RS485_Slave.Open();
	TaskManager_Delay(100 MSec);
	
	memset(Send, NULL, sizeof(Send));
	for(U16 Index=RESET; Index<sizeof(Send); Index++) {
		Send[Index] = Index;
	}
	
	memset(Receive, NULL, sizeof(Receive));
	Test_55.RS485_Master.Clear();
	Test_55.RS485_Slave.Clear();
	TaskManager_Delay(100 MSec);	
	Test_55.RS485_Master.Send(Send, sizeof(Send));
	TaskManager_Delay(100 MSec);
	Length = sizeof(Receive);
	Test_55.RS485_Slave.Receive(Receive, &Length);
	if(Length != sizeof(Send)) {
		Error = 1;
	}
	else {
		if(memcmp(Receive, Send, Length)) {
			Error = 2;
		}
	}
	
	if(Error == 0) {
		memset(Receive, NULL, sizeof(Receive));
		Test_55.RS485_Master.Clear();
		Test_55.RS485_Slave.Clear();
		TaskManager_Delay(100 MSec);
		Test_55.RS485_Slave.Send(Send, sizeof(Send));
		TaskManager_Delay(100 MSec);
		Length = sizeof(Receive);
		Test_55.RS485_Master.Receive(Receive, &Length);
		if(Length != sizeof(Send)) {
			Error = 3;
		}
		else {
			if(memcmp(Receive, Send, Length)) {
				Error = 4;
			}
		}
	}
	
	Test_55.DigitalOutput.RS485_En.Disable();
	Test_55.DigitalOutput.Power_5v_En.Disable();
	if(Error == 0) {
		sprintf((char*)Data, "OK");
	}
	else {
		sprintf((char*)Data, "RS485 Error : %d", Error);
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID55_MBUS(U8* Data)
{
	TaskManager_Delay(200 MSec);
	U8 Error = 0;
	U8 Send[256];
	U8 Receive[256];
	uint32_t Length;
	
	Test_55.DigitalOutput.MBUS_En.Enable();
	Test_55.MBUS_Master.Open();
	Test_55.MBUS_Slave.Open();
	TaskManager_Delay(100 MSec);
	
	memset(Send, NULL, sizeof(Send));
	for(U16 Index=RESET; Index<sizeof(Send); Index++) {
		Send[Index] = Index;
	}
	
	memset(Receive, NULL, sizeof(Receive));
	Test_55.MBUS_Master.Clear();
	Test_55.MBUS_Slave.Clear();
	TaskManager_Delay(100 MSec);	
	Test_55.MBUS_Master.Send(Send, sizeof(Send));
	TaskManager_Delay(100 MSec);
	Length = sizeof(Receive);
	Test_55.MBUS_Slave.Receive(Receive, &Length);
	if(Length != sizeof(Send)) {
		Error = 1;
	}
	else {
		if(memcmp(Receive, Send, Length)) {
			Error = 2;
		}
	}
	
	if(Error == 0) {
		memset(Receive, NULL, sizeof(Receive));
		Test_55.MBUS_Master.Clear();
		Test_55.MBUS_Slave.Clear();
		TaskManager_Delay(100 MSec);
		Test_55.MBUS_Slave.Send(Send, sizeof(Send));
		TaskManager_Delay(100 MSec);
		Length = sizeof(Receive);
		Test_55.MBUS_Master.Receive(Receive, &Length);
		if(Length != sizeof(Send)) {
			Error = 3;
		}
		else {
			if(memcmp(Receive, Send, Length)) {
				Error = 4;
			}
		}
	}
	
	Test_55.DigitalOutput.MBUS_En.Disable();
	if(Error == 0) {
		sprintf((char*)Data, "OK");
	}
	else {
		sprintf((char*)Data, "MBUS Error : %d", Error);
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID55_Power_12v_Off(U8* Data)
{
	TaskManager_Delay(1 Sec);
	Test_55.DigitalOutput.Power_12v_En.Disable();
	sprintf((char*)Data, "OK");
}
/*--------------------------------------------------------------------------------------------------------------------*/
void StartTasks();
static U64 StartTasks_STAK[4096/8];
int main (void) {
	os_sys_init_user(StartTasks, 255, &StartTasks_STAK, sizeof(StartTasks_STAK));
	return 0;
}
/************************************************** Tasks *************************************************************/
__task void StartTasks(void) {

	TaskManager_Delay(20 MSec);
	
	// Init drivers
	__init_RTC();
//	__init_WDT();
	__init_Timer();
	__init_GPIO();
	__init_ADC();	
	__init_UART();
	__init_PWM();
	__init_TaskTimer();
	__init_TaskManager();
	
	GPIO_Input_AddPin(TESTBENCH_KEY_A_PORT, TESTBENCH_KEY_A_PIN, NULL, &General.Key.A.ValueBool, PIN_EDGE_TOGGEL, PIN_PULLING_UP, false);
	GPIO_Output_AddPin(TESTBENCH_LED_PORT, TESTBENCH_LED_PIN, &General.LED.A.ValueBool, !WDT_LED_LOGIC);

	// Add tests
	TestBench.Init(&TEST_GetID);
	if(strcmp((char*)TestBench.GetID(), "56") == NULL) {
		GPIO_Input_AddPin(TESTBENCH_TEST_ID56_DIGITAL_INPUT_EVENT_MIC_PORT, TESTBENCH_TEST_ID56_DIGITAL_INPUT_EVENT_MIC_PIN, &TEST_ID56_CheckBuzzer_EventMic, &Test_56.DigitalInput.EventMic.ValueBool, PIN_EDGE_TOGGEL, PIN_PULLING_UP, true);
		GPIO_Input_AddPin(TESTBENCH_TEST_ID56_DIGITAL_INPUT_EVENT_LED_PORT, TESTBENCH_TEST_ID56_DIGITAL_INPUT_EVENT_LED_PIN, &TEST_ID56_CheckBuzzer_EventLED, &Test_56.DigitalInput.EventLED.ValueBool, PIN_EDGE_TOGGEL, PIN_PULLING_UP, true);
		
		GPIO_Output_AddPin(TESTBENCH_TEST_ID56_DIGITAL_OUTPUT_POWER_5V_EN_PORT, TESTBENCH_TEST_ID56_DIGITAL_OUTPUT_POWER_5V_EN_PIN, &Test_56.DigitalOutput.Power_5v_En.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID56_DIGITAL_OUTPUT_POWER_4V_EN_PORT, TESTBENCH_TEST_ID56_DIGITAL_OUTPUT_POWER_4V_EN_PIN, &Test_56.DigitalOutput.Power_4v_En.ValueBool, false);
		
		TestBench.Add((uint8_t*)"HardwareVersion", &TEST_HardwareVersion);
		TestBench.Add((uint8_t*)"SoftwareVersion", &TEST_SoftwareVersion);
		TestBench.Add((uint8_t*)"GetID", &TEST_GetID);
		TestBench.Add((uint8_t*)"ID56_Power_5v_On", &TEST_ID56_Power_5v_On);			
		TestBench.Add((uint8_t*)"ID56_CheckProgram_Test", &TEST_ID56_CheckProgram_Test);	
		TestBench.Add((uint8_t*)"ID56_Power_4v_On", &TEST_ID56_Power_4v_On);
		TestBench.Add((uint8_t*)"ID56_CheckModem", &TEST_ID56_CheckModem);
		TestBench.Add((uint8_t*)"ID56_Power_4v_Off", &TEST_ID56_Power_4v_Off);
		TestBench.Add((uint8_t*)"ID56_RTC_Voltage", &TEST_ID56_RTC_Voltage);
		TestBench.Add((uint8_t*)"ID56_CheckFlash", &TEST_ID56_CheckFlash);	
		TestBench.Add((uint8_t*)"ID56_CheckEEprom", &TEST_ID56_CheckEEprom);		
		TestBench.Add((uint8_t*)"ID56_CheckOP", &TEST_ID56_CheckOP);
		TestBench.Add((uint8_t*)"ID56_CheckBuzzer", &TEST_ID56_CheckBuzzer);
		TestBench.Add((uint8_t*)"ID56_CheckLED_Green", &TEST_ID56_CheckLED_Green);
		TestBench.Add((uint8_t*)"ID56_Power_5v_Off", &TEST_ID56_Power_5v_Off);
		
		// Config user interface
		UI.Init((Media*)&Test_56.Interface);
	}
	else if(strcmp((char*)TestBench.GetID(), "55") == NULL) {
		GPIO_Output_AddPin(TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_POWER_12V_EN_PORT, TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_POWER_12V_EN_PIN, &Test_55.DigitalOutput.Power_12v_En.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_POWER_5V_EN_PORT, TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_POWER_5V_EN_PIN, &Test_55.DigitalOutput.Power_5v_En.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_POWER_3V3_EN_PORT, TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_POWER_3V3_EN_PIN, &Test_55.DigitalOutput.Power_3v3_En.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_BOOSTER_EN_PORT, TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_BOOSTER_EN_PIN, &Test_55.DigitalOutput.Booster_En.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_RELAY_SET_PORT, TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_RELAY_SET_PIN, &Test_55.DigitalOutput.Relay_Set.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_RELAY_RESET_PORT, TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_RELAY_RESET_PIN, &Test_55.DigitalOutput.Relay_Reset.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_MBUS_EN_PORT, TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_MBUS_EN_PIN, &Test_55.DigitalOutput.MBUS_En.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_RS485_EN_PORT, TESTBENCH_TEST_ID55_DIGITAL_OUTPUT_RS485_EN_PIN, &Test_55.DigitalOutput.RS485_En.ValueBool, false);
		
		GPIO_Input_AddPin(TESTBENCH_TEST_ID55_DIGITAL_INPUT_RELAY_STATUS_PORT, TESTBENCH_TEST_ID55_DIGITAL_INPUT_RELAY_STATUS_PIN, NULL, &Test_55.DigitalInput.Relay_Status.ValueBool, PIN_EDGE_TOGGEL, PIN_PULLING_UP, false);
		
		TestBench.Add((uint8_t*)"HardwareVersion", &TEST_HardwareVersion);
		TestBench.Add((uint8_t*)"SoftwareVersion", &TEST_SoftwareVersion);
		TestBench.Add((uint8_t*)"GetID", &TEST_GetID);
		TestBench.Add((uint8_t*)"ID55_Power_12v_On", &TEST_ID55_Power_12v_On);		
		TestBench.Add((uint8_t*)"ID55_5v_Voltage", &TEST_ID55_5v_Voltage);
		TestBench.Add((uint8_t*)"ID55_4v_Voltage", &TEST_ID55_4v_Voltage);
		TestBench.Add((uint8_t*)"ID55_3v3_Voltage", &TEST_ID55_3v3_Voltage);
		TestBench.Add((uint8_t*)"ID55_Booster_Voltage", &TEST_ID55_Booster_Voltage);
		TestBench.Add((uint8_t*)"ID55_Relay", &TEST_ID55_Relay);
		TestBench.Add((uint8_t*)"ID55_RS485", &TEST_ID55_RS485);
		TestBench.Add((uint8_t*)"ID55_MBUS", &TEST_ID55_MBUS);
		TestBench.Add((uint8_t*)"ID55_Power_12v_Off", &TEST_ID55_Power_12v_Off);	
		
		// Config user interface
		UI.Init((Media*)&Test_55.Interface);
	}
	
	os_tsk_delete_self();
}
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
