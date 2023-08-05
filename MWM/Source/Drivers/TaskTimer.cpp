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
#include "wizards.cpp"
//************************************************************ defineds in Wizard ********************************************************//
/*
none
*/
//************************************************************ includes ******************************************************************//
#include "TaskTimer.hpp"
//************************************************************ variables *****************************************************************//
struct TaskTimer_Struct
{
	
	void (*Addr_Fun)(void);
	bool Enable;
	U32 Interval;
	U32 Interval_Conter;
	
} TaskTimer[TASKTIMER_MAX_FUN];


char Flag_Up_TaskTimer = 0;	

static U64 TaskTimer_Task_STAK[TASKTIMER_TASK_STAK_SIZE/8];
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
/**
 * @brief 		پيکره بندي اوليه اين ماژول
*/
/**
 * \image html Task-Timer-03.jpg
*/
void __init_TaskTimer(void)
{
	
	// ايجاد تابع وظيفه براي مديريت کار اين ماژول
	TaskManager_Add("TaskTimer", TaskTimer_Task, TASKTIMER_PRIORITY, &TaskTimer_Task_STAK, sizeof(TaskTimer_Task_STAK));
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		اضافه کردن تابع در اين ماژول 
 * @param[in]	Addr_Fun      تابع که بايد صدا زده شود
 * @param[in]	Enable        فعال يا غير فعال بودن بعد از اضافه شدن
 * @param[in]	Interval_ms   زمان دوره اي صدا زدن تابع معرفي شده
 * @return 		مکان قرارگيري در ساختار 
*/
signed char  TaskTimer_Add(void (*Addr_Fun)(void), bool Enable, int Interval_ms)
{
	if(Flag_Up_TaskTimer<TASKTIMER_MAX_FUN)
	{
		TaskTimer[Flag_Up_TaskTimer].Enable = Enable;
		TaskTimer[Flag_Up_TaskTimer].Addr_Fun = Addr_Fun;
		
		TaskTimer[Flag_Up_TaskTimer].Interval_Conter = 0;
		TaskTimer[Flag_Up_TaskTimer].Interval = Interval_ms;
		
		Flag_Up_TaskTimer++;
		return (Flag_Up_TaskTimer-1);
	}
	else
	{
		return -1;
	}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
* @brief 		 تغير زمان دوره اي تابع
* @param[in]	Addr_Fun_Flag_Up      نام تابعي که زمان اجرايي آن بايد تغير نمايد
* @param[in]	Addr_Fun_Flag_Up      زمان جديد
*/
void TaskTimer_Interval(void (*Addr_Fun_Flag_Up)(void), int Interval_ms)
{
	char timer_i;

	for(timer_i=0;timer_i<Flag_Up_TaskTimer;timer_i++)
	{
		if(TaskTimer[timer_i].Addr_Fun==Addr_Fun_Flag_Up)
		{
			TaskTimer[timer_i].Interval = Interval_ms;
			return;
		}
	}	
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
* @brief 		غير فعال نمودن اجراي تابع در اين ماژول
 * @param[in]	Addr_Fun_Flag_Up      نام تابعي که بايد از اجراي دوره اي متوقف گردد
*/
void TaskTimer_Disable(void (*Addr_Fun_Flag_Up)(void))
{
	char timer_i;

	for(timer_i=0;timer_i<Flag_Up_TaskTimer;timer_i++)
	{
		if(TaskTimer[timer_i].Addr_Fun==Addr_Fun_Flag_Up)
		{
			TaskTimer[timer_i].Enable=false;
			return;
		}
	}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
* @brief 		 فعال نمودن اجراي تابع در اين ماژول
 * @param[in]	Addr_Fun_Flag_Up      نام تابعي که در اجراي دوره اي بايد فعال گردد
*/
void TaskTimer_Enable(void (*Addr_Fun_Flag_Up)(void))
{
	char timer_i;

	for(timer_i=0;timer_i<Flag_Up_TaskTimer;timer_i++)
	{
		if(TaskTimer[timer_i].Addr_Fun==Addr_Fun_Flag_Up)
		{
			TaskTimer[timer_i].Enable=true;
			return;
		}
	}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
* @brief 		 خواندن وضعيت فعال يا غير فعال بودن اجراي تابع در اين ماژول
 * @param[in]	Addr_Fun_Flag_Up     تابعي که وضعيت آن بايد بررسي گردد
*/
bool TaskTimer_Read(void (*Addr_Fun_Flag_Up)(void))
{
	char timer_i;

	for(timer_i=0;timer_i<Flag_Up_TaskTimer;timer_i++)
	{
		if(TaskTimer[timer_i].Addr_Fun==Addr_Fun_Flag_Up)
		{
			return TaskTimer[timer_i].Enable;
		}
	}
	return false;
}
//*************************************************************** tasks *******************************************************************//
/**
* @brief 		 task manage TaskTimer
*/
__task void TaskTimer_Task(void)
{

	TaskManager_Delay(5 Sec);

	char timer_i;

	while(true)
	{
		for(timer_i=0;timer_i<Flag_Up_TaskTimer;timer_i++)
		{
			if(TaskTimer[timer_i].Enable==true)
			{
				TaskTimer[timer_i].Interval_Conter++;
				if(TaskTimer[timer_i].Interval_Conter>=TaskTimer[timer_i].Interval)
				{
					TaskTimer[timer_i].Interval_Conter=0;
					TaskTimer[timer_i].Addr_Fun();
				}
			}
		}
		TaskManager_Delay(1 MSec);
	}
}
//************************************************************** vectors ******************************************************************//
/*
none
*/
//****************************************************************************************************************************************//










