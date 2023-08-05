#ifndef __PWM_HPP
#define __PWM_HPP
//----------------------------------------------------------
#include "defines.h"
#include "debug.hpp"
#include "stm32l1xx_tim.h"
#include "stm32l1xx_rcc.h"
#include "gpio.hpp"
#include "TaskManager.hpp"
//----------------------------------------------------------
void __init_PWM(void);

void PWM_Write(U8 Channel, U16 Frequence, U16 Duty);			
//----------------------------------------------------------
#endif
