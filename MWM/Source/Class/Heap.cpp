//*********************************************************** Explanation ***************************************************************//
/*
Last Update : 1396/12/15
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
//************************************************************ includes ******************************************************************//
#include "heap.hpp"
//************************************************************ defineds ******************************************************************//
/*
none
*/
//************************************************************ variables *****************************************************************//
/*
none
*/
//************************************************************* opjects ******************************************************************//
/*
none
*/
//************************************************************ functions *****************************************************************//
void __init_HEAP(void)
{
	HEAP::GetInstance()->Init();
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void HEAP::Init(void)
{

}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
bool HEAP::GetBlock(void* &Pointer, U32 Size, U8* Name)
{
	U8 Locate;
	U32 Volume;

	Volume = RESET;
	for(Locate=RESET; Locate<HEAP_SLICE_SIZE; Locate++)
	{
		if(Slice[Locate].GetUsed())
		{
			Volume += Slice[Locate].GetSize();
		}
		else
		{
			break;
		}
	}

	
	if(Locate < HEAP_SLICE_SIZE)
	{
		if((Volume+Size)<=sizeof(Space))
		{
			Slice[Locate].SetUsed(true);
			Slice[Locate].SetName(Name);
			Slice[Locate].SetAddress((void*)(Space + Volume));
			Slice[Locate].SetSize(Size);
			Slice[Locate].SetPointer(&Pointer);
			
			Pointer = Slice[Locate].GetAddress();
			return true;
		}
	}
	
	HardFault_Handler();
	return false;
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void HEAP::ClearBlock(void* &Pointer)
{
	U8 Locate;
	for(Locate=RESET; Locate<HEAP_SLICE_SIZE; Locate++)
	{
		if(Slice[Locate].GetUsed())
		{
			if(Slice[Locate].GetPointer() == &Pointer)
			{
				Slice[Locate].ResetUsed();
				Slice[Locate].ResetName();
				Slice[Locate].ResetAddress();
				Slice[Locate].ResetPointer();
				Slice[Locate].ResetSize();						

				Pointer = NULL;
				
				DefrageSpace();
				break;
			}
		}
	}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void HEAP::DefrageSpace(void)
{
	U8 Locate;
	U32 Volume;
	bool Find;

	Defragement:
	Find = false;
	Volume = RESET;
	for(Locate=RESET; Locate<HEAP_SLICE_SIZE; Locate++)
	{
		if(Slice[Locate].GetUsed())
		{
			if(Find)
			{
				for(U32 Index=RESET; Index<Slice[Locate].GetSize();Index++)
				{
					Space[Volume+Index] = ((U8*)Slice[Locate].GetAddress())[Index];
				}
				
				Slice[Locate-1].SetUsed(true);
				Slice[Locate-1].SetName(Slice[Locate].GetName());
				Slice[Locate-1].SetAddress((void*)(Space + Volume));
				Slice[Locate-1].SetSize(Slice[Locate].GetSize());
				Slice[Locate-1].SetPointer(Slice[Locate].GetPointer());
				
				*Slice[Locate-1].Pointer = Slice[Locate-1].GetAddress();
				
				Slice[Locate].ResetUsed();
				Slice[Locate].ResetName();
				Slice[Locate].ResetAddress();
				Slice[Locate].ResetSize();

				goto Defragement;
			}
			else
			{
				Volume += Slice[Locate].GetSize();
			}
		}
		else
		{
			Find = true;
		}
	}
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void* operator new(U32 Size) 
{
	
	void* Address = malloc(Size);
	if(!Address)
	{
		HardFault_Handler();
	}
	
	return Address;
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










