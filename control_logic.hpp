#pragma once
#include "clock.hpp";
#include <vector>;
#include "memory.hpp";
#include "register.hpp";
#include "bus.hpp";
#include <stdint.h>;

#define MICROCODE_WIDTH 11

// defs = ['pc incr', 'ram in', 'ram out', 'a in', 'a out', 'ir in', 'reset', 'b in', 'alu out', 'halt']
// if this changes it also must be updated in mTranslator.py
enum Controls {PC_INCR, RAM_IN, RAM_OUT, A_IN, A_OUT, IR_IN, RESET, B_IN, ALU_OUT, HALT, PC_IN};

class ControlLogic
{
public:
	Clock logicClock;
	// microcode
	std::vector<std::vector<int>> microcode;
	// connections to all other components
	Clock* PC;
	Memory* memory;
	Register* a, * b, * output, * mar, * ir;
	Bus* bus;
	ALU* alu;
	ControlLogic(Bus* bus, Register* a, Register* b, Register* output,
		Register* mar, Register* ir, Memory* memory, Clock* PC, ALU* alu) :
		a(a),
		b(b),
		output(output),
		mar(mar),
		ir(ir),
		bus(bus), 
		memory(memory),
		PC(PC),
		alu(alu)
	{
		logicClock.tick = 0;
		// load microcode
		std::ifstream microcodeFile("./microcode.txt");
		if (!microcodeFile) {
			std::cerr << "Failed to open microcode file... exiting." << std::endl;
			exit(1);
		}
		std::string line = "";
		while (std::getline(microcodeFile, line)) {
			std::vector<int> instruction;
			for (int a = 0; a < MICROCODE_WIDTH; ++a) {
				instruction.push_back(line[a] == '0' ? 0 : 1);
			}
			microcode.push_back(instruction);
		}
	};
	void step() {
		// evaluate the microcode instruction at microcode[IR + logicClock]
		// and carry out the modifications to the system components
		std::vector<int>& i = microcode[ir->value + logicClock.tick];
		for (auto a = i.begin(); a < i.end(); a++)
		{
			std::cout << *a;
		}
		std::cout << std::endl;
		std::cout << logicClock.tick << std::endl;

		if (i[Controls::PC_INCR]) {
			PC->tick++;
			std::cout << "PC INCR\t";
		}

		if (i[Controls::RAM_OUT]) {
			bus->value = memory->instructions[PC->tick].value;
			std::cout << "RAM OUT\t";
		}
		if (i[Controls::A_OUT]) {
			bus->value = a->value; // 8 lsb to the bus
			// 8 msb would be a->value << 8
			std::cout << "A OUT\t";
		}
		if (i[Controls::ALU_OUT]) {
			bus->value = alu->add(a->value, b->value); // for now the ALU is just an adder
			std::cout << "ALU OUT\t";
		}
		if (i[Controls::A_IN]) {
			a->value = (bus->value & 0xFF); // 8 lsb from bus
			std::cout << "A IN\t";
		}
		if (i[Controls::IR_IN]) {
			ir->value = (bus->value >> 8);
			std::cout << "IR IN\t";
		}
		if (i[Controls::B_IN]) {
			b->value = (bus->value & 0xFF); // 8 lsb from bus
			std::cout << "B IN\t";
		}
		if (i[Controls::PC_IN]) {
			PC->tick = (bus->value & 0xFF); // get address to jump to
		}
		if (i[Controls::HALT]) {
			PC->pause = true;
			std::cout << "HALT\t";
		}
		if (i[Controls::RESET]) {
			logicClock.tick = 0;
			std::cout << "RESET\t";
			// PC->tick = 0;
		}
		if (0 == i[Controls::RESET]) {
			logicClock.tick += 1;
		}
		// always have alu result in output register
		output->value = alu->add(a->value, b->value);
	};
private:
};