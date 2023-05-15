#pragma once
#include "bus.hpp";
#include <stdint.h>;

struct _register
{
	bool in;
	bool out;
	Bus* bus;
	uint8_t value;
};
typedef struct _register Register;