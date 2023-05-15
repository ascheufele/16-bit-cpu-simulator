#pragma once
#include <stdint.h>;

struct program_counter
{
	// wont limit to 8 bits so we can write longer programs
	uint32_t value = 0;
};
typedef struct program_counter Program_Counter;