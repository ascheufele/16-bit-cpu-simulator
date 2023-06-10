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

int main(void)
{
	std::system("python ./mTranslator.py"); // update microcode
	std::system("python ./assembler.py myProgram.zander"); // update program binary
	sf::RenderWindow win(sf::VideoMode(1280, 720), "CPU Simulator");

	// set up
	CPU cpu("./myProgram.zander.binary");
	
	// sfml testing
	sf::Font font;
	const std::string filename("Segment7Standard.otf");
	std::cout << filename << std::endl;
	
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2<float>(200.0, 200.0));
	rect.setPosition(sf::Vector2<float>(100, 100));
	//win.draw(rect);
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

		cpu.step();
		win.clear(sf::Color::Black);
		std::cout << "clear" << std::endl;
		win.draw(cpu);
		win.display();

	}

	return 0;
}