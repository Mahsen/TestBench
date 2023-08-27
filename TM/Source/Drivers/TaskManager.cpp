//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1395/02/29
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
#include "TaskManager.hpp"
//************************************************************ variables *****************************************************************//
long long Time_Refresh;
long long All_Proccess;

unsigned char Task_Manager_Added = 0;
struct Task_Manager_STRUCT Task_Manager [TASK_MANAGER_MAX_MANAGER];

OS_TID Task_ID_running;
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
/**
 * @brief 	پيکره بندي اوليه اين ماژول
*/
/**
 * \image html 2014-12-22_15-58-08.png
*/
void __init_TaskManager(void)
{
//	/// استفاده از تابع وقفه تايمر شماره براي محاسبه ميزان پردازش توابع وظيفه
//	//{
//	TIMER_Add(1, &TaskManager_Timing);
//	//}
	
	//Add IDLE To List Tasks
	//{
	Task_Manager[Task_Manager_Added].Task_ID = 255;
	Task_Manager[Task_Manager_Added].Name = (char*)"IDLE";
	Task_Manager[Task_Manager_Added].Proccess = RESET;

	Task_Manager_Added++;
	//}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void __ASM AsmJumpTo(U32 Address) 
{
			MOV LR, #0xFFFFFFFF    ;Reset Link Register
			LDR SP, [R0, #0]       ;Load new stack pointer address
			LDR PC, [R0, #4]       ;Load new program counter address
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void TaskManager_JumpTo(U32 Address)
{
			__disable_irq();
			SCB->VTOR = Address;
			__enable_irq();

			AsmJumpTo(Address);
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	اضافه کردن تابع وظيفه در اين ماژول 
 * @param[in]	Name         نام منحصر به فرد براي تابع وظيفه
 * @param[in]	Task         تابع وظيفه اي که مي خواهيم در اين ماژول اضافه گردد
 * @param[in]	Priority     اولويت تابع وظيفه
 * @param[in]	Stack        پشته لازم براي تابع وظيفه
 * @param[in]	Stack_Size   سايز پشته براي تابع وظيفه
 * @return 	تعداد توابع وظيفه اضافه شده در اين ماژول
*/
signed char TaskManager_Add(const char* Name, void (*Task)(void), char Priority, void *Stack, unsigned int Stack_Size)
{
	if(Task_Manager_Added >= TASK_MANAGER_MAX_MANAGER)
	{
		return TASK_MANAGER_OUTOFRANG;
	}

	Task_Manager[Task_Manager_Added].Task = Task;
	Task_Manager[Task_Manager_Added].Priority = Priority;
	Task_Manager[Task_Manager_Added].Stack = Stack;
	Task_Manager[Task_Manager_Added].Stack_Size = Stack_Size;
	
	Task_Manager[Task_Manager_Added].Task_ID = os_tsk_create_user (Task_Manager[Task_Manager_Added].Task, Task_Manager[Task_Manager_Added].Priority, Task_Manager[Task_Manager_Added].Stack, Task_Manager[Task_Manager_Added].Stack_Size);

	Task_Manager[Task_Manager_Added].Name = (char*)Name;
	Task_Manager[Task_Manager_Added].Proccess = RESET;

	Task_Manager_Added++;
	
	return Task_Manager_Added;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	حذف تابع وظيفه 
 * @param[in]	Name         نام تابع وظيفه اي که مي خواهيم حذف شود
 * @return 	وضعيت انجام
*/
signed char TaskManager_Kill(const char* Name)
{
	if(Task_Manager_Added == 1)
	{
		  return TASK_MANAGER_NOANYTASK;
	}
	
	for(unsigned char i_NumberOfTasks_Added = 0;  i_NumberOfTasks_Added<Task_Manager_Added ; i_NumberOfTasks_Added++)
	{
		if(strcmp(&Task_Manager[i_NumberOfTasks_Added].Name[0],&Name[0]) == 0)
		{
			if(rt_tsk_self() == Task_Manager[i_NumberOfTasks_Added].Task_ID)
			{
				Task_Manager[i_NumberOfTasks_Added].Name = Task_Manager[Task_Manager_Added-1].Name;
				Task_Manager[i_NumberOfTasks_Added].Proccess = RESET;
				Task_Manager[i_NumberOfTasks_Added].Task_ID = Task_Manager[Task_Manager_Added-1].Task_ID;
					
				Task_Manager_Added--;

				os_tsk_delete_self();

				//return TASK_MANAGER_SUCCESS;

			}
			else
			{
				if(os_tsk_delete(Task_Manager[i_NumberOfTasks_Added].Task_ID) == OS_R_OK)
				{
					Task_Manager[i_NumberOfTasks_Added].Name = Task_Manager[Task_Manager_Added-1].Name;
					Task_Manager[i_NumberOfTasks_Added].Proccess = RESET;
					Task_Manager[i_NumberOfTasks_Added].Task_ID = Task_Manager[Task_Manager_Added-1].Task_ID;
						
					Task_Manager_Added--;
					
					return TASK_MANAGER_SUCCESS;
				}
				else
				{
					return TASK_MANAGER_CANNOTKILL;
				}
			}
		}
	}
	
	return TASK_MANAGER_NOTFINDTASK;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	خواندن مقدار پردازش تابع وظيفه
 * @param[in]	Name         نام تابع وظيفه که مقدار پردازش آن را مي خواهيم بخوانيم
 * @return 	مقدار پردازش
*/
float TaskManager_ReadProccess(const char* Name)
{

	for(unsigned char i_NumberOfTasks_Added = 0;  i_NumberOfTasks_Added<Task_Manager_Added ; i_NumberOfTasks_Added++)
	{
		if(strcmp(&Task_Manager[i_NumberOfTasks_Added].Name[0],&Name[0]) == 0)
		{
			return Task_Manager[i_NumberOfTasks_Added].Percent_Proccess;
		}
	}
	
	return TASK_MANAGER_TASKOFF;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	ايجاد تاخير زماني
 * @param[in]	Ticks         مقدار تاخير زماني بر اساس تيک سيستم عامل
*/
void TaskManager_Delay(U32 Ticks)
{
	volatile U32 TimeDivision = (Ticks / (1 Sec));
	volatile U32 TimeRemaining = (Ticks % (1 Sec));

	for(int Time = 0; Time<TimeDivision;Time++)
	{
		os_dly_wait(1 Sec);
	}
	
	if(TimeRemaining)
	{
		os_dly_wait(TimeRemaining);
	}
}
//*************************************************************** tasks *******************************************************************//
/*
none
*/
//************************************************************** vectors ******************************************************************//
void TaskManager_Timing(void)
{

	Task_ID_running = rt_tsk_self();

	for(unsigned char i_NumberOfTasks_Added = 0;  i_NumberOfTasks_Added<Task_Manager_Added ; i_NumberOfTasks_Added++)
	{
		if(Task_Manager[i_NumberOfTasks_Added].Task_ID == Task_ID_running)
		{
			Task_Manager[i_NumberOfTasks_Added].Proccess++;
		}
	}

	All_Proccess++;

	Time_Refresh++;

	if(Time_Refresh > 10)
	{
		for(char i = 0;  i<Task_Manager_Added ; i++)
		{
			Task_Manager[i].Percent_Proccess = (((((float)Task_Manager[i].Proccess) * 100)/((float)All_Proccess)));
			Task_Manager[i].Proccess = RESET;
		}		

		All_Proccess = RESET;
		Time_Refresh = RESET;
	}


}
//****************************************************************************************************************************************//










