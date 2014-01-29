#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "genkey.h"

// genkey function
static void genkey(char* key)
{
    srand(time(NULL));
  
    for(int ii = 0; ii < 8; ii++)
    {
	key[ii] = rand() % 255;
    }

    // parity bits (it's not mandatory)

    // test if the expansion function works

    // no ? recursive call
}

// function to print a char in binary
void printbits(unsigned char v) {
   for(ii = 7; ii >= 0; ii--) putchar('0' + ((v >> ii) & 1));
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
