#ifndef __ADC_HPP
#define __ADC_HPP
//----------------------------------------------------------
#include "defines.h"
#include "debug.hpp"
#include "stm32l1xx_adc.h"
#include "gpio.hpp"
#include "TaskManager.hpp"
//----------------------------------------------------------
void __init_ADC(void);

U32 ADC_Read (U16 Channel);			
//----------------------------------------------------------
#endif
