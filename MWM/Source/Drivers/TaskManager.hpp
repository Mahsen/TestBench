#ifndef __TASK_MANAGER_HPP
#define __TASK_MANAGER_HPP
//----------------------------------------------------------
#include "defines.h"
#include "timer.hpp"
//----------------------------------------------------------
#define TASK_MANAGER_MAX_MANAGER            14
#define TASK_MANAGER_OS_TICK                1000  //OS_TICK in "RTX_Conf_CM.c" 

#define OneUnic                       			1
#define MSec   				                      *1000/TASK_MANAGER_OS_TICK
#define Sec                         	      *1000000/TASK_MANAGER_OS_TICK

#define TASK_MANAGER_DELAYFIRSTTASK         20 MSec

#define TASK_MANAGER_SUCCESS                0
#define TASK_MANAGER_TASKOFF                -1
#define TASK_MANAGER_NOANYTASK              1
#define TASK_MANAGER_NOTFINDTASK            2
#define TASK_MANAGER_CANNOTKILL             3
#define TASK_MANAGER_OUTOFRANG              4

#define TASK_MANAGER_MUTEXWAIT(x)           while(x){TaskManager_Delay(OneUnic);};x=true
#define TASK_MANAGER_MUTEXRELEASE(x)        x=false

#define TASK_MANAGER_LOOPUNTIL(x)           for(U32 LOOPUNTIL_time=0;(LOOPUNTIL_time<0xFFFFF)&&(x);LOOPUNTIL_time++){TaskManager_Delay(OneUnic);}
#define TASK_MANAGER_WHILEUNTIL(x)          for(U32 LOOPUNTIL_time=0;(LOOPUNTIL_time<0xFFFFF)&&(x);LOOPUNTIL_time++){}
//----------------------------------------------------------
struct Task_Manager_STRUCT
{
	char *Name;
	  
	OS_TID Task_ID;
	void (*Task)(void);
	char Priority;
	void *Stack;
	unsigned int Stack_Size;
	long Proccess;
	float Percent_Proccess;
		
};

extern unsigned char Task_Manager_Added;
extern struct Task_Manager_STRUCT Task_Manager [TASK_MANAGER_MAX_MANAGER];
//----------------------------------------------------------
void __init_TaskManager(void);
void TaskManager_JumpTo(U32 Address);
signed char TaskManager_Add(const char* Name, void (*Task)(void), char Priority, void *Stack, unsigned int Stack_Size);
signed char TaskManager_Kill(const char* Name);
float TaskManager_ReadProccess(const char* Name);
void TaskManager_Delay(U32 Ticks);
void TaskManager_Timing(void);
//----------------------------------------------------------
#endif
