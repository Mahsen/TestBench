#ifndef __DEFINES_H
#define __DEFINES_H
//----------------------------------------------------------
#include <RTL.h>								                             // Include the RL-RTX header file
#include "stm32l1xx.h"
#include <string.h>
#include <stdio.h>
//----------------------------------------------------------
#define OFFSETOF(Type, Field)    ((unsigned long) &(((Type *) 0)->Field))
//----------------------------------------------------------
typedef void (*CallBack_Type)(void);
//----------------------------------------------------------
#define     C_UNIC              * 1
//----------------------------------------------------------
#define     NULL_CHAR           0x00
#define     CR_CHAR             0x0D
#define     LF_CHAR             0x0A
#define     ACK_CHAR            0x06
#define     CTRLZ_CHAR          0x1A
#define     DEL_CHAR            0x7F
#define     SOH_CHAR            0x01
#define     STX_CHAR            0x02
#define     ETX_CHAR            0x03
#define     EOT_CHAR            0x04
#define     NAK_CHAR            0x15
//----------------------------------------------------------
//	#ifndef TRUE
//		#define   TRUE               1
//	#endif
//	#ifndef TRUE
//		#define   FALSE              0
//	#endif
//	#ifndef SET
//		#define   SET                1
//	#endif
//	#ifndef RESET
//		#define   RESET              0
//	#endif
	#ifndef OUTPUT
		#define   OUTPUT             1
	#endif
	#ifndef INPUT
		#define   INPUT              0
	#endif
//	#ifndef ENABLE
//		#define   ENABLE             1
//	#endif
//	#ifndef DISABLE
//		#define   DISABLE            0
//	#endif
//	#ifndef UP
//		#define   UP                 1
//	#endif
#endif
