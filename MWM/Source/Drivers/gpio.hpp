#ifndef __GPIO_HPP
#define __GPIO_HPP
//----------------------------------------------------------
#include "defines.h"
#include "Wizards.cpp"
#include "TaskManager.hpp"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_exti.h"
#include "stm32l1xx_syscfg.h"
#include "misc.h"
//----------------------------------------------------------
#define PIN_EDGE_UP		                           0	
#define PIN_EDGE_DOWN 	                                   1
#define PIN_EDGE_TOGGEL 	                           2

#define PIN_PULLING_FLOAT                                  0
#define PIN_PULLING_DOWN 	                           1
#define PIN_PULLING_UP		                           2	
//----------------------------------------------------------
extern const GPIO_TypeDef*  GPIO_PORTSEL[];
extern const U32  GPIO_PORTCLOCK[];
//----------------------------------------------------------
struct struct_GPIO
{
	U8 NumOfOutput;
	void SetNumOfOutput(U8 Value)
	{
		NumOfOutput = Value;
	}
	U8 GetNumOfOutput(void)
	{
		return NumOfOutput;
	}
	void IncreaseNumOfOutput(void)
	{
		NumOfOutput++;
	}
	
	struct struct_Output
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
		U8 Port;
		void SetPort(U8 Value)
		{
			Port = Value;
		}
		U8 GetPort(void)
		{
			return Port;
		}
		U8 Pin;
		void SetPin(U8 Value)
		{
			Pin = Value;
		}
		U8 GetPin(void)
		{
			return Pin;
		}
		bool *AddrValue;
		void SetAddrValue(bool *Value)
		{
			AddrValue = Value;
		}
		bool *GetAddrValue(void)
		{
			return AddrValue;
		}
		bool FeedValue;
		void SetFeedValue(bool Value)
		{
			FeedValue = Value;
		}
		bool GetFeedValue(void)
		{
			return FeedValue;
		}
		
		struct_Output(void)
		{
			SetEnable(false);
			SetPort(RESET);
			SetPin (RESET);
			SetAddrValue(NULL);
			SetFeedValue(false);
		}
	} Output[GPIO_OUTPUT_MAX];
	
	U8 NumOfInput;
	void SetNumOfInput(U8 Value)
	{
		NumOfInput = Value;
	}
	U8 GetNumOfInput(void)
	{
		return NumOfInput;
	}
	void IncreaseNumOfInput(void)
	{
		NumOfInput++;
	}
	struct struct_Input
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
		U8 Port;
		void SetPort(U8 Value)
		{
			Port = Value;
		}
		U8 GetPort(void)
		{
			return Port;
		}
		U8 Pin;
		void SetPin(U8 Value)
		{
			Pin = Value;
		}
		U8 GetPin(void)
		{
			return Pin;
		}
		void (*AddrFun)(void);
		void SetAddrFun(void (*Value)(void))
		{
			AddrFun = Value;
		}
		void *GetAddrFun(void)
		{
			return (void*)AddrFun;
		}
		void RunAddrFun(void)
		{
			(*AddrFun)();
		}
		bool *AddrValue;
		void SetAddrValue(bool *Value)
		{
			AddrValue = Value;
		}
		bool *GetAddrValue(void)
		{
			return AddrValue;
		}
		bool FeedValue;
		void SetFeedValue(bool Value)
		{
			FeedValue = Value;
		}
		bool GetFeedValue(void)
		{
			return FeedValue;
		}
		U8 Edge;
		void SetEdge(U8 Value)
		{
			Edge = Value;
		}
		U8 GetEdge(void)
		{
			return Edge;
		}
		bool ByInt;
		void SetByInt(bool Value)
		{
			ByInt = Value;
		}
		bool GetByInt(void)
		{
			return ByInt;
		}
		
		struct_Input(void)
		{
			SetEnable(false);
			SetPort(RESET);
			SetPin(RESET);
			SetAddrFun(NULL);
			SetAddrValue(NULL);
			SetFeedValue(false);
			SetEdge(RESET);
			SetByInt(false);
		}		
	} Input[GPIO_INPUT_MAX];
	
	struct_GPIO(void)
	{
		SetNumOfOutput(RESET);
		SetNumOfInput(RESET);
	}
};
//----------------------------------------------------------
void __init_GPIO(void);
void __uninit_GPIO(void);

S8 GPIO_Output_AddPin(U8 Port, U8 Pin,bool * Addr_Value, bool Default);
S8 GPIO_Input_AddPin(U8 Port, U8 Pin,void (*Addr_Fun)(void), bool *Addr_Value, U8 Edge, U8 Pulling, bool ByInt);
//----------------------------------------------------------
__task void GPIO_Output_Task(void);		
__task void GPIO_Input_Task(void);	
//----------------------------------------------------------
#ifdef __cplusplus
extern "C" 
{
#endif
		__irq void EXTI0_IRQHandler(void);
		__irq void EXTI1_IRQHandler(void);
		__irq void EXTI2_IRQHandler(void);
		__irq void EXTI3_IRQHandler(void);
		__irq void EXTI4_IRQHandler(void);
		__irq void EXTI9_5_IRQHandler(void);
		__irq void EXTI15_10_IRQHandler(void);
		
#ifdef __cplusplus
}
#endif
#endif
