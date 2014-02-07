#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "DES.h"

// Verify if the parity bits are okay
bool key_parity_verify(uint64_t key)
{
    int jj;
    int parity_bit = 0;

    for(int ii = 0; ii < 64; ii++)
    {
	jj = ii % 8; // block of 8 bits
	
	// test the parity bit
	if(jj == 7)
	{
	    if(parity_bit == 0)
	    {
		// test if ii-th bit != 0
		if( ((key << ii) & firstbit) != (uint64_t)0)
		    return false;
	    }
	    else
	    {
		// test if ii-th bit != 1
		if( ((key << ii) & firstbit) != firstbit)
		    return false;
	    }
	    parity_bit = 0; // re-init parity_bit for next byte block
	}
	else
	{
	    if( ((key << ii) & firstbit) == firstbit)
	    {
		parity_bit = parity_bit == 0 ? 1 : 0;
	    }
	}
    }

    return true;
}

// Algorithm that expands the given key
// into 16 different subkeys
void key_schedule(uint64_t* key)
{
    uint64_t key_temp;

    // test key parity bits
    if(!key_parity_verify(*key))
    {
	printf("The key you used is malformated : parity bits incorrect\n");
	exit(EXIT_FAILURE);
    }

    // initial permutation 
    for(int ii = 0; ii < 64; ii++)
    {
	//	DesInitial[ii];
    }

    // 

    //
}

// function to print a char in binary
void printbits(uint64_t v) {
    for(int ii = 0; ii < 64; ii++)
    {
	if( ((v << ii) & firstbit) == (uint64_t)0)
	    printf("0");
	else
	    printf("1");
    }
}

// test only
int main()
{
    uint64_t key_test = 0b0110000010110110011001101111101000111111111010001011000110001110;

    printbits(key_test);

    printf("\n");

    if(key_parity_verify(key_test) == true)
    {
	printf("yes");
    }
    else
    {
	printf("no");
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}
