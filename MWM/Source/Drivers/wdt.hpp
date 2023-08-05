#ifndef __WDT_HPP
#define __WDT_HPP
//----------------------------------------------------------
#include "defines.h"
#include "TaskManager.hpp"
#include "stm32l1xx_iwdg.h"
//----------------------------------------------------------
#ifdef __cplusplus
extern "C" 
{
#endif
	__irq void HardFault_Handler(void); /// در startup_stm32l1xx_hd.s قرار دارد
#ifdef __cplusplus
}
#endif
//----------------------------------------------------------
#define   WDT_TIMEOUTPROCESS   1200
#define   WDT_TRYWHATHAPPEN    5
//----------------------------------------------------------
void __init_WDT(void);
void __uninit_WDT(void);
void WDT_Reset(void);
void WDT_BuzzerOn(void);
void WDT_BuzzerOff(void);
void WDT_BuzzerToggle(void);
//----------------------------------------------------------		
__task void WDT_Task(void);
//----------------------------------------------------------
#endif
