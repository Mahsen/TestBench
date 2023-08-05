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
#include "wizards.cpp"
//************************************************************ defineds in Wizard ********************************************************//
/*
none
*/	
//************************************************************ includes ******************************************************************//
#include "debug.hpp"
//************************************************************ variables *****************************************************************//
#if(DEBUG_ENABLE)
	#if(DEBUG_ENABLE_LOG)
		struct TABLE_DEBUG
		{
			RTC_Struct   DateTime;
			char         Buffer[128]; 
			U8           Length_Buffer;
		};
		EMSQL<TABLE_DEBUG, 1000> emsql_table_debug;
		char DEBUG_Buffer[1024];
		RTC_Struct DEBUG_datetime;
	#endif	
#endif			                                   
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
/**
 * @brief 	پيکره بندي اوليه اين ماژول
*/
/**
 * \image html 54854debug.jpg
*/
void __init_Debug(void)
{
#if(DEBUG_ENABLE)

	/// پيکره بندي پورت سريال با تنظيمات متناسب با ديباگ
	UART_UpdateSetting(DEBUG_UART, DEBUG_BOUDRATE, DEBUG_DATABIT, DEBUG_PARITY, DEBUG_STOPBIT, true);
	
	#if(DEBUG_ENABLE_LOG)
	
		/// معرفي فايل ذخيره سازي ديباگ
	      emsql_table_debug.Bind("emsql_table_debug");
		
	#endif	
	#warning "Debug : Turn On"
#else
	#warning "Debug : Turn Off"
#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	ارسال به پورت ديباگ و ذخيره سازي آن در فايل
 * @param[in]	String    data input of string
*/
void Debug(const char * String)
{
#if(DEBUG_ENABLE)
	#if(DEBUG_ENABLE_ALERT)
		/// ارسال ديتا به پورت سريال
		Debug_Alert(String);
	#endif
	#if(DEBUG_ENABLE_LOG)
		/// ذخيره سازي ديتا درون فايل
		Debug_Log(String);
	#endif
#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	ارسال به پورت ديباگ 
 * @param[in]	String    data input of string
*/
void Debug_Alert(const char * String)
{
#if(DEBUG_ENABLE&&DEBUG_ENABLE_ALERT)
	UART_Send_String(DEBUG_UART, (uint8_t*)"Debug_Alert(", 12);
	UART_Send_String(DEBUG_UART, (uint8_t*)String, strlen(String));
	UART_Send_String(DEBUG_UART, (uint8_t*)")\r\n", 3);
#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	ارسال به پورت ديباگ 
 * @param[in]	String    data input of string
*/
void Debug_Alert(unsigned char * String)
{
#if(DEBUG_ENABLE&&DEBUG_ENABLE_ALERT)
	UART_Send_String(DEBUG_UART, (uint8_t*)"Debug_Alert(", 12);
	UART_Send_String(DEBUG_UART, (uint8_t*)String, strlen((char*)String));
	UART_Send_String(DEBUG_UART, (uint8_t*)")\r\n", 3);
#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	ارسال به پورت ديباگ 
 * @param[in]	String    data input of string
*/
void Debug_Alert(const unsigned char * String)
{
#if(DEBUG_ENABLE&&DEBUG_ENABLE_ALERT)
	UART_Send_String(DEBUG_UART, (uint8_t*)"Debug_Alert(", 12);
	UART_Send_String(DEBUG_UART, (uint8_t*)String, strlen((char*)String));
	UART_Send_String(DEBUG_UART, (uint8_t*)")\r\n", 3);
#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	ارسال به پورت ديباگ و ذخيره سازي آن در فايل
 * @param[in]	Value    data input of integer
*/
void Debug(int Value)
{
#if(DEBUG_ENABLE)
	char String[20];
	sprintf(String,"%d",Value);
	#if(DEBUG_ENABLE_ALERT)
		Debug_Alert(String);
	#endif
	#if(DEBUG_ENABLE_LOG)
		Debug_Log(String);
	#endif
#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	ارسال به پورت ديباگ
 * @param[in]	Value    data input of integer
*/
void Debug_Alert(int Value)
{
	char String[20];
	sprintf(String,"%d",Value);
	#if(DEBUG_ENABLE_ALERT)
		Debug_Alert(String);
	#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	ارسال به پورت ديباگ و ذخيره سازي آن در فايل
 * @param[in]	Value    data input of long integer
*/
void Debug(long int Value)
{
#if(DEBUG_ENABLE)
	char String[20];
	sprintf(String,"%ld",Value);
	#if(DEBUG_ENABLE_ALERT)
		Debug_Alert(String);
	#endif
	#if(DEBUG_ENABLE_LOG)
		Debug_Log(String);
	#endif
#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	ارسال به پورت ديباگ
 * @param[in]	Value    data input of long integer
*/
void Debug_Alert(long int Value)
{
	char String[20];
	sprintf(String,"%ld",Value);
	#if(DEBUG_ENABLE_ALERT)
		Debug_Alert(String);
	#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	ارسال به پورت ديباگ و ذخيره سازي آن در فايل
 * @param[in]	Value    data input of float
*/
void Debug(float Value)
{
#if(DEBUG_ENABLE)
	char String[20];
	sprintf(String,"%f",Value);
	#if(DEBUG_ENABLE_ALERT)
		Debug_Alert(String);
	#endif
	#if(DEBUG_ENABLE_LOG)
		Debug_Log(String);
	#endif
#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	ارسال به پورت ديباگ
 * @param[in]	Value    data input of float
*/
void Debug_Alert(float Value)
{
	char String[20];
	sprintf(String,"%f",Value);
	#if(DEBUG_ENABLE_ALERT)
		Debug_Alert(String);
	#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 	  ذخيره سازي آن در فايل
 * @param[in]	String    data input of string
*/
void Debug_Log(const char * String)
{
#if(DEBUG_ENABLE&&DEBUG_ENABLE_LOG)

			if(Inited_SD_CARD)
			{
				U16 TimeOutOpenEMSQL = 60;
				while(TimeOutOpenEMSQL--)		
				{
						if(emsql_table_debug.Open())
						{
							emsql_table_debug.Finish();
							
							emsql_table_debug.Fields.DateTime = RTC_GetDateTime_Shamsi();
							emsql_table_debug.Fields.Length_Buffer = strlen(String);
							strcpy(emsql_table_debug.Fields.Buffer, String);
								
							emsql_table_debug.Update();
							emsql_table_debug.Close();

							break;
						}
						TaskManager_Delay(1 Sec);
				}
			}
#endif
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//#if(DEBUG_ENABLE)
//#if(DEBUG_ENABLE_LOG)
//bool DEBUG_Execute_SaaGPRS(U16 Unique_Request, U16 Unique_Respond, U8 *Command, U8 *Meter_Number, U8 *Password, U16 Current_Packet, U16 Number_Of_Packet, U8 *Data, U16 Data_Length)
//{
//		if(Current_Packet == Number_Of_Packet)
//		{
//			/// بررسي رشته کامند با دستور خواندن لاگ
//			if(strcmp(SAAGPRS_DEBUG_READ_LOG, (char*)Command) == NULL)
//			{

//					U16 TimeOutOpenEMSQL = 10000;

//					while(TimeOutOpenEMSQL--)
//					{
//						if(emsql_table_debug.Open())
//						{
//								int AllRecord = emsql_table_debug.All_Record();
//								int FirstSearchRecord = 0;
//								int NumberSearchRecord = 0;

//								if(Data_Length)
//								{
//									sscanf((char*)Data, "%d", &NumberSearchRecord);
//								}
//								
//								if((AllRecord > NumberSearchRecord) && (NumberSearchRecord))
//								{
//									FirstSearchRecord = AllRecord - NumberSearchRecord;
//								}
//								else
//								{
//									NumberSearchRecord = AllRecord;
//									FirstSearchRecord = 0;
//								}

//								U32 Length = RESET;
//								U16 packet = RESET;
//								
//								emsql_table_debug.Where(FirstSearchRecord);	
//								
//								for(U16 i=0; (i<NumberSearchRecord); i++)
//								{
//									emsql_table_debug.Refresh();

//									if((Length + (emsql_table_debug.Fields.Length_Buffer + 24)) >= Modem.Protocol.saa.Setting.GetGPRSLengthPacket())
//									{
//											packet++;
//											Length = RESET;
//									}
//											
//									Length += emsql_table_debug.Fields.Length_Buffer + 24;
//									emsql_table_debug.Next();
//								}
//								
//								if(Length)
//								{
//									packet++;
//								}
//									
//								U16 sent = RESET;
//								if(packet)
//								{

//									Length = RESET;	
//									
//									emsql_table_debug.Where(FirstSearchRecord);
//								
//									memset(DEBUG_Buffer, 0, sizeof(DEBUG_Buffer));
//									for(U16 i=0; (i<NumberSearchRecord); i++)
//									{

//											emsql_table_debug.Refresh();

//											if((Length + (emsql_table_debug.Fields.Length_Buffer + 24)) >= Modem.Protocol.saa.Setting.GetGPRSLengthPacket())
//											{
//												sent++;
//												Modem.Protocol.saa.AddSendGPRS(Unique_Request, \
//													Command, \
//													Meter_Number, \
//													Password, \
//													sent, \
//													packet, \
//													true, \
//													(U8*)DEBUG_Buffer, \
//													Length);
//											
//												memset(DEBUG_Buffer, 0, sizeof(DEBUG_Buffer));
//												Length = RESET;
//											}
//											
//											sprintf(&DEBUG_Buffer[Length], "%04d/%02d/%02d %02d:%02d:%02d : %s\r\n", \
//												emsql_table_debug.Fields.DateTime.Year, \
//												emsql_table_debug.Fields.DateTime.Month, \
//												emsql_table_debug.Fields.DateTime.Day, \
//												emsql_table_debug.Fields.DateTime.Hour, \
//												emsql_table_debug.Fields.DateTime.Minute, \
//												emsql_table_debug.Fields.DateTime.Second, \
//												emsql_table_debug.Fields.Buffer);
//									
//											Length = strlen(DEBUG_Buffer);

//											emsql_table_debug.Next();
//									}

//									if(Length)
//									{
//											Modem.Protocol.saa.AddSendGPRS(Unique_Request, Command, Meter_Number, Password, packet, packet, true, (U8*)DEBUG_Buffer, Length);
//									}
//								}
//								else
//								{
//									Modem.Protocol.saa.AddSendGPRS(Unique_Request, Command, Meter_Number, Password, 1, 1, true, (U8*)"EMPTY", 5);								
//								}
//								
//								emsql_table_debug.Close();
//								return true;
//						}
//						
//						TaskManager_Delay(10 MSec);
//					}

//			}
//			/// بررسي رشته کامند با دستور پاک کردن لاگ 
//			else if(strcmp(SAAGPRS_DEBUG_EXECUTE_DELETELOG, (char*)Command) == NULL)
//			{
//					U16 TimeOutOpenEMSQL = 10000;

//					while(TimeOutOpenEMSQL--)
//					{		
//						if(emsql_table_debug.Open())
//						{	
//								emsql_table_debug.Delete();
//								emsql_table_debug.Close();

//								Modem.Protocol.saa.AddSendGPRS(Unique_Request, Command, Meter_Number, Password, 1, 1, true, (U8*)"OK", 2);	
//								
//								return true;
//								
//						}
//						TaskManager_Delay(10 MSec);
//					}
//					
//					Modem.Protocol.saa.AddSendGPRS(Unique_Request, Command, Meter_Number, Password, 1, 1, true, (U8*)"ERROR", 5);	
//					
//					return true;			
//			}

//			Modem.Protocol.saa.AddSendGPRS( \
//				Unique_Respond, \
//				Command, \
//				Meter_Number, \
//				Password, \
//				1, \
//				1, \
//				false, \
//				(U8*)"Command Not Support", \
//				19);
//		}
//		
//	
//		return false;	
//}
//#endif
//#endif
//*************************************************************** tasks *******************************************************************//
/*
none
*/
//************************************************************** vectors ******************************************************************//
/*
none
*/
//****************************************************************************************************************************************//










