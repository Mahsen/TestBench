//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1395/01/29
Programmer : Mohammad Lotfi
Site : http://www.mahsen.ir
Tel : +989124662703
*/
//************************************************************* Warning *****************************************************************//
/*
none
*/
//************************************************************* Wizard ******************************************************************//
/*
nones
*/	
//************************************************************ defineds in Wizard ********************************************************//
/*
none
*/	
//************************************************************ includes ******************************************************************//
#include "HexType.hpp"
//************************************************************ variables *****************************************************************//
const U8 HEXTYPE_Value_Hex2Ascii[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};					                                   
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
/**
 * @brief 		Convert Hex to Ascii
 * @param[in]	Convert Hex
 * @return 		Ascii 
*/
U8 HEXTYPE_Hex2Ascii(U8 Convert)
{
	return HEXTYPE_Value_Hex2Ascii[Convert];
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		    Convert Hex to Ascii
 * @param[in]	    Convert data input hex
 * @param[out]	  ConvertTo data output ascii
 * @param[in]   	Length data Convert
*/
void HEXTYPE_Hex2Ascii(U8* Convert,U8* ConvertTo,U16 Length)
{
	for(U16 i=0,j=0;i<Length;i++,j+=2)
	{
		ConvertTo[j+1] = HEXTYPE_Value_Hex2Ascii[((Convert[i])&0x0F)];
		ConvertTo[j] = HEXTYPE_Value_Hex2Ascii[(((Convert[i])&0xF0)>>4)];
	}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		Convert Ascii to Hex
 * @param[in]	Convert Ascii
 * @return 		Hex
*/
U8 HEXTYPE_Ascii2Hex(U8 Convert)
{
	
	if((Convert >= '0') && (Convert <= '9'))
	{
		return (Convert - '0' + 0x00);
	}
	else if((Convert >= 'a') && (Convert <= 'f'))
	{
		return (Convert - 'a' + 0x0A);			
	}
	else if((Convert >= 'A') && (Convert <= 'F'))
	{
		return (Convert - 'A' + 0x0A);			
	}
	else
	{
		return 0x00;
	}

}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	Convert Ascii to Hex
 * @param[in]	    Convert data input Ascii
 * @param[out]	  ConvertTo data output Hex
 * @param[in]   Length data Convert
*/
void HEXTYPE_Ascii2Hex(U8* Convert,U8* ConvertTo,U16 Length)
{
	S16 i = 0, j = 0;

	for(;i<Length;i++,j+=2)
	{
		ConvertTo[i] = (((HEXTYPE_Ascii2Hex(Convert[j]) << 4) & 0xF0) | (HEXTYPE_Ascii2Hex(Convert[j+1]) & 0x0F));
	}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	Find location data in another data
 * @param[in]	Source         input data for source
 * @param[in]	Source_Length  length input data for source
 * @param[in]	Find input     data for search
 * @param[in]	Find_Length    length  input data for search
 * @return 	location find
*/
S16 HEXTYPE_MemFind(U8* Source,U16 Source_Length, U8* Find, U16 Find_Length)
{

	bool Find_Flag;
	for(U16 i=0; i<Source_Length ;i++)
	{
		Find_Flag = true;
		for(int j=0; j<(Find_Length-1) ;j++)
		{
			if(Source[i+j] != Find[j])
			{
				Find_Flag = false;
				break;
			}
		}
		if(Find_Flag)
		{
			return i;
		}
	}

  	return -1;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		Are data input is printable
 * @param[in]	Data    input data for check
 * @param[in]	Length  length input data for check
 * @return 		if data is printable return true
*/
bool HEXTYPE_ArePrintable(U8* Data,U16 Length)
{
	for(U16 i=0 ; i<Length ;i++)
	{
		if(Data[i]<0x20 && Data[i]!='\r' && Data[i]!='\n')
		{
			return false;
		}
	}

	return true;
}
//************************************************************** vectors ******************************************************************//
/*
none
*/
//****************************************************************************************************************************************//










