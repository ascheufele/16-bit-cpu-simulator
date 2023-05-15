#include <iostream>
#include <fstream>
#include <stdint.h>
#include <vector>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "clock.hpp";
#include "program_counter.hpp";
#include "bus.hpp";
#include "register.hpp";
#include "instruction.hpp";
#include "memory.hpp";
#include "alu.hpp";
#include "control_logic.hpp";

// notes
// probably want to take this approach when optimizing:
// everything inherits from component
// we have a vector of components that we index based on microcode bit / column name
// when we do this we can set in / out since we are in a polymorphic state

// bus contents |= source

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