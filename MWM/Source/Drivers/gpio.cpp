//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1395/03/05
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
#include "gpio.hpp"
//************************************************************ variables *****************************************************************//
#if(GPIO_ENABLE)
static bool  GPIO_Inited = false;
const GPIO_TypeDef*  GPIO_PORTSEL[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};
const U32  GPIO_PORTCLOCK[] = {RCC_AHBPeriph_GPIOA, RCC_AHBPeriph_GPIOB, RCC_AHBPeriph_GPIOC, RCC_AHBPeriph_GPIOD, RCC_AHBPeriph_GPIOE, RCC_AHBPeriph_GPIOF, RCC_AHBPeriph_GPIOG, RCC_AHBPeriph_GPIOH};
const U8  GPIO_EXTI[] = {EXTI_PortSourceGPIOA, EXTI_PortSourceGPIOB, EXTI_PortSourceGPIOC, EXTI_PortSourceGPIOD, EXTI_PortSourceGPIOE, EXTI_PortSourceGPIOF, EXTI_PortSourceGPIOG, EXTI_PortSourceGPIOH};
struct_GPIO GPIO;
#if(GPIO_OUTPUT_ENABLE)
	static U64 GPIO_output_Task_STAK[GPIO_OUTPUT_TASK_STAK_SIZE/8];
#endif
#if(GPIO_INPUT_ENABLE)
	static U64 GPIO_input_Task_STAK[GPIO_INPUT_TASK_STAK_SIZE/8];
#endif
#endif
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
#if(GPIO_ENABLE)
/**
 * @brief 		initialize GPIO
*/
void __init_GPIO(void)
{
	if(!GPIO_Inited)
	{
//		GPIO_InitTypeDef  GPIO_InitStructure;
//		
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//		
//		//Ext 1
//		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);	
//		GPIO_InitStructure.GPIO_Pin = (1 << 6);
//		GPIO_Init(GPIOE, &GPIO_InitStructure);						
//		
//		//Ext 2
//		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);	
//		GPIO_InitStructure.GPIO_Pin = (1 << 13);
//		GPIO_Init(GPIOC, &GPIO_InitStructure);						
//		
//		//Ext 3
//		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	
//		GPIO_InitStructure.GPIO_Pin = (1 << 0);
//		GPIO_Init(GPIOA, &GPIO_InitStructure);						
//		
//		//Ext 4
//		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	
//		GPIO_InitStructure.GPIO_Pin = (1 << 4);
//		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		//__uninit_GPIO();

#if(GPIO_OUTPUT_ENABLE)
		/// Add "GPIO_OUTPUT" task
		TaskManager_Add("GPIO_OUTPUT", GPIO_Output_Task, GPIO_OUTPUT_PRIORITY, &GPIO_output_Task_STAK, sizeof(GPIO_output_Task_STAK));
#endif
#if(GPIO_INPUT_ENABLE)
		/// Add "GPIO_INPUT" task
		TaskManager_Add("GPIO_INPUT", GPIO_Input_Task, GPIO_INPUT_PRIORITY, &GPIO_input_Task_STAK, sizeof(GPIO_input_Task_STAK));	
#endif

		GPIO_Inited = true;
	}
	else
	{
		GPIO_InitTypeDef  GPIO_InitStructure;
		for(U8 gpio_i=RESET; gpio_i<GPIO.GetNumOfOutput(); gpio_i++)
		{
			GPIO_InitStructure.GPIO_Pin = (1 << GPIO.Output[gpio_i].GetPin());
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

			RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[GPIO.Output[gpio_i].GetPort()], ENABLE);		
			GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[GPIO.Output[gpio_i].GetPort()], &GPIO_InitStructure);
		}
		for(U8 gpio_i=RESET; gpio_i<GPIO.GetNumOfInput(); gpio_i++)
		{
			if(!GPIO.Input[gpio_i].GetByInt())
			{
				GPIO_InitStructure.GPIO_Pin = (1 << GPIO.Input[gpio_i].GetPin());
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
				
				RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[GPIO.Input[gpio_i].GetPort()], ENABLE);		
				GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[GPIO.Input[gpio_i].GetPort()], &GPIO_InitStructure);
			}
		}
	}
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(GPIO_ENABLE)
/**
 * @brief 		uninitialize GPIO
*/
void __uninit_GPIO(void)
{
	/// غير فعال نمودن تمامي پورت ها
	//{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	/// PORTA
	//{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =   /*  GPIO_Pin_0 | */GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3/* | GPIO_Pin_4 \
					*/| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 \
					| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
					| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_InitStructure.GPIO_Pin);
	
//	GPIO_InitStructure.GPIO_Pin =   /*  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 \
//					| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 \
//					| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
//					| GPIO_Pin_15*/;		
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOA, GPIO_InitStructure.GPIO_Pin);
	//}
	/// PORTB
	//{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =     GPIO_Pin_0 | GPIO_Pin_1 /*| GPIO_Pin_2 */| GPIO_Pin_3 | GPIO_Pin_4 \
					| GPIO_Pin_5 /*| GPIO_Pin_6 | GPIO_Pin_7 */| GPIO_Pin_8 | GPIO_Pin_9/* \
					| GPIO_Pin_10 | GPIO_Pin_11 */| GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
					| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_InitStructure.GPIO_Pin);
	
	GPIO_InitStructure.GPIO_Pin =   /*  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 \
					| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 \
					| */GPIO_Pin_10 | GPIO_Pin_11/* | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
					| GPIO_Pin_15*/;		
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_InitStructure.GPIO_Pin);
	//}
	/// PORTC
	//{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =     GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 \
					| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 \
					| GPIO_Pin_10 | GPIO_Pin_11 /*| GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
					| GPIO_Pin_15*/;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
			
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC, GPIO_InitStructure.GPIO_Pin);
	
//	GPIO_InitStructure.GPIO_Pin =   /*  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 \
//					| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 \
//					| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
//					| GPIO_Pin_15*/;		
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOC, GPIO_InitStructure.GPIO_Pin);
	//}
	/// PORTD
	//{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =   /*  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 \
					| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 \
					| */GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
					| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
			
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD, GPIO_InitStructure.GPIO_Pin);
	
	GPIO_InitStructure.GPIO_Pin =   /*  GPIO_Pin_0 | */GPIO_Pin_1/* | GPIO_Pin_2 */| GPIO_Pin_3 | GPIO_Pin_4 \
					| GPIO_Pin_5 /*| GPIO_Pin_6 */| GPIO_Pin_7/* | GPIO_Pin_8 | GPIO_Pin_9 \
					| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
					| GPIO_Pin_15*/;		
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, GPIO_InitStructure.GPIO_Pin);
	//}
	/// PORTE
	//{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =     GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 \
					| GPIO_Pin_5 /*| GPIO_Pin_6 */| GPIO_Pin_7/* | GPIO_Pin_8 */| GPIO_Pin_9 \
					| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
					| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
			
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOE, GPIO_InitStructure.GPIO_Pin);
	
//	GPIO_InitStructure.GPIO_Pin =   /*  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 \
//					| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 \
//					| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
//					| GPIO_Pin_15*/;	
//	GPIO_Init(GPIOE, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOE, GPIO_InitStructure.GPIO_Pin);
	//}
	/// PORTF
	//{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =   /*  GPIO_Pin_0 | */GPIO_Pin_1/* | GPIO_Pin_2 */| GPIO_Pin_3 /*| GPIO_Pin_4 \
					*/| GPIO_Pin_5 | GPIO_Pin_6 /*| GPIO_Pin_7 */| GPIO_Pin_8 | GPIO_Pin_9 \
					| GPIO_Pin_10/* | GPIO_Pin_11 | GPIO_Pin_12*/ | GPIO_Pin_13/* | GPIO_Pin_14 \
					*/| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
			
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOF, GPIO_InitStructure.GPIO_Pin);
	
	GPIO_InitStructure.GPIO_Pin =   /*  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | */GPIO_Pin_4/* \
					| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 \
					| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13*/ | GPIO_Pin_14/* \
					| GPIO_Pin_15*/;		
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_SetBits(GPIOF, GPIO_InitStructure.GPIO_Pin);
	//}
	/// PORTG
	//{	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =     GPIO_Pin_0 /*| GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 \
					*/| GPIO_Pin_5/* | GPIO_Pin_6 */| GPIO_Pin_7 | GPIO_Pin_8/* | GPIO_Pin_9 \
					| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 */| GPIO_Pin_13 | GPIO_Pin_14/* \
					| GPIO_Pin_15*/;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
			
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOG, GPIO_InitStructure.GPIO_Pin);
	
	GPIO_InitStructure.GPIO_Pin =   /*  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 \
					| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | */GPIO_Pin_9 \
					| GPIO_Pin_10 | GPIO_Pin_11/* | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
					| GPIO_Pin_15*/;		
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_SetBits(GPIOG, GPIO_InitStructure.GPIO_Pin);
	//}
	/// PORTH
	//{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOH, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =   /*  GPIO_Pin_0 | GPIO_Pin_1 | */GPIO_Pin_2/* | GPIO_Pin_3 | GPIO_Pin_4 \
					| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 \
					| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
					| GPIO_Pin_15*/;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
			
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOH, GPIO_InitStructure.GPIO_Pin);
	
//	GPIO_InitStructure.GPIO_Pin =   /*  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 \
//					| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 \
//					| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 \
//					| GPIO_Pin_15*/;		
//	GPIO_Init(GPIOH, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOH, GPIO_InitStructure.GPIO_Pin);
	//}
	//}

}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(GPIO_OUTPUT_ENABLE)
/**
 * @brief 		Add pin for output
 * @param[in]	Port number port
 * @param[in]	Pin number pin
 * @param[in]	Addr_Value pointer value
 * @param[in]	Default default value
 * @return 		number of added for output
*/
S8 GPIO_Output_AddPin(U8 Port, U8 Pin,bool *Addr_Value, bool Default)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/// Check max gpio output
	if(GPIO.GetNumOfOutput()<GPIO_OUTPUT_MAX)
	{
		
		// Configure output mode
		GPIO_InitStructure.GPIO_Pin = (1 << Pin);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		
		/// GPIO Peripheral clock enable
		GPIO.Output[GPIO.GetNumOfOutput()].SetPort(Port);
		RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[Port], ENABLE);		
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[Port], &GPIO_InitStructure);

		/// Add to struct gpio output		
		GPIO.Output[GPIO.GetNumOfOutput()].SetPin(Pin);
		GPIO.Output[GPIO.GetNumOfOutput()].SetAddrValue(Addr_Value);
		GPIO.Output[GPIO.GetNumOfOutput()].SetFeedValue(*Addr_Value);
		
		*Addr_Value = Default;
		
		/// Increase number of gpio output used
		GPIO.IncreaseNumOfOutput();
	}
	else
	{
		//Debug("GPIO: Out of range gpio output pin => S8 GPIO_Output_AddPin(...)");
		return -1;
	}
	
	return GPIO.GetNumOfOutput();
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(GPIO_INPUT_ENABLE)
/**
 * @brief 		Add pin for input
 * @param[in]	Port number port
 * @param[in]	Pin number pin
 * @param[in]	Addr_Fun pointer function call on change edge
 * @param[in]	Addr_Value pointer value
 * @param[in]	Edge how time call function
 * @param[in]	ByInt if run to interrupt value
 * @param[in]	Default default value
 * @return 		number of added for input
*/
S8 GPIO_Input_AddPin(U8 Port, U8 Pin,void (*Addr_Fun)(void), bool *Addr_Value, U8 Edge, U8 Pulling, bool ByInt)
{
	GPIO_InitTypeDef         GPIO_InitStructure;
	EXTI_InitTypeDef         EXTI_InitStructure;	
	NVIC_InitTypeDef         NVIC_InitStructure;
	
	/// Check max gpio input
	if(GPIO.GetNumOfInput()<GPIO_INPUT_MAX)
	{
		
		/// Configure input mode
		GPIO_InitStructure.GPIO_Pin = (1 << Pin);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = (Pulling==PIN_PULLING_UP)?GPIO_PuPd_UP:(Pulling==PIN_PULLING_DOWN)?GPIO_PuPd_DOWN:GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		
		/// GPIO Peripheral clock enable
		GPIO.Input[GPIO.GetNumOfInput()].SetPort(Port);
		RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[Port], ENABLE);		
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[Port], &GPIO_InitStructure);

		/// Add to struct gpio input
		GPIO.Input[GPIO.GetNumOfInput()].SetPin(Pin);
		GPIO.Input[GPIO.GetNumOfInput()].SetAddrFun(Addr_Fun);
		GPIO.Input[GPIO.GetNumOfInput()].SetAddrValue(Addr_Value);
		*Addr_Value = GPIO_ReadInputDataBit((GPIO_TypeDef*)GPIO_PORTSEL[Port], (1 << Pin));
		GPIO.Input[GPIO.GetNumOfInput()].SetFeedValue(*Addr_Value);
		GPIO.Input[GPIO.GetNumOfInput()].SetEdge(Edge);
		GPIO.Input[GPIO.GetNumOfInput()].SetByInt(ByInt);
		
		if(ByInt)
		{
			RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG , ENABLE);
			
			EXTI_InitStructure.EXTI_Line = (1 << Pin); 
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
			EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; 
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;
			EXTI_Init(&EXTI_InitStructure);
			
			EXTI_ClearFlag(1 << Pin);
			EXTI_ClearITPendingBit(1 << Pin);

			if(Pin == 0)
			{
				NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
			}
			else if(Pin == 1)
			{
				NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
			}
			else if(Pin == 2)
			{
				NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
			}
			else if(Pin == 3)
			{
				NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
			}
			else if(Pin == 4)
			{
				NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
			}
			else if(Pin == 5 || Pin == 6 || Pin == 7 || Pin == 8 || Pin == 9)
			{
				NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn ;
			}
			else if(Pin == 10 || Pin == 11 || Pin == 12 || Pin == 13 || Pin == 14 || Pin == 15)
			{
				NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
			}
			
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure); 

			SYSCFG_EXTILineConfig(GPIO_EXTI[Port], Pin);
		}
		
		/// Increase number of gpio input used
		GPIO.IncreaseNumOfInput();
		
	}
	else
	{
		//Debug("GPIO: Out of range gpio input pin => S8 GPIO_Input_AddPin(...)");
		return -1;
	}
			
	return GPIO.GetNumOfInput();
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(GPIO_INPUT_ENABLE)
void GPIO_RefreshInputsByInt(U32 irq)
{
	U8 gpio_i;
	
	/// Refresh value gpio input by changing the pin [toggle,rising,falling]
	/// Call function in add
	for(gpio_i=RESET; gpio_i<GPIO.GetNumOfInput(); gpio_i++)
	{
		if(GPIO.Input[gpio_i].GetByInt())
		{
			if(irq == GPIO.Input[gpio_i].GetPin())
			{
				*GPIO.Input[gpio_i].GetAddrValue() = GPIO_ReadInputDataBit((GPIO_TypeDef*)GPIO_PORTSEL[GPIO.Input[gpio_i].GetPort()], (1 << GPIO.Input[gpio_i].GetPin()));
				
				if(*GPIO.Input[gpio_i].GetAddrValue() != GPIO.Input[gpio_i].GetFeedValue())
				{
					if(GPIO.Input[gpio_i].GetEdge()==PIN_EDGE_TOGGEL)
					{
						if(GPIO.Input[gpio_i].GetAddrFun())
						{
							GPIO.Input[gpio_i].RunAddrFun();
						}
					}
					else if((GPIO.Input[gpio_i].GetEdge()==PIN_EDGE_UP) && (GPIO.Input[gpio_i].GetFeedValue()==false))
					{
						if(GPIO.Input[gpio_i].GetAddrFun())
						{
							GPIO.Input[gpio_i].RunAddrFun();
						}
					}
					else if((GPIO.Input[gpio_i].GetEdge()==PIN_EDGE_DOWN) && (GPIO.Input[gpio_i].GetFeedValue()==true))
					{
						if(GPIO.Input[gpio_i].GetAddrFun())
						{
							GPIO.Input[gpio_i].RunAddrFun();
						}
					}
					
					*GPIO.Input[gpio_i].GetAddrValue() = GPIO_ReadInputDataBit((GPIO_TypeDef*)GPIO_PORTSEL[GPIO.Input[gpio_i].GetPort()], (1 << GPIO.Input[gpio_i].GetPin()));
					GPIO.Input[gpio_i].SetFeedValue(*GPIO.Input[gpio_i].GetAddrValue());
				}
			}
		}
	}
}
#endif
//*************************************************************** tasks *******************************************************************//
#if(GPIO_OUTPUT_ENABLE)
/**
 * @brief 	 task manage output pin
*/
__task void GPIO_Output_Task(void)
{

	/// Delays in beginning the task
	TaskManager_Delay(TASK_MANAGER_DELAYFIRSTTASK);
	
	U8 gpio_i;
	
	/// Task {
	while(true)
	{

		/// Refresh pin by changing the value gpio output
		for(gpio_i=RESET; gpio_i<GPIO.GetNumOfOutput(); gpio_i++)
		{
			if((*GPIO.Output[gpio_i].GetAddrValue()) != GPIO.Output[gpio_i].GetFeedValue())
			{
				if(*GPIO.Output[gpio_i].GetAddrValue())
				{
					GPIO_SetBits((GPIO_TypeDef*)GPIO_PORTSEL[GPIO.Output[gpio_i].GetPort()], (1 << GPIO.Output[gpio_i].GetPin()));
				}
				else
				{
					GPIO_ResetBits((GPIO_TypeDef*)GPIO_PORTSEL[GPIO.Output[gpio_i].GetPort()], (1 << GPIO.Output[gpio_i].GetPin()));
				}
				GPIO.Output[gpio_i].SetFeedValue(*GPIO.Output[gpio_i].GetAddrValue());
			}
		}

		/// Delay one Tick
		TaskManager_Delay(10 MSec);	
	}
	/// }
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(GPIO_INPUT_ENABLE)
/**
 * @brief 	 task manage input pin
*/
__task void GPIO_Input_Task(void)  //find minimum Pulse Width 500 us
{

	/// Delays in beginning the task
	TaskManager_Delay(TASK_MANAGER_DELAYFIRSTTASK);
	
	U8 gpio_i;
	
	/// Task {
	while(true)
	{
		/// Refresh value gpio input by changing the pin [toggle,rising,falling]
		/// Call function in add
		for(gpio_i=RESET; gpio_i<GPIO.GetNumOfInput(); gpio_i++)
		{
			*GPIO.Input[gpio_i].GetAddrValue() = GPIO_ReadInputDataBit((GPIO_TypeDef*)GPIO_PORTSEL[GPIO.Input[gpio_i].GetPort()], (1 << GPIO.Input[gpio_i].GetPin()));
		
			if(*GPIO.Input[gpio_i].GetAddrValue() != GPIO.Input[gpio_i].GetFeedValue())
			{
				if(!GPIO.Input[gpio_i].GetByInt())
				{
					if(GPIO.Input[gpio_i].GetEdge()==PIN_EDGE_TOGGEL)
					{
						if(GPIO.Input[gpio_i].GetAddrFun())
						{
							GPIO.Input[gpio_i].RunAddrFun();							
						}
					}
					else if((GPIO.Input[gpio_i].GetEdge()==PIN_EDGE_UP) && (GPIO.Input[gpio_i].GetFeedValue()==false))
					{
						if(GPIO.Input[gpio_i].GetAddrFun())
						{
							GPIO.Input[gpio_i].RunAddrFun();							
						}
					}
					else if((GPIO.Input[gpio_i].GetEdge()==PIN_EDGE_DOWN) && (GPIO.Input[gpio_i].GetFeedValue()==true))
					{
						if(GPIO.Input[gpio_i].GetAddrFun())
						{
							GPIO.Input[gpio_i].RunAddrFun();							
						}
					}
				}
				
				GPIO.Input[gpio_i].SetFeedValue(*GPIO.Input[gpio_i].GetAddrValue());
			}
		}
		
		/// Delay one Mili Second
		TaskManager_Delay(10 MSec);
	}
	/// }
}
#endif
//************************************************************** vectors ******************************************************************//
#if(GPIO_INPUT_ENABLE)
void EXTI0_IRQHandler(void) __irq
{
	
	GPIO_RefreshInputsByInt(0);
		
	/// EXTI_Line0 پاک کردن فلگ وقفه
	//{
	EXTI_ClearFlag(EXTI_Line0);
	EXTI_ClearITPendingBit(EXTI_Line0);
	//}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void EXTI1_IRQHandler(void) __irq
{
	
	GPIO_RefreshInputsByInt(1);
		
	/// EXTI_Line1 پاک کردن فلگ وقفه
	//{
	EXTI_ClearFlag(EXTI_Line1);
	EXTI_ClearITPendingBit(EXTI_Line1);
	//}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void EXTI2_IRQHandler(void) __irq
{
	
	GPIO_RefreshInputsByInt(2);
		
	/// EXTI_Line2 پاک کردن فلگ وقفه
	//{
	EXTI_ClearFlag(EXTI_Line2);
	EXTI_ClearITPendingBit(EXTI_Line2);
	//}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void EXTI3_IRQHandler(void) __irq
{
	
	GPIO_RefreshInputsByInt(3);
		
	/// EXTI_Line3 پاک کردن فلگ وقفه
	//{
	EXTI_ClearFlag(EXTI_Line3);
	EXTI_ClearITPendingBit(EXTI_Line3);
	//}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void EXTI4_IRQHandler(void) __irq
{
	
	GPIO_RefreshInputsByInt(4);
		
	/// EXTI_Line4 پاک کردن فلگ وقفه
	//{
	EXTI_ClearFlag(EXTI_Line4);
	EXTI_ClearITPendingBit(EXTI_Line4);
	//}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void EXTI9_5_IRQHandler(void) __irq
{
	
	/// EXTI_Line5 پاک کردن فلگ وقفه
	//{
	if(EXTI_GetFlagStatus(EXTI_Line5))
	{
		GPIO_RefreshInputsByInt(5);
		EXTI_ClearFlag(EXTI_Line5);
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	//}
	/// EXTI_Line6 پاک کردن فلگ وقفه
	//{
	else if(EXTI_GetFlagStatus(EXTI_Line6))
	{
		GPIO_RefreshInputsByInt(6);
		EXTI_ClearFlag(EXTI_Line6);
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	//}
	/// EXTI_Line7 پاک کردن فلگ وقفه
	//{
	else if(EXTI_GetFlagStatus(EXTI_Line7))
	{
		GPIO_RefreshInputsByInt(7);
		EXTI_ClearFlag(EXTI_Line7);
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
	//}
	/// EXTI_Line8 پاک کردن فلگ وقفه
	//{
	else if(EXTI_GetFlagStatus(EXTI_Line8))
	{
		GPIO_RefreshInputsByInt(8);
		EXTI_ClearFlag(EXTI_Line8);
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	//}
	/// EXTI_Line9 پاک کردن فلگ وقفه
	//{
	else if(EXTI_GetFlagStatus(EXTI_Line9))
	{
		GPIO_RefreshInputsByInt(9);
		EXTI_ClearFlag(EXTI_Line9);
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
	//}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void EXTI15_10_IRQHandler(void) __irq
{
		
	/// EXTI_Line10 پاک کردن فلگ وقفه
	//{
	if(EXTI_GetFlagStatus(EXTI_Line10))
	{
		GPIO_RefreshInputsByInt(10);
		EXTI_ClearFlag(EXTI_Line10);
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
	//}
	/// EXTI_Line11 پاک کردن فلگ وقفه
	//{
	else if(EXTI_GetFlagStatus(EXTI_Line11))
	{
		GPIO_RefreshInputsByInt(11);
		EXTI_ClearFlag(EXTI_Line11);
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
	//}
	/// EXTI_Line12 پاک کردن فلگ وقفه
	//{
	else if(EXTI_GetFlagStatus(EXTI_Line12))
	{
		GPIO_RefreshInputsByInt(12);
		EXTI_ClearFlag(EXTI_Line12);
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
	//}
	/// EXTI_Line13 پاک کردن فلگ وقفه
	//{
	else if(EXTI_GetFlagStatus(EXTI_Line13))
	{
		GPIO_RefreshInputsByInt(13);
		EXTI_ClearFlag(EXTI_Line13);
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
	//}
	/// EXTI_Line14 پاک کردن فلگ وقفه
	//{
	else if(EXTI_GetFlagStatus(EXTI_Line14))
	{
		GPIO_RefreshInputsByInt(14);
		EXTI_ClearFlag(EXTI_Line14);
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	//}
	/// EXTI_Line15 پاک کردن فلگ وقفه
	//{
	else if(EXTI_GetFlagStatus(EXTI_Line15))
	{
		GPIO_RefreshInputsByInt(15);
		EXTI_ClearFlag(EXTI_Line15);
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
	//}
}
#endif
//****************************************************************************************************************************************//










