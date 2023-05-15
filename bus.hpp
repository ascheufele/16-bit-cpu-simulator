#pragma once
#include <stdint.h>;

struct bus
{
	union busValue
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
		};
		uint8_t value;
	};
};
typedef struct bus Bus;