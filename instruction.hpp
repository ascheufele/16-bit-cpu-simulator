#pragma once
#include <stdint.h>;
struct instruction
{
	union contents
	{
		struct bits
		{
			unsigned int bit_0 : 1;
			unsigned int bit_1 : 1;
			unsigned int bit_2 : 1;
			unsigned int bit_3 : 1;
			unsigned int bit_4 : 1;
			unsigned int bit_5 : 1;
			unsigned int bit_6 : 1;
			unsigned int bit_7 : 1;
			unsigned int bit_8 : 1;
			unsigned int bit_9 : 1;
			unsigned int bit_10 : 1;
			unsigned int bit_11 : 1;
			unsigned int bit_12 : 1;
			unsigned int bit_13 : 1;
			unsigned int bit_14 : 1;
			unsigned int bit_15 : 1;
		};
		uint8_t value;
	};
};
typedef struct instruction Instruction;