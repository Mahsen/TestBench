#ifndef __DATETYPE_HPP
#define __DATETYPE_HPP
//----------------------------------------------------------
#include "defines.h"
#include "rtc.hpp"
//----------------------------------------------------------
void DATETYPE_Mil2Shmcv(struct RTC_DateTime *rtc);
void DATETYPE_Shm2Milcv(struct RTC_DateTime *rtc);

bool DATETYPE_ApplyDayLightSavingShamsi(RTC_DateTime *Date_time);

bool DATETYPE_IsLeep(U16 Year);

bool DATETYPE_DetectLastDayOfMonth(RTC_DateTime *Date_time);
bool DATETYPE_DetectLastDayOfWeek(RTC_DateTime *Date_time);
//----------------------------------------------------------
#endif
