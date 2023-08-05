#ifndef __TAGBENCH_HPP
#define __TAGBENCH_HPP
//----------------------------------------------------------
#include "defines.h"
#include "AdvancedTypes.hpp"
//----------------------------------------------------------
class class_TagBench
{
	public:	
		struct {
			class_String<1024> Message;
			class_String<64> Command;
			class_String<512> Data;
		} Parmeters;
		void Init();
		bool Detach();
		bool Attach();
};
#endif
