#ifndef __TESTBENCH_HPP
#define __TESTBENCH_HPP
//----------------------------------------------------------
#include "defines.h"
#include "tagbench.hpp"
//----------------------------------------------------------
class Test {
    public: 
			uint8_t *_Command;
			void (*_Handle)(uint8_t *Data);
			Test(uint8_t *Command, void (*Handle)(uint8_t *Data)) : _Command(Command) , _Handle(Handle) {}			
};
class class_TestBench : class_TagBench
{
	private:
		uint8_t Tests_Count;
		Test* Tests[64];
	public:
		uint8_t* (*GetID)();
		bool Add(uint8_t *Command, void (*Handle)(uint8_t *Data));
		void Init(uint8_t* (*_GetID)()) { GetID = _GetID;};
		bool Pars(uint8_t *Message, uint32_t *Length);
		bool Execute();
};
extern class_TestBench TestBench;
//----------------------------------------------------------
#endif
