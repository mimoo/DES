#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "DES.h"

// useful function to print a char in binary
void printbits(uint64_t v)
{
    for(int ii = 0; ii < 64; ii++)
    {
	if( ((v << ii) & FIRSTBIT) == (uint64_t)0)
	    printf("0");
	else
	    printf("1");
    }
}

// Verify if the parity bits are okay
bool key_parity_verify(uint64_t key)
{
    int parity_bit = 0;

    for(int ii = 0; ii < 64; ii++)
    {
	// test the parity bit
	if(ii % 8 == 7)
	{
	    if(parity_bit == 0)
	    {
		// test if ii-th bit != 0
		if( ((key << ii) & FIRSTBIT) != (uint64_t)0)
		{
		    printf("parity error at bit #%i\n", ii + 1);
		    return false;
		}
	    }
	    else
	    {
		// test if ii-th bit != 1
		if( ((key << ii) & FIRSTBIT) != FIRSTBIT)
		{
		    printf("parity error at bit #%i\n", ii + 1);
		    return false;
		}
	    }
	    parity_bit = 0; // re-init parity_bit for next byte block
	}
	else
	{
	    if( ((key << ii) & FIRSTBIT) == FIRSTBIT)
	    {
		parity_bit = parity_bit == 0 ? 1 : 0;
	    }
	}
    }

    return true;
}

//
//      KEY SCHEDULE
//
// input :
//   * next_key : uint64_t next_key 0;
//   * round : [[1, 16]]
// changes :
//   * [key] is good to be used in the XOR in the rounds
//   * [next_key] is the combined leftkey+rightkey to be used
//     in the key_schedule for next round
//
void key_schedule(uint64_t* key, uint64_t* next_key, int round)
{
    uint64_t key_left = 0;
    uint64_t key_right = 0;

    uint64_t key_left_temp = 0;
    uint64_t key_right_temp = 0;

    // First Round => PC-1 : Permuted Choice 1
    if(round == 1)
    {
	for(int ii = 0; ii < 56; ii++)
	{
	    if(ii < 28)
		key_left += (((*key << (PC1[ii] - 1)) & FIRSTBIT) >> ii);
	    else
		key_right += (((*key << (PC1[ii] - 1)) & FIRSTBIT) >> ii);
	}
    }
    // Other rounds? => Seperate key into two key halves.
    else
    {
	for(int ii = 0; ii < 56; ii++)
	{
	    if(ii < 28)
		key_left += (((*key << ii) & FIRSTBIT) >> ii);
	    else
		key_right += (((*key << ii) & FIRSTBIT) >> ii);
	}
    }

    // Rotations
    key_left_temp = Rotations[round] == 1 ? FIRSTBIT : 0xC000000000000000;
    key_right_temp = Rotations[round] == 1 ? FIRSTBIT : 0xC000000000000000;

    key_left_temp = (key_left & key_left_temp) >> (28 - Rotations[round]);
    key_right_temp = (key_right & key_right_temp) >> (28 - Rotations[round]);

    key_left_temp += (key_left << Rotations[round]);
    key_right_temp += (key_right << Rotations[round]);

    // Combine the 2 keys into 1 (also used for following rounds)
    for(int ii = 0; ii < 56; ii++)
    {
	if(ii < 28)
	    *next_key += (((key_left_temp << ii) & FIRSTBIT) >> ii);
	else
	    *next_key += (((key_right_temp << (ii % 28)) & FIRSTBIT) >> ii);
    }

    // PC-2 : Permuted Choice 2
    *key = 0;

    for(int ii = 0; ii < 56; ii++)
    {
	*key += ( (*next_key << (PC2[ii] - 1)) & FIRSTBIT) >> ii;
    }

    // All Good!
}
