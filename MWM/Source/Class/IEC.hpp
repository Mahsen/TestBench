#ifndef __IEC_HPP
#define __IEC_HPP
//----------------------------------------------------------
#include "defines.h"
#include "media.hpp"
#include "taskmanager.hpp"
#include "heap.hpp"
#include "debug.hpp"
#include "sha256.hpp"
#include "hextype.hpp"
#include "timer.hpp"
#include "eeprom.hpp"
#include "timer.hpp"
#include "stdlib.h"
//----------------------------------------------------------
#define  IEC_READOUT                           '0'
#define  IEC_PROGRAMING                        '1'
#define  IEC_MANUFACTOR                        '2'

#define  IEC_DEFAULT_KEY_SECRET1                1111111111111111
#define  IEC_DEFAULT_KEY_SECRET2                9999999999999999
#define  IEC_LEVEL0                             0
#define  IEC_LEVEL1                             1
#define  IEC_LEVEL2                             2
//----------------------------------------------------------
const U8  IEC_Status_Messages[][40] = 
{
	"Success",
	"ReadOut",
	"Continues",
	"Error_OBIS",
	"Error_NoFun",
	"Error_Address",
	"Error_Receive",
	"Error_CRC",
	"Error_Disconnect",
	"Error_TimeOut",
	"Error_Full",
	"Error_Pass",
	"Error_Format",
	"Error_NotOpen",
	"Error_BoudRate",
	"Error_Password",
	"Error_Level",
	"Error_NoMedia"
};
//----------------------------------------------------------
class IEC
{
	
	public:
		
		/// توابع عمومي
		//{		
		void Init(void);
		static U8 GetBCC  (U8 *Data, U16 Data_Length);		
		//}
	
		/// ساختار حالت
		//{
	        struct Status
		{
			struct
			{
				enum 
				{
					Success = RESET,
					ReadOut,
					Continues,
					Error_OBIS,
					Error_NoFun,
					Error_Address,
					Error_Receive,
					Error_CRC,
					Error_Disconnect,
					Error_TimeOut,
					Error_Full,
					Error_Pass,
					Error_Format,
					Error_NotOpen,
					Error_BoudRate,
					Error_Password,
					Error_Level,
					Error_NoMedia
				};
			} Messages;

			U8 Message;
			void SetMessage(U8 Value)
			{
				Message = Value;
			}
			U8 GetMessage(void)
			{
				return Message;
			}
			
			U8*  ToString(void)
			{
				return (U8*)IEC_Status_Messages[Message];
			}
		};
		//}
		
		/// پارامتر ها
		//{
		struct struct_Parameters
		{
			/// متغير فلگ ذخيره سازي
			//{		
			bool FlagSave;
			void SetFlagSave(U32 Value)
			{
				FlagSave = Value;
			}	
			U32 GetFlagSave(void)
			{
				return FlagSave;
			}			
			void ResetFlagSave(void)
			{
				SetFlagSave(false);
			}
			//}
			
			/// کليد رمز 1
			//{
			U64 Secret1;
			void SetSecret1(U64 Value)
			{
				Secret1 = Value;
			}
			U64 GetSecret1(void)
			{
				return Secret1;
			}
			void ResetSecret1(void)
			{
				SetSecret1(IEC_DEFAULT_KEY_SECRET1);
			}
			//}
			/// کليد رمز 2
			//{
			U64 Secret2;
			void SetSecret2(U64 Value)
			{
				Secret2 = Value;
			}
			U64 GetSecret2(void)
			{
				return Secret2;
			}
			void ResetSecret2(void)
			{
				SetSecret2(IEC_DEFAULT_KEY_SECRET2);
			}
			//}
			
			/// آدرس پروتکل
			//{
			U8  PrimaryAddress[16];
			void SetPrimaryAddress(U8* Value)
			{
				strcpy((char*)PrimaryAddress, (char*)Value);
			}
			U8* GetPrimaryAddress(void)
			{
				return PrimaryAddress;
			}
			void ResetPrimaryAddress(void)
			{
				SetPrimaryAddress((U8*)"01");
			}
			//}
		
			void Save(void)
			{
				U8 SavedToEEPROM;
				U32 Address = ADDRESSEEPROM_IEC_OFFSET_ADDRESS;

				EEPROM_WriteData(Address, (U8*)&Secret1, sizeof(Secret1));	
				Address += sizeof(Secret1);
				
				EEPROM_WriteData(Address, (U8*)&Secret2, sizeof(Secret2));	
				Address += sizeof(Secret2);
				
				EEPROM_WriteData(Address, (U8*)&PrimaryAddress, sizeof(PrimaryAddress));	
				Address += sizeof(PrimaryAddress);
				
				/// مقدار دهي فلگ
				//{
				SavedToEEPROM = 0xBB;
				EEPROM_WriteData(Address, &SavedToEEPROM, 1);	
				//}			
				//}
			}
			
			void Load(void)
			{
				U8 SavedToEEPROM;
				U32 Address = ADDRESSEEPROM_IEC_OFFSET_ADDRESS;
				U32 AddressFlag = ADDRESSEEPROM_IEC_OFFSET_ADDRESS;

				AddressFlag += sizeof(Secret1);
				AddressFlag += sizeof(Secret2);
				AddressFlag += sizeof(PrimaryAddress);
				
				EEPROM_ReadData(AddressFlag, &SavedToEEPROM, 1);

				if(SavedToEEPROM == 0xBB)
				{					
					/// خواندن از آخرين بکآپ
					//{
					EEPROM_ReadData(Address, (U8*)&Secret1, sizeof(Secret1));	
					Address += sizeof(Secret1);
					
					EEPROM_ReadData(Address, (U8*)&Secret2, sizeof(Secret2));	
					Address += sizeof(Secret2);
					
					EEPROM_ReadData(Address, (U8*)&PrimaryAddress, sizeof(PrimaryAddress));	
					Address += sizeof(PrimaryAddress);
					//}
				}
				else
				{
					
					/// مقدار دهي اوليه 
					//{
					ResetSecret1();
					ResetSecret2();
					ResetPrimaryAddress();
					//}
					
					/// نوشتن بر آخرين بکآپ
					//{
					Save();			
					//}
				}
				
				///FlagSave مقدار دهي اوليه 
				//{
				ResetFlagSave();
				//}
			}
			
		} Parameters;
		//}
		
		struct struct_Client
		{
			private:
					
				bool Is_Open;	

				/// متغير بافر
				//{
				U8 Buffer[1024];
				void ResetBuffer(void)
				{
					memset(Buffer, NULL, sizeof(Buffer));
				}
				//}
			
				/// متغير مدياي ارتباطي
				//{
				MEDIA* Media;
				void SetMedia(MEDIA* Value)
				{
					Media = Value;
				}
				MEDIA* GetMedia(void)
				{
					return Media;
				}
				//}
						
				U32   IEC_Delay;
		
			public:
				
				Status Connect(MEDIA* MyMedia, U8* MyAddress, U8 Level, void (*Respond)(U8 *Data, U16 Length), U8 *Password, U32 StartBoudrate, U8 Mode, bool SendNULL);
				Status DisConnect(void);
				Status SendCommand(U8 *Data, void (*Respond)(U8 *Data, U16 Length));
				
				struct_Client (void)
				{
					Is_Open = false;
				}

				bool IsOpen(void)
				{
					return Is_Open;
				}
				
				bool Open(void)
				{
					if(!Is_Open)
					{
							Is_Open = true;
							return true;
					}
					
					return false;
				}
				
				bool Close(void)
				{
					if(Is_Open)
					{
							Is_Open = false;
							return true;
					}
					
					return false;
				}
		} Client;
	
		/// ساخت نمونه ساختار شي
		//{
		static IEC* GetInstance(void)
		{
			static void* THIS = NULL;
			
			if(!THIS)
			{
				HEAP::GetInstance()->GetBlock(THIS, sizeof(IEC), (U8*)"IEC");
			}
			
			return (IEC*)THIS;
		}
		//}
};
//----------------------------------------------------------
void __init_IEC(void);
//----------------------------------------------------------
#endif
