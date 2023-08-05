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
struct {
	struct {
		struct_ValueBool A;
	} Key;
	struct {
		struct_ValueBool A;
	} LED;
} General;
struct {	
	struct {
		struct_ValueBool Power_5v_En;
		struct_ValueBool Power_4v_En;
	} DigitalOutput;
	struct {
	} DigitalInput;
	struct {
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
	class : Media
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
} Test_56;
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
void StartTasks();
static U64 StartTasks_STAK[4096/8];
int main (void) {
	os_sys_init_user(StartTasks, 255, &StartTasks_STAK, sizeof(StartTasks_STAK));
	return 0;
}
/************************************************** Tasks *************************************************************/
__task void StartTasks(void) {

	TaskManager_Delay(20 MSec);
		
	__init_RTC();
	__init_WDT();
	__init_Timer();
	__init_GPIO();
	__init_ADC();	
	__init_UART();
	__init_PWM();
	__init_TaskTimer();
	__init_TaskManager();
	
	TestBench.Init(&TEST_GetID);
	if(strcmp((char*)TestBench.GetID(), "56") == NULL) {
		GPIO_Output_AddPin(TESTBENCH_TEST_ID56_DIGITAL_OUTPUT_POWER_5V_EN_PORT, TESTBENCH_TEST_ID56_DIGITAL_OUTPUT_POWER_5V_EN_PIN, &Test_56.DigitalOutput.Power_5v_En.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID56_DIGITAL_OUTPUT_POWER_4V_EN_PORT, TESTBENCH_TEST_ID56_DIGITAL_OUTPUT_POWER_4V_EN_PIN, &Test_56.DigitalOutput.Power_4v_En.ValueBool, false);
		
		TestBench.Add((uint8_t*)"HardwareVersion", &TEST_HardwareVersion);
		TestBench.Add((uint8_t*)"SoftwareVersion", &TEST_SoftwareVersion);
		TestBench.Add((uint8_t*)"GetID", &TEST_GetID);
		TestBench.Add((uint8_t*)"ID56_Power_5v_On", &TEST_ID56_Power_5v_On);			
		TestBench.Add((uint8_t*)"ID56_CheckProgram_Test", &TEST_ID56_CheckProgram_Test);	
		TestBench.Add((uint8_t*)"ID56_Power_4v_On", &TEST_ID56_Power_4v_On);
		TestBench.Add((uint8_t*)"ID56_CheckModem", &TEST_ID56_CheckModem);
		TestBench.Add((uint8_t*)"ID56_RTC_Voltage", &TEST_ID56_RTC_Voltage);
		TestBench.Add((uint8_t*)"ID56_CheckFlash", &TEST_ID56_CheckFlash);	
		TestBench.Add((uint8_t*)"ID56_Power_4v_Off", &TEST_ID56_Power_4v_Off);
		TestBench.Add((uint8_t*)"ID56_Power_5v_Off", &TEST_ID56_Power_5v_Off);
	}
	
	UI.Init();
	
	os_tsk_delete_self();
}
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
