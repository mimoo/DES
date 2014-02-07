#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "DES.h"

// generate a 64bit random DES key
// adds parity bits (last bit of each byte)
// check for weak keys using key_schedule of DES.c
static void genkey(uint64_t* key)
{
    srand(time(NULL));
 
    int parity_bit = 0;

    for(int ii = 0; ii < 64; ii++) 
    {
	// parity bit
	if(ii % 8 == 7)
	{
	    if(parity_bit == 1)
	    {
		*key += (FIRSTBIT >> ii);
	    }
	    parity_bit = 0; // re-init parity_bit for next byte block
	}
	else
	{
	    if(rand() % 2 == 1)
	    {
		*key += (FIRSTBIT >> ii);
		parity_bit = parity_bit == 0 ? 1 : 0;
	    
	    }
	}
    }

    // test if the expansion function works

    // no ? recursive call
}

// function to print a char in binary
void printbits(uint64_t v) {
    for(int ii = 0; ii < 64; ii++)
    {
	if( ((v << ii) & FIRSTBIT) == (uint64_t)0)
	    printf("0");
	else
	    printf("1");
    }
}

int main()
{
    uint64_t key = 0;

    genkey(&key);
    
    printbits(key);

    return EXIT_SUCCESS;
}
