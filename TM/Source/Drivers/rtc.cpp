//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1395/12/12
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
#include "rtc.hpp"
#include "TaskManager.hpp"
#include <time.h>
//************************************************************ variables *****************************************************************//
/// ساختار تابع صدا زدن براي آلارم
//{
struct struct_RTC_Event
{

	/// متغير تابع آلارم
	//{
	void (*FunAlarm)(void);
	void SetFunAlarm(void (*Value)(void))
	{
		FunAlarm = Value;
	}
	void ResetFunAlarm(void)
	{
		FunAlarm = NULL;
	}
	void RunFunAlarm(void)
	{
		if(FunAlarm)
		{
			(*FunAlarm)();
		}
	}
	//}
	
	/// متغير تابع ساعتي
	//{
	void (*Fun15Minutely)(RTC_DateTime::struct_Time Time);
	void SetFun15Minutely(void (*Value)(RTC_DateTime::struct_Time Time))
	{
		Fun15Minutely = Value;
	}
	void ResetFun15Minutely(void)
	{
		Fun15Minutely = NULL;
	}
	void RunFun15Minutely(RTC_DateTime::struct_Time Time)
	{
		if(Fun15Minutely)
		{
			(*Fun15Minutely)(Time);
		}
	}
	//}
	
	/// تابع ايجاد کننده
	//{
	struct_RTC_Event(void)
	{
		ResetFunAlarm();
		ResetFun15Minutely();
	}
	//}

} RTC_Event;
//}
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
/**
 * @brief 		initialize RTC
*/
void __init_RTC(void)
{
	RTC_DateTime DateTime;

	/* Enable the PWR clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);   

	/* Allow access to RTC */
	PWR_RTCAccessCmd(ENABLE);
	
	/* Enable the LSE OSC */
	RCC_LSEConfig(RCC_LSE_ON);     
	
	/* Wait till LSE is ready */  
	for(U32 TimeOut = 0xFFFFF; ((RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)&&(TimeOut)); TimeOut--);
	
	/* Select the RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);   
	
	/* Enable the RTC Clock */
	RCC_RTCCLKCmd(ENABLE);     
	
	/* Wait for RTC APB registers synchronisation */
	RTC_WaitForSynchro();   
	
	TaskManager_Delay(200 MSec);
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void RTC_Add15MinutelyEvent(void (*Event)(RTC_DateTime::struct_Time Time))
{
	RTC_Event.SetFun15Minutely(Event);
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void RTC_SetAlarm(void (*Event)(void), S16 Hour, S16 Minute)
{
	RTC_Event.SetFunAlarm(Event);
	
	/// تنظيم آلارم
	//{	
	RTC_AlarmTypeDef RTC_AlarmStruct;
	
	RTC_AlarmCmd(RTC_Alarm_B , DISABLE);
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
	RTC_AlarmStruct.RTC_AlarmDateWeekDay = 1;
	
	/// تنظيم زمان آلارم
	//{
	RTC_AlarmStruct.RTC_AlarmTime.RTC_Seconds = 5;
	RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes = Minute;
	RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours = Hour;

	
	RTC_AlarmStruct.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
	
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_B, &RTC_AlarmStruct);
	RTC_AlarmCmd(RTC_Alarm_B, ENABLE);
	
	RTC_ITConfig(RTC_IT_ALRB, ENABLE);
	//}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void RTC_SetDateTime_Miladi(RTC_DateTime* DateTime)
{
	RTC_SetDateTime_Miladi(DateTime->Date.GetYear(), \
		DateTime->Date.GetMonth(), \
		DateTime->Date.GetDay(), \
		DateTime->Time.GetHour(), \
		DateTime->Time.GetMinute(), \
		DateTime->Time.GetSecond());
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		Set datetime miladi
 * @param[in]	Year
 * @param[in]	Month
 * @param[in]	Day
 * @param[in]	Hour
 * @param[in]	Minute
 * @param[in]	Second
*/
void RTC_SetDateTime_Miladi(S16 Year, S16 Month, S16 Day, S16 Hour, S16 Minute, S16 Second)
{
	
	RTC_DateTypeDef  RTC_DateStructure;
	RTC_TimeTypeDef  RTC_TimeStructure;
	
	if(Year>=0)
	{
		///Set miladi year
		RTC_DateStructure.RTC_Year = Year - 2000;
	}
	
	if(Month>=0)
	{
		///Set miladi month
		RTC_DateStructure.RTC_Month = Month;
	}
	
	if(Day>=0)
	{
		///Set miladi day
		RTC_DateStructure.RTC_Date = Day;
	}
	
	if(Hour>=0)
	{
		///Set miladi hour		
		RTC_TimeStructure.RTC_Hours = Hour;
	}
	
	if(Minute>=0)
	{
		///Set miladi minute
		RTC_TimeStructure.RTC_Minutes = Minute;
	}
	
	if(Second>=0)
	{
		///Set miladi second
		RTC_TimeStructure.RTC_Seconds = Second;
	}

	RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Friday;
	RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure);
	RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
	
	/// تنظيم ثانويه آلارم
	//{
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);
	RTC_AlarmTypeDef RTC_AlarmStruct;
	
	RTC_AlarmCmd(RTC_Alarm_A , DISABLE);
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
	RTC_AlarmStruct.RTC_AlarmDateWeekDay = 1;
	
	/// محاسبه براي 15 دقيقه بعد
	//{
	RTC_AlarmStruct.RTC_AlarmTime.RTC_Seconds = 0;
	if(Minute < 15)
	{
		RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes = 15;
		RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours = Hour;
	}
	else
	{
		RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes = 0;
		RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours = RTC_INCREASEHOUR(Hour);
	}
	//}

	RTC_AlarmStruct.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
	
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStruct);
	RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
	//}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void RTC_SetDateTime_Shamsi(RTC_DateTime* DateTime)
{
	RTC_SetDateTime_Shamsi(DateTime->Date.GetYear(), \
		DateTime->Date.GetMonth(), \
		DateTime->Date.GetDay(), \
		DateTime->Time.GetHour(), \
		DateTime->Time.GetMinute(), \
		DateTime->Time.GetSecond());
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		Set datetime shamsi
 * @param[in]	Year
 * @param[in]	Month
 * @param[in]	Day
 * @param[in]	Hour
 * @param[in]	Minute
 * @param[in]	Second
*/
void RTC_SetDateTime_Shamsi(S16 Year, S16 Month, S16 Day, S16 Hour, S16 Minute, S16 Second)
{
	RTC_DateTime b_DateTime;

	b_DateTime.Date.SetYear(Year - 1300);
	b_DateTime.Date.SetMonth(Month);
	b_DateTime.Date.SetDay(Day);
	
	b_DateTime.Time.SetSecond(Second);
	b_DateTime.Time.SetMinute(Minute);
	b_DateTime.Time.SetHour(Hour);
	
	/// Convert Shamsi to Miladi because incoming shamsi But system works with miladi
	DATETYPE_Shm2Milcv(&b_DateTime);
	
	b_DateTime.Date.SetYear(b_DateTime.Date.GetYear() + 2000);
	
	RTC_SetDateTime_Miladi(b_DateTime.Date.GetYear(), \
				b_DateTime.Date.GetMonth(), \
				b_DateTime.Date.GetDay(), \
				b_DateTime.Time.GetHour(), \
				b_DateTime.Time.GetMinute(), \
				b_DateTime.Time.GetSecond());
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		Get datetime miladi
 * @return 		struct rtc
*/
RTC_DateTime RTC_GetDateTime_Miladi(void)
{
	RTC_DateTime b_DateTime;
	RTC_DateTypeDef  RTC_DateStructure;
	RTC_TimeTypeDef  RTC_TimeStructure;

	/// Get current miladi date and time
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);	

	b_DateTime.Time.SetSecond(RTC_TimeStructure.RTC_Seconds);
	b_DateTime.Time.SetMinute(RTC_TimeStructure.RTC_Minutes);
	b_DateTime.Time.SetHour(RTC_TimeStructure.RTC_Hours);

	b_DateTime.Date.SetDay(RTC_DateStructure.RTC_Date);
	b_DateTime.Date.SetMonth(RTC_DateStructure.RTC_Month);
	b_DateTime.Date.SetYear(RTC_DateStructure.RTC_Year + 2000);

	return b_DateTime;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		Get datetime shamsi
 * @return 		struct rtc
*/
RTC_DateTime RTC_GetDateTime_Shamsi(void)
{
	
	/// Get current miladi date and time
	RTC_DateTime b_DateTime = RTC_GetDateTime_Miladi();
	b_DateTime.Date.SetYear(b_DateTime.Date.GetYear() - 2000);
	
	/// Convert miladi to shamsi
	DATETYPE_Mil2Shmcv(&b_DateTime);
	
	b_DateTime.Date.SetYear(b_DateTime.Date.GetYear() + 1300);

	return b_DateTime;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
U64 RTC_DateTimeTo40Bit(RTC_DateTime *DateTime)
{
	return RTC_DateTimeTo40Bit(DateTime->Date.GetYear(), \
					DateTime->Date.GetMonth(), \
					DateTime->Date.GetDay(), \
					DateTime->Time.GetHour(), \
					DateTime->Time.GetMinute(), \
					DateTime->Time.GetSecond());
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
U64 RTC_DateTimeTo40Bit(S16 Year, S16 Month, S16 Day, S16 Hour, S16 Minute, S16 Second)
{
	U64 _40Bit = RESET;

	_40Bit |= ((((U64)(Year & 0x3FFF)) << 26) | \
			(((U64)(Month & 0xF)) << 22) | \
			(((U64)(Day & 0x1F)) << 17) | \
			(((U64)(Hour & 0x1F)) << 12) | \
			(((U64)(Minute & 0x3F)) << 6) | \
			(((U64)(Second & 0x3F)) << 0));
	
	_40Bit &= 0xFFFFFFFFFF;
	
	return _40Bit;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
RTC_DateTime RTC_40BitToDateTime(U64 _40Bit)
{
	RTC_DateTime DateTime;

	DateTime.Date.SetYear((_40Bit >> 26) & 0x3FFF);
	DateTime.Date.SetMonth((_40Bit >> 22) & 0xF);
	DateTime.Date.SetDay((_40Bit >> 17) & 0x1F);
	
	DateTime.Time.SetHour((_40Bit >> 12) & 0x1F);
	DateTime.Time.SetMinute((_40Bit >> 6) & 0x3F);
	DateTime.Time.SetSecond((_40Bit >> 0) & 0x3F);
	
	return DateTime;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void RTC_WriteBackUp(U8 *Data, U32 OffSet, U32 Length)
{
	U32 Block = RESET;
	U32 OffSetBlock = RESET;
	
	OffSetBlock = OffSet % 4;
	OffSet /= 4;
	
	for(U16 Index=RESET; Index<Length ;)
	{
		Block = RTC_ReadBackupRegister(OffSet);
		for(; ((OffSetBlock<4) && (Index<Length)); OffSetBlock++, Index++)
		{
			Block &= ~(0xFF << (OffSetBlock*8));
			Block |= ((Data[Index] & 0xFF) << (OffSetBlock*8));
		}	
		RTC_WriteBackupRegister(OffSet, Block);
		
		OffSetBlock = RESET;
		OffSet++;
	}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void RTC_ReadBackUp(U8 *Data, U32 OffSet, U32 Length)
{
	U32 Block = RESET;
	U32 OffSetBlock = RESET;
	
	OffSetBlock = OffSet % 4;
	OffSet /= 4;
	
	for(U16 Index=RESET; Index<Length ;)
	{
		Block = RTC_ReadBackupRegister(OffSet);
		for(; ((OffSetBlock<4) && (Index<Length)); OffSetBlock++, Index++)
		{
			Data[Index] = (Block >> (OffSetBlock*8)) & 0xFF;
		}	

		OffSetBlock = RESET;
		OffSet++;
	}
}
//*************************************************************** tasks *******************************************************************//
/*
none
*/
//************************************************************** vectors ******************************************************************//
void RTC_Alarm_IRQHandler(void) __irq
{
	RTC_TimeTypeDef  RTC_TimeStructure;
	RTC_DateTime::struct_Time Time;
	
	if(RTC_GetITStatus(RTC_IT_ALRA))
	{
		
		RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
		Time.SetHour(RTC_TimeStructure.RTC_Hours);
		Time.SetMinute(RTC_TimeStructure.RTC_Minutes);
		Time.SetSecond(RTC_TimeStructure.RTC_Seconds);

		/// تنظيم ثانويه آلارم
		//{
		RTC_ITConfig(RTC_IT_ALRA, ENABLE);
		RTC_AlarmTypeDef RTC_AlarmStruct;
		
		RTC_AlarmCmd(RTC_Alarm_A , DISABLE);
		RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
		RTC_AlarmStruct.RTC_AlarmDateWeekDay = 1;
		
		/// محاسبه براي 15 دقيقه بعد
		//{
		RTC_AlarmStruct.RTC_AlarmTime.RTC_Seconds = 0;
		if(Time.GetMinute() < 15)
		{
			RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes = 15;
			RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours = Time.GetHour();
		}
		else if(Time.GetMinute() < 30)
		{
			RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes = 30;
			RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours = Time.GetHour();
		}
		else if(Time.GetMinute() < 45)
		{
			RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes = 45;
			RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours = Time.GetHour();
		}
		else
		{
			RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes = 0;
			RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours = RTC_INCREASEHOUR(Time.GetHour());
		}
		//}

		RTC_AlarmStruct.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
		
		RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStruct);
		RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
		//}

		/// صدا زدن تابع ساعتي
		//{
		RTC_Event.RunFun15Minutely(Time);
		//}
		
		/// RTC_IT_ALRA پاک کردن فلگ وقفه
		//{		
		RTC_ClearITPendingBit(RTC_IT_ALRA);		
		//}
	}
	else
	{
		
		/// صدا زدن تابع آلارم
		//{
		RTC_Event.RunFunAlarm();
		//}
		
		/// RTC_IT_ALRB پاک کردن فلگ وقفه
		//{		
		RTC_ClearITPendingBit(RTC_IT_ALRB);		
		//}
	}
	
	
	/// EXTI_Line17 پاک کردن فلگ وقفه
	//{	
	EXTI_ClearFlag(EXTI_Line17);
	EXTI_ClearITPendingBit(EXTI_Line17);
	//}
	
}
//****************************************************************************************************************************************//

