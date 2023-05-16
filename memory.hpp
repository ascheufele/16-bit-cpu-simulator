#pragma once
#include "program_counter.hpp";
#include "instruction.hpp";

struct memory
{
	// these arrays will be indexed with the Program Counter/MAR
	Instruction instructions[32];
};
typedef struct memory Memory;