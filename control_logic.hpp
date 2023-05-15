#pragma once
#include "clock.hpp";
#include <vector>;
#include "memory.hpp";
#include "register.hpp";
#include "bus.hpp";
#include <stdint.h>;

#define MICROCODE_WIDTH 10

// defs = ['pc incr', 'ram in', 'ram out', 'a in', 'a out', 'ir in', 'reset', 'b in', 'alu out', 'halt']
// if this changes it also must be updated in mTranslator.py
enum Controls {PC_INCR, RAM_IN, RAM_OUT, A_IN, A_OUT, IR_IN, RESET, B_IN, ALU_OUT, HALT};

class ControlLogic
{
public:
	Clock logicClock;
	// microcode
	std::vector<std::vector<int>> microcode;
	// connections to all other components
	Clock* mainClock;
	Memory* memory;
	Register* a, * b, * output, * mar, * ir;
	Bus* bus;
	ControlLogic(Bus* bus, Register* a, Register* b, Register* output,
		Register* mar, Register* ir, Memory* memory, Clock* mainClock) :
		a(a),
		b(b),
		output(output),
		mar(mar),
		ir(ir),
		bus(bus), 
		memory(memory),
		mainClock(mainClock)
	{
		logicClock.tick = 0;
		// load microcode
		std::ifstream microcodeFile("./microcode.txt");
		if (!microcodeFile) {
			std::cout << "Failed to open microcode file... exiting." << std::endl;
			exit(1);
		}
		std::string line = "";
		while (std::getline(microcodeFile, line)) {
			std::vector<int> instruction;
			for (int a = 0; a < MICROCODE_WIDTH; ++a) {
				std::cout << line[a] << std::endl;
				instruction.push_back(line[a] == '0' ? 0 : 1);
			}
			microcode.push_back(instruction);
		}
	};
	void step() {
		// evaluate the microcode instruction at microcode[PC + logicClock]

		// if (reset)
		{
			logicClock.tick = 0;
		}
		// else
		{
			logicClock.tick += 1;
		}
	};
private:
};