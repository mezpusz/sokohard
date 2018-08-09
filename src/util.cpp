#include "util.h"

unsigned long int rand_next = 1;

unsigned int Random()
{
	rand_next = rand_next * 1103515245 + 12345;
	return ((unsigned int)(rand_next / 65536) % 32768);
}

void seedRandom(unsigned int seed)
{
	rand_next = seed;
}