//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1396/12/23
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
//************************************************************ defineds in Wizard ********************************************************//
/*
none
*/	
//************************************************************ includes ******************************************************************//
#include "segment.hpp"
//************************************************************ variables *****************************************************************//
const U8 Segment_Numberic[] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47};
const U8 Segment_Demo1[] = {0x01, 0x20, 0x40, 0x02, 0x01, 0x10, 0x08, 0x04};
const U8 Segment_Demo2[] = {0x01, 0x02, 0x40, 0x20, 0x01, 0x04, 0x08, 0x10};
U8 Segment_BufferBlink[2];
U16 Segment_Demo = RESET;
bool Segment_BlinkFeed = false;
//************************************************************* objects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
void __init_Segment(void)
{	
	TaskTimer_Add(&Segment_Blink, false, 100);
	
	Segment_WriteString((U8*)"  ", false, 20000);
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void Segment_Blink(void)
{
	static U8 Blink = true;
	
	Segment_Demo--;
	if(Segment_Demo > 8)
	{
		if(Segment_BlinkFeed)
		{
			if((Segment_Demo % 5) == 0)
			{
				if(Blink)
				{
					Segment_WriteString(Segment_BufferBlink, true);
					Blink = false;
				}
				else
				{
					GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_ENABLE_PORT], (1 << SEGMENT_ENABLE_PIN));
					Blink = true;
				}
			}
		}
	}
	else
	{
		GPIO_InitTypeDef  GPIO_InitStructure;

		U8 Buffer[2];
		Buffer[0] = Segment_Demo1[Segment_Demo];
		Buffer[1] = Segment_Demo2[Segment_Demo];
		
		RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[SEGMENT_SERIAL_PORT] | \
					GPIO_PORTCLOCK[SEGMENT_ENABLE_PORT] | \
					GPIO_PORTCLOCK[SEGMENT_LOADRIGHT_PORT] | \
					GPIO_PORTCLOCK[SEGMENT_LOADLEFT_PORT] | \
					GPIO_PORTCLOCK[SEGMENT_CLOCK_PORT], ENABLE);
		
		// Configure output SEGMENT_SERIAL
		//{
		GPIO_InitStructure.GPIO_Pin = (1 << SEGMENT_SERIAL_PIN);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_SERIAL_PORT], &GPIO_InitStructure);
		//}
		
		// Configure output SEGMENT_ENABLE
		//{
		GPIO_InitStructure.GPIO_Pin = (1 << SEGMENT_ENABLE_PIN);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_ENABLE_PORT], &GPIO_InitStructure);
		//}
		
		// Configure output SEGMENT_LOADLEFT
		//{
		GPIO_InitStructure.GPIO_Pin = (1 << SEGMENT_LOADLEFT_PIN);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADLEFT_PORT], &GPIO_InitStructure);
		//}
		
		// Configure output SEGMENT_LOADRIGHT
		//{
		GPIO_InitStructure.GPIO_Pin = (1 << SEGMENT_LOADRIGHT_PIN);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADRIGHT_PORT], &GPIO_InitStructure);
		//}
		
		// Configure output SEGMENT_CLOCK
		//{
		GPIO_InitStructure.GPIO_Pin = (1 << SEGMENT_CLOCK_PIN);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], &GPIO_InitStructure);
		//}

		GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADLEFT_PORT], (1 << SEGMENT_LOADLEFT_PIN));	
		GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADRIGHT_PORT], (1 << SEGMENT_LOADRIGHT_PIN));
		
		GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], (1 << SEGMENT_CLOCK_PIN));
		TaskManager_Delay(1 MSec);		
		for(S8 Index=7; Index>=0; Index--)
		{
			if(Buffer[0] & (1 << Index))
			{			
				GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_SERIAL_PORT], (1 << SEGMENT_SERIAL_PIN));
			}
			else
			{
				GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_SERIAL_PORT], (1 << SEGMENT_SERIAL_PIN));
			}
			
			GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], (1 << SEGMENT_CLOCK_PIN));
			TaskManager_Delay(2 MSec);
			GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], (1 << SEGMENT_CLOCK_PIN));
		}	
		GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADLEFT_PORT], (1 << SEGMENT_LOADLEFT_PIN));
		TaskManager_Delay(2 MSec);
		GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADLEFT_PORT], (1 << SEGMENT_LOADLEFT_PIN));
		
		GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], (1 << SEGMENT_CLOCK_PIN));
		TaskManager_Delay(1 MSec);	
		for(S8 Index=7; Index>=0; Index--)
		{
			if(Buffer[1] & (1 << Index))
			{			
				GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_SERIAL_PORT], (1 << SEGMENT_SERIAL_PIN));
			}
			else
			{
				GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_SERIAL_PORT], (1 << SEGMENT_SERIAL_PIN));
			}
			
			GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], (1 << SEGMENT_CLOCK_PIN));
			TaskManager_Delay(2 MSec);
			GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], (1 << SEGMENT_CLOCK_PIN));
		}
		GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADRIGHT_PORT], (1 << SEGMENT_LOADRIGHT_PIN));
		TaskManager_Delay(2 MSec);
		GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADRIGHT_PORT], (1 << SEGMENT_LOADRIGHT_PIN));

		GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_ENABLE_PORT], (1 << SEGMENT_ENABLE_PIN));
		
		if(Segment_Demo == 0)
		{
			Segment_Demo = 8;
		}
	}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void Segment_WriteString(U8* Data, bool Blink)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	TaskTimer_Disable(&Segment_Blink);
	Segment_BlinkFeed = Blink;
	
	U8 Buffer[2];

	memcpy(Buffer, Data, 2);
	memcpy(Segment_BufferBlink, Data, 2);
	
	for(U8 Index=RESET; Index<2; Index++)
	{
		if(Buffer[Index] >= '0' && Buffer[Index] <= '9')
		{
			Buffer[Index] = Segment_Numberic[(Buffer[Index] - '0')];
		}
		else if(Buffer[Index] >= 'A' && Buffer[Index] <= 'F')
		{
			Buffer[Index] = Segment_Numberic[(Buffer[Index] - 'A') + 10];
		}
		else if(Buffer[Index] >= 'a' && Buffer[Index] <= 'f')
		{
			Buffer[Index] = Segment_Numberic[(Buffer[Index] - 'a') + 10];
		}
		else
		{
			Buffer[Index] = RESET;
		}
	}
	
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[SEGMENT_SERIAL_PORT] | \
				GPIO_PORTCLOCK[SEGMENT_ENABLE_PORT] | \
				GPIO_PORTCLOCK[SEGMENT_LOADRIGHT_PORT] | \
				GPIO_PORTCLOCK[SEGMENT_LOADLEFT_PORT] | \
				GPIO_PORTCLOCK[SEGMENT_CLOCK_PORT], ENABLE);
	
	// Configure output SEGMENT_SERIAL
	//{
	GPIO_InitStructure.GPIO_Pin = (1 << SEGMENT_SERIAL_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_SERIAL_PORT], &GPIO_InitStructure);
	//}
	
	// Configure output SEGMENT_ENABLE
	//{
	GPIO_InitStructure.GPIO_Pin = (1 << SEGMENT_ENABLE_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_ENABLE_PORT], &GPIO_InitStructure);
	//}
	
	// Configure output SEGMENT_LOADLEFT
	//{
	GPIO_InitStructure.GPIO_Pin = (1 << SEGMENT_LOADLEFT_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADLEFT_PORT], &GPIO_InitStructure);
	//}
	
	// Configure output SEGMENT_LOADRIGHT
	//{
	GPIO_InitStructure.GPIO_Pin = (1 << SEGMENT_LOADRIGHT_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADRIGHT_PORT], &GPIO_InitStructure);
	//}
	
	// Configure output SEGMENT_CLOCK
	//{
	GPIO_InitStructure.GPIO_Pin = (1 << SEGMENT_CLOCK_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], &GPIO_InitStructure);
	//}

	GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADLEFT_PORT], (1 << SEGMENT_LOADLEFT_PIN));	
	GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADRIGHT_PORT], (1 << SEGMENT_LOADRIGHT_PIN));
	
	GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], (1 << SEGMENT_CLOCK_PIN));
	TaskManager_Delay(1 MSec);		
	for(S8 Index=7; Index>=0; Index--)
	{
		if(Buffer[0] & (1 << Index))
		{			
			GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_SERIAL_PORT], (1 << SEGMENT_SERIAL_PIN));
		}
		else
		{
			GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_SERIAL_PORT], (1 << SEGMENT_SERIAL_PIN));
		}
		
		GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], (1 << SEGMENT_CLOCK_PIN));
		TaskManager_Delay(2 MSec);
		GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], (1 << SEGMENT_CLOCK_PIN));
	}	
	GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADLEFT_PORT], (1 << SEGMENT_LOADLEFT_PIN));
	TaskManager_Delay(2 MSec);
	GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADLEFT_PORT], (1 << SEGMENT_LOADLEFT_PIN));
	
	GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], (1 << SEGMENT_CLOCK_PIN));
	TaskManager_Delay(1 MSec);	
	for(S8 Index=7; Index>=0; Index--)
	{
		if(Buffer[1] & (1 << Index))
		{			
			GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_SERIAL_PORT], (1 << SEGMENT_SERIAL_PIN));
		}
		else
		{
			GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_SERIAL_PORT], (1 << SEGMENT_SERIAL_PIN));
		}
		
		GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], (1 << SEGMENT_CLOCK_PIN));
		TaskManager_Delay(2 MSec);
		GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_CLOCK_PORT], (1 << SEGMENT_CLOCK_PIN));
	}
	GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADRIGHT_PORT], (1 << SEGMENT_LOADRIGHT_PIN));
	TaskManager_Delay(2 MSec);
	GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_LOADRIGHT_PORT], (1 << SEGMENT_LOADRIGHT_PIN));

	GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[SEGMENT_ENABLE_PORT], (1 << SEGMENT_ENABLE_PIN));
	
	TaskTimer_Enable(&Segment_Blink);
	
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void Segment_WriteString(U8* Data, bool Blink, U16 Timeout)
{
	Segment_Demo = Timeout/100;
	Segment_WriteString(Data, Blink);
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










