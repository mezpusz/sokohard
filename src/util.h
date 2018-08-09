#pragma once

/*
 *      Taken from the K&R C programming language book. Page 46.
 *      returns a pseudo-random integer of 0..32767. Note that
 *      this is compatible with the System V function rand(), not
 *      with the bsd function rand() that returns 0..(2**31)-1.
 */
unsigned int Random();

/*
 * Helper function for random in interval.
 */
inline unsigned int Random(unsigned int first, unsigned int last)
{
    return Random() % (last-first) + first;
}

/*
 *      companion routine to rand(). Initializes the seed.
 */
void seedRandom(unsigned int seed);
