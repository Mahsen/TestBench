//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1396/05/25
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
#include "wdt.hpp"
#include "gpio.hpp"
//************************************************************ variables *****************************************************************//
bool WDT_BUZZER = false;
#if(WDT_ENABLE)
bool WDT_LED = false;
static U64 WDT_Task_STAK[WDT_Task_STAK_SIZE/8];
#endif
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//

#if(WDT_ENABLE==0)
	#warning "Watch Dog Timer : Turn Off !!!"
#endif

/**
 * @brief 		initialize Watch Dog Timer
*/
void __init_WDT(void)
{
	/// بررسي وضعيت فلگ تايمر نگهبان
	//{
	if(RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
	{

	}
	else if(RCC_GetFlagStatus(RCC_FLAG_SFTRST) != RESET)
	{

	}
	else if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
		
	}
	else if(RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
	{
		
	}
	else
	{
		
	}
	//}

	/// WDT پاک نمودن فلگ 
	//{
	RCC_ClearFlag();	
	//}
	
	#if(WDT_ENABLE)
	
	/// Config WDG 
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_256);		 

	#if(WDT_LED_ENABLE)
	/// Add LED status to gpio driver
	GPIO_Output_AddPin(WDT_LED_PORT, WDT_LED_PIN, &WDT_LED, !WDT_LED_LOGIC);
	#endif

	/// Add "WDT" task with lower priority to task manager
	TaskManager_Add("WDT", WDT_Task, WDT_PRIORITY, &WDT_Task_STAK, sizeof(WDT_Task_STAK));

	#endif
	
	#if(WDT_BUZZER_ENABLE)
	/// Add BUZZER status to gpio driver
	GPIO_Output_AddPin(WDT_BUZZER_PORT, WDT_BUZZER_PIN, &WDT_BUZZER, !WDT_BUZZER_LOGIC);
	#endif

}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

/**
 * @brief 		Reset Watch Dog Timer
*/
void WDT_Reset(void)
{
#if(WDT_ENABLE)
	/// Enable WDG // 25 Sec
	IWDG_ReloadCounter();
#endif
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

void WDT_BuzzerOn(void)
{
	WDT_BUZZER = WDT_BUZZER_LOGIC;
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

void WDT_BuzzerOff(void)
{
	WDT_BUZZER = !WDT_BUZZER_LOGIC;
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

void WDT_BuzzerToggle(void)
{
	for(U8 Index=RESET; Index< 5; Index++)
	{
		WDT_BuzzerOn();	
		TaskManager_Delay(130 MSec);
		WDT_BuzzerOff();
		TaskManager_Delay(70 MSec);
	}
}

//*************************************************************** tasks *******************************************************************//
/**
 * @brief 		Task Watch Dog Timer
*/
#if(WDT_ENABLE)
__task void WDT_Task(void)
{

	/// Delays in beginning the task
	TaskManager_Delay(TASK_MANAGER_DELAYFIRSTTASK);

	WDT_BUZZER = false;
	
	U16 BlinkCycle = 0;
	U32 Time = 0;

	/// Enable WDG // 25 Sec
	IWDG_SetReload(0xFFF);
	IWDG_ReloadCounter();
	IWDG_Enable();
	
	/// Task {
	while(true)
	{
		
		Time++;
		if(Time >= 5000)
		{	
			/* Reset IWDG counter */
			WDT_Reset();
			
			Time = RESET;
		}
		
		BlinkCycle++;
		if(BlinkCycle <= 100)
		{
			WDT_LED = WDT_LED_LOGIC;
		}
		else if(BlinkCycle <= 200)
		{
			WDT_LED = !WDT_LED_LOGIC;
		}
		else if(BlinkCycle <= 400)
		{
			WDT_LED = WDT_LED_LOGIC;
		}
		else if(BlinkCycle <= 1200)
		{
			WDT_LED = !WDT_LED_LOGIC;
		}
		else
		{
			BlinkCycle = RESET;
		}

		
		/// Delay one Mili Second
		TaskManager_Delay(1 MSec);		
	}
	/// }
}
#endif
//************************************************************** vectors ******************************************************************//
void HardFault_Handler(void) __irq
{
	while (true);
}
//****************************************************************************************************************************************//
