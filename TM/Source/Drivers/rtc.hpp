#ifndef __RTC_HPP
#define __RTC_HPP
//----------------------------------------------------------
#include "defines.h"
#include "stm32l1xx_rtc.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_pwr.h"
#include "stm32l1xx_exti.h"
#include "DateType.hpp"
#include "debug.hpp"
////----------------------------------------------------------
#define RTC___RTCCLK                                    32768
#define RTC_INCREASEHOUR(x)                             ((x)<23)?((x)+1):0
//------------------------------------------------------------
/// ساختار تاريخ و ساعت
//{
struct RTC_DateTime
{
	struct struct_Date
	{
		S32 Day;
		S32 GetDay(void)
		{
			return Day;
		}
		void SetDay(S32 Value)
		{
			Day = Value;
		}
		S32 Month;
		S32 GetMonth(void)
		{
			return Month;
		}
		void SetMonth(S32 Value)
		{
			Month = Value;
		}
		S32 Year;
		S32 GetYear(void)
		{
			return Year;
		}
		void SetYear(S32 Value)
		{
			Year = Value;
		}
		
		struct_Date(void)
		{

		}
		
		struct_Date(bool Reset)
		{
			SetDay(RESET);
			SetMonth(RESET);
			SetYear(RESET);
		}
	} Date;

	struct struct_Time
	{
		S32 Second;
		S32 GetSecond(void)
		{
			return Second;
		}
		void SetSecond(S32 Value)
		{
			Second = Value;
		}
		S32 Minute;
		S32 GetMinute(void)
		{
			return Minute;
		}
		void SetMinute(S32 Value)
		{
			Minute = Value;
		}
		S32 Hour;
		S32 GetHour(void)
		{
			return Hour;
		}
		void SetHour(S32 Value)
		{
			Hour = Value;
		}

		struct_Time(void)
		{
			
		}
		
		struct_Time(bool Reset)
		{
			SetSecond(RESET);
			SetMinute(RESET);
			SetHour(RESET);
		}
	} Time;
};
//}
//----------------------------------------------------------
void __init_RTC(void);

void RTC_SetDateTime_Miladi(RTC_DateTime* DateTime);
void RTC_SetDateTime_Miladi(S16 Year, S16 Month, S16 Day, S16 Hour, S16 Minute, S16 Second);
void RTC_SetDateTime_Shamsi(RTC_DateTime* DateTime);
void RTC_SetDateTime_Shamsi(S16 Year, S16 Month, S16 Day, S16 Hour, S16 Minute, S16 Second);

RTC_DateTime RTC_GetDateTime_Miladi(void);
RTC_DateTime RTC_GetDateTime_Shamsi(void);

U64 RTC_DateTimeTo40Bit(RTC_DateTime *DateTime);
U64 RTC_DateTimeTo40Bit(S16 Year, S16 Month, S16 Day, S16 Hour, S16 Minute, S16 Second);
RTC_DateTime RTC_40BitToDateTime(U64 _40Bit);

U64 RTC_DistanceMiladiOfSecond(RTC_DateTime* Old, RTC_DateTime* New);

void RTC_WriteBackUp(U8 *Data, U32 OffSet, U32 Length);
void RTC_ReadBackUp(U8 *Data, U32 OffSet, U32 Length);

void RTC_Add15MinutelyEvent(void (*Event)(RTC_DateTime::struct_Time Time));

void RTC_SetAlarm(void (*Event)(void), S16 Hour, S16 Minute);

#ifdef __cplusplus
extern "C" 
{
#endif
	__irq void RTC_Alarm_IRQHandler(void);
		
#ifdef __cplusplus
}
#endif
//----------------------------------------------------------
#endif
