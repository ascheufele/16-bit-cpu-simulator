#pragma once
#include "register.hpp";
#include <stdint.h>;

struct ALU
{
	Register* a, * b;
	uint8_t add(uint8_t a, uint8_t b) { return a + b; }
	uint8_t sub(uint8_t a, uint8_t b) { return a - b; }
	//uint8_t lsh(uint8_t a, uint8_t b) { return a << b; }
	//uint8_t rsh(uint8_t a, uint8_t b) { return a >> b; }
};
typedef struct ALU ALU;