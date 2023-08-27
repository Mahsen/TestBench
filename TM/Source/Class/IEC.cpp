//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1396/03/31
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
none
*/
//************************************************************ defineds ******************************************************************//
/*
none
*/
//************************************************************ includes ******************************************************************//
#include "iec.hpp"
//************************************************************ variables *****************************************************************//
const U32 IEC_Table_BoadRate[] = {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};		
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
/**
 * @brief 		initialize IEC
*/
void __init_IEC(void)
{
	
	/// پيکره بندي کلاس
	//{
	IEC::GetInstance()->Init();
	//}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void IEC::Init(void)
{
	/// بارگذاري رمز
	//{
	Parameters.Load();
	//}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
U8 IEC::GetBCC  (U8 *Data, U16 Data_Length)
{
	U8 bcc = RESET;

	for(U16 Index=1;Index<Data_Length;Index++)
	{
		bcc ^= Data[Index];
	}

	return bcc;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
IEC::Status IEC::struct_Client::Connect(MEDIA* MyMedia, U8* MyAddress, U8 Level, void (*Respond)(U8 *Data, U16 Length), U8 *Password, U32 StartBoudrate, U8 Mode, bool SendNULL)
{
	Status status;
	status.SetMessage(status.Messages.Success);

	U16 b_time;
	U32 Length;
	U8  Boudrate;
	U8* Identification;

	if(!Is_Open)
	{
		status.SetMessage(status.Messages.Error_NotOpen);
		return status;
	}
	
	if(!MyMedia)
	{
		status.SetMessage(status.Messages.Error_NoMedia);
		return status;
	}

	///Init first boudrate
	//{
	SetMedia(MyMedia);	
	GetMedia()->Speed(StartBoudrate);
	//}
	
	Boudrate = 0;
	IEC_Delay = 1 Sec;
	
	///Send null if (SendNULL==true)
	//{
	if(SendNULL)
	{
		b_time = 3;
		memset(Buffer,0,sizeof(Buffer));
		while(b_time--)
		{
			GetMedia()->Send(Buffer, sizeof(Buffer));
			TaskManager_Delay(100 MSec);
		}
	}
	//}
	
	
	///Request Identification sample : "/?!<CR><LF>"
	//{
	GetMedia()->Reset();
	sprintf((char*)Buffer, "/?%s!\r\n", MyAddress?(char*)MyAddress:"");
	TaskManager_Delay(100 MSec);
	GetMedia()->Send(Buffer, strlen((char*)Buffer));

	/// دريافت پکت
	//{
	status.SetMessage(status.Messages.Error_TimeOut);
	for(U32 Index=RESET; Index<50; Index++)
	{
		if(GetMedia()->GetStatus().Receive.GetBusy())
		{
			for(U32 Index=RESET; Index<100; Index++)
			{		
				Length = GetMedia()->GetStatus().Receive.GetLength();	
				TaskManager_Delay(500 MSec);
				if(Length == GetMedia()->GetStatus().Receive.GetLength())
				{
					break;
				}		
			}

			if(GetMedia()->GetStatus().Receive.GetLength() > sizeof(Buffer))
			{
				status.SetMessage(status.Messages.Error_Full);
				return status;
			}
			
			memset(Buffer, NULL, sizeof(Buffer));
			Length = GetMedia()->Receive(Buffer, GetMedia()->GetStatus().Receive.GetLength());
	
			break;
		}
		TaskManager_Delay(300 MSec);
	}
	//}
	
	/// تعيين باوو جديد 
	//{
	Identification = (U8*)strchr((char*)Buffer, '/');
	Boudrate = Identification[4];
	
	if((Boudrate >= 'A') && (Boudrate <= 'H'))
	{
		IEC_Delay = ((7-(Boudrate-'A'))*(100 MSec));
	}
	else if ((Boudrate >= '0') && (Boudrate <= '6'))
	{
		IEC_Delay = ((7-(Boudrate-'0'))*(100 MSec));
	}
	else
	{
		status.SetMessage(status.Messages.Error_BoudRate);
		return status;
	}
	
	GetMedia()->Reset();
	sprintf((char*)Buffer, "0%c%c\r\n", Boudrate, Mode);
	GetMedia()->Send(Buffer, strlen((char*)Buffer));
	//}

	/// انتخاب بادريت جديد
	//{
	GetMedia()->Speed(IEC_Table_BoadRate[Boudrate - '0']);
	//}

	/// دريافت پکت
	//{
	status.SetMessage(status.Messages.Error_TimeOut);
	for(U32 Index=RESET; Index<100; Index++)
	{
		if(GetMedia()->GetStatus().Receive.GetBusy())
		{
			for(U32 Index=RESET; Index<100; Index++)
			{
				Length = GetMedia()->GetStatus().Receive.GetLength();	
				TaskManager_Delay(100 MSec);
				if(Length == GetMedia()->GetStatus().Receive.GetLength())
				{
					break;
				}		
			}

			if(GetMedia()->GetStatus().Receive.GetLength() > sizeof(Buffer))
			{
				status.SetMessage(status.Messages.Error_Full);
				return status;
			}
			
			memset(Buffer, NULL, sizeof(Buffer));
			Length = GetMedia()->Receive(Buffer, GetMedia()->GetStatus().Receive.GetLength());
	
			Respond(Buffer, Length);
			
			status.SetMessage(status.Messages.Success);

			break;
		}
		TaskManager_Delay(100 MSec);
	}
	//}
	
	if(Level==IEC_LEVEL2)
	{
		/// ارسال سطح دسترسي
		//{
		GetMedia()->Reset();
		
		U8 HashLevel2[65];
		U64 Random = 0;
		U64 Pass = 0;
		SHA256_CTX ctx;
		
		char *pch1 = strchr((char*)Buffer, '(');
		if(pch1)
		{
			pch1++;
			char *pch2 = strchr((char*)Buffer, ')');
			
			if(pch2)
			{
				pch2[0] = 0;
				Random = atoll(pch1);
			}
		}
		Pass = Random + IEC::GetInstance()->Parameters.GetSecret2();	
		/// محاسبه کد سطح دسترسي 2
		//{
		sha256_init(&ctx);
		ResetBuffer();
		sprintf((char*)Buffer, "%lld", Pass);
		sha256_update(&ctx, Buffer, strlen((char*)Buffer));
		sha256_final(&ctx, Buffer);
		memset(HashLevel2, NULL, sizeof(HashLevel2));
		HEXTYPE_Hex2Ascii(Buffer, HashLevel2, 32);
		//}
		
		sprintf((char*)Buffer, "P2(%s,TESTBENCH)", HashLevel2);
		status = SendCommand(Buffer, Respond);
		TaskManager_Delay(200 MSec);		
		//}
	}
	
	return status;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		DisConnect by IEC Protocol
 * @return 		State
*/
IEC::Status IEC::struct_Client::DisConnect(void)
{
	Status status;
	status.SetMessage(status.Messages.Success);
	
	sprintf((char*)Buffer, "B0q");
	TaskManager_Delay(300 MSec);
	Media->Send(Buffer, strlen((char*)Buffer));	
	TaskManager_Delay(200 MSec);
	
	return status;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/**
 * @brief 		Send command to contor
 * @param[in]	Data         data input
 * @param[in]	SaveRequest  save request data
 * @param[in]	SaveRespond  save respond data
 * @return 		State
*/
IEC::Status IEC::struct_Client::SendCommand(U8 *Data, void (*Respond)(U8 *Data, U16 Length))
{
	Status status;
	status.SetMessage(status.Messages.Success);
	
	U32 Length;
	U8  b_bcc;

	if(!Is_Open)
	{
		status.SetMessage(status.Messages.Error_NotOpen);
		return status;
	}
	
	if(!GetMedia())
	{
		status.SetMessage(status.Messages.Error_NoMedia);
		return status;
	}
	
	//Send Command Request and Respond
	//{
	GetMedia()->Reset();

	strcpy((char*)Buffer, (char*)Data);
	Length = strlen((char*)Buffer);

	///Send command
	TaskManager_Delay(10 MSec);
	
	Buffer[Length] = GetBCC(Buffer, Length); 
	GetMedia()->Send(Buffer, ++Length);
	
	
	/// دريافت پکت
	//{
	status.SetMessage(status.Messages.Error_TimeOut);
	for(U32 WateTime=RESET; WateTime<150; WateTime++)
	{
		if(GetMedia()->GetStatus().Receive.GetBusy())
		{
			for(U32 Index=RESET; Index<100; Index++)
			{		
				Length = GetMedia()->GetStatus().Receive.GetLength();	
				TaskManager_Delay(100 MSec);
				if(Length == GetMedia()->GetStatus().Receive.GetLength())
				{
					break;
				}		
			}

			if(GetMedia()->GetStatus().Receive.GetLength() > sizeof(Buffer))
			{
				status.SetMessage(status.Messages.Error_Full);
				return status;
			}
			
			memset(Buffer, NULL, sizeof(Buffer));
			Length = GetMedia()->Receive(Buffer, GetMedia()->GetStatus().Receive.GetLength());
	
			status.SetMessage(status.Messages.Success);

			b_bcc = RESET;
			for(int Index = 1; Index<Length; Index++)
			{
				b_bcc ^= Buffer[Index];
			}
			
			Respond(Buffer, Length);
			
			if(Buffer[Length-2] == ETX_CHAR)
			{
				if(b_bcc)
				{
					status.SetMessage(status.Messages.Error_CRC);
				}			
				b_bcc = 0;

				break;
			}
			else if(Buffer[Length-2] == EOT_CHAR)
			{
				if(b_bcc)
				{
					status.SetMessage(status.Messages.Error_CRC);
					break;
				}			
				b_bcc = 0;										
				sprintf((char*)Buffer, "%c", ACK_CHAR);
				
				///Send <ACK> if get <EOT>
				GetMedia()->Reset();
				GetMedia()->Send(Buffer, 1);
				WateTime=RESET;
			}
			else if(Buffer[0] == NAK_CHAR)
			{
				status.SetMessage(status.Messages.Error_CRC);
				break;
			}
			else if(Buffer[0] == ACK_CHAR)
			{
				break;
			}
		
		}
		TaskManager_Delay(100 MSec);
	}
	//}
		
	return status;
}
//*************************************************************** tasks *******************************************************************//
/*
none
*/
//************************************************************** vectors ******************************************************************//
/*
none
*/
//****************************************************************************************************************************************//










