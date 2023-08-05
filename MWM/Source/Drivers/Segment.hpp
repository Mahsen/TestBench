#ifndef __SEGMENT_HPP
#define __SEGMENT_HPP
//----------------------------------------------------------
#include "defines.h"
#include "gpio.hpp"
#include "tasktimer.hpp"
//----------------------------------------------------------
void __init_Segment(void);	
void Segment_Blink(void);
void Segment_WriteString(U8* Data, bool Blink);
void Segment_WriteString(U8* Data, bool Blink, U16 Timeout);
//----------------------------------------------------------
#endif
