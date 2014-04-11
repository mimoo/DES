#include <time.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "DES.h"

// Function to print uint64_t in binary
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

// Generate a 64bit random DES key
// Add parity bits (last bit of each byte)
// Check for weak keys using key_schedule of DES.c
static void genkey(uint64_t* key)
{
    srand(time(NULL));

    // Generate key
    int parity_bit = 0;

    for(int ii = 0; ii < 64; ii++) 
    {
        // Parity bit
        if(ii % 8 == 7)
        {
            if(parity_bit == 1)
                *key += (FIRSTBIT >> ii);
            parity_bit = 0; // Re-init parity_bit for next byte block
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

    // Test the key schedule
    uint64_t a_key[16];
    a_key[0] = *key;
    uint64_t next_key;

    for(int ii = 0; ii < 16; ii++)
    {
        key_schedule(&a_key[ii], &next_key, ii);
        if(ii != 15)
            a_key[ii + 1] = next_key;
    }

    // Test for weak keys
    bool weak = false;

    for(int ii = 0; ii < 16; ii++)
    {
        for(int jj = 0; jj < 16; jj++)
        {
            if(jj != ii)
            {
                if(a_key[ii] == a_key[jj])
                    weak = true;
            }
        }
    }

    // If the generated key is weak, do the algorithm one more time
    if(weak)
    {
        genkey(key);
    }
}

int main()
{
    uint64_t key = 0;

    genkey(&key);
    
    printf("Here's one key for you sir: \n");
    printbits(key);
    printf("\n");

    return EXIT_SUCCESS;
}
