#include <cstdlib>
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
#include "CPU.hpp";

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
	std::system("python ./mTranslator.py"); // update microcode
	std::system("python ./assembler.py myProgram.zander"); // update program binary
	sf::RenderWindow win(sf::VideoMode(1280, 720), "CPU Simulator");
	//Clock clock;
	//Register A, B;
	//Program_Counter programCounter;

	// set up
	//load_program();
	//load_microcode();
	CPU cpu("./myProgram.zander.binary");
	
	// sfml testing
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2<float>(200.0, 200.0));
	rect.setPosition(sf::Vector2<float>(100, 100));
	win.draw(rect);
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

		//win.clear();
		cpu.step();
		// draw
		win.display();

	}

	return 0;
}