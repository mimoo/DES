#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// genkey function
static void genkey(char* key)
{
    srand(time(NULL));
    int parity_bit = 0;

    // generate block by block
    for(int ii = 0; ii < 8; ii++) 
    {
	// in each block 7 bits to generate
	for(int bit = 0; bit < 7; bit++)
	{
	    if(rand() % 2 == 1)
	    {
		key[ii] = key[ii] ^ (0x80 >> bit);
		parity_bit = parity_bit == 0 ? 1 : 0;
	    }
	}
	// 8th bit is parity bit
	if(parity_bit == 1)
	{
	    key[ii] = key[ii] ^ (0x01);
	    parity_bit = 0;
	}
    }

    // test if the expansion function works

    // no ? recursive call
}

// function to print a char in binary
void printbits(unsigned char v) {
   for(int ii = 7; ii >= 0; ii--) putchar('0' + ((v >> ii) & 1));
}

int main()
{
    char key[8];

    genkey(key);

    for(int ii = 0; ii < 8; ii++)
    {
	printbits(key[ii]);
    }

    return EXIT_SUCCESS;
}
