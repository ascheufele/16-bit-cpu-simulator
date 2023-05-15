#pragma once
#include "program_counter.hpp";
#include "instruction.hpp";

struct memory
{

	bool writeEnable; // When true write value from BUS to location in from MAR
	Program_Counter* pc;
	// these arrays will be indexed with the Program Counter/MAR
	Instruction instructions[32];
};
typedef struct memory Memory;