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
	struct { // Jac
		enum union_JackState
		{
			JackState_Off = RESET,
			JackState_Up,
			JackState_Down			
		} State;			
		void Off(void)
		{
			State = JackState_Off;
			GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I1_PORT], (1 << TESTBENCH_JAC_I1_PIN));
			GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I2_PORT], (1 << TESTBENCH_JAC_I2_PIN));
			GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I3_PORT], (1 << TESTBENCH_JAC_I3_PIN));
			GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I4_PORT], (1 << TESTBENCH_JAC_I4_PIN));
		}
		void Up(void)
		{
			Off();
			State = JackState_Up;
			GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I1_PORT], (1 << TESTBENCH_JAC_I1_PIN));
			GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I2_PORT], (1 << TESTBENCH_JAC_I2_PIN));
			GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I3_PORT], (1 << TESTBENCH_JAC_I3_PIN));
			GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I4_PORT], (1 << TESTBENCH_JAC_I4_PIN));
		}
		void Down(void)
		{
			Off();
			State = JackState_Down;
			GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I1_PORT], (1 << TESTBENCH_JAC_I1_PIN));
			GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I2_PORT], (1 << TESTBENCH_JAC_I2_PIN));
			GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I3_PORT], (1 << TESTBENCH_JAC_I3_PIN));
			GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I4_PORT], (1 << TESTBENCH_JAC_I4_PIN));
		}			
		U8 GetState(void)
		{
			return State;
		}
		U32 GetCurrent(void)
		{
			return ADC_Read(TESTBENCH_JAC_ADC_CHANNEL);
		}
	} Jac;
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
		struct_ValueBool Power_220v_Test;		
		struct_ValueBool Power_220v_En;
		struct_ValueBool Power_12v_Test;		
		struct_ValueBool Power_12v_En;	
		struct_ValueBool VBatt_Enable;
		struct_ValueBool Reset;
		struct_ValueBool ZeroCross_Gen;
	} DigitalOutput;
	struct { // DigitalInput
		struct_ValueBool Limit_Down;
		struct_ValueBool Limit_Up;
		struct_ValueBool N_Reset;
		struct_ValueBool F_Reset;
		struct_ValueBool LED_Light;
		struct_ValueBool Zero_Cross_Detect;
	} DigitalInput;
	struct { // AnalogInput
		float Get_Power_220v_Current(void) {
			volatile float Val_ADC = (float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_POWER_220V_CURRENT_CHANNEL);
			volatile float Min_ADC = Val_ADC;
			volatile float Max_ADC = Val_ADC;
			volatile float Vm = 0;
			volatile float Vrms = 0;
			
			for(int Count=RESET; Count<60; Count++)
			{
				Val_ADC = (float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_POWER_220V_CURRENT_CHANNEL);
				
				if(Val_ADC < Min_ADC)
				{
					Min_ADC = Val_ADC;
				}
				if(Val_ADC > Max_ADC)
				{
					Max_ADC = Val_ADC;
				}
				
				TaskManager_Delay(50 MSec);
			}
			
			Val_ADC = Max_ADC - Min_ADC;
			
			Vm = Val_ADC * 0.000806 * 1.47;
			Vrms = Vm * 0.707;
			
			return (Vrms * 6);
		}
		float Get_Power_12v_Current(void) {
			return ((((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_POWER_12V_CURRENT_CHANNEL) * 1.47 * 0.000806) - 2.5) * 6);
		}
		float Get_Power_12v_Voltage(void) {
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_POWER_12V_VOLTAGE_CHANNEL) * 5.7 * 0.000806);
		}
		float Get_3V3_Voltage(void) {
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_3V3_VOLTAGE_CHANNEL) * 1.47 * 0.000806);
		}
		float Get_GSM_Voltage(void) {
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_GSM_VOLTAGE_CHANNEL) * 1.47 * 0.000806);
		}
		float Get_GSM_EXT_Voltage(void) {
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_GSM_EXT_VOLTAGE_CHANNEL) * 1.47 * 0.000806);
		}
		float Get_Batt_Voltage(void) {
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_BATT_VOLTAGE_CHANNEL) * 1.1 * 0.000806);
		}
		float Get_RTC_Voltage(void) {
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_RTC_VOLTAGE_CHANNEL) * 1.1 * 0.000806);
		}
		float Get_LED_Power_Voltage(void) {
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_LED_POWER_VOLTAGE_CHANNEL) * 0.000806);
		}
		float Get_LED_RS485_Voltage(void) {
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_LED_RS485_VOLTAGE_CHANNEL) * 0.000806);
		}
		float Get_LED_NET1_Voltage(void) {
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_LED_NET1_VOLTAGE_CHANNEL) * 0.000806);
		}
		float Get_LED_NET2_Voltage(void) {
			return ((float)ADC_Read(TESTBENCH_TEST_ID7_ANALOG_INPUT_LED_NET2_VOLTAGE_CHANNEL) * 0.000806);
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
				*Length = 0;
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
	class : Media // OP
	{
		public:
			virtual bool Open() {		
				Update(9600);
				return true;
			}
			virtual bool Update(uint32_t Speed) {
				UART_UpdateSetting(TESTBENCH_TEST_ID7_MEDIA_OP_MEDIA_UART, Speed, USART_WordLength_8b, USART_Parity_No, USART_StopBits_1, true);
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
				*Length = 0;
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
	class : Media // RS485
	{
		public:
			virtual bool Open() {		
				Update(9600);
				return true;
			}
			virtual bool Update(uint32_t Speed) {
				UART_UpdateSetting(TESTBENCH_TEST_ID7_MEDIA_RS485_MEDIA_UART, Speed, 0x2000, USART_Parity_Even, USART_StopBits_1, true);
				return true;
			}
			virtual bool Send(uint8_t *Message, uint32_t Length) {		
				UART_Send_String(TESTBENCH_TEST_ID7_MEDIA_RS485_MEDIA_UART, Message, Length);
				return true;
			}
			virtual bool Receive(uint8_t *Message, uint32_t *Length) {	
				if(UART_Read_State_FIFO(TESTBENCH_TEST_ID7_MEDIA_RS485_MEDIA_UART).rxBusy()) {
					for(U32 Index=RESET; Index<100; Index++)
					{
						*Length = UART_Read_State_FIFO(TESTBENCH_TEST_ID7_MEDIA_RS485_MEDIA_UART).rx_Length;	
						TaskManager_Delay(100 MSec);
						if(*Length == UART_Read_State_FIFO(TESTBENCH_TEST_ID7_MEDIA_RS485_MEDIA_UART).rx_Length)
						{
							break;
						}
					}
					if(*Length) {
						*Length = UART_Receive_String_FIFO(TESTBENCH_TEST_ID7_MEDIA_RS485_MEDIA_UART, Message, *Length);
						return true;
					}
				}
				*Length = 0;
				return false;
			}
			virtual bool Clear() {		
				UART_Reset_Buffer_FIFO(TESTBENCH_TEST_ID7_MEDIA_RS485_MEDIA_UART);
				return true;
			}
			virtual bool Reset() {		
				return false;
			}
			virtual bool Close() {		
				return false;
			}		
	} RS485;
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
void TEST_JacInit() {
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[TESTBENCH_JAC_I1_PORT] | \
				GPIO_PORTCLOCK[TESTBENCH_JAC_I2_PORT] | \
				GPIO_PORTCLOCK[TESTBENCH_JAC_I3_PORT] | \
				GPIO_PORTCLOCK[TESTBENCH_JAC_I4_PORT] | \
				GPIO_PORTCLOCK[TESTBENCH_JAC_EN1_PORT] | \
				GPIO_PORTCLOCK[TESTBENCH_JAC_EN2_PORT], ENABLE);
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_JAC_I1_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I1_PORT], &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_JAC_I2_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I2_PORT], &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_JAC_I3_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I3_PORT], &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_JAC_I4_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_I4_PORT], &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_JAC_EN1_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_EN1_PORT], &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = (1 << TESTBENCH_JAC_EN2_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_EN2_PORT], &GPIO_InitStructure);
	
	GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_EN1_PORT], (1 << TESTBENCH_JAC_EN1_PIN));
	GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[TESTBENCH_JAC_EN2_PORT], (1 << TESTBENCH_JAC_EN2_PIN));
	
	General.Jac.Off();
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_DownStand(U8* Data)
{
	TEST_JacInit();
	
	General.Jac.Down();
	TaskManager_Delay(20 Sec);
	General.Jac.Off();
	
	sprintf((char*)Data, "OK");
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_UpStand(U8* Data)
{
	TEST_JacInit();
	
	General.Jac.Up();
	TaskManager_Delay(12 Sec);
	General.Jac.Off();
	
	sprintf((char*)Data, "OK");
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_Power_220v_On(U8* Data) {
		float Value;
	
		Test_7.DigitalOutput.Power_12v_En.Disable();
		TaskManager_Delay(1 Sec);
	
		Test_7.DigitalOutput.Power_220v_En.Enable();
		Test_7.DigitalOutput.Power_220v_Test.Disable();
		TaskManager_Delay(4 Sec);
	
		Value = Test_7.AnalogInput.Get_Power_220v_Current();
		
		General.LED.A.Disable();
		if((Value > 0) && (Value < 0.08))
		{
				Test_7.DigitalOutput.Power_220v_Test.Enable();
				General.LED.A.Enable();			
				sprintf((char*)Data, "OK");
		}
		else
		{
				Test_7.DigitalOutput.Power_220v_Test.Disable();
				Test_7.DigitalOutput.Power_220v_En.Disable();
				Test_7.DigitalOutput.Power_12v_En.Disable();
			
				sprintf((char*)Data, "%.2f Amp", Value);
		}	
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_Power_220v_Off(U8* Data) {
	
		Test_7.DigitalOutput.Power_220v_Test.Disable();
		Test_7.DigitalOutput.Power_220v_En.Disable();
		Test_7.DigitalOutput.Power_12v_En.Disable();
		General.LED.A.Disable();
	
		sprintf((char*)Data, "OK");	
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_Power_12v_On(U8* Data) {
		float Value[2];
	
		Test_7.DigitalOutput.Power_220v_Test.Disable();
		Test_7.DigitalOutput.Power_220v_En.Disable();
		TaskManager_Delay(1 Sec);
		Test_7.DigitalOutput.Power_12v_En.Enable();
		TaskManager_Delay(2 Sec);
	
		Value[0] = Test_7.AnalogInput.Get_Power_12v_Voltage();
		Value[1] = Test_7.AnalogInput.Get_Power_12v_Current();

		General.LED.A.Disable();
		if((Value[0] >= 11.8) && (Value[0] <= 12.2) && (Value[1] <= 0.6))
		{
				General.LED.A.Enable();
				sprintf((char*)Data, "OK");
		}
		else
		{
				Test_7.DigitalOutput.Power_220v_Test.Disable();
				Test_7.DigitalOutput.Power_220v_En.Disable();
				Test_7.DigitalOutput.Power_12v_En.Disable();
			
				sprintf((char*)Data, "%.2f Volt,%.2f Amp", Value[0], Value[1]);
		}	
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_Power_12v_Off(U8* Data) {
	
		Test_7.DigitalOutput.Power_220v_Test.Disable();
		Test_7.DigitalOutput.Power_220v_En.Disable();
		Test_7.DigitalOutput.Power_12v_En.Disable();
		General.LED.A.Disable();
	
		sprintf((char*)Data, "OK");
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_CheckProgram_Test(U8* Data) {
		U8 Buffer[256];
		uint32_t Length;
		
		Test_7.RS485.Open();
		TaskManager_Delay(5 Sec);
		Test_7.RS485.Reset();
		Test_7.RS485.Send((U8*)"C00", 3);
		TaskManager_Delay(3 Sec);
		memset(Buffer, NULL, sizeof(Buffer));
		Length = sizeof(Buffer);
		Test_7.RS485.Receive(Buffer, &Length);

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
void TEST_ID7_CheckProgram_Final(U8* Data) {
		U8 Buffer[256];
		uint32_t Length;
		
		Test_7.OP.Open();
		TaskManager_Delay(5 Sec);
		Test_7.OP.Reset();
		Test_7.OP.Send((U8*)"C00", 3);
		TaskManager_Delay(3 Sec);
		memset(Buffer, NULL, sizeof(Buffer));
		Length = sizeof(Buffer);
		Test_7.OP.Receive(Buffer, &Length);
	
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
void TEST_ID7_Power_3V3(U8* Data) {
	TaskManager_Delay(200 MSec);
	float Value = Test_7.AnalogInput.Get_3V3_Voltage();
	if((Value > 3.2) && (Value < 3.4))
	{
		sprintf((char*)Data, "OK");
	}
	else
	{
		sprintf((char*)Data, "%.2f Volt", Value);
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_GSM_Voltage(U8* Data) {
	float Value;
	Test_7.RS485.Open();
	
	Test_7.RS485.Send((U8*)"C51", 3);
	TaskManager_Delay(9 Sec);
	Value = Test_7.AnalogInput.Get_GSM_Voltage();
	
	Test_7.RS485.Send((U8*)"C50", 3);
	TaskManager_Delay(1 Sec);
	
	if((Value >= 3.6) && (Value <= 4.2))
	{
		sprintf((char*)Data, "OK");
	}
	else
	{
		sprintf((char*)Data, "%.2f Volt", Value);
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_GSM_EXT_Voltage(U8* Data) {
	float Value;
	Test_7.RS485.Open();
	
	Test_7.RS485.Send((U8*)"C51", 3);
	TaskManager_Delay(9 Sec);
	Value = Test_7.AnalogInput.Get_GSM_EXT_Voltage();
	
	Test_7.RS485.Send((U8*)"C50", 3);
	TaskManager_Delay(1 Sec);
	
	if((Value >= 1.7) && (Value <= 1.9))
	{
		sprintf((char*)Data, "OK");
	}
	else
	{
		sprintf((char*)Data, "%.2f Volt", Value);
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_Batt_Voltage(U8* Data) {
	TaskManager_Delay(200 MSec);
	float Value = Test_7.AnalogInput.Get_Batt_Voltage();
	
	if((Value > 2.95) && (Value < 3.5))
	{
		sprintf((char*)Data, "OK");
	}
	else
	{
		sprintf((char*)Data, "%.2f Volt", Value);
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_RTC_Voltage(U8* Data) {
	Test_7.DigitalOutput.VBatt_Enable.Enable();
	TaskManager_Delay(200 MSec);
	float Value = Test_7.AnalogInput.Get_RTC_Voltage();
	Test_7.DigitalOutput.VBatt_Enable.Disable();
	
	if((Value > 2.8) && (Value < 3.2))
	{
		sprintf((char*)Data, "OK");
	}
	else
	{
		sprintf((char*)Data, "%.2f Volt", Value);
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_CheckDataOP(U8* Data) {
	bool Pass;
	U8 Buffer[128];
	uint32_t Length;

	///
	//{
	sprintf((char*)Data, "ERROR");


	Test_7.OP.Open();
	Test_7.OP.Reset();
					
	for(U16 Index=RESET; Index<sizeof(Buffer); Index++)
	{
		Buffer[Index] = Index;		
	}
	
	Test_7.OP.Send(Buffer, sizeof(Buffer));
	
	TaskManager_Delay(3 Sec);
	
	Pass = false;
	Length = sizeof(Buffer);
	Test_7.OP.Receive(Buffer, &Length);

	if(Length)
	{
		Pass = true;
		for(U16 Index=RESET; Index<sizeof(Buffer); Index++)
		{
			if(Buffer[Index] != (0xFF-Index))
			{
				Pass = false;
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
void TEST_ID7_CheckDataRS485(U8* Data) {
	bool Pass;
	U8 Buffer[128];
	uint32_t Length;

	///
	//{
	sprintf((char*)Data, "ERROR");


	Test_7.RS485.Open();
	Test_7.RS485.Reset();
					
	for(U16 Index=RESET; Index<sizeof(Buffer); Index++)
	{
		Buffer[Index] = Index;
		
	}
	
	Test_7.RS485.Send(Buffer, sizeof(Buffer));
	
	TaskManager_Delay(3 Sec);
	
	Pass = false;
	Length = sizeof(Buffer);
	Test_7.RS485.Receive(Buffer, &Length);
	
	if(Length)
	{
		Pass = true;
		for(U16 Index=RESET; Index<sizeof(Buffer); Index++)
		{
			if(Buffer[Index] != (0xFF-Index))
			{
				Pass = false;
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
void TEST_ID7_CheckN_Reset(U8* Data) {
	sprintf((char*)Data, "ERROR");
	
	PWM_Write(5, 50, 7);
	TaskManager_Delay(200 MSec);
	if(Test_7.DigitalInput.N_Reset.Get() == true)
	{
		PWM_Write(5, 50, 10);	
		TaskManager_Delay(200 MSec);
		if(Test_7.DigitalInput.N_Reset.Get() == false)
		{			
			sprintf((char*)Data, "OK");
		}
	}

	PWM_Write(5, 50, 7);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_CheckF_Reset(U8* Data) {
	sprintf((char*)Data, "ERROR");
	
	PWM_Write(5, 50, 7);
	TaskManager_Delay(200 MSec);
	if(Test_7.DigitalInput.F_Reset.Get() == true)
	{
		PWM_Write(5, 50, 5);
		TaskManager_Delay(200 MSec);
		if(Test_7.DigitalInput.F_Reset.Get() == false)
		{
			sprintf((char*)Data, "OK");
		}
	}

	PWM_Write(5, 50, 7);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_CheckLED_Power_Voltage(U8* Data) {
	float Value;
	bool Pass;
	
	///
	//{
	Pass = true;
	sprintf((char*)Data, "OK");
	Test_7.RS485.Open();
	
	Test_7.RS485.Send((U8*)"C21", 3);
	TaskManager_Delay(1 Sec);
	Value = Test_7.AnalogInput.Get_LED_Power_Voltage();
	if(!((Value >= 1.35) && (Value <= 1.55)))
	{
			Pass = false;
	}
	
	Test_7.RS485.Send((U8*)"C20", 3);
	Test_7.RS485.Reset();
	TaskManager_Delay(1 Sec);
	Value = Test_7.AnalogInput.Get_LED_Power_Voltage();
	if(!(Value == 0))
	{
			Pass = false;
	}

	if(!Pass)
	{
		sprintf((char*)Data, "ERROR");
	}

	//}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_CheckLED_RS485_Voltage(U8* Data) {
	float Value;
	bool Pass;
	
	///
	//{
	Pass = true;
	sprintf((char*)Data, "OK");
	Test_7.RS485.Open();
	
	Test_7.RS485.Send((U8*)"C31", 3);
	TaskManager_Delay(1 Sec);
	Value = Test_7.AnalogInput.Get_LED_RS485_Voltage();
	if(!((Value >= 1.35) && (Value <= 1.55)))
	{
			Pass = false;
	}
	
	Test_7.RS485.Send((U8*)"C30", 3);
	Test_7.RS485.Reset();
	TaskManager_Delay(1 Sec);
	Value = Test_7.AnalogInput.Get_LED_RS485_Voltage();
	if(!(Value == 0))
	{
			Pass = false;
	}

	if(!Pass)
	{
		sprintf((char*)Data, "ERROR");
	}

	//}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_CheckLED_NET1_Voltage(U8* Data) {
	float Value;
	bool Pass;
	
	///
	//{
	Pass = true;
	sprintf((char*)Data, "OK");
	Test_7.RS485.Open();
	
	Test_7.RS485.Send((U8*)"C41", 3);
	TaskManager_Delay(1 Sec);
	Value = Test_7.AnalogInput.Get_LED_NET1_Voltage();
	if(!((Value >= 1.35) && (Value <= 1.55)))
	{
			Pass = false;
	}
	
	Test_7.RS485.Send((U8*)"C40", 3);
	Test_7.RS485.Reset();
	TaskManager_Delay(1 Sec);
	Value = Test_7.AnalogInput.Get_LED_NET1_Voltage();
	if(!(Value == 0))
	{
			Pass = false;
	}

	if(!Pass)
	{
		sprintf((char*)Data, "ERROR");
	}

	//}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_CheckLED_NET2_Voltage(U8* Data) {
	float Value;
	bool Pass;
	
	///
	//{
	Pass = true;
	sprintf((char*)Data, "OK");
	Test_7.RS485.Open();
	
	Test_7.RS485.Send((U8*)"C12", 3);
	TaskManager_Delay(1 Sec);
	Value = Test_7.AnalogInput.Get_LED_NET2_Voltage();
	if(!((Value >= 0.8) && (Value <= 1.4)))
	{
			Pass = false;
	}
	
	Test_7.RS485.Send((U8*)"C11", 3);
	TaskManager_Delay(1 Sec);
	Value = Test_7.AnalogInput.Get_LED_NET2_Voltage();
	if(!((Value >= 1.35) && (Value <= 1.55)))
	{
			Pass = false;
	}
	
	Test_7.RS485.Send((U8*)"C10", 3);
	Test_7.RS485.Reset();
	TaskManager_Delay(1 Sec);
	Value = Test_7.AnalogInput.Get_LED_NET2_Voltage();
	if(!(Value == 0))
	{
			Pass = false;
	}

	if(!Pass)
	{
		sprintf((char*)Data, "ERROR");
	}

	//}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_CheckFlash(U8* Data) {
		U8 Buffer[128];
		uint32_t Length;
		
		Test_7.RS485.Open();
		
		Test_7.RS485.Reset();
		Test_7.RS485.Send((U8*)"R70", 3);
		TaskManager_Delay(10 Sec);
		Length = sizeof(Buffer);	
		Test_7.RS485.Receive(Buffer, &Length);

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
void TEST_ID7_WriteDomain(U8* Data) {
		Test_7.RS485.Open();
		
		Test_7.RS485.Reset();
		Test_7.RS485.Send((U8*)"W82", 3);
		TaskManager_Delay(1 Sec);
		Test_7.RS485.Reset();
		Test_7.RS485.Send(Data, strlen((char*)Data));
		TaskManager_Delay(1 Sec);
	
		sprintf((char*)Data, "OK");	
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_WriteDateTime(U8* Data) {
		Test_7.RS485.Open();
		
		Test_7.RS485.Reset();
		Test_7.RS485.Send((U8*)"W83", 3);
		TaskManager_Delay(1 Sec);
		Test_7.RS485.Reset();
		Test_7.RS485.Send(Data, strlen((char*)Data));
		TaskManager_Delay(1 Sec);
	
		sprintf((char*)Data, "OK");
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_WriteSerial(U8* Data) {
		Test_7.RS485.Open();
		
		Test_7.RS485.Reset();
		Test_7.RS485.Send((U8*)"W80", 3);
		TaskManager_Delay(1 Sec);
		Test_7.RS485.Reset();
		Test_7.RS485.Send(Data, strlen((char*)Data));
		TaskManager_Delay(1 Sec);
	
		sprintf((char*)Data, "OK");	
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_WriteProduction_Year(U8* Data) {
		Test_7.RS485.Open();
		
		Test_7.RS485.Reset();
		Test_7.RS485.Send((U8*)"W81", 3);
		TaskManager_Delay(1 Sec);
		Test_7.RS485.Reset();
		Test_7.RS485.Send(&Data[2], 2);
		TaskManager_Delay(1 Sec);
	
		sprintf((char*)Data, "OK");
}
/*--------------------------------------------------------------------------------------------------------------------*/
void TEST_ID7_ReadPeroperty(U8* Data) {
		U8 Buffer[256];
		uint32_t Length;
		
		Test_7.RS485.Open();
		
		Test_7.RS485.Reset();
		Test_7.RS485.Send((U8*)"R80", 3);
		TaskManager_Delay(2 Sec);
		memset(Buffer, NULL, sizeof(Buffer));
		Length = sizeof(Buffer);	
		Test_7.RS485.Receive(Buffer, &Length);

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
void TEST_ID7_CheckGSM_Status(U8* Data) {
	U8 Buffer[128];
	uint32_t Length;
	
	Test_7.RS485.Open();
	
	Test_7.RS485.Send((U8*)"C61", 3);
	TaskManager_Delay(20 Sec);

	Test_7.RS485.Reset();
	Test_7.RS485.Send((U8*)"R60", 3);
	TaskManager_Delay(2 Sec);
	Length = sizeof(Buffer);	
	Test_7.RS485.Receive(Buffer, &Length);

	Test_7.RS485.Send((U8*)"C60", 3);
	TaskManager_Delay(1 Sec);
	
	Test_7.RS485.Send((U8*)"C50", 3);
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
U32 TEST_ID7_Counter_ZeroCross;
void TEST_ID7_Event_ZeroCross(void) {
	TEST_ID7_Counter_ZeroCross++;
}
void TEST_ID7_CheckZeroCross(U8* Data) {
	///
	//{
	TEST_ID7_Counter_ZeroCross = RESET;
	TaskManager_Delay(1 Sec);
	if((TEST_ID7_Counter_ZeroCross >= 95) && (TEST_ID7_Counter_ZeroCross < 120))
	{
			sprintf((char*)Data, "OK");
	}
	else
	{
			sprintf((char*)Data, "%d", TEST_ID7_Counter_ZeroCross);
	}
	//}
}
void TEST_Key_Press(void) {
	U8 Data[16];
	if(General.Key.A.Get() == false) {
		TaskManager_Delay(3 Sec);
		if(General.Key.A.Get() == false) {			
			TEST_JacInit();
			General.Jac.Down();
		}
		else {
			TEST_JacInit();
			General.Jac.Up();
		}		
	}
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
	__init_WDT();
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
		PWM_Write(5, 50, 7);

		GPIO_Output_AddPin(TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_220V_TEST_PORT, TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_220V_TEST_PIN, &Test_7.DigitalOutput.Power_220v_Test.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_220V_EN_PORT, TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_220V_EN_PIN, &Test_7.DigitalOutput.Power_220v_En.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_12V_TEST_PORT, TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_12V_TEST_PIN, &Test_7.DigitalOutput.Power_12v_Test.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_12V_EN_PORT, TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_POWER_12V_EN_PIN, &Test_7.DigitalOutput.Power_12v_En.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_VBATT_ENABLE_PORT, TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_VBATT_ENABLE_PIN, &Test_7.DigitalOutput.VBatt_Enable.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_RESET_PORT, TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_RESET_PIN, &Test_7.DigitalOutput.Reset.ValueBool, false);
		GPIO_Output_AddPin(TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_ZERO_CROSS_GEN_PORT, TESTBENCH_TEST_ID7_DIGITAL_OUTPUT_ZERO_CROSS_GEN_PIN, &Test_7.DigitalOutput.ZeroCross_Gen.ValueBool, false);

		GPIO_Input_AddPin(TESTBENCH_TEST_ID7_DIGITAL_INPUT_N_RESET_PORT, TESTBENCH_TEST_ID7_DIGITAL_INPUT_N_RESET_PIN, NULL, &Test_7.DigitalInput.N_Reset.ValueBool, PIN_EDGE_TOGGEL, PIN_PULLING_UP, false);
		GPIO_Input_AddPin(TESTBENCH_TEST_ID7_DIGITAL_INPUT_F_RESET_PORT, TESTBENCH_TEST_ID7_DIGITAL_INPUT_F_RESET_PIN, NULL, &Test_7.DigitalInput.F_Reset.ValueBool, PIN_EDGE_TOGGEL, PIN_PULLING_UP, false);
		GPIO_Input_AddPin(TESTBENCH_TEST_ID7_DIGITAL_INPUT_LED_LIGHT_PORT, TESTBENCH_TEST_ID7_DIGITAL_INPUT_LED_LIGHT_PIN, NULL, &Test_7.DigitalInput.LED_Light.ValueBool, PIN_EDGE_TOGGEL, PIN_PULLING_UP, false);
		GPIO_Input_AddPin(TESTBENCH_TEST_ID7_DIGITAL_INPUT_ZERO_CROSS_DETECT_PORT, TESTBENCH_TEST_ID7_DIGITAL_INPUT_ZERO_CROSS_DETECT_PIN, &TEST_ID7_Event_ZeroCross, &Test_7.DigitalInput.Zero_Cross_Detect.ValueBool, PIN_EDGE_DOWN, PIN_PULLING_UP, true);						

		TestBench.Add((uint8_t*)"HardwareVersion", &TEST_HardwareVersion);
		TestBench.Add((uint8_t*)"SoftwareVersion", &TEST_SoftwareVersion);
		TestBench.Add((uint8_t*)"GetID", &TEST_GetID);
		TestBench.Add((uint8_t*)"DownStand", &TEST_DownStand);
		TestBench.Add((uint8_t*)"UpStand", &TEST_UpStand);		
		TestBench.Add((uint8_t*)"ID7_Power_220v_On", &TEST_ID7_Power_220v_On);
		TestBench.Add((uint8_t*)"ID7_Power_220v_Off", &TEST_ID7_Power_220v_Off);
		TestBench.Add((uint8_t*)"ID7_Power_12v_On", &TEST_ID7_Power_12v_On);
		TestBench.Add((uint8_t*)"ID7_Power_3V3", &TEST_ID7_Power_3V3);
		TestBench.Add((uint8_t*)"ID7_Power_12v_Off", &TEST_ID7_Power_12v_Off);
		TestBench.Add((uint8_t*)"ID7_CheckProgram_Test", &TEST_ID7_CheckProgram_Test);
		TestBench.Add((uint8_t*)"ID7_GSM_Voltage", &TEST_ID7_GSM_Voltage);
		TestBench.Add((uint8_t*)"ID7_GSM_EXT_Voltage", &TEST_ID7_GSM_EXT_Voltage);
		TestBench.Add((uint8_t*)"ID7_Batt_Voltage", &TEST_ID7_Batt_Voltage);
		TestBench.Add((uint8_t*)"ID7_RTC_Voltage", &TEST_ID7_RTC_Voltage);
		TestBench.Add((uint8_t*)"ID7_CheckDataOP", &TEST_ID7_CheckDataOP);
		TestBench.Add((uint8_t*)"ID7_CheckDataRS485", &TEST_ID7_CheckDataRS485);
		TestBench.Add((uint8_t*)"ID7_CheckN_Reset", &TEST_ID7_CheckN_Reset);
		TestBench.Add((uint8_t*)"ID7_CheckF_Reset", &TEST_ID7_CheckF_Reset);
		TestBench.Add((uint8_t*)"ID7_CheckLED_Power_Voltage", &TEST_ID7_CheckLED_Power_Voltage);
		TestBench.Add((uint8_t*)"ID7_CheckLED_RS485_Voltage", &TEST_ID7_CheckLED_RS485_Voltage);
		TestBench.Add((uint8_t*)"ID7_CheckLED_NET1_Voltage", &TEST_ID7_CheckLED_NET1_Voltage);
		TestBench.Add((uint8_t*)"ID7_CheckLED_NET2_Voltage", &TEST_ID7_CheckLED_NET2_Voltage);
		TestBench.Add((uint8_t*)"ID7_CheckFlash", &TEST_ID7_CheckFlash);
		TestBench.Add((uint8_t*)"ID7_CheckGSM_Status", &TEST_ID7_CheckGSM_Status);
		TestBench.Add((uint8_t*)"ID7_WriteDomain", &TEST_ID7_WriteDomain);
		TestBench.Add((uint8_t*)"ID7_WriteDateTime", &TEST_ID7_WriteDateTime);
		TestBench.Add((uint8_t*)"ID7_WriteSerial", &TEST_ID7_WriteSerial);
		TestBench.Add((uint8_t*)"ID7_WriteProduction_Year", &TEST_ID7_WriteProduction_Year);
		TestBench.Add((uint8_t*)"ID7_ReadPeroperty", &TEST_ID7_ReadPeroperty);
		TestBench.Add((uint8_t*)"ID7_CheckProgram_Final", &TEST_ID7_CheckProgram_Final);
		TestBench.Add((uint8_t*)"ID7_CheckZeroCross", &TEST_ID7_CheckZeroCross);

		// Config user interface
		UI.Init((Media*)&Test_7.Interface);
	}
	
	while (true) {
		TEST_Key_Press();
		TaskManager_Delay(1 Sec);
	}
}
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
