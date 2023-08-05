#ifndef __TIMER_HPP
#define __TIMER_HPP
//----------------------------------------------------------
#include "defines.h"
#include "misc.h"
#include "stm32l1xx_tim.h"
#include "stm32l1xx_rcc.h"
//----------------------------------------------------------
#define   TIMER_MAXCHANNELTIMER                            5
#define   TIMER_CHANNELOUTOFRANGE                          0xFF
#define   TIMER_CLOCK                                      60000/*32768*/
#define   TIMER_CLOCK_SCALE                                60.000/*32.768*/
//----------------------------------------------------------
#ifdef __cplusplus
extern "C" 
{
#endif
__irq void TIM9_IRQHandler(void);
	#ifdef __cplusplus
}
#endif
//----------------------------------------------------------
void __init_Timer(void);
void __uninit_Timer(void);

U8    TIMER_Add(U64 Period, void (*CallPeriod) (void));
void  TIMER_SetEnable(U16 Channel, bool Value);
void  TIMER_SetCount(U16 Channel, U64 Value);
U64   TIMER_GetCount(U16 Channel);
//----------------------------------------------------------
#endif
