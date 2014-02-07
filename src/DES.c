#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "DES.h"

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
		if( ((key << ii) & firstbit) != (uint64_t)0)
		{
		    printf("parity error at bit #%i\n", ii + 1);
		    return false;
		}
	    }
	    else
	    {
		// test if ii-th bit != 1
		if( ((key << ii) & firstbit) != firstbit)
		{
		    printf("parity error at bit #%i\n", ii + 1);
		    return false;
		}
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
<<<<<<< HEAD
void printbits(unsigned char v)
{
   for(int ii = 7; ii >= 0; ii--) putchar('0' + ((v >> ii) & 1));
=======
void printbits(uint64_t v) {
    for(int ii = 0; ii < 64; ii++)
    {
	if( ((v << ii) & firstbit) == (uint64_t)0)
	    printf("0");
	else
	    printf("1");
    }
>>>>>>> a43d3fbed764fda410523fd9fd127bb61043d81d
}

// test only
int main()
{
    uint64_t key_test = 0b1110100111001111011111100111000101010110011011000010100001100011;

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
