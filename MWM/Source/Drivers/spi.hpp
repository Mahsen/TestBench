#ifndef __SPI_FS_HPP
#define __SPI_FS_HPP
//----------------------------------------------------------
#include "defines.h"
#include "TaskManager.hpp"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_spi.h"
#include "stm32l1xx_rcc.h"
#include "gpio.hpp"
//----------------------------------------------------------
#define RXNE         SPI_I2S_FLAG_RXNE
#define TXE          SPI_I2S_FLAG_TXE
#define BSY          SPI_I2S_FLAG_BSY
//----------------------------------------------------------
void __init_SPI(void);
void __uninit_SPI(void);
bool SPI_Update (U8 Port);
U8 SPI_SendByte (U8 Port, U8 Byte);
bool SPI_Send (U8 Port, U8 *Data, U32 Length);
bool SPI_Receive (U8 Port, U8 *Data, U32 Length);
bool SPI_BusSpeed (U32 KBaud);
#endif



