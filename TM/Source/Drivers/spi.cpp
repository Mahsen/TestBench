//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1395/10/20
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
//************************************************************ defineds ******************************************************************//
/*
none
*/
//************************************************************ includes ******************************************************************//
#include "spi.hpp"
//************************************************************ variables *****************************************************************//
volatile bool SPI_MutexHandleUpdate[2];
volatile bool SPI_MutexHandleSendByte[2];
volatile bool SPI_MutexHandleSend[2];
volatile bool SPI_MutexHandleReceive[2];
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
void __init_SPI(void)
{
	TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleUpdate[0]);
	TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleSendByte[0]);
	TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleSend[0]);
	TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleReceive[0]);
	
	SPI_Update(1);
	SPI_Update(2);
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void __uninit_SPI(void) 
{
	#if(SPI1_ENABLE==1)
	SPI_DeInit(SPI1);
	#endif
	#if(SPI2_ENABLE==1)
	SPI_DeInit(SPI2);
	#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
bool SPI_Update (U8 Port) 
{
	/// Wait Mutex SPI_Update
	TASK_MANAGER_MUTEXWAIT(SPI_MutexHandleUpdate[0]);
	
	/// Initialize and enable the SPI Interface module
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	#if(SPI1_ENABLE==1)
	if(Port == 1)
	{

		/*!< Enable the SPI clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);


		/*!< Enable GPIO clocks */
		RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[SPI1_SCK_PORT] | GPIO_PORTCLOCK[SPI1_MISO_PORT] | GPIO_PORTCLOCK[SPI1_MOSI_PORT], ENABLE);

		/*!< SPI pins configuration *************************************************/
		//{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

		/*!< SPI SCK pin configuration */
		GPIO_InitStructure.GPIO_Pin = (1 << SPI1_SCK_PIN);
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SPI1_SCK_PORT], &GPIO_InitStructure);

		GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[SPI1_SCK_PORT], SPI1_SCK_PIN, GPIO_AF_SPI1) ;


		/*!< SPI MOSI pin configuration */
		GPIO_InitStructure.GPIO_Pin =  (1 << SPI1_MOSI_PIN);
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SPI1_MOSI_PORT], &GPIO_InitStructure);

		GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[SPI1_MOSI_PORT], SPI1_MOSI_PIN, GPIO_AF_SPI1) ;


		/*!< SPI MISO pin configuration */
		GPIO_InitStructure.GPIO_Pin =  (1 << SPI1_MISO_PIN);
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SPI1_MISO_PORT], &GPIO_InitStructure);

		GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[SPI1_MISO_PORT], SPI1_MISO_PIN, GPIO_AF_SPI1) ;

		/*!< SPI configuration */
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;

		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_InitStructure.SPI_CRCPolynomial = 7;

		SPI_Init(SPI1, &SPI_InitStructure);
		SPI_Cmd(SPI1, ENABLE);
		
		/// Release Mutex SPI_Update
		TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleUpdate[0]);
	
		return true;
	}
	#endif
	#if(SPI2_ENABLE==1)
	if(Port == 2)
	{

		/*!< Enable the SPI clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

		/*!< Enable GPIO clocks */
		RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[SPI2_SCK_PORT] | GPIO_PORTCLOCK[SPI2_MISO_PORT] | GPIO_PORTCLOCK[SPI2_MOSI_PORT], ENABLE);

		/*!< SPI pins configuration *************************************************/
		//{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

		/*!< SPI SCK pin configuration */
		GPIO_InitStructure.GPIO_Pin = (1 << SPI2_SCK_PIN);
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SPI2_SCK_PORT], &GPIO_InitStructure);
				
		GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[SPI2_SCK_PORT], SPI2_SCK_PIN, GPIO_AF_SPI2) ;

		/*!< SPI MOSI pin configuration */
		GPIO_InitStructure.GPIO_Pin =  (1 << SPI2_MOSI_PIN);
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SPI2_MOSI_PORT], &GPIO_InitStructure);

		GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[SPI2_MOSI_PORT], SPI2_MOSI_PIN, GPIO_AF_SPI2) ;

		/*!< SPI MISO pin configuration */
		GPIO_InitStructure.GPIO_Pin =  (1 << SPI2_MISO_PIN);
		GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[SPI2_MISO_PORT], &GPIO_InitStructure);

		GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[SPI2_MISO_PORT], SPI2_MISO_PIN, GPIO_AF_SPI2) ;
		//}

		/*!< SPI configuration */
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;

		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_InitStructure.SPI_CRCPolynomial = 7;


		SPI_Init(SPI2, &SPI_InitStructure);
		SPI_Cmd(SPI2, ENABLE);
	
		/// Release Mutex SPI_Update
		TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleUpdate[0]);
	
		return true;
	}
	#endif	
	
	/// Release Mutex SPI_Update
	TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleUpdate[0]);
	
	return false;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
U8 SPI_SendByte (U8 Port, U8 Byte) 
{
	/// Wait Mutex SPI_SendByte
	TASK_MANAGER_MUTEXWAIT(SPI_MutexHandleSendByte[0]);
	
	/* Write and Read a byte on SPI interface. */
	#if(SPI1_ENABLE==1)
	if(Port == 1)
	{
		/* Write and Read a byte on SPI interface. */
		SPI1->DR = Byte;	 
		/* Wait if RNE cleared, Rx FIFO is empty. */
		while (!(SPI1->SR & RXNE));
		
		/// Release Mutex SPI_SendByte
		TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleSendByte[0]);
		
		return (SPI1->DR);   
	}
	#endif	
	#if(SPI2_ENABLE==1)
	if(Port == 2)
	{
		/* Write and Read a byte on SPI interface. */
		SPI2->DR = Byte;	 
		/* Wait if RNE cleared, Rx FIFO is empty. */
		while (!(SPI2->SR & RXNE));
		
		/// Release Mutex SPI_SendByte
		TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleSendByte[0]);
		
		return (SPI2->DR); 
	}
	#endif	
	
	/// Release Mutex SPI_SendByte
	TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleSendByte[0]);
	
	return RESET;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
bool SPI_Send (U8 Port, U8 *Data, U32 Length) 
{
	/// Wait Mutex SPI_Send
	TASK_MANAGER_MUTEXWAIT(SPI_MutexHandleSend[0]);
	
	/* Send buffer to SPI interface. */
	U32 i;
	volatile U8  f;
	#if(SPI1_ENABLE==1)
	if(Port == 1)
	{
		for (i = 0; i < Length; i++) 
		{    
			SPI1->DR = Data[i];
			/* Wait if TXE cleared, Tx FIFO is full. */
			while (!(SPI1->SR & TXE));

			f = SPI1->DR;
		}
		/* Wait until Tx finished, drain Rx FIFO. */
		while (SPI1->SR & (BSY | RXNE)) 
		{
			f = SPI1->DR;
		}
		
		/// Release Mutex SPI_Send
		TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleSend[0]);
		
		return true;
	}
	#endif
	#if(SPI2_ENABLE==1)
	if(Port == 2)
	{
		for (i = 0; i < Length; i++) 
		{    
			SPI2->DR = Data[i];
			/* Wait if TXE cleared, Tx FIFO is full. */
			while (!(SPI2->SR & TXE));

			f = SPI2->DR;
		}
		/* Wait until Tx finished, drain Rx FIFO. */
		while (SPI2->SR & (BSY | RXNE)) 
		{
			f = SPI2->DR;
		}
		
		/// Release Mutex SPI_Send
		TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleSend[0]);
		
		return true;
	}
	#endif	
	
	/// Release Mutex SPI_Send
	TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleSend[0]);
	
	return false;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
bool SPI_Receive (U8 Port, U8 *Data, U32 Length) 
{
	/// Wait Mutex SPI_Receive
	TASK_MANAGER_MUTEXWAIT(SPI_MutexHandleReceive[0]);
	
	/* Receive SPI data to buffer. */
	U32 i;
	
	#if(SPI1_ENABLE==1)
	if(Port == 1)
	{
		for (i = 0; i < Length; i++) 
		{
			SPI1->DR = 0xFF;
			/* Wait if RNE cleared, Rx FIFO is empty. */
			while (!(SPI1->SR & RXNE));
			Data[i] = SPI1->DR;
		}
		
		/// Release Mutex SPI_Receive
		TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleReceive[0]);
		
		return true;
	}
	#endif
	#if(SPI2_ENABLE==1)
	if(Port == 2)
	{
		for (i = 0; i < Length; i++) 
		{
			SPI2->DR = 0xFF;
			/* Wait if RNE cleared, Rx FIFO is empty. */
			while (!(SPI2->SR & RXNE));
			Data[i] = SPI2->DR;
		}
		
		/// Release Mutex SPI_Receive
		TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleReceive[0]);
		
		return true;
	}	
	#endif	
	
	/// Release Mutex SPI_Receive
	TASK_MANAGER_MUTEXRELEASE(SPI_MutexHandleReceive[0]);
	
	return false;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
bool SPI_BusSpeed (U32 KBaud) 
{
	
	return true;
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


