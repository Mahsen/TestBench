//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1396/03/06
Programmer : Mohammad Lotfi
Site : http://www.mahsen.ir
Tel : +989124662703
*/
//************************************************************* Warning *****************************************************************//
/*
none
*/
//************************************************************* Wizard ******************************************************************//
/*
none
*/
//************************************************************ defineds ******************************************************************//
/*
none
*/
//************************************************************ includes ******************************************************************//
#include "DateType.hpp"
//************************************************************ variables *****************************************************************//
const U8 shmtable[6][12]={
        {11,10,10,9,9,9,8,9,9,10,11,9       },
        {20,20,21,21,22,22,22,22,21,21,20,19},
        {11,10,10,9,9,9,8,9,9,10,11,10      },
        {20,20,21,21,22,22,22,22,21,21,20,19},
        {12,11,11,10,10,10,9,10,10,11,12,10 },
        {19,19,20,20,21,21,21,21,20,20,19,18}};

 const U8 miltable[6][12]={
        {20,19,19,19,20,20,21,21,21,21,20,20},
        {10,11,10,12,11,11,10,10,10,9,10,10 },
        {19,18,20,20,21,21,22,22,22,22,21,21},
        {11,12,10,11,10,10,9,9,9,8,9,9      },
        {20,19,20,20,21,21,22,22,22,22,21,21},
        {10,11,9,11,10,10,9,9,9,8,9,9       }};
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		  Convert Miladi to Shamsi
 * @param[in]	  rtc struct of rtc Miladi
 * @param[out]	rtc struct of rtc	Shamsi	
*/		
void DATETYPE_Mil2Shmcv(struct RTC_DateTime *rtc)
{
	//unsigned char ym,mm,dm;
	U8 k,t1,t2;
		 // rtc->year -= 2000; 
	k = rtc->Date.GetYear() % 4;
	
	if(k == 3)
	{		
		k = 2;
	}
	
	k *= 2;
	t1 = miltable[k][rtc->Date.GetMonth() - 1];
	t2 = miltable[k + 1][rtc->Date.GetMonth() - 1];
	
	if(rtc->Date.GetMonth() < 3 || (rtc->Date.GetMonth() == 3 && rtc->Date.GetDay() <= miltable[k][rtc->Date.GetMonth() - 1]))
	{
		rtc->Date.SetYear(rtc->Date.GetYear()+78); //1378;
	}
	else
	{
		rtc->Date.SetYear(rtc->Date.GetYear()+79); //1379;
	}
	
	if(rtc->Date.GetDay() <= t1)
	{
		rtc->Date.SetDay(rtc->Date.GetDay() + t2);
		rtc->Date.SetMonth((rtc->Date.GetMonth() + 8) % 12 + 1);
	}
	else
	{
		rtc->Date.SetDay(rtc->Date.GetDay() - t1);
		rtc->Date.SetMonth((rtc->Date.GetMonth() + 9) % 12 + 1);
	}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		  Convert Shamsi to Miladi
 * @param[in]	  rtc struct of rtc Shamsi
 * @param[out]	rtc struct of rtc	Miladi	
*/		
void DATETYPE_Shm2Milcv(struct RTC_DateTime *rtc)
{
		U8 k,t1,t2;
		//rtc->year -= 1300;
		k = rtc->Date.GetYear() % 4;
	
		if(k == 0)
		{	
			k = 2;
		}	
		else
		{	
			k = k + k;
		}
		
		t1 = shmtable[k - 2][rtc->Date.GetMonth() - 1];
		t2 = shmtable[k - 1][rtc->Date.GetMonth() - 1];
		
		if(rtc->Date.GetMonth() < 10 || (rtc->Date.GetMonth() == 10 && rtc->Date.GetDay() <= shmtable[k - 2][rtc->Date.GetMonth() - 1]))
		{
			rtc->Date.SetYear(rtc->Date.GetYear()-79);           //100-21=79         //rtc->year += 21;//1921;
		}
		else
		{
			rtc->Date.SetYear(rtc->Date.GetYear()-78);         //100-22=78         //rtc->year += 22;//1922;
		}
		
		if(rtc->Date.GetDay() <= t1)
		{
			rtc->Date.SetDay(rtc->Date.GetDay() + t2);
			rtc->Date.SetMonth((rtc->Date.GetMonth() + 1) % 12 + 1);
		}
		else
		{
			rtc->Date.SetDay(rtc->Date.GetDay() - t1);
			rtc->Date.SetMonth((rtc->Date.GetMonth() + 2) % 12 + 1);
		}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	 Apply DayLight Saving Shamsi
 * @param[in]	 rtc struct of rtc Shamsi
 * @param[out]	 if apply day light saving return true and change input pointer
*/
bool DATETYPE_ApplyDayLightSavingShamsi(RTC_DateTime *Date_time)
{
	static bool ChangeIsValid = true;

	if(Date_time->Date.GetMonth()==1 && \
		Date_time->Date.GetDay()==1 && \
		Date_time->Time.GetHour()==0) //-- Farvardin 1st Clock Goes On Hour Ahead
	{
		Date_time->Time.SetHour(1);
		return true;
	}
	else if(Date_time->Date.GetMonth()==6 && \
		((Date_time->Date.GetDay()==31) || (Date_time->Date.GetDay()==30)))
	{
		if(ChangeIsValid && \
			Date_time->Date.GetDay()==31)
		{
			if(Date_time->Time.GetHour()==0)
			{
				ChangeIsValid = false;
				Date_time->Time.SetHour(23);
				Date_time->Date.SetDay(30);

				return true;
			}
		}
	}
	else
	{
		ChangeIsValid = true;
	}
	
	return false;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
bool DATETYPE_IsLeep(U16 Year)
{
	int a = 0 , b = 1309;
	for (int i = 1309; i<=Year-4; i+=4)
	{
		b+=4;
		a+=1;
		
		if (a%8==0)
		{
			b++;
		}
	}

	return (Year==b);
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	 Detect The Last Day Of Month
 * @param[in]	 rtc struct of rtc Shamsi
 * @param[out]	 if today is the last day of month return true else return false
*/
bool DATETYPE_DetectLastDayOfMonth(RTC_DateTime *Date_time)
{
	if(Date_time->Date.GetMonth() <= 6)
	{
		if(Date_time->Date.GetDay() == 31)
		{
			return true;
		}
	}
	else if( (Date_time->Date.GetMonth()>=7) && (Date_time->Date.GetMonth()<=11) )
	{
		if(Date_time->Date.GetDay() == 30)
		{
			return true;
		}
	}
	else // Montrh of Esfand
	{
		if(DATETYPE_IsLeep(Date_time->Date.GetYear()))
		{
			if(Date_time->Date.GetDay() == 30)
			{
				return true;
			}
		}
		else 
		{
			if(Date_time->Date.GetDay() == 29)
			{
				return true;
			}
		}
	}
	return false;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	 Detect The Last Day Of Week
 * @param[in]	 rtc struct of rtc Shamsi
 * @param[out]	 if today is the last day of month return true else return false
*/
bool DATETYPE_DetectLastDayOfWeek(RTC_DateTime *Date_time)
{
	U16 h0 = 1;
	U16 week = RESET;
	
	for(U16 Year = 92; (Year <= Date_time->Date.GetYear()); Year++)
	{
		if(DATETYPE_IsLeep(Year))
		{
			h0++;
		}
		h0++;
	}
	
	if(Date_time->Date.GetMonth() <= 7)
	{
		week = (3 * Date_time->Date.GetMonth()) + Date_time->Date.GetDay() + h0;
	}
	else if(Date_time->Date.GetMonth() >= 8)
	{
		week = (2 * Date_time->Date.GetMonth()) + Date_time->Date.GetDay() + h0;
	}
	
	return ((week%7)==6);
}
//*************************************************************** tasks *******************************************************************//
/*
none
*/
//************************************************************** vectors ******************************************************************//
/*
none
*/
//****************************************************************************************************************************************//




