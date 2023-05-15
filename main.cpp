#include <iostream>
#include <fstream>
#include <stdint.h>
#include <vector>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

// notes
// probably want to take this approach when optimizing:
// everything inherits from component
// we have a vector of components that we index based on microcode bit / column name
// when we do this we can set in / out since we are in a polymorphic state

// bus contents |= source

#define MICROCODE_WIDTH 10

struct clock
{
	unsigned int tick = 0;
	bool pause = false; // set to true when we want to manually step the program
};
typedef struct clock Clock;

struct program_counter
{
	// wont limit to 8 bits so we can write longer programs
	uint32_t value = 0;
};
typedef struct program_counter Program_Counter;

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

struct _register
{
	bool in;
	bool out;
	Bus* bus;
	uint8_t value;
};
typedef struct _register Register;

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

struct memory
{

	bool writeEnable; // When true write value from BUS to location in from MAR
	Program_Counter* pc;
	// these arrays will be indexed with the Program Counter/MAR
	Instruction instructions[32];
};
typedef struct memory Memory;


struct ALU
{
	Register* a, * b;
	uint8_t add(uint8_t a, uint8_t b) { return a + b; }
	uint8_t sub(uint8_t a, uint8_t b) { return a - b; }
	//uint8_t lsh(uint8_t a, uint8_t b) { return a << b; }
	//uint8_t rsh(uint8_t a, uint8_t b) { return a >> b; }
};
typedef struct ALU ALU;

struct control_logic
{
	Clock logicClock;
	// microcode
	std::vector<int[MICROCODE_WIDTH]> microcode;
	// connections to all other components
	Clock* mainClock;
	Memory* memory;
	Register* a, *b, *output, *mar, *mbr;
	Bus* bus;
};
typedef struct control_logic Control_Logic;

void load_microcode()
{
	std::ifstream mc("./microcode.txt");
	char c;
	while (mc)
	{	
		for (int i = 0; i < MICROCODE_WIDTH; ++i)
		{
			mc >> c;
			std::cout << c;
		}
		std::cout << std::endl;
	}
}

void load_program()
{
	std::cout << "load program not yet implemented" << std::endl;
}

int main(void)
{
	sf::RenderWindow win(sf::VideoMode(800, 600), "CPU Simulator");
	Clock clock;
	Register A, B;
	Program_Counter programCounter;

	// set up
	load_program();
	load_microcode();
	
	while (win.isOpen())
	{
		sf::Event e;
		while (win.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				win.close();
			}
		}

		win.clear();
		// step
		// draw
		win.display();

	}

	return 0;
}