#pragma once
#include "alu.hpp";
#include "bus.hpp";
#include "clock.hpp";
#include "control_logic.hpp";
#include "instruction.hpp";
#include "memory.hpp";
#include "program_counter.hpp";
#include "register.hpp";

class CPU
{
public:
	Bus bus;
	Clock clock;
	Program_Counter programCounter;
	ControlLogic controlLogic;
	Register a;
	Register b;
	Register output;
	Register mar;
	Register ir;
	Memory memory;
	ALU alu;
	CPU() : controlLogic(ControlLogic(&bus, &a, &b, &output, &mar, &ir, &memory, &clock, &alu)) {
		// set pc to 0;
		programCounter.value = 0;
		// set MAR to 0;
		mar.value = 0;
		ir.value = 0;
		// connect the components to the bus
	};
	void step() {
		if (clock.pause) {
			return;
		}
		controlLogic.step();
	};
};