#ifndef __HEXTYPE_HPP
#define __HEXTYPE_HPP
//----------------------------------------------------------
#include "defines.h" 
//----------------------------------------------------------
void HEXTYPE_Hex2Ascii(U8* Convert,U8* ConvertTo,U16 Length);
U8 HEXTYPE_Hex2Ascii(U8 Convert);
void HEXTYPE_Ascii2Hex(U8* Convert,U8* ConvertTo,U16 Length);
U8 HEXTYPE_Ascii2Hex(U8 Convert);
S16 HEXTYPE_MemFind(U8* Source,U16 Source_Length, U8* Find, U16 Find_Length);
bool HEXTYPE_ArePrintable(U8* Data,U16 Length);
//----------------------------------------------------------
#endif
