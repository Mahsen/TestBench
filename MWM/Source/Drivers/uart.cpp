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
#include "Wizards.cpp"
//**************************************************************** defineds **************************************************************//
#if((UART_1_ENABLE&&UART_1_INT)||(UART_2_ENABLE&&UART_2_INT)||(UART_3_ENABLE&&UART_3_INT)||(UART_4_ENABLE&&UART_4_INT)||(UART_5_ENABLE&&UART_5_INT)) //INIT DEFINE FIFO UARTs
	/* Buf mask */
	#define __BUF_MASK(com)                   (com-1)
	/* Check buf is full or not */
	#define __BUF_IS_FULL(head, tail, com)    ((tail&__BUF_MASK(com))==((head+1)&__BUF_MASK(com)))
	/* Check buf will be full in next receiving or not */
	#define __BUF_WILL_FULL(head, tail, com)  ((tail&__BUF_MASK(com))==((head+2)&__BUF_MASK(com)))
	/* Check buf is empty */
	#define __BUF_IS_EMPTY(head, tail, com)   ((head&__BUF_MASK(com))==(tail&__BUF_MASK(com)))
	/* Reset buf */
	#define __BUF_RESET(bufidx)	              (bufidx=0)
	#define __BUF_INCR(bufidx, com)	          (bufidx=(bufidx+1)&__BUF_MASK(com))
	#define  UART_Send_FIFO_Task_STAK_SIZE    512
#endif
//************************************************************ includes ******************************************************************//
#include "uart.hpp"
#include "gpio.hpp"
#include "TaskManager.hpp"
//************************************************************ variables *****************************************************************//
#if((UART_1_ENABLE)||(UART_2_ENABLE)||(UART_3_ENABLE)||(UART_4_ENABLE)||(UART_5_ENABLE))
static bool  UART_Inited = false;
#endif
#if(UART_1_ENABLE) //BUFFER UART1
USART_InitTypeDef        UART1_InitStructure;
bool UART1_WordLength_7b = false;
#if(UART_1_INT)
	struct UART1_RING_BUFFER_STRUCT
	{
		__IO U16 rx_head;                /*!< UART Rx ring buffer head index */
		__IO U16 rx_tail;                /*!< UART Rx ring buffer tail index */
		__IO U8  rx[UART_1_RING_BUFSIZE_RX];  /*!< UART Rx data ring buffer */
		#if(UART_1_INT_SEND_MODE==1)
		__IO U16 tx_head;                /*!< UART Tx ring buffer head index */
		__IO U16 tx_tail;                /*!< UART Tx ring buffer tail index */		
		__IO U8  tx[UART_1_RING_BUFSIZE_TX];  /*!< UART Tx data ring buffer */
		#endif
	} UART1_RING_BUFFER;	
	
	#if(UART_1_INT_SEND_MODE==1)
	bool UART1_RING_BUFFER_FLAG_Write_In_Proccess = false;
	bool UART1_RING_BUFFER_FLAG_Sending_In_Proccess = false;
	static U64 UART1_Send_FIFO_Task_STAK[UART_Send_FIFO_Task_STAK_SIZE/8];
	#endif
#endif
#endif
#if(UART_2_ENABLE) //BUFFER UART2
USART_InitTypeDef        UART2_InitStructure;
bool UART2_WordLength_7b = false;
#if(UART_2_INT)
	struct UART2_RING_BUFFER_STRUCT
	{
		__IO U16 rx_head;                /*!< UART Rx ring buffer head index */
		__IO U16 rx_tail;                /*!< UART Rx ring buffer tail index */
		__IO U8  rx[UART_2_RING_BUFSIZE_RX];  /*!< UART Rx data ring buffer */
		#if(UART_2_INT_SEND_MODE==1)
		__IO U16 tx_head;                /*!< UART Tx ring buffer head index */
		__IO U16 tx_tail;                /*!< UART Tx ring buffer tail index */		
		__IO U8  tx[UART_2_RING_BUFSIZE_TX];  /*!< UART Tx data ring buffer */
		#endif
	} UART2_RING_BUFFER;	
	
	#if(UART_2_INT_SEND_MODE==1)
	bool UART2_RING_BUFFER_FLAG_Write_In_Proccess = false;
	bool UART2_RING_BUFFER_FLAG_Sending_In_Proccess = false;
	static U64 UART2_Send_FIFO_Task_STAK[UART_Send_FIFO_Task_STAK_SIZE/8];
	#endif
#endif
#endif
#if(UART_3_ENABLE) //BUFFER UART3
USART_InitTypeDef        UART3_InitStructure;
bool UART3_WordLength_7b = false;
#if(UART_3_INT)
	struct UART3_RING_BUFFER_STRUCT
	{
		__IO U16 rx_head;                /*!< UART Rx ring buffer head index */
		__IO U16 rx_tail;                /*!< UART Rx ring buffer tail index */
		__IO U8  rx[UART_3_RING_BUFSIZE_RX];  /*!< UART Rx data ring buffer */
		#if(UART_3_INT_SEND_MODE==1)
		__IO U16 tx_head;                /*!< UART Tx ring buffer head index */
		__IO U16 tx_tail;                /*!< UART Tx ring buffer tail index */		
		__IO U8  tx[UART_3_RING_BUFSIZE_TX];  /*!< UART Tx data ring buffer */
		#endif
	} UART3_RING_BUFFER;	
	
	#if(UART_3_INT_SEND_MODE==1)
	bool UART3_RING_BUFFER_FLAG_Write_In_Proccess = false;
	bool UART3_RING_BUFFER_FLAG_Sending_In_Proccess = false;
	static U64 UART3_Send_FIFO_Task_STAK[UART_Send_FIFO_Task_STAK_SIZE/8];
	#endif
#endif
#endif
#if(UART_4_ENABLE) //BUFFER UART4
USART_InitTypeDef        UART4_InitStructure;
bool UART4_WordLength_7b = false;
#if(UART_4_INT)
	struct UART4_RING_BUFFER_STRUCT
	{
		__IO U16 rx_head;                /*!< UART Rx ring buffer head index */
		__IO U16 rx_tail;                /*!< UART Rx ring buffer tail index */
		__IO U8  rx[UART_4_RING_BUFSIZE_RX];  /*!< UART Rx data ring buffer */
		#if(UART_4_INT_SEND_MODE==1)
		__IO U16 tx_head;                /*!< UART Tx ring buffer head index */
		__IO U16 tx_tail;                /*!< UART Tx ring buffer tail index */		
		__IO U8  tx[UART_4_RING_BUFSIZE_TX];  /*!< UART Tx data ring buffer */
		#endif
	} UART4_RING_BUFFER;	
	
	#if(UART_4_INT_SEND_MODE==1)
	bool UART4_RING_BUFFER_FLAG_Write_In_Proccess = false;
	bool UART4_RING_BUFFER_FLAG_Sending_In_Proccess = false;
	static U64 UART4_Send_FIFO_Task_STAK[UART_Send_FIFO_Task_STAK_SIZE/8];
	#endif
#endif
#endif
	#if(UART_5_ENABLE) //BUFFER UART5
USART_InitTypeDef        UART5_InitStructure;
bool UART5_WordLength_7b = false;
#if(UART_5_INT)
	struct UART5_RING_BUFFER_STRUCT
	{
		__IO U16 rx_head;                /*!< UART Rx ring buffer head index */
		__IO U16 rx_tail;                /*!< UART Rx ring buffer tail index */
		__IO U8  rx[UART_5_RING_BUFSIZE_RX];  /*!< UART Rx data ring buffer */
		#if(UART_5_INT_SEND_MODE==1)
		__IO U16 tx_head;                /*!< UART Tx ring buffer head index */
		__IO U16 tx_tail;                /*!< UART Tx ring buffer tail index */		
		__IO U8  tx[UART_5_RING_BUFSIZE_TX];  /*!< UART Tx data ring buffer */
		#endif
	} UART5_RING_BUFFER;	
	
	#if(UART_5_INT_SEND_MODE==1)
	bool UART5_RING_BUFFER_FLAG_Write_In_Proccess = false;
	bool UART5_RING_BUFFER_FLAG_Sending_In_Proccess = false;
	static U64 UART5_Send_FIFO_Task_STAK[UART_Send_FIFO_Task_STAK_SIZE/8];
	#endif
#endif
#endif

U8 UART_TimerChannel;
	
volatile bool UART_MutexHandleSendingChar[2];
volatile bool UART_MutexHandleSendingString[2];
volatile bool UART_MutexHandleReceiveChar[2];
volatile bool UART_MutexHandleReceiveString[2];
volatile bool UART_MutexHandleUpdateSetting[2];
volatile bool UART_MutexHandleResetFIFO[2];
volatile bool UART_MutexHandleReadStateFIFO[2];
#if((UART_1_ENABLE&&UART_1_INT&&(UART_1_INT_SEND_MODE==1))||(UART_2_ENABLE&&UART_2_INT&&(UART_2_INT_SEND_MODE==1))||(UART_3_ENABLE&&UART_3_INT&&(UART_3_INT_SEND_MODE==1))||(UART_4_ENABLE&&UART_4_INT&&(UART_4_INT_SEND_MODE==1))||(UART_5_ENABLE&&UART_5_INT&&(UART_5_INT_SEND_MODE==1)))
volatile bool UART_MutexHandleSendingStringFIFO[2];
#endif
volatile bool UART_MutexHandleReceiveStringFIFO[2];
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
/**
 * @brief 		initialize UART
*/
void __init_UART(void)//INIT UARTs
{

	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleSendingChar[0]);
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleSendingString[0]);
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleReceiveChar[0]);
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleReceiveString[0]);
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleUpdateSetting[0]);
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleResetFIFO[0]);
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleReadStateFIFO[0]);
	#if((UART_1_ENABLE&&UART_1_INT&&(UART_1_INT_SEND_MODE==1))||(UART_2_ENABLE&&UART_2_INT&&(UART_2_INT_SEND_MODE==1))||(UART_3_ENABLE&&UART_3_INT&&(UART_3_INT_SEND_MODE==1))||(UART_4_ENABLE&&UART_4_INT&&(UART_4_INT_SEND_MODE==1))||(UART_5_ENABLE&&UART_5_INT&&(UART_5_INT_SEND_MODE==1)))
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleSendingStringFIFO[0]);
	#endif	
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleReceiveStringFIFO[0]);



	GPIO_InitTypeDef         GPIO_InitStruct;

	#if(UART_1_ENABLE) //INIT UART1 and INTERRUPT

	// Enable clock for GPIO TX
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[UART_1_TX_PINSEL_PORT], ENABLE);
	// Enable clock for GPIO RX
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[UART_1_RX_PINSEL_PORT], ENABLE);

	// Initialize pins as alternating function
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;

	GPIO_InitStruct.GPIO_Pin =  (1 << UART_1_TX_PINSEL_PIN);
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[UART_1_TX_PINSEL_PORT], &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin =  (1 << UART_1_RX_PINSEL_PIN);
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[UART_1_RX_PINSEL_PORT], &GPIO_InitStruct);

	GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[UART_1_TX_PINSEL_PORT], UART_1_TX_PINSEL_PIN, GPIO_AF_USART1);
	GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[UART_1_RX_PINSEL_PORT], UART_1_RX_PINSEL_PIN, GPIO_AF_USART1);

	//Enable clock for USART1 peripheral
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	if(!UART_Inited)
	{
		/// Update UART1 data setting
		UART1_UpdateSetting(UART_1_BOUDRATE, UART_1_DATABIT, UART_1_PARITY, UART_1_STOPBIT, true);

		#if(UART_1_INT&&(UART_1_INT_SEND_MODE==1)) //INIT TASK UART1
		/// Add "UART1_SEND_FIFO" task
		TaskManager_Add("UART1_SEND_FIFO", UART1_Send_FIFO_Task, UART_1_INT_SEND_PRIORITY, &UART1_Send_FIFO_Task_STAK, sizeof(UART1_Send_FIFO_Task_STAK));
		#endif

		#if(UART_1_INT&&(UART_1_INT_SEND_MODE==2))
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		DMA_DeInit(DMA1_Channel1);
		#endif
	}
	else
	{
		UART1_UpdateSetting(NULL,NULL,NULL,NULL, false);
	}
	#endif

	#if(UART_2_ENABLE) //INIT UART2 and INTERRUPT

	// Enable clock for GPIO TX
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[UART_2_TX_PINSEL_PORT], ENABLE);
	// Enable clock for GPIO RX
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[UART_2_RX_PINSEL_PORT], ENABLE);

	// Initialize pins as alternating function
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;

	GPIO_InitStruct.GPIO_Pin =  (1 << UART_2_TX_PINSEL_PIN);
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[UART_2_TX_PINSEL_PORT], &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin =  (1 << UART_2_RX_PINSEL_PIN);
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[UART_2_RX_PINSEL_PORT], &GPIO_InitStruct);

	GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[UART_2_TX_PINSEL_PORT], UART_2_TX_PINSEL_PIN, GPIO_AF_USART2);
	GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[UART_2_RX_PINSEL_PORT], UART_2_RX_PINSEL_PIN, GPIO_AF_USART2);

	//Enable clock for USART2 peripheral
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	if(!UART_Inited)
	{
		/// Update UART2 data setting
		UART2_UpdateSetting(UART_2_BOUDRATE, UART_2_DATABIT, UART_2_PARITY, UART_2_STOPBIT, true);

		#if(UART_2_INT&&(UART_2_INT_SEND_MODE==1)) //INIT TASK UART2
		/// Add "UART2_SEND_FIFO" task
		TaskManager_Add("UART2_SEND_FIFO", UART2_Send_FIFO_Task, UART_2_INT_SEND_PRIORITY, &UART2_Send_FIFO_Task_STAK, sizeof(UART2_Send_FIFO_Task_STAK));
		#endif

		#if(UART_2_INT&&(UART_2_INT_SEND_MODE==2))
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		DMA_DeInit(DMA1_Channel1);
		#endif
	}
	else
	{
		UART2_UpdateSetting(NULL,NULL,NULL,NULL, false);
	}
	#endif
	#if(UART_3_ENABLE) //INIT UART3 and INTERRUPT

	// Enable clock for GPIO TX
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[UART_3_TX_PINSEL_PORT], ENABLE);
	// Enable clock for GPIO RX
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[UART_3_RX_PINSEL_PORT], ENABLE);

	// Initialize pins as alternating function
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;

	GPIO_InitStruct.GPIO_Pin =  (1 << UART_3_TX_PINSEL_PIN);
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[UART_3_TX_PINSEL_PORT], &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin =  (1 << UART_3_RX_PINSEL_PIN);
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[UART_3_RX_PINSEL_PORT], &GPIO_InitStruct);

	GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[UART_3_TX_PINSEL_PORT], UART_3_TX_PINSEL_PIN, GPIO_AF_USART3);
	GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[UART_3_RX_PINSEL_PORT], UART_3_RX_PINSEL_PIN, GPIO_AF_USART3);

	//Enable clock for USART3 peripheral
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	if(!UART_Inited)
	{
		/// Update UART3 data setting
		UART3_UpdateSetting(UART_3_BOUDRATE, UART_3_DATABIT, UART_3_PARITY, UART_3_STOPBIT, true);

		#if(UART_3_INT&&(UART_3_INT_SEND_MODE==1)) //INIT TASK UART3
		/// Add "UART3_SEND_FIFO" task
		TaskManager_Add("UART3_SEND_FIFO", UART3_Send_FIFO_Task, UART_3_INT_SEND_PRIORITY, &UART3_Send_FIFO_Task_STAK, sizeof(UART3_Send_FIFO_Task_STAK));
		#endif

		#if(UART_3_INT&&(UART_3_INT_SEND_MODE==2))
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		DMA_DeInit(DMA1_Channel1);
		#endif
	}
	else
	{
		UART3_UpdateSetting(NULL,NULL,NULL,NULL, false);
	}

	#endif
	#if(UART_4_ENABLE) //INIT UART4 and INTERRUPT

	// Enable clock for GPIO TX
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[UART_4_TX_PINSEL_PORT], ENABLE);
	// Enable clock for GPIO RX
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[UART_4_RX_PINSEL_PORT], ENABLE);

	// Initialize pins as alternating function
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;

	GPIO_InitStruct.GPIO_Pin =  (1 << UART_4_TX_PINSEL_PIN);
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[UART_4_TX_PINSEL_PORT], &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin =  (1 << UART_4_RX_PINSEL_PIN);
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[UART_4_RX_PINSEL_PORT], &GPIO_InitStruct);

	GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[UART_4_TX_PINSEL_PORT], UART_4_TX_PINSEL_PIN, GPIO_AF_UART4);
	GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[UART_4_RX_PINSEL_PORT], UART_4_RX_PINSEL_PIN, GPIO_AF_UART4);

	//Enable clock for USART4 peripheral
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	if(!UART_Inited)
	{
		/// Update UART4 data setting
		UART4_UpdateSetting(UART_4_BOUDRATE, UART_4_DATABIT, UART_4_PARITY, UART_4_STOPBIT, true);

		#if(UART_4_INT&&(UART_4_INT_SEND_MODE==1)) //INIT TASK UART4
		/// Add "UART4_SEND_FIFO" task
		TaskManager_Add("UART4_SEND_FIFO", UART4_Send_FIFO_Task, UART_4_INT_SEND_PRIORITY, &UART4_Send_FIFO_Task_STAK, sizeof(UART4_Send_FIFO_Task_STAK));
		#endif

		#if(UART_4_INT&&(UART_4_INT_SEND_MODE==2))
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		DMA_DeInit(DMA1_Channel1);
		#endif
	}
	else
	{
		UART4_UpdateSetting(NULL,NULL,NULL,NULL, false);
	}

	#endif
	#if(UART_5_ENABLE) //INIT UART5 and INTERRUPT

	// Enable clock for GPIO TX
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[UART_5_TX_PINSEL_PORT], ENABLE);
	// Enable clock for GPIO RX
	RCC_AHBPeriphClockCmd(GPIO_PORTCLOCK[UART_5_RX_PINSEL_PORT], ENABLE);

	// Initialize pins as alternating function
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;

	GPIO_InitStruct.GPIO_Pin =  (1 << UART_5_TX_PINSEL_PIN);
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[UART_5_TX_PINSEL_PORT], &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin =  (1 << UART_5_RX_PINSEL_PIN);
	GPIO_Init((GPIO_TypeDef*)GPIO_PORTSEL[UART_5_RX_PINSEL_PORT], &GPIO_InitStruct);

	GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[UART_5_TX_PINSEL_PORT], UART_5_TX_PINSEL_PIN, GPIO_AF_UART5);
	GPIO_PinAFConfig((GPIO_TypeDef*)GPIO_PORTSEL[UART_5_RX_PINSEL_PORT], UART_5_RX_PINSEL_PIN, GPIO_AF_UART5);

	//Enable clock for USART5 peripheral
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

	if(!UART_Inited)
	{
		/// Update UART5 data setting
		UART5_UpdateSetting(UART_5_BOUDRATE, UART_5_DATABIT, UART_5_PARITY, UART_5_STOPBIT, true);

		#if(UART_5_INT&&(UART_5_INT_SEND_MODE==1)) //INIT TASK UART5
		/// Add "UART5_SEND_FIFO" task
		TaskManager_Add("UART5_SEND_FIFO", UART5_Send_FIFO_Task, UART_5_INT_SEND_PRIORITY, &UART5_Send_FIFO_Task_STAK, sizeof(UART5_Send_FIFO_Task_STAK));
		#endif

		#if(UART_5_INT&&(UART_5_INT_SEND_MODE==2))
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		DMA_DeInit(DMA1_Channel1);
		#endif
	}
	else
	{
		UART5_UpdateSetting(NULL,NULL,NULL,NULL, false);
	}
	#endif

	UART_Inited = true;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		Uninit UART
*/
void __uninit_UART(void)//UNINIT UARTs
{
//	GPIO_InitTypeDef         GPIO_InitStruct;

#if(UART_1_ENABLE)
	/// Uninit UART1
	#if(UART_1_WAKEUPINSLEEP==0)
	USART_DeInit(USART1);
	#endif	
		
#endif	
#if(UART_2_ENABLE)
	/// Uninit UART2
	#if(UART_2_WAKEUPINSLEEP==0)
	USART_DeInit(USART2);
	#endif	

#endif	
#if(UART_3_ENABLE)
	/// Uninit UART3
	#if(UART_3_WAKEUPINSLEEP==0)
	USART_DeInit(USART3);
	#endif	
#endif	
#if(UART_4_ENABLE)
	/// Uninit UART4
	#if(UART_4_WAKEUPINSLEEP==0)
	USART_DeInit(UART4);
	#endif	
#endif	
#if(UART_5_ENABLE)
	/// Uninit UART5
	#if(UART_5_WAKEUPINSLEEP==0)
	USART_DeInit(UART5);
	#endif	
#endif		

}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_1_ENABLE) //UPDATE UART1 SETTING
/**
 * @brief 		Update data setting UART1
 * @param[in]	Boudrate Boudrate = {Standard Range}
 * @param[in]	DataBit DataBit = {5,6,7,8}
 * @param[in]	Parity Parity = {None=0,Odd=1,Even=2,Sp_1=3,Sp_0=4}
 * @param[in]	StopBit StopBit = {1,2}
 * @param[in]	MustUpdate if ==false update with old static setting struct
*/
void UART1_UpdateSetting(U32 Boudrate, U16 DataBit, U16 Parity, U16 StopBit, bool MustUpdate)
{
	// UART Configuration structure variable
	NVIC_InitTypeDef         NVIC_InitStructure;
	
	USART_DeInit(USART1);
	
	///	Ckecking MustUpdate	
	if(MustUpdate)
	{	
		/// Initialize uart Config
		UART1_InitStructure.USART_BaudRate = Boudrate;
		if(DataBit == 0x2000)
		{
			DataBit = USART_WordLength_8b;
			UART1_WordLength_7b = true;
		}		
		else
		{
			UART1_WordLength_7b = false;
		}
		
		UART1_InitStructure.USART_WordLength = DataBit;
		UART1_InitStructure.USART_StopBits = StopBit;
		UART1_InitStructure.USART_Parity = Parity;
		UART1_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		UART1_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	}

	// USART configuration 
	USART_Init(USART1, &UART1_InitStructure);

#if(UART_1_INT) //INIT INTERRUPT UART1
	UART1_Reset_Buffer_FIFO();
	
	// Enable the USART1 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART_1_INT_RECEIVE_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
		
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
#endif
		
	USART_Cmd(USART1, ENABLE);

}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_2_ENABLE) //UPDATE UART2 SETTING
/**
 * @brief 		Update data setting UART2
 * @param[in]	Boudrate Boudrate = {Standard Range}
 * @param[in]	DataBit DataBit = {5,6,7,8}
 * @param[in]	Parity Parity = {None=0,Odd=1,Even=2,Sp_1=3,Sp_0=4}
 * @param[in]	StopBit StopBit = {1,2}
 * @param[in]	MustUpdate if ==false update with old static setting struct
*/
void UART2_UpdateSetting(U32 Boudrate, U16 DataBit, U16 Parity, U16 StopBit, bool MustUpdate)
{
	// UART Configuration structure variable
	NVIC_InitTypeDef         NVIC_InitStructure;
	
	USART_DeInit(USART2);
	
	///	Ckecking MustUpdate	
	if(MustUpdate)
	{	
		/// Initialize uart Config
		UART2_InitStructure.USART_BaudRate = Boudrate;
		if(DataBit == 0x2000)
		{
			DataBit = USART_WordLength_8b;
			UART2_WordLength_7b = true;
		}
		else
		{
			UART2_WordLength_7b = false;
		}

		UART2_InitStructure.USART_WordLength = DataBit;
		UART2_InitStructure.USART_StopBits = StopBit;
		UART2_InitStructure.USART_Parity = Parity;
		UART2_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		UART2_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	}

	// USART configuration 
	USART_Init(USART2, &UART2_InitStructure);

#if(UART_2_INT) //INIT INTERRUPT UART2
	UART2_Reset_Buffer_FIFO();
	
	// Enable the USART2 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART_2_INT_RECEIVE_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
#endif
	
	USART_Cmd(USART2, ENABLE);

}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_3_ENABLE) //UPDATE UART3 SETTING
/**
 * @brief 		Update data setting UART3
 * @param[in]	Boudrate Boudrate = {Standard Range}
 * @param[in]	DataBit DataBit = {5,6,7,8}
 * @param[in]	Parity Parity = {None=0,Odd=1,Even=2,Sp_1=3,Sp_0=4}
 * @param[in]	StopBit StopBit = {1,2}
 * @param[in]	MustUpdate if ==false update with old static setting struct
*/
void UART3_UpdateSetting(U32 Boudrate, U16 DataBit, U16 Parity, U16 StopBit, bool MustUpdate)
{
	// UART Configuration structure variable
	NVIC_InitTypeDef         NVIC_InitStructure;
	
	USART_DeInit(USART3);
	
	///	Ckecking MustUpdate	
	if(MustUpdate)
	{	
		/// Initialize uart Config
		UART3_InitStructure.USART_BaudRate = Boudrate;
		if(DataBit == 0x2000)
		{
			DataBit = USART_WordLength_8b;
			UART3_WordLength_7b = true;
		}		
		else
		{
			UART3_WordLength_7b = false;
		}
		
		UART3_InitStructure.USART_WordLength = DataBit;
		UART3_InitStructure.USART_StopBits = StopBit;
		UART3_InitStructure.USART_Parity = Parity;
		UART3_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		UART3_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	}

	// USART configuration 
	USART_Init(USART3, &UART3_InitStructure);

#if(UART_3_INT) //INIT INTERRUPT UART3
	UART3_Reset_Buffer_FIFO();
	
	// Enable the USART3 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART_3_INT_RECEIVE_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
		
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
#endif
		
	USART_Cmd(USART3, ENABLE);

}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_4_ENABLE) //UPDATE UART1 SETTING
/**
 * @brief 		Update data setting UART4
 * @param[in]	Boudrate Boudrate = {Standard Range}
 * @param[in]	DataBit DataBit = {5,6,7,8}
 * @param[in]	Parity Parity = {None=0,Odd=1,Even=2,Sp_1=3,Sp_0=4}
 * @param[in]	StopBit StopBit = {1,2}
 * @param[in]	MustUpdate if ==false update with old static setting struct
*/
void UART4_UpdateSetting(U32 Boudrate, U16 DataBit, U16 Parity, U16 StopBit, bool MustUpdate)
{
	// UART Configuration structure variable
	NVIC_InitTypeDef         NVIC_InitStructure;
	
	USART_DeInit(UART4);
	
	///	Ckecking MustUpdate	
	if(MustUpdate)
	{	
		/// Initialize uart Config
		UART4_InitStructure.USART_BaudRate = Boudrate;
		if(DataBit == 0x2000)
		{
			DataBit = USART_WordLength_8b;
			UART4_WordLength_7b = true;
		}		
		else
		{
			UART4_WordLength_7b = false;
		}
		
		UART4_InitStructure.USART_WordLength = DataBit;
		UART4_InitStructure.USART_StopBits = StopBit;
		UART4_InitStructure.USART_Parity = Parity;
		UART4_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		UART4_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	}

	// USART configuration 
	USART_Init(UART4, &UART4_InitStructure);

#if(UART_4_INT) //INIT INTERRUPT UART4
	UART4_Reset_Buffer_FIFO();
	
	// Enable the USART4 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART_4_INT_RECEIVE_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
		
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
#endif
		
	USART_Cmd(UART4, ENABLE);

}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_5_ENABLE) //UPDATE UART5 SETTING
/**
 * @brief 		Update data setting UART5
 * @param[in]	Boudrate Boudrate = {Standard Range}
 * @param[in]	DataBit DataBit = {5,6,7,8}
 * @param[in]	Parity Parity = {None=0,Odd=1,Even=2,Sp_1=3,Sp_0=4}
 * @param[in]	StopBit StopBit = {1,2}
 * @param[in]	MustUpdate if ==false update with old static setting struct
*/
void UART5_UpdateSetting(U32 Boudrate, U16 DataBit, U16 Parity, U16 StopBit, bool MustUpdate)
{
	// UART Configuration structure variable
	NVIC_InitTypeDef         NVIC_InitStructure;
	
	USART_DeInit(UART5);
	
	///	Ckecking MustUpdate	
	if(MustUpdate)
	{	
		/// Initialize uart Config
		UART5_InitStructure.USART_BaudRate = Boudrate;
		if(DataBit == 0x2000)
		{
			DataBit = USART_WordLength_8b;
			UART5_WordLength_7b = true;
		}		
		else
		{
			UART5_WordLength_7b = false;
		}
		
		UART5_InitStructure.USART_WordLength = DataBit;
		UART5_InitStructure.USART_StopBits = StopBit;
		UART5_InitStructure.USART_Parity = Parity;
		UART5_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		UART5_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	}

	// USART configuration 
	USART_Init(UART5, &UART5_InitStructure);

#if(UART_5_INT) //INIT INTERRUPT UART5
	UART5_Reset_Buffer_FIFO();
	
	// Enable the USART5 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART_5_INT_RECEIVE_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
		
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
#endif
		
	USART_Cmd(UART5, ENABLE);

}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if((UART_1_ENABLE)||(UART_2_ENABLE)||(UART_3_ENABLE)||(UART_4_ENABLE)||(UART_5_ENABLE))
/**
 * @brief 		Update data setting UART
 * @param[in]	Port Uart number
 * @param[in]	Boudrate Boudrate = {Standard Range}
 * @param[in]	DataBit DataBit = {5,6,7,8}
 * @param[in]	Parity Parity = {None=0,Odd=1,Even=2,Sp_1=3,Sp_0=4}
 * @param[in]	StopBit StopBit = {1,2}
 * @param[in]	MustUpdate if ==false update with old static setting struct
*/
void UART_UpdateSetting(U8 Port, U32 Boudrate, U16 DataBit, U16 Parity, U16 StopBit, bool MustUpdate)
{

	/// Wait Mutex UART_MutexHandleUpdateSetting[0]
	TASK_MANAGER_MUTEXWAIT(UART_MutexHandleUpdateSetting[0]);

	#if(UART_1_ENABLE)
	if(Port==1)
	{
		UART1_UpdateSetting(Boudrate, DataBit, Parity, StopBit, MustUpdate);
	}
	#endif
		
	#if(UART_2_ENABLE)
	if(Port==2)
	{
		UART2_UpdateSetting(Boudrate, DataBit, Parity, StopBit, MustUpdate);
	}
	#endif

	#if(UART_3_ENABLE)
	if(Port==3)
	{
		UART3_UpdateSetting(Boudrate, DataBit, Parity, StopBit, MustUpdate);
	}
	#endif
	#if(UART_4_ENABLE)
	if(Port==4)
	{
		UART4_UpdateSetting(Boudrate, DataBit, Parity, StopBit, MustUpdate);
	}
	#endif

	#if(UART_5_ENABLE)
	if(Port==5)
	{
		UART5_UpdateSetting(Boudrate, DataBit, Parity, StopBit, MustUpdate);
	}
	#endif
	
	/// Release Mutex UART_MutexHandleUpdateSetting[0]
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleUpdateSetting[0]);
		
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_1_ENABLE&&UART_1_INT) //RESET FIFO UART1
/**
 * @brief 		Reset soft fifo uart1
*/
void UART1_Reset_Buffer_FIFO(void)
{
	/// Reset uart1 ring buf head and tail idx
	__BUF_RESET(UART1_RING_BUFFER.rx_head);
	__BUF_RESET(UART1_RING_BUFFER.rx_tail);
	#if(UART_1_INT_SEND_MODE==1)	
	__BUF_RESET(UART1_RING_BUFFER.tx_head);
	__BUF_RESET(UART1_RING_BUFFER.tx_tail);
	#endif
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_2_ENABLE&&UART_2_INT) //RESET FIFO UART2
/**
 * @brief 		Reset soft fifo uart2
*/
void UART2_Reset_Buffer_FIFO(void)
{
	/// Reset uart2 ring buf head and tail idx
	__BUF_RESET(UART2_RING_BUFFER.rx_head);
	__BUF_RESET(UART2_RING_BUFFER.rx_tail);
	#if(UART_2_INT_SEND_MODE==1)	
	__BUF_RESET(UART2_RING_BUFFER.tx_head);
	__BUF_RESET(UART2_RING_BUFFER.tx_tail);
	#endif
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_3_ENABLE&&UART_3_INT) //RESET FIFO UART3
/**
 * @brief 		Reset soft fifo uart3
*/
void UART3_Reset_Buffer_FIFO(void)
{
	/// Reset uart3 ring buf head and tail idx
	__BUF_RESET(UART3_RING_BUFFER.rx_head);
	__BUF_RESET(UART3_RING_BUFFER.rx_tail);
	#if(UART_3_INT_SEND_MODE==1)	
	__BUF_RESET(UART3_RING_BUFFER.tx_head);
	__BUF_RESET(UART3_RING_BUFFER.tx_tail);
	#endif
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_4_ENABLE&&UART_4_INT) //RESET FIFO UART4
/**
 * @brief 		Reset soft fifo uart4
*/
void UART4_Reset_Buffer_FIFO(void)
{
	/// Reset uart4 ring buf head and tail idx
	__BUF_RESET(UART4_RING_BUFFER.rx_head);
	__BUF_RESET(UART4_RING_BUFFER.rx_tail);
	#if(UART_4_INT_SEND_MODE==1)	
	__BUF_RESET(UART4_RING_BUFFER.tx_head);
	__BUF_RESET(UART4_RING_BUFFER.tx_tail);
	#endif
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_5_ENABLE&&UART_5_INT) //RESET FIFO UART5
/**
 * @brief 		Reset soft fifo uart5
*/
void UART5_Reset_Buffer_FIFO(void)
{
	/// Reset uart5 ring buf head and tail idx
	__BUF_RESET(UART5_RING_BUFFER.rx_head);
	__BUF_RESET(UART5_RING_BUFFER.rx_tail);
	#if(UART_5_INT_SEND_MODE==1)	
	__BUF_RESET(UART5_RING_BUFFER.tx_head);
	__BUF_RESET(UART5_RING_BUFFER.tx_tail);
	#endif
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if((UART_1_ENABLE&&UART_1_INT)||(UART_2_ENABLE&&UART_2_INT)||(UART_3_ENABLE&&UART_3_INT)||(UART_4_ENABLE&&UART_4_INT)||(UART_5_ENABLE&&UART_5_INT))
/**
 * @brief 		Reset soft fifo uart
 * @param[in]	Port Uart number
*/
void UART_Reset_Buffer_FIFO(U8 Port)
{
	
	/// Wait Mutex UART_MutexHandleResetFIFO[0]
	TASK_MANAGER_MUTEXWAIT(UART_MutexHandleResetFIFO[0]);

	#if(UART_1_ENABLE&&UART_1_INT)
	if(Port==1)
	{	
		UART1_Reset_Buffer_FIFO();
	}
	#endif

	#if(UART_2_ENABLE&&UART_2_INT)
	if(Port==2)
	{	
		UART2_Reset_Buffer_FIFO();
	}
	#endif

	#if(UART_3_ENABLE&&UART_3_INT)
	if(Port==3)
	{	
		UART3_Reset_Buffer_FIFO();
	}
	#endif

	#if(UART_4_ENABLE&&UART_4_INT)
	if(Port==4)
	{	
		UART4_Reset_Buffer_FIFO();
	}
	#endif

	#if(UART_5_ENABLE&&UART_5_INT)
	if(Port==5)
	{	
		UART5_Reset_Buffer_FIFO();
	}
	#endif
	
	/// Release Mutex UART_MutexHandleResetFIFO[0]
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleResetFIFO[0]);
		
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if((UART_1_ENABLE)||(UART_2_ENABLE)||(UART_3_ENABLE)||(UART_4_ENABLE)||(UART_5_ENABLE))  //SEND CHAR TO UARTs
/**
 * @brief 		Send char UART
 * @param[in]	Port Uart number
 * @param[in]	input char for send
*/
void UART_Send_Char(U8 Port, U8 input)
{
	/// Wait Mutex UART_MutexHandleSendingChar[0]
	TASK_MANAGER_MUTEXWAIT(UART_MutexHandleSendingChar[0]);

	#if(UART_1_ENABLE)
	if(Port==1)
	{
		TASK_MANAGER_LOOPUNTIL(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		USART_SendData(USART1, input);
		TASK_MANAGER_LOOPUNTIL(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		
	}
	#endif
	
	#if(UART_2_ENABLE)
	if(Port==2)
	{
		TASK_MANAGER_LOOPUNTIL(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2, input);
		TASK_MANAGER_LOOPUNTIL(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	}
	#endif
	
	#if(UART_3_ENABLE)
	if(Port==3)
	{
		TASK_MANAGER_LOOPUNTIL(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
		USART_SendData(USART3, input);
		TASK_MANAGER_LOOPUNTIL(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	}
	#endif
	
	#if(UART_4_ENABLE)
	if(Port==4)
	{
		TASK_MANAGER_LOOPUNTIL(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
		USART_SendData(UART4, input);
		TASK_MANAGER_LOOPUNTIL(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	}
	#endif
	
	#if(UART_5_ENABLE)
	if(Port==5)
	{
		TASK_MANAGER_LOOPUNTIL(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
		USART_SendData(UART5, input);
		TASK_MANAGER_LOOPUNTIL(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
	}
	#endif
	
	/// Release Mutex UART_MutexHandleSendingChar[0]	
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleSendingChar[0]);
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if((UART_1_ENABLE)||(UART_2_ENABLE)||(UART_3_ENABLE)||(UART_4_ENABLE)||(UART_5_ENABLE))  //SEND STRING TO UARTs
/**
 * @brief 		Send string UART
 * @param[in]	Port Uart number
 * @param[in]	input *input for send
 * @param[in]	Size size of *input
*/
void UART_Send_String(U8 Port,U8 *input, uint16_t Size)
{

	/// Wait Mutex UART_MutexHandleSendingString[0]
	TASK_MANAGER_MUTEXWAIT(UART_MutexHandleSendingString[0]);

#if(UART_1_ENABLE)
		if(Port==1)
		{
#if(UART_1_INT&&(UART_1_INT_SEND_MODE==1))	
		for(int i = 0, Length = 0; i<Size ; )
		{
			  Length = (((Size-i)>=UART_1_RING_BUFSIZE_TX)?(UART_1_RING_BUFSIZE_TX):(Size-i));
		UART1_Send_String_FIFO(&input[i],Length);	
			  i+=Length;
		}
#elif(UART_1_INT&&(UART_1_INT_SEND_MODE==2))
		DMA_InitTypeDef  DMA_InitStructure;

		// Setup GPDMA channel --------------------------------
		DMA_InitStructure.DMA_MemoryBaseAddr = (U32)input;
		DMA_InitStructure.DMA_PeripheralBaseAddr = (U32)(USART1->DR);
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		DMA_InitStructure.DMA_BufferSize = Size;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;

		
		DMA_Init(DMA1_Channel1, &DMA_InitStructure);
		DMA_Cmd(DMA1_Channel1, ENABLE);
		USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
		
		TASK_MANAGER_LOOPUNTIL(DMA_GetFlagStatus(DMA1_IT_TC1) == RESET); 
		DMA_ClearFlag(DMA1_IT_HT1  | DMA1_IT_TC1);

#else	
		while(Size--)
		{
			UART_Send_Char(1, *(input++));
		}
#endif	
		}
#endif
		
#if(UART_2_ENABLE)
		if(Port==2)
		{
#if(UART_2_INT&&(UART_2_INT_SEND_MODE==1))	
		for(int i = 0, Length = 0; i<Size ; )
		{
			  Length = (((Size-i)>=UART_2_RING_BUFSIZE_TX)?(UART_2_RING_BUFSIZE_TX):(Size-i));
		UART2_Send_String_FIFO(&input[i],Length);	
			  i+=Length;
		}
#elif(UART_2_INT&&(UART_2_INT_SEND_MODE==2))
		DMA_InitTypeDef  DMA_InitStructure;
		
		// Setup GPDMA channel --------------------------------
		DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
		DMA_InitStructure.DMA_Memory0BaseAddr = (U32)input;
		DMA_InitStructure.DMA_PeripheralBaseAddr = (U32)(USART2->DR);
		DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
		DMA_InitStructure.DMA_BufferSize = Size;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
		DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
		DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
		DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		
		DMA_Init(DMA1_Stream0, &DMA_InitStructure);
		DMA_Cmd(DMA1_Stream0, ENABLE);
		USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
		
		TASK_MANAGER_LOOPUNTIL(DMA_GetFlagStatus(DMA1_Stream0, DMA_FLAG_TCIF0) == RESET); 
		DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_HTIF0  | DMA_FLAG_TCIF0);

#else	
		while(Size--)
		{
			UART_Send_Char(2, *(input++));
		}
#endif	
		}
#endif
		
#if(UART_3_ENABLE)
		if(Port==3)
		{
#if(UART_3_INT&&(UART_3_INT_SEND_MODE==1))	
		for(int i = 0, Length = 0; i<Size ; )
		{
			  Length = (((Size-i)>=UART_3_RING_BUFSIZE_TX)?(UART_3_RING_BUFSIZE_TX):(Size-i));
		UART3_Send_String_FIFO(&input[i],Length);	
			  i+=Length;
		}
#elif(UART_3_INT&&(UART_3_INT_SEND_MODE==2))
		DMA_InitTypeDef  DMA_InitStructure;
		
		// Setup GPDMA channel --------------------------------
		DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
		DMA_InitStructure.DMA_Memory0BaseAddr = (U32)input;
		DMA_InitStructure.DMA_PeripheralBaseAddr = (U32)(USART3->DR);
		DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
		DMA_InitStructure.DMA_BufferSize = Size;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
		DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
		DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
		DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		
		DMA_Init(DMA1_Stream0, &DMA_InitStructure);
		DMA_Cmd(DMA1_Stream0, ENABLE);
		USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
		
		TASK_MANAGER_LOOPUNTIL(DMA_GetFlagStatus(DMA1_Stream0, DMA_FLAG_TCIF0) == RESET); 
		DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_HTIF0  | DMA_FLAG_TCIF0);

#else	
		while(Size--)
		{
			UART_Send_Char(3, *(input++));
		}
#endif	
		}
#endif

#if(UART_4_ENABLE)
		if(Port==4)
		{
#if(UART_4_INT&&(UART_4_INT_SEND_MODE==1))	
		for(int i = 0, Length = 0; i<Size ; )
		{
			  Length = (((Size-i)>=UART_4_RING_BUFSIZE_TX)?(UART_4_RING_BUFSIZE_TX):(Size-i));
		UART4_Send_String_FIFO(&input[i],Length);	
			  i+=Length;
		}
#elif(UART_4_INT&&(UART_4_INT_SEND_MODE==2))
		DMA_InitTypeDef  DMA_InitStructure;
		
		// Setup GPDMA channel --------------------------------
		DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
		DMA_InitStructure.DMA_Memory0BaseAddr = (U32)input;
		DMA_InitStructure.DMA_PeripheralBaseAddr = (U32)(UART4->DR);
		DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
		DMA_InitStructure.DMA_BufferSize = Size;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
		DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
		DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
		DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		
		DMA_Init(DMA1_Stream0, &DMA_InitStructure);
		DMA_Cmd(DMA1_Stream0, ENABLE);
		USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
		
		TASK_MANAGER_LOOPUNTIL(DMA_GetFlagStatus(DMA1_Stream0, DMA_FLAG_TCIF0) == RESET); 
		DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_HTIF0  | DMA_FLAG_TCIF0);

#else	
		while(Size--)
		{
			UART_Send_Char(4, *(input++));
		}
#endif	
		}
#endif

#if(UART_5_ENABLE)
		if(Port==5)
		{
#if(UART_5_INT&&(UART_5_INT_SEND_MODE==1))	
		for(int i = 0, Length = 0; i<Size ; )
		{
			  Length = (((Size-i)>=UART_5_RING_BUFSIZE_TX)?(UART_5_RING_BUFSIZE_TX):(Size-i));
		UART5_Send_String_FIFO(&input[i],Length);	
			  i+=Length;
		}
#elif(UART_5_INT&&(UART_5_INT_SEND_MODE==2))
		DMA_InitTypeDef  DMA_InitStructure;
		
		// Setup GPDMA channel --------------------------------
		DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
		DMA_InitStructure.DMA_Memory0BaseAddr = (U32)input;
		DMA_InitStructure.DMA_PeripheralBaseAddr = (U32)(UART5->DR);
		DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
		DMA_InitStructure.DMA_BufferSize = Size;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
		DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
		DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
		DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		
		DMA_Init(DMA1_Stream0, &DMA_InitStructure);
		DMA_Cmd(DMA1_Stream0, ENABLE);
		USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
		
		TASK_MANAGER_LOOPUNTIL(DMA_GetFlagStatus(DMA1_Stream0, DMA_FLAG_TCIF0) == RESET); 
		DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_HTIF0  | DMA_FLAG_TCIF0);

#else	
		while(Size--)
		{
			UART_Send_Char(5, *(input++));
		}
#endif	
		}
#endif

	/// Release Mutex UART_MutexHandleSendingString[0]
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleSendingString[0]);
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if((UART_1_ENABLE)||(UART_2_ENABLE)||(UART_3_ENABLE)||(UART_4_ENABLE)||(UART_5_ENABLE))  //RECEIVE CHAR FROM UARTs
/**
 * @brief 		Receive char UART
 * @param[in]	Port Uart number
*/
U8 UART_Receive_Char(U8 Port)
{
	U8   Byte = 0;
	
	/// Wait Mutex UART_MutexHandleReceiveChar[0]
	TASK_MANAGER_MUTEXWAIT(UART_MutexHandleReceiveChar[0]);

	#if(UART_1_ENABLE)
	if(Port==1)
	{
		return USART_ReceiveData(USART1);
	}
	#endif
	
	#if(UART_2_ENABLE)
	if(Port==2)
	{
		return USART_ReceiveData(USART2);
	}
	#endif
	
	#if(UART_3_ENABLE)
	if(Port==3)
	{
		return USART_ReceiveData(USART3);
	}
	#endif
	
	#if(UART_4_ENABLE)
	if(Port==4)
	{
		return USART_ReceiveData(UART4);
	}
	#endif
	
	#if(UART_5_ENABLE)
	if(Port==5)
	{
		return USART_ReceiveData(UART5);
	}
	#endif
	
	/// Release Mutex UART_MutexHandleReceiveChar[0]
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleReceiveChar[0]);
		
	return Byte;
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_1_ENABLE&&UART_1_INT) //READ STATE FIFO UART1
/**
 * @brief 		read state UART1
 * @return 		struct of state
*/
struct UART_State_FIFO_STRUCT UART1_Read_State_FIFO(void)
{
	struct UART_State_FIFO_STRUCT UART1_State_FIFO;
	UART1_State_FIFO.rx_Busy = false;
	UART1_State_FIFO.tx_Busy = false;
	UART1_State_FIFO.rx_Buffer = RESET;
	UART1_State_FIFO.tx_Buffer = RESET;
	UART1_State_FIFO.rx_Length = RESET;
	UART1_State_FIFO.tx_Length = RESET;
	
	if(!__BUF_IS_EMPTY(UART1_RING_BUFFER.rx_head, UART1_RING_BUFFER.rx_tail,UART_1_RING_BUFSIZE_RX))
	{
		UART1_State_FIFO.rx_Busy = true;
	}

	UART1_State_FIFO.rx_Buffer = UART_1_RING_BUFSIZE_RX;
	UART1_State_FIFO.rx_Length = UART1_RING_BUFFER.rx_head - UART1_RING_BUFFER.rx_tail;

	#if(UART_1_INT_SEND_MODE==1)
		UART1_State_FIFO.tx_Busy = UART1_RING_BUFFER_FLAG_Sending_In_Proccess;
		UART1_State_FIFO.tx_Buffer = UART_1_RING_BUFSIZE_TX;
		UART1_State_FIFO.tx_Length = UART1_RING_BUFFER.tx_head - UART1_RING_BUFFER.tx_tail;	
	#endif

	return UART1_State_FIFO;
}
#endif	
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_2_ENABLE&&UART_2_INT) //READ STATE FIFO UART2
/**
 * @brief 		read state UART2
 * @return 		struct of state
*/
struct UART_State_FIFO_STRUCT UART2_Read_State_FIFO(void)
{
	struct UART_State_FIFO_STRUCT UART2_State_FIFO;
	UART2_State_FIFO.rx_Busy = false;
	UART2_State_FIFO.tx_Busy = false;
	UART2_State_FIFO.rx_Buffer = RESET;
	UART2_State_FIFO.tx_Buffer = RESET;
	UART2_State_FIFO.rx_Length = RESET;
	UART2_State_FIFO.tx_Length = RESET;
	
	if(!__BUF_IS_EMPTY(UART2_RING_BUFFER.rx_head, UART2_RING_BUFFER.rx_tail,UART_2_RING_BUFSIZE_RX))
	{
		UART2_State_FIFO.rx_Busy = true;
	}

	UART2_State_FIFO.rx_Buffer = UART_2_RING_BUFSIZE_RX;
	UART2_State_FIFO.rx_Length = UART2_RING_BUFFER.rx_head - UART2_RING_BUFFER.rx_tail;

	#if(UART_2_INT_SEND_MODE==1)
		UART2_State_FIFO.tx_Busy = UART2_RING_BUFFER_FLAG_Sending_In_Proccess;
		UART2_State_FIFO.tx_Buffer = UART_2_RING_BUFSIZE_TX;
		UART2_State_FIFO.tx_Length = UART2_RING_BUFFER.tx_head - UART2_RING_BUFFER.tx_tail;	
	#endif

	return UART2_State_FIFO;
}
#endif	
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_3_ENABLE&&UART_3_INT) //READ STATE FIFO UART3
/**
 * @brief 		read state UART1
 * @return 		struct of state
*/
struct UART_State_FIFO_STRUCT UART3_Read_State_FIFO(void)
{
	struct UART_State_FIFO_STRUCT UART3_State_FIFO;
	UART3_State_FIFO.rx_Busy = false;
	UART3_State_FIFO.tx_Busy = false;
	UART3_State_FIFO.rx_Buffer = RESET;
	UART3_State_FIFO.tx_Buffer = RESET;
	UART3_State_FIFO.rx_Length = RESET;
	UART3_State_FIFO.tx_Length = RESET;
	
	if(!__BUF_IS_EMPTY(UART3_RING_BUFFER.rx_head, UART3_RING_BUFFER.rx_tail,UART_3_RING_BUFSIZE_RX))
	{
		UART3_State_FIFO.rx_Busy = true;
	}

	UART3_State_FIFO.rx_Buffer = UART_3_RING_BUFSIZE_RX;
	UART3_State_FIFO.rx_Length = UART3_RING_BUFFER.rx_head - UART3_RING_BUFFER.rx_tail;

	#if(UART_3_INT_SEND_MODE==1)
		UART3_State_FIFO.tx_Busy = UART3_RING_BUFFER_FLAG_Sending_In_Proccess;
		UART3_State_FIFO.tx_Buffer = UART_3_RING_BUFSIZE_TX;
		UART3_State_FIFO.tx_Length = UART3_RING_BUFFER.tx_head - UART3_RING_BUFFER.tx_tail;	
	#endif

	return UART3_State_FIFO;
}
#endif	
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_4_ENABLE&&UART_4_INT) //READ STATE FIFO UART4
/**
 * @brief 		read state UART1
 * @return 		struct of state
*/
struct UART_State_FIFO_STRUCT UART4_Read_State_FIFO(void)
{
	struct UART_State_FIFO_STRUCT UART4_State_FIFO;
	UART4_State_FIFO.rx_Busy = false;
	UART4_State_FIFO.tx_Busy = false;
	UART4_State_FIFO.rx_Buffer = RESET;
	UART4_State_FIFO.tx_Buffer = RESET;
	UART4_State_FIFO.rx_Length = RESET;
	UART4_State_FIFO.tx_Length = RESET;
	
	if(!__BUF_IS_EMPTY(UART4_RING_BUFFER.rx_head, UART4_RING_BUFFER.rx_tail,UART_4_RING_BUFSIZE_RX))
	{
		UART4_State_FIFO.rx_Busy = true;
	}

	UART4_State_FIFO.rx_Buffer = UART_4_RING_BUFSIZE_RX;
	UART4_State_FIFO.rx_Length = UART4_RING_BUFFER.rx_head - UART4_RING_BUFFER.rx_tail;

	#if(UART_4_INT_SEND_MODE==1)
		UART4_State_FIFO.tx_Busy = UART4_RING_BUFFER_FLAG_Sending_In_Proccess;
		UART4_State_FIFO.tx_Buffer = UART_4_RING_BUFSIZE_TX;
		UART4_State_FIFO.tx_Length = UART4_RING_BUFFER.tx_head - UART4_RING_BUFFER.tx_tail;	
	#endif

	return UART4_State_FIFO;
}
#endif	
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_5_ENABLE&&UART_5_INT) //READ STATE FIFO UART5
/**
 * @brief 		read state UART1
 * @return 		struct of state
*/
struct UART_State_FIFO_STRUCT UART5_Read_State_FIFO(void)
{
	struct UART_State_FIFO_STRUCT UART5_State_FIFO;
	UART5_State_FIFO.rx_Busy = false;
	UART5_State_FIFO.tx_Busy = false;
	UART5_State_FIFO.rx_Buffer = RESET;
	UART5_State_FIFO.tx_Buffer = RESET;
	UART5_State_FIFO.rx_Length = RESET;
	UART5_State_FIFO.tx_Length = RESET;
	
	if(!__BUF_IS_EMPTY(UART5_RING_BUFFER.rx_head, UART5_RING_BUFFER.rx_tail,UART_5_RING_BUFSIZE_RX))
	{
		UART5_State_FIFO.rx_Busy = true;
	}

	UART5_State_FIFO.rx_Buffer = UART_5_RING_BUFSIZE_RX;
	UART5_State_FIFO.rx_Length = UART5_RING_BUFFER.rx_head - UART5_RING_BUFFER.rx_tail;

	#if(UART_5_INT_SEND_MODE==1)
		UART5_State_FIFO.tx_Busy = UART5_RING_BUFFER_FLAG_Sending_In_Proccess;
		UART5_State_FIFO.tx_Buffer = UART_5_RING_BUFSIZE_TX;
		UART5_State_FIFO.tx_Length = UART5_RING_BUFFER.tx_head - UART5_RING_BUFFER.tx_tail;	
	#endif

	return UART5_State_FIFO;
}
#endif	
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if((UART_1_ENABLE&&UART_1_INT)||(UART_2_ENABLE&&UART_2_INT)||(UART_3_ENABLE&&UART_3_INT)||(UART_4_ENABLE&&UART_4_INT)||(UART_5_ENABLE&&UART_5_INT))
/**
 * @brief 		read state UART
 * @param[in]	Port Uart number
 * @return 		struct of state
*/
struct UART_State_FIFO_STRUCT UART_Read_State_FIFO(U8 Port)
{

	/// Wait Mutex UART_MutexHandleReadStateFIFO[0]
	TASK_MANAGER_MUTEXWAIT(UART_MutexHandleReadStateFIFO[0]);

	struct UART_State_FIFO_STRUCT UART_State_FIFO;
	UART_State_FIFO.rx_Busy = false;
	UART_State_FIFO.tx_Busy = false;
	UART_State_FIFO.rx_Buffer = RESET;
	UART_State_FIFO.tx_Buffer = RESET;
	UART_State_FIFO.rx_Length = RESET;
	UART_State_FIFO.tx_Length = RESET;

	#if(UART_1_ENABLE&&UART_1_INT)
	if(Port==1)
	{
		UART_State_FIFO = UART1_Read_State_FIFO();
	}
	#endif

	#if(UART_2_ENABLE&&UART_2_INT)
	if(Port==2)
	{
		UART_State_FIFO = UART2_Read_State_FIFO();
	}
	#endif
	
	#if(UART_3_ENABLE&&UART_3_INT)
	if(Port==3)
	{
		UART_State_FIFO = UART3_Read_State_FIFO();
	}
	#endif
	
	#if(UART_4_ENABLE&&UART_4_INT)
	if(Port==4)
	{
		UART_State_FIFO = UART4_Read_State_FIFO();
	}
	#endif
	
	#if(UART_5_ENABLE&&UART_5_INT)
	if(Port==5)
	{
		UART_State_FIFO = UART5_Read_State_FIFO();
	}
	#endif
	
	/// Release Mutex UART_MutexHandleReadStateFIFO[0]
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleReadStateFIFO[0]);
		
	return UART_State_FIFO;
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_1_ENABLE&&UART_1_INT) //RECEIVE FIFO UART1
/**
 * @brief 		Receive string UART1 from soft fifo
 * @param[output]	rxbuf *rxbuf for receive
 * @param[in]	buflen size of *rxbuf
 * @return 		length receive
*/
U16 UART1_Receive_String_FIFO(U8 *rxbuf,U16 buflen)
{

	U8 *data = (U8 *) &rxbuf[0];
	U16 bytes = 0;

	/// Disable interrupt uart1
	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);

	/// Loop until receive buffer ring is empty or until max_bytes expires 
	while ((buflen > 0) && (!(__BUF_IS_EMPTY(UART1_RING_BUFFER.rx_head, UART1_RING_BUFFER.rx_tail, UART_1_RING_BUFSIZE_RX))))
	{
		/// Read data from ring buffer into user buffer
		*data = UART1_RING_BUFFER.rx[UART1_RING_BUFFER.rx_tail];
		data++;
		/// Update tail pointer
		__BUF_INCR(UART1_RING_BUFFER.rx_tail,UART_1_RING_BUFSIZE_RX);
		/// Increment data count and decrement buffer size count
		bytes++;
		buflen--;
	}
	
	/// Enable interrupt uart1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	return bytes;
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_2_ENABLE&&UART_2_INT) //RECEIVE FIFO UART2
/**
 * @brief 		Receive string UART2 from soft fifo
 * @param[output]	rxbuf *rxbuf for receive
 * @param[in]	buflen size of *rxbuf
 * @return 		length receive
*/
U16 UART2_Receive_String_FIFO(U8 *rxbuf,U16 buflen)
{

	U8 *data = (U8 *) &rxbuf[0];
	U16 bytes = 0;

	/// Disable interrupt uart2
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);

	/// Loop until receive buffer ring is empty or until max_bytes expires 
	while ((buflen > 0) && (!(__BUF_IS_EMPTY(UART2_RING_BUFFER.rx_head, UART2_RING_BUFFER.rx_tail,UART_2_RING_BUFSIZE_RX))))
	{
		/// Read data from ring buffer into user buffer
		*data = UART2_RING_BUFFER.rx[UART2_RING_BUFFER.rx_tail];
		data++;
		/// Update tail pointer
		__BUF_INCR(UART2_RING_BUFFER.rx_tail,UART_2_RING_BUFSIZE_RX);
		/// Increment data count and decrement buffer size count
		bytes++;
		buflen--;
	}
	
	/// Enable interrupt uart2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	return bytes;
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_3_ENABLE&&UART_3_INT) //RECEIVE FIFO UART3
/**
 * @brief 		Receive string UART3 from soft fifo
 * @param[output]	rxbuf *rxbuf for receive
 * @param[in]	buflen size of *rxbuf
 * @return 		length receive
*/
U16 UART3_Receive_String_FIFO(U8 *rxbuf,U16 buflen)
{

	U8 *data = (U8 *) &rxbuf[0];
	U16 bytes = 0;

	/// Disable interrupt uart1
	USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);

	/// Loop until receive buffer ring is empty or until max_bytes expires 
	while ((buflen > 0) && (!(__BUF_IS_EMPTY(UART3_RING_BUFFER.rx_head, UART3_RING_BUFFER.rx_tail, UART_3_RING_BUFSIZE_RX))))
	{
		/// Read data from ring buffer into user buffer
		*data = UART3_RING_BUFFER.rx[UART3_RING_BUFFER.rx_tail];
		data++;
		/// Update tail pointer
		__BUF_INCR(UART3_RING_BUFFER.rx_tail,UART_3_RING_BUFSIZE_RX);
		/// Increment data count and decrement buffer size count
		bytes++;
		buflen--;
	}
	
	/// Enable interrupt uart3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	return bytes;
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_4_ENABLE&&UART_4_INT) //RECEIVE FIFO UART4
/**
 * @brief 		Receive string UART4 from soft fifo
 * @param[output]	rxbuf *rxbuf for receive
 * @param[in]	buflen size of *rxbuf
 * @return 		length receive
*/
U16 UART4_Receive_String_FIFO(U8 *rxbuf,U16 buflen)
{

	U8 *data = (U8 *) &rxbuf[0];
	U16 bytes = 0;

	/// Disable interrupt uart1
	USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);

	/// Loop until receive buffer ring is empty or until max_bytes expires 
	while ((buflen > 0) && (!(__BUF_IS_EMPTY(UART4_RING_BUFFER.rx_head, UART4_RING_BUFFER.rx_tail, UART_4_RING_BUFSIZE_RX))))
	{
		/// Read data from ring buffer into user buffer
		*data = UART4_RING_BUFFER.rx[UART4_RING_BUFFER.rx_tail];
		data++;
		/// Update tail pointer
		__BUF_INCR(UART4_RING_BUFFER.rx_tail,UART_4_RING_BUFSIZE_RX);
		/// Increment data count and decrement buffer size count
		bytes++;
		buflen--;
	}
	
	/// Enable interrupt uart4
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	return bytes;
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_5_ENABLE&&UART_5_INT) //RECEIVE FIFO UART5
/**
 * @brief 		Receive string UART5 from soft fifo
 * @param[output]	rxbuf *rxbuf for receive
 * @param[in]	buflen size of *rxbuf
 * @return 		length receive
*/
U16 UART5_Receive_String_FIFO(U8 *rxbuf,U16 buflen)
{

	U8 *data = (U8 *) &rxbuf[0];
	U16 bytes = 0;

	/// Disable interrupt uart1
	USART_ITConfig(UART5, USART_IT_RXNE, DISABLE);

	/// Loop until receive buffer ring is empty or until max_bytes expires 
	while ((buflen > 0) && (!(__BUF_IS_EMPTY(UART5_RING_BUFFER.rx_head, UART5_RING_BUFFER.rx_tail, UART_5_RING_BUFSIZE_RX))))
	{
		/// Read data from ring buffer into user buffer
		*data = UART5_RING_BUFFER.rx[UART5_RING_BUFFER.rx_tail];
		data++;
		/// Update tail pointer
		__BUF_INCR(UART5_RING_BUFFER.rx_tail,UART_5_RING_BUFSIZE_RX);
		/// Increment data count and decrement buffer size count
		bytes++;
		buflen--;
	}
	
	/// Enable interrupt uart5
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
	return bytes;
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if((UART_1_ENABLE&&UART_1_INT)||(UART_2_ENABLE&&UART_2_INT)||(UART_3_ENABLE&&UART_3_INT)||(UART_4_ENABLE&&UART_4_INT)||(UART_5_ENABLE&&UART_5_INT))
/**
 * @brief 		Receive string UART from soft fifo
 * @param[in]	Port Uart number
 * @param[output]	rxbuf *rxbuf for receive
 * @param[in]	buflen size of *rxbuf
 * @return 		length receive
*/
U16 UART_Receive_String_FIFO(U8 Port, U8 *rxbuf,U16 buflen)
{

	U16 Length;

	/// Wait Mutex UART_MutexHandleReceiveStringFIFO[0]
	TASK_MANAGER_MUTEXWAIT(UART_MutexHandleReceiveStringFIFO[0]);

	#if(UART_1_ENABLE&&UART_1_INT)
	if(Port==1)
	{
		Length = UART1_Receive_String_FIFO(rxbuf, buflen);
	}
	#endif

	#if(UART_2_ENABLE&&UART_2_INT)
	if(Port==2)
	{
		Length = UART2_Receive_String_FIFO(rxbuf, buflen);
	}
	#endif

	#if(UART_3_ENABLE&&UART_3_INT)
	if(Port==3)
	{
		Length = UART3_Receive_String_FIFO(rxbuf, buflen);
	}
	#endif

	#if(UART_4_ENABLE&&UART_4_INT)
	if(Port==4)
	{
		Length = UART4_Receive_String_FIFO(rxbuf, buflen);
	}
	#endif

	#if(UART_5_ENABLE&&UART_5_INT)
	if(Port==5)
	{
		Length = UART5_Receive_String_FIFO(rxbuf, buflen);
	}
	#endif
	
	/// Release Mutex UART_MutexHandleReceiveStringFIFO
	TASK_MANAGER_MUTEXRELEASE(UART_MutexHandleReceiveStringFIFO[0]);

	return Length;
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_1_ENABLE&&UART_1_INT&&(UART_1_INT_SEND_MODE==1)) //SEND FIFO UART1
/**
 * @brief 		Send string UART1 to soft fifo
 * @param[in]	input *input for send
 * @param[in]	Size size of *input
*/
void UART1_Send_String_FIFO(U8 *input,uint16_t Size)
{
	U8 *data = (U8 *) input;

	/// Wait until flag sending or flag write notbusy uart2 is busy
	while(UART1_RING_BUFFER_FLAG_Sending_In_Proccess || UART1_RING_BUFFER_FLAG_Write_In_Proccess)
	{
		
		/// Delay one Tick
		TaskManager_Delay(OneUnic);
	}
	
	/// Flag write uart2 busy	
	UART1_RING_BUFFER_FLAG_Write_In_Proccess = true;
	
	while ((Size > 0) && (!__BUF_IS_FULL(UART1_RING_BUFFER.tx_head, UART1_RING_BUFFER.tx_tail,UART_1_RING_BUFSIZE_TX)))
	{
		/// Write data from buffer into ring buffer
		UART1_RING_BUFFER.tx[UART1_RING_BUFFER.tx_head] = *data;
		data++;

		/// Increment head pointer
		__BUF_INCR(UART1_RING_BUFFER.tx_head, UART_1_RING_BUFSIZE_TX);
		Size--;
	}
	
	/// Flag write uart1 notbusy
	UART1_RING_BUFFER_FLAG_Write_In_Proccess = false;
	/// Flag sending uart1 busy
	UART1_RING_BUFFER_FLAG_Sending_In_Proccess = true;

}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_2_ENABLE&&UART_2_INT&&(UART_2_INT_SEND_MODE==1)) //SEND FIFO UART2
/**
 * @brief 		Send string UART2 to soft fifo
 * @param[in]	input *input for send
 * @param[in]	Size size of *input
*/
void UART2_Send_String_FIFO(U8 *input,uint16_t Size)
{
	U8 *data = (U8 *) input;

	/// Wait until flag sending or flag write notbusy uart2 is busy
	while(UART2_RING_BUFFER_FLAG_Sending_In_Proccess || UART2_RING_BUFFER_FLAG_Write_In_Proccess)
	{
		
		/// Delay one Tick
		TaskManager_Delay(OneUnic);
	}
	
	/// Flag write uart2 busy	
	UART2_RING_BUFFER_FLAG_Write_In_Proccess = true;
	
	while ((Size > 0) && (!__BUF_IS_FULL(UART2_RING_BUFFER.tx_head, UART2_RING_BUFFER.tx_tail,UART_2_RING_BUFSIZE_TX)))
	{
		/// Write data from buffer into ring buffer
		UART2_RING_BUFFER.tx[UART2_RING_BUFFER.tx_head] = *data;
		data++;

		/// Increment head pointer
		__BUF_INCR(UART2_RING_BUFFER.tx_head,UART_2_RING_BUFSIZE_TX);
		Size--;
	}
	
	/// Flag write uart2 notbusy
	UART2_RING_BUFFER_FLAG_Write_In_Proccess = false;
	/// Flag sending uart2 busy
	UART2_RING_BUFFER_FLAG_Sending_In_Proccess = true;

}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_3_ENABLE&&UART_3_INT&&(UART_3_INT_SEND_MODE==1)) //SEND FIFO UART3
/**
 * @brief 		Send string UART3 to soft fifo
 * @param[in]	input *input for send
 * @param[in]	Size size of *input
*/
void UART3_Send_String_FIFO(U8 *input,uint16_t Size)
{
	U8 *data = (U8 *) input;

	/// Wait until flag sending or flag write notbusy uart6 is busy
	while(UART3_RING_BUFFER_FLAG_Sending_In_Proccess || UART3_RING_BUFFER_FLAG_Write_In_Proccess)
	{
		
		/// Delay one Tick
		TaskManager_Delay(OneUnic);
	}
	
	/// Flag write uart3 busy	
	UART3_RING_BUFFER_FLAG_Write_In_Proccess = true;
	
	while ((Size > 0) && (!__BUF_IS_FULL(UART3_RING_BUFFER.tx_head, UART3_RING_BUFFER.tx_tail,UART_3_RING_BUFSIZE_TX)))
	{
		/// Write data from buffer into ring buffer
		UART3_RING_BUFFER.tx[UART3_RING_BUFFER.tx_head] = *data;
		data++;

		/// Increment head pointer
		__BUF_INCR(UART3_RING_BUFFER.tx_head, UART_3_RING_BUFSIZE_TX);
		Size--;
	}
	
	/// Flag write uart3 notbusy
	UART3_RING_BUFFER_FLAG_Write_In_Proccess = false;
	/// Flag sending uart3 busy
	UART3_RING_BUFFER_FLAG_Sending_In_Proccess = true;

}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_4_ENABLE&&UART_4_INT&&(UART_4_INT_SEND_MODE==1)) //SEND FIFO UART4
/**
 * @brief 		Send string UART4 to soft fifo
 * @param[in]	input *input for send
 * @param[in]	Size size of *input
*/
void UART4_Send_String_FIFO(U8 *input,uint16_t Size)
{
	U8 *data = (U8 *) input;

	/// Wait until flag sending or flag write notbusy uart6 is busy
	while(UART4_RING_BUFFER_FLAG_Sending_In_Proccess || UART4_RING_BUFFER_FLAG_Write_In_Proccess)
	{
		
		/// Delay one Tick
		TaskManager_Delay(OneUnic);
	}
	
	/// Flag write uart4 busy	
	UART4_RING_BUFFER_FLAG_Write_In_Proccess = true;
	
	while ((Size > 0) && (!__BUF_IS_FULL(UART4_RING_BUFFER.tx_head, UART4_RING_BUFFER.tx_tail,UART_4_RING_BUFSIZE_TX)))
	{
		/// Write data from buffer into ring buffer
		UART4_RING_BUFFER.tx[UART4_RING_BUFFER.tx_head] = *data;
		data++;

		/// Increment head pointer
		__BUF_INCR(UART4_RING_BUFFER.tx_head, UART_4_RING_BUFSIZE_TX);
		Size--;
	}
	
	/// Flag write uart4 notbusy
	UART4_RING_BUFFER_FLAG_Write_In_Proccess = false;
	/// Flag sending uart4 busy
	UART4_RING_BUFFER_FLAG_Sending_In_Proccess = true;

}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_5_ENABLE&&UART_5_INT&&(UART_5_INT_SEND_MODE==1)) //SEND FIFO UART5
/**
 * @brief 		Send string UART5 to soft fifo
 * @param[in]	input *input for send
 * @param[in]	Size size of *input
*/
void UART5_Send_String_FIFO(U8 *input,uint16_t Size)
{
	U8 *data = (U8 *) input;

	/// Wait until flag sending or flag write notbusy uart6 is busy
	while(UART5_RING_BUFFER_FLAG_Sending_In_Proccess || UART5_RING_BUFFER_FLAG_Write_In_Proccess)
	{
		
		/// Delay one Tick
		TaskManager_Delay(OneUnic);
	}
	
	/// Flag write uart5 busy	
	UART5_RING_BUFFER_FLAG_Write_In_Proccess = true;
	
	while ((Size > 0) && (!__BUF_IS_FULL(UART5_RING_BUFFER.tx_head, UART5_RING_BUFFER.tx_tail,UART_5_RING_BUFSIZE_TX)))
	{
		/// Write data from buffer into ring buffer
		UART5_RING_BUFFER.tx[UART5_RING_BUFFER.tx_head] = *data;
		data++;

		/// Increment head pointer
		__BUF_INCR(UART5_RING_BUFFER.tx_head, UART_5_RING_BUFSIZE_TX);
		Size--;
	}
	
	/// Flag write uart5 notbusy
	UART5_RING_BUFFER_FLAG_Write_In_Proccess = false;
	/// Flag sending uart5 busy
	UART5_RING_BUFFER_FLAG_Sending_In_Proccess = true;

}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if((UART_1_ENABLE&&UART_1_INT&&(UART_1_INT_SEND_MODE==1))||(UART_2_ENABLE&&UART_2_INT&&(UART_2_INT_SEND_MODE==1))||(UART_3_ENABLE&&UART_3_INT&&(UART_3_INT_SEND_MODE==1))||(UART_4_ENABLE&&UART_4_INT&&(UART_4_INT_SEND_MODE==1))||(UART_5_ENABLE&&UART_5_INT&&(UART_5_INT_SEND_MODE==1)))
/**
 * @brief 		Send string UART to soft fifo
 * @param[in]	Port Uart number
 * @param[in]	input *input for send
 * @param[in]	Size size of *input
*/
void UART_Send_String_FIFO(U8 Port,U8 *input,uint16_t Size)
{
	
	/// Wait Mutex UART_MutexHandleSendingString[0]FIFO
	TASK_MANAGER_MUTEXWAIT(UART_MutexHandleSendingString[0]FIFO);

	#if(UART_1_ENABLE&&UART_1_INT&&(UART_1_INT_SEND_MODE==1))
	if(Port==2)
	{
		UART2_Send_String_FIFO(input, Size);
	}
	#endif

	#if(UART_2_ENABLE&&UART_2_INT&&(UART_2_INT_SEND_MODE==1))
	if(Port==2)
	{
		UART2_Send_String_FIFO(input, Size);
	}
	#endif

	#if(UART_3_ENABLE&&UART_3_INT&&(UART_3_INT_SEND_MODE==1))
	if(Port==3)
	{
		UART3_Send_String_FIFO(input, Size);
	}
	#endif

	/// Release Mutex UART_MutexHandleSendingString[0]FIFO
	TASK_MANAGER_MUTEXRELEASE (UART_MutexHandleSendingString[0]FIFO);
}
#endif
//*************************************************************** tasks *******************************************************************//
#if(UART_1_ENABLE&&UART_1_INT&&(UART_1_INT_SEND_MODE==1)) //TASK SEND FIFO UART1
/**
 * @brief 	 task manage send uart1
*/
__task void UART1_Send_FIFO_Task(void)
{
	 U8 sent_fifo;
	
	 TaskManager_Delay(TASK_MANAGER_DELAYFIRSTTASK);
	
   while (1) 
	 {
		  /// Wait until flag sending uart2 is notbusy
		  while(UART1_RING_BUFFER_FLAG_Sending_In_Proccess == false)
	{
		TaskManager_Delay(10 MSec);
	}
		 
	/// Loop until send buffer ring is empty or flag sending uart2 is busy	
	while(!__BUF_IS_EMPTY(UART1_RING_BUFFER.tx_head, UART1_RING_BUFFER.tx_tail, UART_1_RING_BUFSIZE_TX))
	{
		
	  if(UART1_RING_BUFFER_FLAG_Sending_In_Proccess == false)
		{
			break;
		}
		
		/// Move a piece of data into the transmit FIFO
		((LPC_UART_TypeDef *)LPC_UART1)->THR = ((U8 *)&UART1_RING_BUFFER.tx[UART1_RING_BUFFER.tx_tail])[0];
		sent_fifo++;
		
		if(sent_fifo>=16)
		{
			while(!(((LPC_UART_TypeDef *)LPC_UART1)->LSR & UART_LSR_THRE))
			{
		
		/// Delay one Tick
		TaskManager_Delay(OneUnic);
			}
			sent_fifo=0;
		}
			/// Update transmit ring FIFO tail pointer
		__BUF_INCR(UART1_RING_BUFFER.tx_tail, UART_1_RING_BUFSIZE_TX);
	}

	/// Flag sending uart1 notbusy		
	UART1_RING_BUFFER_FLAG_Sending_In_Proccess = false;
	/// Delay one Tick
	TaskManager_Delay(OneUnic);
   }
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_2_ENABLE&&UART_2_INT&&(UART_2_INT_SEND_MODE==1)) //TASK SEND FIFO UART2
/**
 * @brief 	 task manage send uart2
*/
__task void UART2_Send_FIFO_Task(void)
{
	 U8 sent_fifo;
	
	 TaskManager_Delay(TASK_MANAGER_DELAYFIRSTTASK);
	
   while (1) 
	 {
		  /// Wait until flag sending uart2 is notbusy
		  while(UART2_RING_BUFFER_FLAG_Sending_In_Proccess == false)
	{
		TaskManager_Delay(10 MSec);
	}
		 
	/// Loop until send buffer ring is empty or flag sending uart2 is busy	
	while(!__BUF_IS_EMPTY(UART2_RING_BUFFER.tx_head,UART2_RING_BUFFER.tx_tail,UART_2_RING_BUFSIZE_TX))
	{
		
	  if(UART2_RING_BUFFER_FLAG_Sending_In_Proccess == false)
		{
			break;
		}
		
		/// Move a piece of data into the transmit FIFO
		((LPC_UART_TypeDef *)LPC_UART2)->THR = ((U8 *)&UART2_RING_BUFFER.tx[UART2_RING_BUFFER.tx_tail])[0];
		sent_fifo++;
		
		if(sent_fifo>=16)
		{
			while(!(((LPC_UART_TypeDef *)LPC_UART2)->LSR & UART_LSR_THRE))
			{
		
		/// Delay one Tick
		TaskManager_Delay(OneUnic);
			}
			sent_fifo=0;
		}
			/// Update transmit ring FIFO tail pointer
		__BUF_INCR(UART2_RING_BUFFER.tx_tail,UART_2_RING_BUFSIZE_TX);
	}

	/// Flag sending uart2 notbusy		
	UART2_RING_BUFFER_FLAG_Sending_In_Proccess = false;
	/// Delay one Tick
	TaskManager_Delay(OneUnic);
   }
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_3_ENABLE&&UART_3_INT&&(UART_3_INT_SEND_MODE==1)) //TASK SEND FIFO UART3
/**
 * @brief 	 task manage send uart3
*/
__task void UART3_Send_FIFO_Task(void)
{
	 U8 sent_fifo;
	
	 TaskManager_Delay(TASK_MANAGER_DELAYFIRSTTASK);
	
   while (1) 
	 {
		  /// Wait until flag sending uart3 is notbusy
		  while(UART3_RING_BUFFER_FLAG_Sending_In_Proccess == false)
	{
		TaskManager_Delay(10 MSec);
	}
		 
	/// Loop until send buffer ring is empty or flag sending uart3 is busy	
	while(!__BUF_IS_EMPTY(UART3_RING_BUFFER.tx_head, UART3_RING_BUFFER.tx_tail, UART_3_RING_BUFSIZE_TX))
	{
		
	  if(UART3_RING_BUFFER_FLAG_Sending_In_Proccess == false)
		{
			break;
		}
		
		/// Move a piece of data into the transmit FIFO
		((LPC_UART_TypeDef *)LPC_UART3)->THR = ((U8 *)&UART3_RING_BUFFER.tx[UART3_RING_BUFFER.tx_tail])[0];
		sent_fifo++;
		
		if(sent_fifo>=16)
		{
			while(!(((LPC_UART_TypeDef *)LPC_UART3)->LSR & UART_LSR_THRE))
			{
		
		/// Delay one Tick
		TaskManager_Delay(OneUnic);
			}
			sent_fifo=0;
		}
			/// Update transmit ring FIFO tail pointer
		__BUF_INCR(UART3_RING_BUFFER.tx_tail, UART_3_RING_BUFSIZE_TX);
	}

	/// Flag sending uart3 notbusy		
	UART3_RING_BUFFER_FLAG_Sending_In_Proccess = false;
	/// Delay one Tick
	TaskManager_Delay(OneUnic);
   }
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_4_ENABLE&&UART_4_INT&&(UART_4_INT_SEND_MODE==1)) //TASK SEND FIFO UART4
/**
 * @brief 	 task manage send uart4
*/
__task void UART4_Send_FIFO_Task(void)
{
	 U8 sent_fifo;
	
	 TaskManager_Delay(TASK_MANAGER_DELAYFIRSTTASK);
	
   while (1) 
	 {
		  /// Wait until flag sending uart4 is notbusy
		  while(UART4_RING_BUFFER_FLAG_Sending_In_Proccess == false)
	{
		TaskManager_Delay(10 MSec);
	}
		 
	/// Loop until send buffer ring is empty or flag sending uart4 is busy	
	while(!__BUF_IS_EMPTY(UART4_RING_BUFFER.tx_head, UART4_RING_BUFFER.tx_tail, UART_4_RING_BUFSIZE_TX))
	{
		
	  if(UART4_RING_BUFFER_FLAG_Sending_In_Proccess == false)
		{
			break;
		}
		
		/// Move a piece of data into the transmit FIFO
		((LPC_UART_TypeDef *)LPC_UART4)->THR = ((U8 *)&UART4_RING_BUFFER.tx[UART4_RING_BUFFER.tx_tail])[0];
		sent_fifo++;
		
		if(sent_fifo>=16)
		{
			while(!(((LPC_UART_TypeDef *)LPC_UART4)->LSR & UART_LSR_THRE))
			{
		
		/// Delay one Tick
		TaskManager_Delay(OneUnic);
			}
			sent_fifo=0;
		}
			/// Update transmit ring FIFO tail pointer
		__BUF_INCR(UART4_RING_BUFFER.tx_tail, UART_4_RING_BUFSIZE_TX);
	}

	/// Flag sending uart4 notbusy		
	UART4_RING_BUFFER_FLAG_Sending_In_Proccess = false;
	/// Delay one Tick
	TaskManager_Delay(OneUnic);
   }
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_5_ENABLE&&UART_5_INT&&(UART_5_INT_SEND_MODE==1)) //TASK SEND FIFO UART5
/**
 * @brief 	 task manage send uart5
*/
__task void UART5_Send_FIFO_Task(void)
{
	 U8 sent_fifo;
	
	 TaskManager_Delay(TASK_MANAGER_DELAYFIRSTTASK);
	
   while (1) 
	 {
		  /// Wait until flag sending uart5 is notbusy
		  while(UART5_RING_BUFFER_FLAG_Sending_In_Proccess == false)
	{
		TaskManager_Delay(10 MSec);
	}
		 
	/// Loop until send buffer ring is empty or flag sending uart5 is busy	
	while(!__BUF_IS_EMPTY(UART5_RING_BUFFER.tx_head, UART5_RING_BUFFER.tx_tail, UART_5_RING_BUFSIZE_TX))
	{
		
	  if(UART5_RING_BUFFER_FLAG_Sending_In_Proccess == false)
		{
			break;
		}
		
		/// Move a piece of data into the transmit FIFO
		((LPC_UART_TypeDef *)LPC_UART5)->THR = ((U8 *)&UART5_RING_BUFFER.tx[UART5_RING_BUFFER.tx_tail])[0];
		sent_fifo++;
		
		if(sent_fifo>=16)
		{
			while(!(((LPC_UART_TypeDef *)LPC_UART5)->LSR & UART_LSR_THRE))
			{
		
		/// Delay one Tick
		TaskManager_Delay(OneUnic);
			}
			sent_fifo=0;
		}
			/// Update transmit ring FIFO tail pointer
		__BUF_INCR(UART5_RING_BUFFER.tx_tail, UART_5_RING_BUFSIZE_TX);
	}

	/// Flag sending uart5 notbusy		
	UART5_RING_BUFFER_FLAG_Sending_In_Proccess = false;
	/// Delay one Tick
	TaskManager_Delay(OneUnic);
   }
}
#endif
//************************************************************** vectors ******************************************************************//
#if(UART_1_ENABLE&&UART_1_INT) //INTERRUPT RECEIVE FIFO UART1
/**
 * @brief 		interrupt uart1
*/
void USART1_IRQHandler(void) __irq
{
	U8 tmpc;

	/// Clear UART1 interrupt
	if (USART_GetITStatus(USART1, USART_FLAG_TC) != RESET)
	{
		USART_ClearITPendingBit(USART1, USART_FLAG_TC);
	}

	tmpc = (UART1_WordLength_7b)?(USART_ReceiveData(USART1)&0x7F):USART_ReceiveData(USART1);
	
	/// Write to soft fifo uart1 if soft fifo not full
	if (!__BUF_IS_FULL(UART1_RING_BUFFER.rx_head, UART1_RING_BUFFER.rx_tail, UART_1_RING_BUFSIZE_RX))
	{
		UART1_RING_BUFFER.rx[UART1_RING_BUFFER.rx_head] = tmpc;
		__BUF_INCR(UART1_RING_BUFFER.rx_head, UART_1_RING_BUFSIZE_RX);
	}
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_2_ENABLE&&UART_2_INT) //INTERRUPT RECEIVE FIFO UART2
/**
 * @brief 		interrupt uart2
*/
void USART2_IRQHandler(void) __irq
{
	U8 tmpc;

	/// Clear UART2 interrupt
	if (USART_GetITStatus(USART2, USART_FLAG_TC) != RESET)
	{
		USART_ClearITPendingBit(USART2, USART_FLAG_TC);
	}
	
	tmpc = (UART2_WordLength_7b)?(USART_ReceiveData(USART2)&0x7F):USART_ReceiveData(USART2);
	
	/// Write to soft fifo uart2 if soft fifo not full
	if (!__BUF_IS_FULL(UART2_RING_BUFFER.rx_head, UART2_RING_BUFFER.rx_tail, UART_2_RING_BUFSIZE_RX))
	{
		UART2_RING_BUFFER.rx[UART2_RING_BUFFER.rx_head] = tmpc;
		__BUF_INCR(UART2_RING_BUFFER.rx_head, UART_2_RING_BUFSIZE_RX);
	}
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_3_ENABLE&&UART_3_INT) //INTERRUPT RECEIVE FIFO UART3
/**
 * @brief 		interrupt uart3
*/
void USART3_IRQHandler(void) __irq
{
	U8 tmpc;

	/// Clear UART3 interrupt
	if (USART_GetITStatus(USART3, USART_FLAG_TC) != RESET)
	{
		USART_ClearITPendingBit(USART3, USART_FLAG_TC);
	}

	tmpc = (UART3_WordLength_7b)?(USART_ReceiveData(USART3)&0x7F):USART_ReceiveData(USART3);
	
	/// Write to soft fifo uart3 if soft fifo not full
	if (!__BUF_IS_FULL(UART3_RING_BUFFER.rx_head, UART3_RING_BUFFER.rx_tail, UART_3_RING_BUFSIZE_RX))
	{
		UART3_RING_BUFFER.rx[UART3_RING_BUFFER.rx_head] = tmpc;
		__BUF_INCR(UART3_RING_BUFFER.rx_head, UART_3_RING_BUFSIZE_RX);
	}
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_4_ENABLE&&UART_4_INT) //INTERRUPT RECEIVE FIFO UART4
/**
 * @brief 		interrupt uart4
*/
void UART4_IRQHandler(void) __irq
{
	U8 tmpc;

	/// Clear UART4 interrupt
	if (USART_GetITStatus(UART4, USART_FLAG_TC) != RESET)
	{
		USART_ClearITPendingBit(UART4, USART_FLAG_TC);
	}

	tmpc = (UART4_WordLength_7b)?(USART_ReceiveData(UART4)&0x7F):USART_ReceiveData(UART4);
	
	/// Write to soft fifo uart4 if soft fifo not full
	if (!__BUF_IS_FULL(UART4_RING_BUFFER.rx_head, UART4_RING_BUFFER.rx_tail, UART_4_RING_BUFSIZE_RX))
	{
		UART4_RING_BUFFER.rx[UART4_RING_BUFFER.rx_head] = tmpc;
		__BUF_INCR(UART4_RING_BUFFER.rx_head, UART_4_RING_BUFSIZE_RX);
	}
}
#endif
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#if(UART_5_ENABLE&&UART_5_INT) //INTERRUPT RECEIVE FIFO UART5
/**
 * @brief 		interrupt uart5
*/
void UART5_IRQHandler(void) __irq
{
	U8 tmpc;

	/// Clear UART5 interrupt
	if (USART_GetITStatus(UART5, USART_FLAG_TC) != RESET)
	{
		USART_ClearITPendingBit(UART5, USART_FLAG_TC);
	}

	tmpc = (UART5_WordLength_7b)?(USART_ReceiveData(UART5)&0x7F):USART_ReceiveData(UART5);
	
	/// Write to soft fifo uart5 if soft fifo not full
	if (!__BUF_IS_FULL(UART5_RING_BUFFER.rx_head, UART5_RING_BUFFER.rx_tail, UART_5_RING_BUFSIZE_RX))
	{
		UART5_RING_BUFFER.rx[UART5_RING_BUFFER.rx_head] = tmpc;
		__BUF_INCR(UART5_RING_BUFFER.rx_head, UART_5_RING_BUFSIZE_RX);
	}
}
#endif
//****************************************************************************************************************************************//










