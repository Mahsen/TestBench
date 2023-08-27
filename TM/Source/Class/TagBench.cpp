/************************************************** Description *******************************************************/
/*
    File : tagbench.cpp
    Programmer : Mohammad Lotfi
    Used : Use header
    Design Pattern : Virtual
    Types of memory : Nothing
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2023/8/5
*/
/************************************************** Warnings **********************************************************/
/*
    Nothing
*/
/************************************************** Wizards ***********************************************************/
/*
    Nothing
*/
/************************************************** Includes **********************************************************/
#include "tagbench.hpp"
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
/*
    Nothing
*/
/************************************************** Variables *********************************************************/
/*
    Nothing
*/
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
bool class_TagBench::Detach()
{
	char *pch;
	
	Parmeters.Command.Reset();
	Parmeters.Data.Reset();
	
	pch = strtok((char*)Parmeters.Message.Get(), "<>:");
	if(pch)
	{
		if(strcmp((char*)pch, "TEST_BENCH") == NULL)
		{
			pch = strtok(NULL, "<>:");			
			if(pch)
			{
				Parmeters.Command.Set((uint8_t*)pch);
				pch = strtok(NULL, "<>");				
				if(pch)
				{
					if(strcmp((char*)pch, "/TEST_BENCH") == NULL)
					{
						return true;
					}
					else
					{
						Parmeters.Data.Set((uint8_t*)pch);
						pch = strtok(NULL, "<>:");
						if(pch)
						{
							if(strcmp((char*)pch, "/TEST_BENCH") == NULL)
							{
								return true;
							}
						}
					}
				}
			}			
		}
	}

	Parmeters.Command.Reset();
	Parmeters.Data.Reset();
	
	return false;
}
/*--------------------------------------------------------------------------------------------------------------------*/
bool class_TagBench::Attach()
{
	Parmeters.Message.Reset();	
	sprintf((char*)Parmeters.Message.Data, "<TEST_BENCH:%s>%s</TEST_BENCH>\r\n", Parmeters.Command.Get(), Parmeters.Data.Get());	
	return true;
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
