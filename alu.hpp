#pragma once
#include "register.hpp";
#include <stdint.h>;

#define ALU_ADD 0
#define ALU_SUB 1
#define ALU_LSH 2
#define ALU_RSH 3

struct ALU
{
	Register* a, * b;
	uint8_t mode = 0;
	uint8_t op(uint8_t a, uint8_t b) {
		switch (mode) {
		case ALU_ADD:
			return a + b;
		case ALU_SUB:
			return a - b;
		case ALU_LSH:
			return a << 1;
		case ALU_RSH:
			return a >> 1;
		}
	}
};
typedef struct ALU ALU;