/************************************************** Description *******************************************************/
/*
    File : dap.c
    Programmer : Mohammad Lotfi
    Used : Nothing
    Design Pattern : Nothing
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2024/1/28
*/
/************************************************** Warnings **********************************************************/
/*
 * Copyright (c) 2014-2016, Alex Taradov <alex@taradov.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/
/************************************************** Wizards ***********************************************************/
/*
    Nothing
*/
/************************************************** Includes **********************************************************/
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dap.h"
#include "defines.h"
#include "stm32l1xx_gpio.h"
/************************************************** Defineds **********************************************************/
#define DAP_IDLE_CYCLES                0
#define DAP_RETRY_COUNT                128
#define DAP_SWD_TURNAROUND             1
#define DAP_SWD_DATA_PHASE             false

#define DHCSR                          0xe000edf0
#define DEMCR                          0xe000edfc
#define AIRCR                          0xe000ed0c

#define CMU_ADDRESS                    0x4000F000
#define CMU_WPREG                      CMU_ADDRESS + 0x0 
#define CMU_FLASHCON                   CMU_ADDRESS + 0x34 
#define CMU_FLASHLOCK                  CMU_ADDRESS + 0x38

#define CMU_WPREG_UNPROTECTED          ((uint32_t)0xA55A) 
#define CMU_FLASHCON_FOP_WRITE         ((uint32_t)0x0001)
#define CMU_FLASHCON_FOP_CHIPERASE     ((uint32_t)0x0003)
#define CMU_FLASHCON_FOP_READ          ((uint32_t)0x0000)
#define CMU_FLASHCON_BUSY              ((uint32_t)0x0004)

#define CMU_FLASHLOCK_UNLOCKED         ((uint32_t)0x7A68)
#define CMU_FLASHLOCK_LOCKED           ((uint32_t)0x0000)

GPIO_InitTypeDef HAL_GPIO_b;
#define HAL_GPIO_SWRST_PORT             GPIOA
#define HAL_GPIO_SWRST_PIN              GPIO_Pin_0
#define HAL_GPIO_SWCLK_PORT             GPIOA
#define HAL_GPIO_SWCLK_PIN              GPIO_Pin_1
#define HAL_GPIO_SWDIO_PORT             GPIOA
#define HAL_GPIO_SWDIO_PIN              GPIO_Pin_2

#define HAL_GPIO_SWRST_out()            HAL_GPIO_b.GPIO_Pin=HAL_GPIO_SWRST_PIN;HAL_GPIO_b.GPIO_Mode=GPIO_Mode_OUT;HAL_GPIO_b.GPIO_OType=GPIO_OType_PP;HAL_GPIO_b.GPIO_PuPd=GPIO_PuPd_NOPULL;HAL_GPIO_b.GPIO_Speed=GPIO_Speed_2MHz;GPIO_Init(HAL_GPIO_SWRST_PORT,&HAL_GPIO_b) //GPIO_SetDir (2, 10, GPIO_DIR_OUTPUT)
#define HAL_GPIO_SWRST_write(Value)     Value?(HAL_GPIO_SWRST_PORT->BSRRL=HAL_GPIO_SWRST_PIN):(HAL_GPIO_SWRST_PORT->BSRRH=HAL_GPIO_SWRST_PIN) //GPIO_PinWrite (2, 10, Value)
#define HAL_GPIO_SWRST_set()            HAL_GPIO_SWRST_write(1)
#define HAL_GPIO_SWRST_clr()            HAL_GPIO_SWRST_write(0)

#define HAL_GPIO_SWCLK_in()             HAL_GPIO_b.GPIO_Pin=HAL_GPIO_SWCLK_PIN;HAL_GPIO_b.GPIO_Mode=GPIO_Mode_IN;HAL_GPIO_b.GPIO_OType=GPIO_OType_PP;HAL_GPIO_b.GPIO_PuPd=GPIO_PuPd_NOPULL;HAL_GPIO_b.GPIO_Speed=GPIO_Speed_2MHz;GPIO_Init(HAL_GPIO_SWCLK_PORT,&HAL_GPIO_b)//GPIO_SetDir (2, 11, GPIO_DIR_INPUT)
#define HAL_GPIO_SWCLK_out()            HAL_GPIO_b.GPIO_Pin=HAL_GPIO_SWCLK_PIN;HAL_GPIO_b.GPIO_Mode=GPIO_Mode_OUT;HAL_GPIO_b.GPIO_OType=GPIO_OType_PP;HAL_GPIO_b.GPIO_PuPd=GPIO_PuPd_NOPULL;HAL_GPIO_b.GPIO_Speed=GPIO_Speed_2MHz;GPIO_Init(HAL_GPIO_SWCLK_PORT,&HAL_GPIO_b)//GPIO_SetDir (2, 11, GPIO_DIR_OUTPUT)
#define HAL_GPIO_SWCLK_write(Value)     Value?(HAL_GPIO_SWCLK_PORT->BSRRL=HAL_GPIO_SWCLK_PIN):(HAL_GPIO_SWCLK_PORT->BSRRH=HAL_GPIO_SWCLK_PIN) //GPIO_PinWrite (2, 11, Value)
#define HAL_GPIO_SWCLK_read()           (GPIOA->IDR&HAL_GPIO_SWCLK_PIN) //GPIO_PinRead (2, 11)
#define HAL_GPIO_SWCLK_set()            HAL_GPIO_SWCLK_write(1)
#define HAL_GPIO_SWCLK_clr()            HAL_GPIO_SWCLK_write(0)
#define HAL_GPIO_SWDIO_pullup()         HAL_GPIO_SWCLK_in()

#define HAL_GPIO_SWDIO_in()             HAL_GPIO_b.GPIO_Pin=HAL_GPIO_SWDIO_PIN;HAL_GPIO_b.GPIO_Mode=GPIO_Mode_IN;HAL_GPIO_b.GPIO_OType=GPIO_OType_PP;HAL_GPIO_b.GPIO_PuPd=GPIO_PuPd_NOPULL;HAL_GPIO_b.GPIO_Speed=GPIO_Speed_2MHz;GPIO_Init(HAL_GPIO_SWDIO_PORT,&HAL_GPIO_b)//GPIO_SetDir (2, 12, GPIO_DIR_INPUT)
#define HAL_GPIO_SWDIO_out()            HAL_GPIO_b.GPIO_Pin=HAL_GPIO_SWDIO_PIN;HAL_GPIO_b.GPIO_Mode=GPIO_Mode_OUT;HAL_GPIO_b.GPIO_OType=GPIO_OType_PP;HAL_GPIO_b.GPIO_PuPd=GPIO_PuPd_NOPULL;HAL_GPIO_b.GPIO_Speed=GPIO_Speed_2MHz;GPIO_Init(HAL_GPIO_SWDIO_PORT,&HAL_GPIO_b)//GPIO_SetDir (2, 12, GPIO_DIR_OUTPUT)
#define HAL_GPIO_SWDIO_write(Value)     Value?(HAL_GPIO_SWDIO_PORT->BSRRL=HAL_GPIO_SWDIO_PIN):(HAL_GPIO_SWDIO_PORT->BSRRH=HAL_GPIO_SWDIO_PIN) //GPIO_PinWrite (2, 12, Value)
#define HAL_GPIO_SWDIO_read()           (GPIOA->IDR&HAL_GPIO_SWDIO_PIN) //GPIO_PinRead (2, 12)
#define HAL_GPIO_SWDIO_set()            HAL_GPIO_SWDIO_write(1)
#define HAL_GPIO_SWDIO_clr()            HAL_GPIO_SWDIO_write(0)

#define DAP_CONFIG_CLOCK_DELAY          1
/************************************************** Names *************************************************************/
/*
    Nothing
*/
/************************************************** Variables *********************************************************/
enum {
  DAP_TRANSFER_APnDP        = 1 << 0,
  DAP_TRANSFER_RnW          = 1 << 1,
  DAP_TRANSFER_A2           = 1 << 2,
  DAP_TRANSFER_A3           = 1 << 3,
  DAP_TRANSFER_MATCH_VALUE  = 1 << 4,
  DAP_TRANSFER_MATCH_MASK   = 1 << 5,
};

enum {
  DAP_TRANSFER_INVALID      = 0,
  DAP_TRANSFER_OK           = 1 << 0,
  DAP_TRANSFER_WAIT         = 1 << 1,
  DAP_TRANSFER_FAULT        = 1 << 2,
  DAP_TRANSFER_ERROR        = 1 << 3,
  DAP_TRANSFER_MISMATCH     = 1 << 4,
};

enum {
  SWD_DP_R_IDCODE           = 0x00,
  SWD_DP_W_ABORT            = 0x00,
  SWD_DP_R_CTRL_STAT        = 0x04,
  SWD_DP_W_CTRL_STAT        = 0x04, // When CTRLSEL == 0
  SWD_DP_W_WCR              = 0x04, // When CTRLSEL == 1
  SWD_DP_R_RESEND           = 0x08,
  SWD_DP_W_SELECT           = 0x08,
  SWD_DP_R_RDBUFF           = 0x0c,
};

enum {
  SWD_AP_CSW  = 0x00 | DAP_TRANSFER_APnDP,
  SWD_AP_TAR  = 0x04 | DAP_TRANSFER_APnDP,
  SWD_AP_DRW  = 0x0c | DAP_TRANSFER_APnDP,

  SWD_AP_DB0  = 0x00 | DAP_TRANSFER_APnDP, // 0x10
  SWD_AP_DB1  = 0x04 | DAP_TRANSFER_APnDP, // 0x14
  SWD_AP_DB2  = 0x08 | DAP_TRANSFER_APnDP, // 0x18
  SWD_AP_DB3  = 0x0c | DAP_TRANSFER_APnDP, // 0x1c

  SWD_AP_CFG  = 0x04 | DAP_TRANSFER_APnDP, // 0xf4
  SWD_AP_BASE = 0x08 | DAP_TRANSFER_APnDP, // 0xf8
  SWD_AP_IDR  = 0x0c | DAP_TRANSFER_APnDP, // 0xfc
};
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
void DAP_CONFIG_SWCLK_write(int value) {
  HAL_GPIO_SWCLK_write(value);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void DAP_CONFIG_SWDIO_write(int value) {
  HAL_GPIO_SWDIO_write(value);
}
/*--------------------------------------------------------------------------------------------------------------------*/
int DAP_CONFIG_SWCLK_read(void) {
  return HAL_GPIO_SWCLK_read();
}
/*--------------------------------------------------------------------------------------------------------------------*/
int DAP_CONFIG_SWDIO_read(void) {
  return HAL_GPIO_SWDIO_read();
}
/*--------------------------------------------------------------------------------------------------------------------*/
void DAP_CONFIG_SWCLK_set(void) {
  HAL_GPIO_SWCLK_set();
}
/*--------------------------------------------------------------------------------------------------------------------*/
void DAP_CONFIG_SWCLK_clr(void) {
  HAL_GPIO_SWCLK_clr();
}
/*--------------------------------------------------------------------------------------------------------------------*/
void DAP_CONFIG_SWDIO_in(void) {
  HAL_GPIO_SWDIO_in();
}
/*--------------------------------------------------------------------------------------------------------------------*/
void DAP_CONFIG_SWDIO_out(void) {
  HAL_GPIO_SWDIO_out();
}
/*--------------------------------------------------------------------------------------------------------------------*/
void DAP_CONFIG_SETUP(void) {
	HAL_GPIO_SWRST_out();
	HAL_GPIO_SWRST_clr();
	HAL_GPIO_SWRST_set();
	
  HAL_GPIO_SWCLK_in();

  HAL_GPIO_SWDIO_in();
  HAL_GPIO_SWDIO_pullup();
}
/*--------------------------------------------------------------------------------------------------------------------*/
void DAP_CONFIG_DISCONNECT(void) {
  HAL_GPIO_SWCLK_in();
  HAL_GPIO_SWDIO_in();
	
	HAL_GPIO_SWRST_clr();
	HAL_GPIO_SWRST_set();
}
/*--------------------------------------------------------------------------------------------------------------------*/
void DAP_CONFIG_CONNECT_SWD(void) {
  HAL_GPIO_SWDIO_out();
  HAL_GPIO_SWDIO_set();

  HAL_GPIO_SWCLK_out();
  HAL_GPIO_SWCLK_set();
}
/*--------------------------------------------------------------------------------------------------------------------*/
void dap_delay_loop(void) {
//#ifdef DAP_CONFIG_CLOCK_DELAY
//  int delay = DAP_CONFIG_CLOCK_DELAY;

//  while (--delay);
//#endif
}
/*--------------------------------------------------------------------------------------------------------------------*/
static void dap_swd_clock(int cycles) {
  while (cycles--) {
    DAP_CONFIG_SWCLK_clr();
    dap_delay_loop();
    DAP_CONFIG_SWCLK_set();
    dap_delay_loop();
  }
}
/*--------------------------------------------------------------------------------------------------------------------*/
static void dap_swd_write(uint32_t value, int size) {
	int i;
  for (i = 0; i < size; i++) {
    DAP_CONFIG_SWDIO_write(value & 1);
    DAP_CONFIG_SWCLK_clr();
    dap_delay_loop();
    DAP_CONFIG_SWCLK_set();
    dap_delay_loop();
    value >>= 1;
  }
}
/*--------------------------------------------------------------------------------------------------------------------*/
static uint32_t dap_swd_read(int size) {
  uint32_t value = 0;
	int i;
	
  for (i = 0; i < size; i++) {
    DAP_CONFIG_SWCLK_clr();
    dap_delay_loop();
    value |= ((uint32_t)DAP_CONFIG_SWDIO_read() << i);
    DAP_CONFIG_SWCLK_set();
    dap_delay_loop();
  }

  return value;
}
/*--------------------------------------------------------------------------------------------------------------------*/
uint32_t dap_parity(uint32_t value) {
  value ^= value >> 16;
  value ^= value >> 8;
  value ^= value >> 4;
  value &= 0x0f;

  return (0x6996 >> value) & 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
static int dap_swd_operation(int req, uint32_t *data) {
  uint32_t value;
  int ack = 0;

  dap_swd_write(0x81 | (dap_parity(req) << 5) | (req << 1), 8);

  DAP_CONFIG_SWDIO_in();

  dap_swd_clock(DAP_SWD_TURNAROUND);

  ack = dap_swd_read(3);

  if (DAP_TRANSFER_OK == ack) {
    if (req & DAP_TRANSFER_RnW) {
      value = dap_swd_read(32);

      if (dap_parity(value) != dap_swd_read(1))
        ack = DAP_TRANSFER_ERROR;

      if (data)
        *data = value;

      dap_swd_clock(DAP_SWD_TURNAROUND);

      DAP_CONFIG_SWDIO_out();
    }
    else {
      dap_swd_clock(DAP_SWD_TURNAROUND);

      DAP_CONFIG_SWDIO_out();

      dap_swd_write(*data, 32);
      dap_swd_write(dap_parity(*data), 1);
    }

    DAP_CONFIG_SWDIO_write(0);
    dap_swd_clock(DAP_IDLE_CYCLES);
  }

  else if (DAP_TRANSFER_WAIT == ack || DAP_TRANSFER_FAULT == ack) {
    if (DAP_SWD_DATA_PHASE && (req & DAP_TRANSFER_RnW))
      dap_swd_clock(32 + 1);

    dap_swd_clock(DAP_SWD_TURNAROUND);

    DAP_CONFIG_SWDIO_out();

    if (DAP_SWD_DATA_PHASE && (0 == (req & DAP_TRANSFER_RnW))) {
      DAP_CONFIG_SWDIO_write(0);
      dap_swd_clock(32 + 1);
    }
  }
  else {
    dap_swd_clock(DAP_SWD_TURNAROUND + 32 + 1);
  }

  DAP_CONFIG_SWDIO_write(1);

  return ack;
}
/*--------------------------------------------------------------------------------------------------------------------*/
static int dap_swd_transfer_word(int req, uint32_t *data) {
  int ack;
	int i;
	
  req &= (DAP_TRANSFER_APnDP | DAP_TRANSFER_RnW | DAP_TRANSFER_A2 | DAP_TRANSFER_A3);

  for (i = 0; i < DAP_RETRY_COUNT; i++) {
    ack = dap_swd_operation(req, data);

    if (DAP_TRANSFER_WAIT != ack)
      break;
  }

  return ack;
}

/*--------------------------------------------------------------------------------------------------------------------*/
static int dap_swd_transfer(int request, uint32_t *data) {
  int ack = DAP_TRANSFER_INVALID;
  bool posted_read = false;
  bool verify_write = false;

  if (request & DAP_TRANSFER_RnW) {
    if (request & DAP_TRANSFER_APnDP) {
      ack = dap_swd_transfer_word(request, NULL);

      if (ack != DAP_TRANSFER_OK)
        return ack;

      posted_read = true;
    }
    else {
      ack = dap_swd_transfer_word(request, data);

      if (DAP_TRANSFER_OK != ack)
        return ack;
    }
  }
  else {
    ack = dap_swd_transfer_word(request, data);

    if (ack != DAP_TRANSFER_OK)
      return ack;

    verify_write = true;
  }

  if (DAP_TRANSFER_OK == ack) {
    if (posted_read)
      ack = dap_swd_transfer_word(SWD_DP_R_RDBUFF | DAP_TRANSFER_RnW, data);

    else if (verify_write)
      ack = dap_swd_transfer_word(SWD_DP_R_RDBUFF | DAP_TRANSFER_RnW, NULL);
  }

  return ack;
}

/*--------------------------------------------------------------------------------------------------------------------*/
static void dap_swj_sequence(int size, uint8_t *data) {
  int offset = 0;

  while (size) {
    int sz = (size > 8) ? 8 : size;

    dap_swd_write(data[offset], sz);

    size -= sz;
    offset++;
  }
}

/*--------------------------------------------------------------------------------------------------------------------*/
static bool dap_read_reg(uint8_t reg, uint32_t *value) {
  return (DAP_TRANSFER_OK == dap_swd_transfer(reg | DAP_TRANSFER_RnW, value));
}

/*--------------------------------------------------------------------------------------------------------------------*/
static bool dap_write_reg(uint8_t reg, uint32_t value) {
  return (DAP_TRANSFER_OK == dap_swd_transfer(reg, &value));
}

/*--------------------------------------------------------------------------------------------------------------------*/
void dap_init(void) {
  DAP_CONFIG_SETUP();
}

/*--------------------------------------------------------------------------------------------------------------------*/
void dap_connect(void) {
  DAP_CONFIG_CONNECT_SWD();
}

/*--------------------------------------------------------------------------------------------------------------------*/
void dap_disconnect(void) {
  DAP_CONFIG_DISCONNECT();
}

/*--------------------------------------------------------------------------------------------------------------------*/
uint32_t dap_read_word(uint32_t addr) {
  uint32_t data;

  if (!dap_write_reg(SWD_AP_TAR, addr))
    return 0;

  if (!dap_read_reg(SWD_AP_DRW, &data))
    return 0;

  return data;
}

/*--------------------------------------------------------------------------------------------------------------------*/
void dap_write_word(uint32_t addr, uint32_t data) {
  dap_write_reg(SWD_AP_TAR, addr);
  dap_write_reg(SWD_AP_DRW, data);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void dap_reset_link(void) {
  uint8_t buf[20];
  uint32_t idcode;

  buf[0] = 0xff;
  buf[1] = 0xff;
  buf[2] = 0xff;
  buf[3] = 0xff;
  buf[4] = 0xff;
  buf[5] = 0xff;
  buf[6] = 0xff;
  buf[7] = 0x9e;
  buf[8] = 0xe7;
  buf[9] = 0xff;
  buf[10] = 0xff;
  buf[11] = 0xff;
  buf[12] = 0xff;
  buf[13] = 0xff;
  buf[14] = 0xff;
  buf[15] = 0xff;
  buf[16] = 0x00;

  dap_swj_sequence((7 + 2 + 7 + 1) * 8, buf);

  dap_read_reg(SWD_DP_R_IDCODE, &idcode);
}

/*--------------------------------------------------------------------------------------------------------------------*/
uint32_t dap_read_idcode(void) {
  uint32_t idcode;

  if (dap_read_reg(SWD_DP_R_IDCODE, &idcode))
    return idcode;

  return 0xffffffff;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void dap_target_prepare(void) {
  dap_write_reg(SWD_DP_W_ABORT, 0x00000016);
  dap_write_reg(SWD_DP_W_SELECT, 0x00000000);
  dap_write_reg(SWD_DP_W_CTRL_STAT, 0x50000f00);
  dap_write_reg(SWD_AP_CSW, 0x23000052);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void dap_target_select(void) {
  // Stop the core
  dap_write_word(DHCSR, 0xa05f0003);
  dap_write_word(DEMCR, 0x00000001);
  dap_write_word(AIRCR, 0x05fa0004);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void dap_target_deselect(void) {
  dap_write_word(DEMCR, 0x00000000);
  dap_write_word(AIRCR, 0x05fa0004);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void dap_target_erase(void) {
  dap_write_word(CMU_WPREG, CMU_WPREG_UNPROTECTED); // Unlock Region
  while (0 == (dap_read_word(CMU_WPREG) & 1));
	
	dap_write_word(CMU_FLASHLOCK, CMU_FLASHLOCK_UNLOCKED);

	dap_write_word(CMU_FLASHCON, CMU_FLASHCON_FOP_CHIPERASE);
	
	dap_write_word(0x00000000, 0x000000FF);
	
	while (dap_read_word(CMU_FLASHCON) & CMU_FLASHCON_BUSY);
	
	dap_write_word(CMU_FLASHCON, CMU_FLASHCON_FOP_READ);
	
	dap_write_word(CMU_FLASHLOCK, CMU_FLASHLOCK_LOCKED);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void dap_target_write_flash(uint32_t addr, const uint8_t *data, uint32_t len) {
	uint32_t offs;
	uint32_t value;

  dap_write_word(CMU_WPREG, CMU_WPREG_UNPROTECTED); // Unlock Region
  while (0 == (dap_read_word(CMU_WPREG) & 1));

	dap_write_word(CMU_FLASHLOCK, CMU_FLASHLOCK_UNLOCKED);

	dap_write_word(CMU_FLASHCON, CMU_FLASHCON_FOP_WRITE);
	
	for (offs = 0; offs < len; offs += sizeof(uint32_t))
  {
    value = ((uint32_t)data[offs + 3] << 24) | ((uint32_t)data[offs + 2] << 16) | ((uint32_t)data[offs + 1] << 8) | (uint32_t)data[offs];
		dap_write_word(addr + offs, value);
		while (dap_read_word(CMU_FLASHCON) & CMU_FLASHCON_BUSY);
	}
	
	dap_write_word(CMU_FLASHCON, CMU_FLASHCON_FOP_READ);
	
	dap_write_word(CMU_FLASHLOCK, CMU_FLASHLOCK_LOCKED);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void dap_target_read_page(uint32_t addr, uint8_t *data, uint16_t len) {
	int offs;
  for (offs = 0; offs < len; offs += sizeof(uint32_t)) {
    uint32_t value = dap_read_word(addr + offs);

    data[offs + 0] = (value >> 0) & 0xff;
    data[offs + 1] = (value >> 8) & 0xff;
    data[offs + 2] = (value >> 16) & 0xff;
    data[offs + 3] = (value >> 24) & 0xff;
  }
}
/************************************************** Tasks *************************************************************/
/*
    Nothing
*/
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/




