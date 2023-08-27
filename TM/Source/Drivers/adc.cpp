//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1397/2/2
Programmer : Mojtaba Nademi
Site : none
Tel : +989214551464
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
#include "adc.hpp"
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
 * @brief 		initialize ADC
*/
void __init_ADC(void)
{
	GPIO_InitTypeDef         GPIO_InitStructure;
	ADC_InitTypeDef          ADC_InitStructure;

	/* Enable the PWR clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	/* ADC1 Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	#if(ADC_CHANNEL0_ENABLE==1)
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL0_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL0_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL0_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL1_ENABLE==1)
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL1_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL1_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL1_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL1B_ENABLE==1)//b
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL1B_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL1B_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL1B_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL2_ENABLE==1)
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL2_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL2_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL2_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL2B_ENABLE==1)//b
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL2B_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL2B_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL2B_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL3_ENABLE==1)
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL3_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL3_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL3_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL3B_ENABLE==1)//b
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL3B_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL3B_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL3B_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL6B_ENABLE==1)//b
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL6B_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL6B_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL6B_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL7B_ENABLE==1) //b
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL7B_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL7B_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL7B_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL8_ENABLE==1)
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL8_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL8_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL8_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL9_ENABLE==1)
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL9_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL9_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL9_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL10_ENABLE==1)
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL10_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL10_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL10_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL10B_ENABLE==1) //b
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL10B_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL10B_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL10B_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL11_ENABLE==1)
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL11_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL11_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL11_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL12_ENABLE==1)
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL12_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL12_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL12_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL13_ENABLE==1)
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL13_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL13_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL13_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL19_ENABLE==1)
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL19_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL19_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL19_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL27_ENABLE==1) 
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL27_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL27_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL27_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL28_ENABLE==1) 
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL28_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL28_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL28_PORT], &GPIO_InitStructure);
	#endif
	
	#if(ADC_CHANNEL30_ENABLE==1) 
	/* Periph clock enable */
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[ADC_CHANNEL30_PORT], ENABLE);

	/* Configure ADC Channel12 as analog input */
	GPIO_InitStructure.GPIO_Pin = (1 << ADC_CHANNEL30_PIN);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[ADC_CHANNEL30_PORT], &GPIO_InitStructure);
	#endif
	
	/* ADC1 Configuration *******************************************************/
	//ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; /* Configure the ADC1 with a resolution equal to 8 bits*/
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv =  ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = 0;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);

}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
U32 ADC_Read (U16 Channel)
{
	U32 ADValue = RESET;
	bool BankB = (((Channel & 0xFF00) >> 8) & 1);
	Channel = (Channel & 0x00FF);
	ADC1->CR2 &= ~(1<<2); //-- Clear Bit Cfg
	
	#if(ADC_CHANNEL0_ENABLE==1)
	if(Channel == 0)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_0 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL1_ENABLE==1)
	if(Channel == 1)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif

	#if(ADC_CHANNEL1B_ENABLE==1)//b
	if((Channel == 1) && (BankB))
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC1->CR2 |= 1<<2; //-- Bit Cfg
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL2_ENABLE==1)
	if(Channel == 2)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		TaskManager_Delay(1 Sec);
		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL2B_ENABLE==1)//b
	if((Channel == 2) && (BankB))
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC1->CR2 |= 1<<2; //-- Bit Cfg
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL3_ENABLE==1)
	if(Channel == 3)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_3 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		TaskManager_Delay(1 Sec);
		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL3B_ENABLE==1)//b
	if((Channel == 3) && (BankB))
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_3 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC1->CR2 |= 1<<2; //-- Bit Cfg
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL6B_ENABLE==1)//b
	if((Channel == 6) && (BankB))
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_6 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC1->CR2 |= 1<<2; //-- Bit Cfg
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
		
		ADC1->CR2 &= !(U32)(1<<2);
	}
	#endif
	
	#if(ADC_CHANNEL7B_ENABLE==1)//b
	if((Channel == 7) && (BankB))
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_7 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC1->CR2 |= 1<<2; //-- Bit Cfg
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
		
		ADC1->CR2 &= !(U32)(1<<2);
	}
	#endif
	
	#if(ADC_CHANNEL8_ENABLE==1)
	if(Channel == 8)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_8 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL9_ENABLE==1)
	if(Channel == 9)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_9 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL10_ENABLE==1)
	if(Channel == 10)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_10 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		TaskManager_Delay(1 Sec);
		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL10B_ENABLE==1)//b
	if((Channel == 10) && (BankB))
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_10 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC1->CR2 |= 1<<2; //-- Bit Cfg
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
		
		ADC1->CR2 &= !(U32)(1<<2);
	}
	#endif
	
	#if(ADC_CHANNEL11_ENABLE==1)
	if(Channel == 11)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_11 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL12_ENABLE==1)
	if(Channel == 12)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_12 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL13_ENABLE==1)
	if(Channel == 13)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_13 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL19_ENABLE==1)
	if(Channel == 19)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_19 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL27_ENABLE==1)
	if(Channel == 27)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_27 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL18_ENABLE==1)
	if(Channel == 18)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_18 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL28_ENABLE==1)
	if(Channel == 28)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_28 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	#if(ADC_CHANNEL30_ENABLE==1)
	if(Channel == 30)
	{
		ADC_RegularChannelConfig(ADC1, ADC_Channel_30 , 1, ADC_SampleTime_384Cycles);  /* 239.5 Cycles as sampling time */
		ADC_Cmd(ADC1, ENABLE); /* Enable ADCperipheral */
		
		ADC_SoftwareStartConv(ADC1);
		TASK_MANAGER_WHILEUNTIL(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));  /* Wait the ADCEN flag */ 

		ADValue = ADC_GetConversionValue(ADC1);
	}
	#endif
	
	return ADValue;
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










