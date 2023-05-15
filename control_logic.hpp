#pragma once
#include "clock.hpp";
#include <vector>;
#include "memory.hpp";
#include "register.hpp";
#include "bus.hpp";
#include <stdint.h>;

#define MICROCODE_WIDTH 10

struct control_logic
{
	Clock logicClock;
	// microcode
	std::vector<int[MICROCODE_WIDTH]> microcode;
	// connections to all other components
	Clock* mainClock;
	Memory* memory;
	Register* a, * b, * output, * mar, * mbr;
	Bus* bus;
};
typedef struct control_logic Control_Logic;