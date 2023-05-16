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
	CPU(std::string pathToBinary) : controlLogic(ControlLogic(&bus, &a, &b, &output, &mar, &ir, &memory, &clock, &alu)) {
		// set pc to 0;
		programCounter.value = 0;
		clock.tick = 0;
		// set MAR to 0;
		mar.value = 0;
		ir.value = 0;
		a.value = 0;
		b.value = 0;
		// load the program
		std::ifstream machineCode(pathToBinary);
		if (!machineCode) {
			std::cerr << "Failed to open program source file... exiting." << std::endl;
			exit(1);
		}
		std::string line = "";
		int instructionNumber = 0;
		while (std::getline(machineCode, line)) {
			memory.instructions[instructionNumber].value = (uint16_t)0;
			for (int a = 0; a < 16; ++a) {
				memory.instructions[instructionNumber].value |= (line[a] == '0' ? 0 : 0b1000000000000000 >> a); // this is readable, right?
			}
			std::cout << "instruction " << instructionNumber << ": " << memory.instructions[instructionNumber].value << std::endl;
			instructionNumber++;
		}
	};
	void step() {
		if (clock.pause) { // halt
			exit(0);
		}
		controlLogic.step();
		prettyPrint();
	};
	void prettyPrint() {
		std::cout << std::endl << "PC: " << clock.tick << std::endl;
		std::cout << "IR: " << (unsigned int)ir.value << std::endl;
		std::cout << "BUS: " << (unsigned int)bus.value << std::endl;
		std::cout << "A: " << (unsigned int)a.value << std::endl;
		std::cout << "B: " << (unsigned int)b.value << std::endl;
		std::cout << std::endl << std::endl;
	}
};