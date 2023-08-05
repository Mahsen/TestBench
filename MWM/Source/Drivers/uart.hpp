#ifndef __UART_HPP
#define __UART_HPP
//----------------------------------------------------------
#include "defines.h"
#include "misc.h"
#include "stm32l1xx_usart.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_dma.h"
//----------------------------------------------------------
struct UART_State_FIFO_STRUCT
{
	bool    rx_Busy;                  /*!< UART Rx ring buffer busy */
	bool rxBusy (void)
	{
		return rx_Busy;
	}
	U32 		rx_Buffer;                /*!< UART Rx ring buffer index */
	U32 rxBuffer (void)
	{
		return rx_Buffer;
	}	
	U32 		rx_Length;                /*!< UART Rx ring buffer head index */
	U32 rxLength (void)
	{
		return rx_Length;
	}		
	bool    tx_Busy;                  /*!< UART Tx ring buffer busy */
	bool txBusy (void)
	{
		return tx_Busy;
	}
	U32 		tx_Buffer;                /*!< UART Tx ring buffer index */
	U32 txBuffer (void)
	{
		return tx_Buffer;
	}		
	U32 		tx_Length;                /*!< UART Tx ring buffer tail index */
	U32 txLength (void)
	{
		return tx_Length;
	}		
};
//----------------------------------------------------------
void __init_UART(void);
void __uninit_UART(void);

void UART1_UpdateSetting(U32 Boudrate, U16 DataBit, U16 Parity, U16 StopBit, bool MustUpdate);
void UART2_UpdateSetting(U32 Boudrate, U16 DataBit, U16 Parity, U16 StopBit, bool MustUpdate);
void UART3_UpdateSetting(U32 Boudrate, U16 DataBit, U16 Parity, U16 StopBit, bool MustUpdate);
void UART4_UpdateSetting(U32 Boudrate, U16 DataBit, U16 Parity, U16 StopBit, bool MustUpdate);
void UART5_UpdateSetting(U32 Boudrate, U16 DataBit, U16 Parity, U16 StopBit, bool MustUpdate);
void UART_UpdateSetting(U8 Port, U32 Boudrate, U16 DataBit, U16 Parity, U16 StopBit, bool MustUpdate);

void UART_Send_Char(U8 Port,U8 input);		
void UART_Send_String(U8 Port,U8 *input,U16 Size);
U8 UART_Receive_Char(U8 Port);

void UART1_Reset_Buffer_FIFO(void);
void UART2_Reset_Buffer_FIFO(void);
void UART3_Reset_Buffer_FIFO(void);
void UART4_Reset_Buffer_FIFO(void);
void UART5_Reset_Buffer_FIFO(void);
void UART_Reset_Buffer_FIFO(U8 Port);

struct UART_State_FIFO_STRUCT UART1_Read_State_FIFO(void);
struct UART_State_FIFO_STRUCT UART2_Read_State_FIFO(void);
struct UART_State_FIFO_STRUCT UART3_Read_State_FIFO(void);
struct UART_State_FIFO_STRUCT UART4_Read_State_FIFO(void);
struct UART_State_FIFO_STRUCT UART5_Read_State_FIFO(void);
struct UART_State_FIFO_STRUCT UART_Read_State_FIFO(U8 Port);

void UART1_Send_String_FIFO(U8 *input,U16 Size);
void UART2_Send_String_FIFO(U8 *input,U16 Size);
void UART3_Send_String_FIFO(U8 *input,U16 Size);
void UART4_Send_String_FIFO(U8 *input,U16 Size);
void UART5_Send_String_FIFO(U8 *input,U16 Size);
void UART_Send_String_FIFO(U8 Port,U8 *input,U16 Size);

U16 UART1_Receive_String_FIFO(U8 *rxbuf,U16 buflen);
U16 UART2_Receive_String_FIFO(U8 *rxbuf,U16 buflen);
U16 UART3_Receive_String_FIFO(U8 *rxbuf,U16 buflen);
U16 UART4_Receive_String_FIFO(U8 *rxbuf,U16 buflen);
U16 UART5_Receive_String_FIFO(U8 *rxbuf,U16 buflen);
U16 UART_Receive_String_FIFO(U8 Port, U8 *rxbuf,U16 buflen);
//----------------------------------------------------------
#ifdef __cplusplus
extern "C" 
{
#endif
	__irq void USART1_IRQHandler(void);
	__irq void USART2_IRQHandler(void);
	__irq void USART3_IRQHandler(void);	
	__irq void UART4_IRQHandler(void);
	__irq void UART5_IRQHandler(void);	
#ifdef __cplusplus
}
#endif
//----------------------------------------------------------
__task void UART1_Send_FIFO_Task(void);
__task void UART2_Send_FIFO_Task(void);
__task void UART3_Send_FIFO_Task(void);
__task void UART4_Send_FIFO_Task(void);
__task void UART5_Send_FIFO_Task(void);
//----------------------------------------------------------
#endif
