#pragma once

struct clock
{
	unsigned int tick = 0;
	bool pause = false; // set to true when we want to manually step the program
};
typedef struct clock Clock;