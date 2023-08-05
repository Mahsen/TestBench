#ifndef __TASKTIMER_HPP
#define __TASKTIMER_HPP
//----------------------------------------------------------
#include "defines.h"
#include "TaskManager.hpp"
//----------------------------------------------------------
void __init_TaskTimer(void);
signed char  TaskTimer_Add(void (*Addr_Fun)(void), bool Enable, int Interval_ms);
void TaskTimer_Disable(void (*Addr_Fun_Flag_Up)(void));
void TaskTimer_Enable(void (*Addr_Fun_Flag_Up)(void));
bool TaskTimer_Read(void (*Addr_Fun_Flag_Up)(void));
void TaskTimer_Interval(void (*Addr_Fun_Flag_Up)(void), int Interval_ms);
	//----------------------------------------------------------
__task void TaskTimer_Task(void);			                   
//----------------------------------------------------------
#endif
