//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1396/03/11
Programmer : Mohammad Lotfi
Site : http://www.mahsen.ir
Tel : +989124662703
*/
//************************************************************* Warning *****************************************************************//
//adc refrence is VrefN and VrefP
//************************************************************* Wizard ******************************************************************//
#include "Wizards.cpp"
//************************************************************ defineds in Wizard ********************************************************//
/*
none
*/	
//************************************************************ includes ******************************************************************//
#include "pwm.hpp"
//************************************************************ variables *****************************************************************//
/*
none
*/
//************************************************************* objects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
/**
 * @brief      initialize PWM
*/
void __init_PWM(void)
{
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_InitStructure;

	#if(PWM_CHANNEL_2_2_ENABLE==1)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 32000;
	TIM_InitStruct.TIM_Prescaler = 1;
	TIM_TimeBaseInit(TIM10, &TIM_InitStruct);
	TIM_Cmd(TIM10, ENABLE);

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_Pulse = 50;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM10, &TIM_OCInitStruct);

	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[PWM_CHANNEL_2_2_PORT], ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = (1 << PWM_CHANNEL_2_2_PIN);
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[PWM_CHANNEL_2_2_PORT], &GPIO_InitStructure);

	TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);
	GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[PWM_CHANNEL_2_2_PORT], PWM_CHANNEL_2_2_PIN, GPIO_AF_TIM10);
	
	PWM_Write(5, 100, 0);
	#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void PWM_Write (U8 Channel, U16 Frequence, U16 Duty)
{
	//frequency in Hz, duty 0-100.0
	long int ratio;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	#if(PWM_CHANNEL_2_2_ENABLE==1)
	if(Duty == 0)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Pin = (1 << PWM_CHANNEL_2_2_PIN);
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[PWM_CHANNEL_2_2_PORT], &GPIO_InitStructure);
		
		GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[PWM_CHANNEL_2_2_PORT], (1 << PWM_CHANNEL_2_2_PIN));				
	}
	else if(Duty >= 100)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Pin = (1 << PWM_CHANNEL_2_2_PIN);
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[PWM_CHANNEL_2_2_PORT], &GPIO_InitStructure);
		
		GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[PWM_CHANNEL_2_2_PORT], (1 << PWM_CHANNEL_2_2_PIN));
	}
	else
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Pin = (1 << PWM_CHANNEL_2_2_PIN);
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[PWM_CHANNEL_2_2_PORT], &GPIO_InitStructure);
		
		GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[PWM_CHANNEL_2_2_PORT], PWM_CHANNEL_2_2_PIN, GPIO_AF_TIM10);
		
		ratio = (long)SystemCoreClock/Frequence;
		TIM10->PSC = (int)(ratio/0xFFFF);
		 
		ratio = ((long)SystemCoreClock/(TIM10->PSC+1));
		TIM10->ARR = (int)(ratio/Frequence)-1;
		 
		TIM10->CCR1 = (int)((TIM10->ARR+1)*Duty)/100-1;
	}
	#endif
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










