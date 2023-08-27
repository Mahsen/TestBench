//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1395/01/29
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
#include "timer.hpp"
//************************************************************ variables *****************************************************************//
#if(TIMER_ENABLE)
static bool  TIMER_Inited = false;

struct struct_TIMER
{
	
	/// متغير تعداد کانال اضافه شده
	//{
	U32 NumChannel;
	void SetNumChannel(U32 Value)
	{
		NumChannel = Value;
	}
	U32 GetNumChannel(void)
	{
		return NumChannel;
	}
	void IncreaseNumChannel(void)
	{
		NumChannel++;
	}
	void ResetNumChannel(void)
	{
		SetNumChannel(RESET);
	}
	//}
	
	struct struct_Channel
	{
		bool Enable;
		void SetEnable(bool Value)
		{
			Enable = Value;
		}
		bool GetEnable(void)
		{
			return Enable;
		}
		void ResetEnable(void)
		{
			SetEnable(false);
		}
		U64 Diff;
		void SetDiff(U64 Value)
		{
			Diff = Value;
		}
		U64 GetDiff(void)
		{
			return Diff;
		}
		void ResetDiff(void)
		{
			SetDiff(RESET);
		}
		U64 Count;
		void SetCount(U64 Value)
		{
			Count = Value;
		}
		void IncreaseCount(U64 Value)
		{
			Count += Value;
		}
		U64 GetCount(void)
		{
			return Count;
		}
		void ResetCount(void)
		{
			SetCount(RESET);
		}		
		U64 Period;
		void SetPeriod(U64 Value)
		{
			Period = Value;
		}
		U64 GetPeriod(void)
		{
			return Period;
		}
		void ResetPeriod(void)
		{
			SetPeriod(RESET);
		}
		void (*CallPeriod)(void);
		void SetCallPeriod(void (*Value)(void))
		{
			CallPeriod = Value;
		}
		void *GetCallPeriod(void)
		{
			return (void*)CallPeriod;
		}
		void RunCallPeriod(void)
		{
			if(GetCallPeriod())
			{
				(*CallPeriod)();
			}
		}
		void ResetCallPeriod(void)
		{
			SetCallPeriod(NULL);
		}
		
		struct_Channel(void)
		{
			ResetEnable();
			ResetCount();
			ResetDiff();
			ResetPeriod();
			ResetCallPeriod();
		}
		
	} Channel[TIMER_MAXCHANNELTIMER];
	
	
	/// تابع ايجاد کننده
	//{
	struct_TIMER(void)
	{
		ResetNumChannel();
	}
	//}
	
} Timer;
#endif
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
#if(TIMER_ENABLE) //INIT TIMERs
/**
 * @brief 		initialize timer
*/
void __init_Timer(void)
{

	if(!TIMER_Inited)
	{
		__uninit_Timer();
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
		
		TIM_TimeBaseInitTypeDef  TIM_InitStructure;
		NVIC_InitTypeDef         NVIC_InitStructure;
		
		TIM_InitStructure.TIM_Period = TIMER_CLOCK - 1;
		TIM_InitStructure.TIM_Prescaler = 1 - 1;
		TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		
		TIM_TimeBaseInit(TIM9, &TIM_InitStructure);

		TIM_RemapConfig(TIM9, TIM10_LSI/*TIM9_LSE*/); //LSE Hz
		//TIM_TIxExternalClockConfig(TIM9, TIM_TIxExternalCLK1Source_TI1, TIM_ICPolarity_Rising, RESET);

		NVIC_InitStructure.NVIC_IRQChannel = TIM9_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);

		TIM_Cmd(TIM9, ENABLE);
	
		TIMER_Inited = true;
	}
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(TIMER_ENABLE)
/**
 * @brief 		uninit timer
*/
void __uninit_Timer(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, DISABLE);
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(TIMER_ENABLE) //Add Timer
U8  TIMER_Add(U64 Period, void (*CallPeriod) (void))
{

	/// Check max Channel Timer
	if(Timer.GetNumChannel()<TIMER_MAXCHANNELTIMER)
	{		
		__disable_irq();
		Timer.Channel[Timer.GetNumChannel()].SetCount(RESET);
		Timer.Channel[Timer.GetNumChannel()].SetDiff(TIM_GetCounter(TIM9));
		__enable_irq();
		Timer.Channel[Timer.GetNumChannel()].SetPeriod(Period);
		Timer.Channel[Timer.GetNumChannel()].SetCallPeriod(CallPeriod);
		
		Timer.Channel[Timer.GetNumChannel()].SetEnable(true);
		Timer.IncreaseNumChannel();
	}
	else
	{
		return TIMER_CHANNELOUTOFRANGE;
	}
	
	return (Timer.GetNumChannel()-1);
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(TIMER_ENABLE) //Add Timer
void  TIMER_SetEnable(U16 Channel, bool Value)
{
	if(Channel<Timer.GetNumChannel())
	{
		Timer.Channel[Channel].SetEnable(Value);						
	}
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(TIMER_ENABLE) //Set Count Timer
void  TIMER_SetCount(U16 Channel, U64 Count)
{
	if(Channel<Timer.GetNumChannel())
	{
		if(Timer.Channel[Channel].GetEnable())
		{
			__disable_irq();
			Timer.Channel[Channel].SetCount(Count);
			Timer.Channel[Channel].SetDiff(TIM_GetCounter(TIM9));
			__enable_irq();
		}	
	}	
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(TIMER_ENABLE) //Get Count Timer
U64  TIMER_GetCount(U16 Channel)
{
	if(Channel<Timer.GetNumChannel())
	{
		if(Timer.Channel[Channel].GetEnable())
		{
			__disable_irq();
			Timer.Channel[Channel].IncreaseCount((TIM_GetCounter(TIM9) - Timer.Channel[Channel].GetDiff()) / TIMER_CLOCK_SCALE);
			Timer.Channel[Channel].ResetDiff();
			__enable_irq();
			
			return Timer.Channel[Channel].GetCount();				
		}	
	}
	
	return RESET;
}
#endif
//*************************************************************** tasks *******************************************************************//
/*
none
*/
//************************************************************** vectors ******************************************************************//
void TIM9_IRQHandler(void) __irq
{
	for(U8 Index=RESET; Index<TIMER_MAXCHANNELTIMER;Index++)
	{
		if(Timer.Channel[Index].GetEnable())
		{
			if(Timer.Channel[Index].GetCount() < 0xFFFFFFFFFFFFFFFF)
			{
				Timer.Channel[Index].IncreaseCount((TIMER_CLOCK - Timer.Channel[Index].GetDiff()) / TIMER_CLOCK_SCALE);
				Timer.Channel[Index].ResetDiff();
			}				
			if(Timer.Channel[Index].GetPeriod())
			{
				if(Timer.Channel[Index].GetCallPeriod())
				{
					if(Timer.Channel[Index].GetCount() >= Timer.Channel[Index].GetPeriod())
					{
						Timer.Channel[Index].SetCount(RESET);
						Timer.Channel[Index].ResetDiff();
						Timer.Channel[Index].RunCallPeriod();
					}
				}
			}		
		}
	}
	
	TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
}
//****************************************************************************************************************************************//










