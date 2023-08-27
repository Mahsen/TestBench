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
    Last Update : 2023/8/23
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
struct { // Test_7
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
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_POWER_TO5V_VOLTAGE_CHANNEL) * 0.000807640625);
		}
		float Get_Power_4v_Voltage(void)
		{
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_POWER_4V_VOLTAGE_CHANNEL) * 0.000807640625);
		}
		float Get_RTC_Voltage(void)
		{
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_RTC_VOLTAGE_CHANNEL) * 0.000807640625);
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
				UART_UpdateSetting(TESTBENCH_TEST_ID7_MEDIA_UI_UART, Speed, USART_WordLength_8b, USART_Parity_No, USART_StopBits_1, true);
				return true;
			}
			virtual bool Send(uint8_t *Message, uint32_t Length) {		
				UART_Send_String(TESTBENCH_TEST_ID7_MEDIA_UI_UART, Message, Length);
				return true;
			}
			virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
				if(UART_Read_State_FIFO(TESTBENCH_TEST_ID7_MEDIA_UI_UART).rxBusy()) {
					for(U32 Index=RESET; Index<100; Index++)
					{
						*Length = UART_Read_State_FIFO(TESTBENCH_TEST_ID7_MEDIA_UI_UART).rx_Length;	
						TaskManager_Delay(100 MSec);
						if(*Length == UART_Read_State_FIFO(TESTBENCH_TEST_ID7_MEDIA_UI_UART).rx_Length)
						{
							break;
						}
					}
					if(*Length) {
						*Length = UART_Receive_String_FIFO(TESTBENCH_TEST_ID7_MEDIA_UI_UART, Message, *Length);
						return true;
					}
				}
				return false;
			}
			virtual bool Clear() {		
				UART_Reset_Buffer_FIFO(TESTBENCH_TEST_ID7_MEDIA_UI_UART);
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
				Update(TESTBENCH_TEST_ID7_MEDIA_METER_MEDIA_BOUDRATE);
				return true;
			}
			virtual bool Update(uint32_t Speed) {
				UART_UpdateSetting(TESTBENCH_TEST_ID7_MEDIA_METER_MEDIA_UART, Speed, USART_WordLength_8b, USART_Parity_No, USART_StopBits_1, true);
				return true;
			}
			virtual bool Send(uint8_t *Message, uint32_t Length) {		
				UART_Send_String(TESTBENCH_TEST_ID7_MEDIA_METER_MEDIA_UART, Message, Length);
				return true;
			}
			virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
				if(UART_Read_State_FIFO(TESTBENCH_TEST_ID7_MEDIA_METER_MEDIA_UART).rxBusy()) {
					for(U32 Index=RESET; Index<100; Index++)
					{
						*Length = UART_Read_State_FIFO(TESTBENCH_TEST_ID7_MEDIA_METER_MEDIA_UART).rx_Length;	
						TaskManager_Delay(100 MSec);
						if(*Length == UART_Read_State_FIFO(TESTBENCH_TEST_ID7_MEDIA_METER_MEDIA_UART).rx_Length)
						{
							break;
						}
					}
					if(*Length) {
						*Length = UART_Receive_String_FIFO(TESTBENCH_TEST_ID7_MEDIA_METER_MEDIA_UART, Message, *Length);
						return true;
					}
				}
				return false;
			}
			virtual bool Clear() {		
				UART_Reset_Buffer_FIFO(TESTBENCH_TEST_ID7_MEDIA_METER_MEDIA_UART);
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
				Update(TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_BOUDRATE);
				return true;
			}
			virtual bool Update(uint32_t Speed) {
				UART_UpdateSetting(TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_UART, Speed, 0x2000, USART_Parity_Even, USART_StopBits_1, true);
				return true;
			}
			virtual bool Send(uint8_t *Message, uint32_t Length) {		
				UART_Send_String(TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_UART, Message, Length);
				return true;
			}
			virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
				if(UART_Read_State_FIFO(TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_UART).rxBusy()) {
					for(U32 Index=RESET; Index<100; Index++)
					{
						*Length = UART_Read_State_FIFO(TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_UART).rx_Length;	
						TaskManager_Delay(100 MSec);
						if(*Length == UART_Read_State_FIFO(TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_UART).rx_Length)
						{
							break;
						}
					}
					if(*Length) {
						*Length = UART_Receive_String_FIFO(TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_UART, Message, *Length);
						return true;
					}
				}
				return false;
			}
			virtual bool Clear() {		
				UART_Reset_Buffer_FIFO(TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_UART);
				return true;
			}
			virtual bool Reset() {		
				return false;
			}
			virtual bool Close() {		
				return false;
			}		
	} OP;
} Test_7;
/************************************************** Functions *********************************************************/
bool TEST_GetID_MUTEX = false;
uint8_t* TEST_GetID() {
	GPIO_InitTypeDef  GPIO_InitStructure;
	U8 Buffer = RESET;
	static uint8_t Data[3];
	
	TASK_MANAGER_MUTEXWAIT(TEST_GetID_MUTEX);

	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[TESTBENCH_GETID_DEC1_PORT] | \
												GPIO_PORTCLOCK[TESTBENCH_GETID_DEC2_PORT] | \
												GPIO_PORTCLOCK[TESTBENCH_GETID_DEC3_PORT], ENABLE);
	
	// Configure output DEC1
	//{
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_GETID_DEC1_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_DEC1_PORT], &GPIO_InitStructure);
	//}

	// Configure output DEC2
	//{
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_GETID_DEC2_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_DEC2_PORT], &GPIO_InitStructure);
	//}

	// Configure output DEC3
	//{
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_GETID_DEC3_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_DEC3_PORT], &GPIO_InitStructure);
	//}

	__disable_irq();
	Buffer = GPIO_ReadInputDataBit((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_DEC1_PORT], (1 << TESTBENCH_GETID_DEC1_PIN));
	Buffer |= (GPIO_ReadInputDataBit((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_DEC2_PORT], (1 << TESTBENCH_GETID_DEC2_PIN)) << 1);
	Buffer |= (GPIO_ReadInputDataBit((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_GETID_DEC3_PORT], (1 << TESTBENCH_GETID_DEC3_PIN)) << 2);
	__enable_irq();
	
	sprintf((char*)Data, "%d", Buffer);
	
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
void TEST_ID7_Power_5v_On(U8* Data)
{
	TaskManager_Delay(200 MSec);
	float Value[2];
	Value[0] = Test_7.AnalogInput.Get_Power_to5v_Voltage();
	
	if(Value[0] >= 2.15) {
		Test_7.DigitalOutput.Power_5v_En.Enable();
		TaskManager_Delay(3 Sec);
		Value[1] = Test_7.AnalogInput.Get_Power_to5v_Voltage();
		if(Value[1] < (Value[0]-(Value[0]*0.3))) {
			Test_7.DigitalOutput.Power_5v_En.Disable();
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
void TEST_ID7_CheckProgram_Test(U8* Data)
{
		U8 Buffer[27];
		uint32_t Length;
		
		Test_7.Meter.Update(9600);
		TaskManager_Delay(10 Sec);
		Test_7.Meter.Clear();
		Test_7.Meter.Send((U8*)"C00", 3);
		TaskManager_Delay(3 Sec);
		memset(Buffer, NULL, sizeof(Buffer));
		Length = Test_7.Meter.Receive(Buffer, &Length);

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
void TEST_ID7_Power_4v_On(U8* Data)
{
	TaskManager_Delay(200 MSec);
	float Value[2];
	Test_7.DigitalOutput.Power_4v_En.Enable();
	TaskManager_Delay(10 Sec);
	Value[0] = Test_7.AnalogInput.Get_Power_4v_Voltage();
	
	if((Value[0] >= 1.75) && (Value[0] <= 1.85)) {
		sprintf((char*)Data, "OK");		
	}
	else {
		Test_7.DigitalOutput.Power_4v_En.Disable();
		sprintf((char*)Data, "Short circuit");
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_CheckModem(U8* Data)
{
	U8 Buffer[128];
	uint32_t Length;
	
	Test_7.Meter.Update(9600);
	Test_7.Meter.Clear();
	Test_7.Meter.Send((U8*)"R10", 3);
	TaskManager_Delay(2 Sec);
	Length = Test_7.Meter.Receive(Buffer, &Length);
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
void TEST_ID7_RTC_Voltage(U8* Data)
{
	TaskManager_Delay(200 MSec);
	float Value[2];
	Value[0] = Test_7.AnalogInput.Get_RTC_Voltage();

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
void TEST_ID7_CheckFlash(U8* Data)
{
		U8 Buffer[128];
		uint32_t Length;
		
		Test_7.Meter.Update(9600);
		Test_7.Meter.Clear();
		Test_7.Meter.Send((U8*)"R20", 3);
		TaskManager_Delay(10 Sec);
		Length = Test_7.Meter.Receive(Buffer, &Length);

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
void TEST_ID7_CheckEEprom(U8* Data)
{
		U8 Buffer[128];
		uint32_t Length;
		
		Test_7.Meter.Update(9600);
		Test_7.Meter.Clear();
		Test_7.Meter.Send((U8*)"R30", 3);
		TaskManager_Delay(10 Sec);
		Length = Test_7.Meter.Receive(Buffer, &Length);

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
void TEST_ID7_CheckOP(U8* Data)
{
	U8 Buffer[128];
	U8 Byte[2];
	uint32_t Length;
	bool Pass;
		
	///
	//{
	sprintf((char*)Data, "ERROR");


	Test_7.OP.Open();
	Test_7.OP.Clear();
					
	for(U16 Index=RESET; Index<sizeof(Buffer); Index++)
	{
		Buffer[Index] = Index;		
	}
	
	Test_7.OP.Send((U8*)Buffer, sizeof(Buffer));
	
	TaskManager_Delay(3 Sec);
	
	Pass = false;
	Length = sizeof(Buffer);
	memset((char*)Buffer, NULL, sizeof(Buffer));
	Test_7.OP.Receive((U8*)Buffer, &Length);
				
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
U32 TEST_ID7_CheckBuzzer_EventMic_Count;
void TEST_ID7_CheckBuzzer_EventMic(void)
{
	TEST_ID7_CheckBuzzer_EventMic_Count++;
}
void TEST_ID7_CheckBuzzer(U8* Data)
{
		TEST_ID7_CheckBuzzer_EventMic_Count = RESET;
		U8 Buffer[128];
		uint32_t Length;
		
		Test_7.Meter.Update(9600);
		Test_7.Meter.Clear();
		Test_7.Meter.Send((U8*)"R40", 3);
		TaskManager_Delay(4 Sec);
		Length = Test_7.Meter.Receive(Buffer, &Length);

		if((Length) && (TEST_ID7_CheckBuzzer_EventMic_Count > 5000))
		{
				sprintf((char*)Data, "%s", Buffer);
		}
		else
		{
				strcpy((char*)Data, "Error");
		}
	
}
/*--------------------------------------------------------------------------------------------------------------------*/
U32 TEST_ID7_CheckBuzzer_EventLED_Count;
void TEST_ID7_CheckBuzzer_EventLED(void)
{
	TEST_ID7_CheckBuzzer_EventLED_Count++;
}
void TEST_ID7_CheckLED_Red(U8* Data)
{
		TEST_ID7_CheckBuzzer_EventLED_Count = RESET;
		U8 Buffer[128];
		uint32_t Length;
		
		Test_7.Meter.Update(9600);
		Test_7.Meter.Clear();
		Test_7.Meter.Send((U8*)"R50", 3);
		TaskManager_Delay(4 Sec);
		Test_7.Meter.Receive(Buffer, &Length);

		if(TEST_ID7_CheckBuzzer_EventLED_Count > 100)
		{
				sprintf((char*)Data, "%s", Buffer);
		}
		else
		{
				strcpy((char*)Data, "Error");
		}
	
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_CheckTamper(U8* Data)
{
		U8 Buffer[128];
		uint32_t Length;
		
		Test_7.Meter.Update(9600);
		Test_7.Meter.Clear();
		Test_7.Meter.Send((U8*)"R60", 3);
		TaskManager_Delay(2 Sec);
		Test_7.Meter.Receive(Buffer, &Length);

		sprintf((char*)Data, "%s", Buffer);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_ResetParm(U8* Data)
{
		U8 Buffer[128];
		uint32_t Length;
		
		Test_7.Meter.Update(9600);
		Test_7.Meter.Clear();
		Test_7.Meter.Send((U8*)"R70", 3);
		TaskManager_Delay(5 Sec);
		Test_7.Meter.Receive(Buffer, &Length);

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
void TEST_ID7_ClearSQL(U8* Data)
{
		U8 Buffer[128];
		uint32_t Length;
		
		TaskManager_Delay(10 Sec);
		Test_7.Meter.Update(9600);
		Test_7.Meter.Clear();		
		Test_7.Meter.Send((U8*)"R80", 3);
		TaskManager_Delay(40 Sec);
		Test_7.Meter.Receive(Buffer, &Length);
	
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
void TEST_ID7_WriteSerial(U8* Data)
{
		U8 Buffer[128];
		uint32_t Length;

		Test_7.Meter.Update(9600);
		Test_7.Meter.Clear();		
		Test_7.Meter.Send((U8*)"W10", 3);
		TaskManager_Delay(500 MSec);
		Test_7.Meter.Clear();
		Test_7.Meter.Send(Data, strlen((char*)Data));
		TaskManager_Delay(3 Sec);
		Test_7.Meter.Receive(Buffer, &Length);
	
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
void TEST_ID7_WriteDateTime(U8* Data)
{
		U8 Buffer[128];
		uint32_t Length;

		Test_7.Meter.Update(9600);
		Test_7.Meter.Clear();		
		Test_7.Meter.Send((U8*)"W20", 3);
		TaskManager_Delay(500 MSec);
		Test_7.Meter.Clear();
		Test_7.Meter.Send(Data, strlen((char*)Data));
		TaskManager_Delay(3 Sec);
		Test_7.Meter.Receive(Buffer, &Length);
	
		if((Length) && (strstr((char*)Buffer, ":")))
		{
				sprintf((char*)Data, "%s", Buffer);
		}
		else
		{
				strcpy((char*)Data, "Error");
		}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_CheckProgram_Final(U8* Data)
{
		U8 Buffer[27];
		uint32_t Length;
		
		Test_7.OP.Update(300);
		TaskManager_Delay(90 Sec);
		Test_7.OP.Clear();
		Test_7.OP.Send((U8*)"C00", 3);
		TaskManager_Delay(3 Sec);
		memset(Buffer, NULL, sizeof(Buffer));
		Length = Test_7.OP.Receive(Buffer, &Length);

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
void TEST_ID7_Power_4v_Off(U8* Data)
{
		TaskManager_Delay(1 Sec);
		Test_7.DigitalOutput.Power_4v_En.Disable();
		sprintf((char*)Data, "OK");
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_Power_5v_Off(U8* Data)
{
		TaskManager_Delay(1 Sec);
		Test_7.DigitalOutput.Power_5v_En.Disable();
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
	if(strcmp((char*)TestBench.GetID(), "7") == NULL) {
		GPIO_Input_AddPin(TESTBENCH_TEST_ID7_DIGITAL_INPUT_EVENT_MIC_PORT, TESTBENCH_TEST_ID7_DIGITAL_INPUT_EVENT_MIC_PIN, &TEST_ID7_CheckBuzzer_EventMic, &Test_7.DigitalInput.EventMic.ValueBool, PIN_EDGE_TOGGEL, PIN_PULLING_UP, true);
		GPIO_Input_AddPin(TESTBENCH_TEST_ID7_DIGITAL_INPUT_EVENT_LED_PORT, TESTBENCH_TEST_ID7_DIGITAL_INPUT_EVENT_LED_PIN, &TEST_ID7_CheckBuzzer_EventLED, &Test_7.DigitalInput.EventLED.ValueBool, PIN_EDGE_TOGGEL, PIN_PULLING_UP, true);
		
		GPIO_Output_AddPin(TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_5V_EN_PORT, TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_5V_EN_PIN, &Test_7.DigitalOutput.Power_5v_En.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_4V_EN_PORT, TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_4V_EN_PIN, &Test_7.DigitalOutput.Power_4v_En.ValueBool, false);
		
		TestBench.Add((uint8_t*)"HardwareVersion", &TEST_HardwareVersion);
		TestBench.Add((uint8_t*)"SoftwareVersion", &TEST_SoftwareVersion);
		TestBench.Add((uint8_t*)"GetID", &TEST_GetID);
		TestBench.Add((uint8_t*)"ID7_Power_5v_On", &TEST_ID7_Power_5v_On);			
		TestBench.Add((uint8_t*)"ID7_CheckProgram_Test", &TEST_ID7_CheckProgram_Test);	
		TestBench.Add((uint8_t*)"ID7_Power_4v_On", &TEST_ID7_Power_4v_On);
		TestBench.Add((uint8_t*)"ID7_CheckModem", &TEST_ID7_CheckModem);
		TestBench.Add((uint8_t*)"ID7_Power_4v_Off", &TEST_ID7_Power_4v_Off);
		TestBench.Add((uint8_t*)"ID7_RTC_Voltage", &TEST_ID7_RTC_Voltage);
		TestBench.Add((uint8_t*)"ID7_CheckFlash", &TEST_ID7_CheckFlash);	
		TestBench.Add((uint8_t*)"ID7_CheckEEprom", &TEST_ID7_CheckEEprom);		
		TestBench.Add((uint8_t*)"ID7_CheckOP", &TEST_ID7_CheckOP);
		TestBench.Add((uint8_t*)"ID7_CheckBuzzer", &TEST_ID7_CheckBuzzer);
		TestBench.Add((uint8_t*)"ID7_CheckLED_Red", &TEST_ID7_CheckLED_Red);
		TestBench.Add((uint8_t*)"ID7_CheckTamper", &TEST_ID7_CheckTamper);
		TestBench.Add((uint8_t*)"ID7_ResetParm", &TEST_ID7_ResetParm);
		TestBench.Add((uint8_t*)"ID7_ClearSQL", &TEST_ID7_ClearSQL);
		TestBench.Add((uint8_t*)"ID7_WriteSerial", &TEST_ID7_WriteSerial);
		TestBench.Add((uint8_t*)"ID7_WriteDateTime", &TEST_ID7_WriteDateTime);
		TestBench.Add((uint8_t*)"ID7_CheckProgram_Final", &TEST_ID7_CheckProgram_Final);
		TestBench.Add((uint8_t*)"ID7_Power_5v_Off", &TEST_ID7_Power_5v_Off);
		
		// Config user interface
		UI.Init((Media*)&Test_7.Interface);
	}
	
	os_tsk_delete_self();
}
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
