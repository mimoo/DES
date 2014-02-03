#include <stdlib.h>
#include <stdio.h>

#include "DES.h"

// Verify if the parity bits are okay
void key_parity_verify(char* key)
{
    for(int bit = 0; bit < 7; bit++)
    {
	if(rand() % 2 == 1)
	{
	    key[ii] = key[ii] ^ (0x80 >> bit);
	    parity_bit = parity_bit == 0 ? 1 : 0;
	}
    }

}
// Algorithm that expands the given key
// into 16 different subkeys
void key_schedule(char* key)
{
    char key_temp[8];
    int jj, kk;

    for(int ii = 0; ii < 64; ii++)
    {
	jj = ii % 8;
	kk = ii / 8; // jj is an integer => kk will be one as well

	printf("%i/n", kk); // test, erase after conf
//	key_temp[kk]
//	DesInitial[ii];
    }
}

// function to print a char in binary
void printbits(unsigned char v) {
   for(int ii = 7; ii >= 0; ii--) putchar('0' + ((v >> ii) & 1));
}

// test only
int main()
{
   
   
    return EXIT_SUCCESS;
}
