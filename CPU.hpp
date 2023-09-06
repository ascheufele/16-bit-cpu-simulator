#pragma once
#include "alu.hpp";
#include "bus.hpp";
#include "clock.hpp";
#include "control_logic.hpp";
#include "instruction.hpp";
#include "memory.hpp";
#include "program_counter.hpp";
#include "register.hpp";

class CPU : public sf::Drawable
{
private:
	// cpu components
	Bus bus;
	Clock clock;
	Program_Counter programCounter;
	ControlLogic controlLogic;
	Register a, b, c, d, e, f;
	Register output;
	Register mar;
	Register ir;
	Memory memory;
	ALU alu;
	// gui related member variables
	sf::Font font;
	sf::Text* a_text, * b_text, * c_text, * d_text, * e_text, * f_text, * ir_text, * alu_text, * pc_text;
public:
	CPU(std::string pathToBinary) : controlLogic(ControlLogic(&bus, &a, &b, &c, &d, &e, &f, &output, &mar, &ir, &memory, &clock, &alu)){
		// set pc to 0;
		programCounter.value = 0;
		clock.tick = 0;
		// set MAR to 0;
		mar.value = 0;
		ir.value = 0;
		a.value = 0;
		b.value = 0;
		c.value = 0;
		d.value = 0;
		e.value = 0;
		f.value = 0;
		// load font for drawing
		if (!font.loadFromFile("Segment7Standard.otf")) {
			std::cout << "Error loading font... exiting" << std::endl;
			exit(1);
		}
		// gui member setup
		// a register text 
		a_text = new sf::Text("", this->font);
		a_text->setFillColor(sf::Color::Red);
		a_text->setPosition(250, 0);
		// b register text 
		b_text = new sf::Text("", this->font);
		b_text->setFillColor(sf::Color::Red);
		b_text->setPosition(250, 50);
		// c register text 
		c_text = new sf::Text("", this->font);
		c_text->setFillColor(sf::Color::Red);
		c_text->setPosition(250, 100);
		// d register text 
		d_text = new sf::Text("", this->font);
		d_text->setFillColor(sf::Color::Red);
		d_text->setPosition(250, 150);
		// e register text 
		e_text = new sf::Text("", this->font);
		e_text->setFillColor(sf::Color::Red);
		e_text->setPosition(250, 200);
		// f register text 
		f_text = new sf::Text("", this->font);
		f_text->setFillColor(sf::Color::Red);
		f_text->setPosition(250, 250);
		// instruction register text 
		ir_text = new sf::Text("", this->font);
		ir_text->setFillColor(sf::Color::Red);
		ir_text->setPosition(250, 300);
		// alu text 
		alu_text = new sf::Text("", this->font);
		alu_text->setFillColor(sf::Color::Red);
		alu_text->setPosition(250, 350);
		// pc text 
		pc_text = new sf::Text("", this->font);
		pc_text->setFillColor(sf::Color::Red);
		pc_text->setPosition(250, 400);
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
	~CPU() {
		delete a_text;
		delete b_text;
		delete c_text;
		delete d_text;
		delete e_text;
		delete f_text;
		delete ir_text;
		delete alu_text;
		delete pc_text;

	}
	void step() {
		if (clock.pause) { // halt
			char c;
			std::cin >> c;
		}
		controlLogic.step();
		prettyPrint();
	};
	void prettyPrint() {
		std::cout << std::endl << "PC: " << clock.tick << std::endl;
		std::cout << "MAR: " << static_cast<unsigned int>(ir.value) << std::endl;
		std::cout << "BUS: " << static_cast<unsigned int>(bus.value) << std::endl;
		std::cout << "A: " << static_cast<unsigned int>(a.value) << std::endl;
		std::cout << "B: " << static_cast<unsigned int>(b.value) << std::endl;
		std::cout << "OUTPUT: " << static_cast<unsigned int>(output.value) << std::endl;
		std::cout << std::endl << std::endl;
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		a_text->setString("A : " + std::to_string(a.value));
		b_text->setString("B : " + std::to_string(b.value));
		c_text->setString("C : " + std::to_string(c.value));
		d_text->setString("D : " + std::to_string(d.value));
		e_text->setString("E : " + std::to_string(e.value));
		f_text->setString("F : " + std::to_string(f.value));
		ir_text->setString("IR : " + std::to_string(ir.value));
		//alu_text->setString("ALU: " + std::to_string(alu.op(alu.a, alu.b))); // need to refactor alu to a class so this works
		pc_text->setString("PC: " + std::to_string(clock.tick));
		target.draw(*a_text);
		target.draw(*b_text);
		target.draw(*c_text);
		target.draw(*d_text);
		target.draw(*e_text);
		target.draw(*f_text);
		target.draw(*ir_text);
		target.draw(*pc_text);
	}
};