#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "DES.h"

//////////////////////////////////////////////////////
//                 GLOBAL VARIABLES                //
////////////////////////////////////////////////////

const int PC1[56] = {
 
   57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4
 
};
 
const int Rotations[16] = {
 
   1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
 
};
 
const int PC2[48] = {
 
   14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32
 
};
 
const int DesInitial[64] = {
 
    58, 50, 42, 34, 26, 18, 10,  2,
    60, 52, 44, 36, 28, 20, 12,  4,
    62, 54, 46, 38, 30, 22, 14,  6,
    64, 56, 48, 40, 32, 24, 16,  8,
    57, 49, 41, 33, 25, 17,  9,  1,
    59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5,
    63, 55, 47, 39, 31, 23, 15,  7
 
};
 
const int DesExpansion[48] = {
    32,  1,  2,  3,  4,  5,  4,  5,
     6,  7,  8,  9,  8,  9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32,  1
  }; 
 
const int DesSbox[8][4][16] = {
 
   {
   {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
   { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
   { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
   {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
   },
 
   {
   {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
   { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
   { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
   {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
   },
 
   {
   {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
   {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
   {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
   { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
   },
 
   {
   { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
   {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
   {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
   { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
   },
 
   {
   { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
   {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
   { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
   {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
   },
 
   {
   {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
   {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
   { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
   { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
   },
 
   {
   { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
   {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
   { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
   { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
   },
 
   {
   {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
   { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
   { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
   { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
   },
 
};
 
const int DesPbox[32] = {
 
    16,  7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9,
    19, 13, 30,  6, 22, 11,  4, 25
 
};
 
const int DesFinal[64] = {
 
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
 
};

//////////////////////////////////////////////////////
//                  FUNCTIONS                      //
////////////////////////////////////////////////////

bool key_parity_verify(uint64_t key)
{
    int parity_bit = 0; // parity helper

    for(int ii = 0; ii < 64; ii++)
    {
	// test the parity bit (8-th bit)
	if(ii % 8 == 7)
	{
	    if(parity_bit == 0)
	    {
		// test if 8-th bit != 0
		if( ((key << ii) & FIRSTBIT) != (uint64_t)0)
		{
		    printf("parity error at bit #%i\n", ii + 1);
		    return false;
		}
	    }
	    else
	    {
		// test if 8-th bit != 1
		if( ((key << ii) & FIRSTBIT) != FIRSTBIT)
		{
		    printf("parity error at bit #%i\n", ii + 1);
		    return false;
		}
	    }
	    parity_bit = 0; // re-init parity_bit for next byte block
	}
	// count numbers of 1 in the 7bit block
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

void key_schedule(uint64_t* key, uint64_t* next_key, int round)
{
    // Init
    uint64_t key_left = 0;
    uint64_t key_right = 0;

    uint64_t key_left_temp = 0;
    uint64_t key_right_temp = 0;

    *next_key = 0; // important !

    // 1. First round => PC-1 : Permuted Choice 1
    if(round == 0)
    {
	for(int ii = 0; ii < 56; ii++)
	{
	    if(ii < 28)
		key_left += (((*key << (PC1[ii] - 1)) & FIRSTBIT) >> ii);
	    else
		key_right += (((*key << (PC1[ii] - 1)) & FIRSTBIT) >> (ii % 28));
	}
    }
    // 1. Other rounds? => Seperate key into two key halves.
    else
    {
	for(int ii = 0; ii < 56; ii++)
	{
	    if(ii < 28)
		key_left += (((*key << ii) & FIRSTBIT) >> ii);
	    else
		key_right += (((*key << ii) & FIRSTBIT) >> (ii % 28));
	}
    }

    // 2. Rotations
    key_left_temp = Rotations[round] == 1 ? FIRSTBIT : 0xC000000000000000;
    key_right_temp = Rotations[round] == 1 ? FIRSTBIT : 0xC000000000000000;

    key_left_temp = (key_left & key_left_temp) >> (28 - Rotations[round]);
    key_right_temp = (key_right & key_right_temp) >> (28 - Rotations[round]);

    key_left_temp += (key_left << Rotations[round]);
    key_right_temp += (key_right << Rotations[round]);

    // Combine the 2 keys into 1 (next_key)
    // next_key will be used for following rounds
    for(int ii = 0; ii < 56; ii++)
    {
	if(ii < 28)
	    *next_key += (((key_left_temp << ii) & FIRSTBIT) >> ii);
	else
	    *next_key += (((key_right_temp << (ii % 28)) & FIRSTBIT) >> ii);
    }

    // 3. PC-2 : Permuted Choice 2
    *key = 0;

    for(int ii = 0; ii < 48; ii++)
    {
	*key += ( (*next_key << (PC2[ii] - 1)) & FIRSTBIT) >> ii;
    }

    // All Good!
    // Use key in the DES rounds.
    // Use next_key in this function again as the new key to change
}


// HUGO :D ?
void rounds(bool encrypt, uint64_t data, uint64_t key, int round)
{ 
  int i;
  int DesExpansion_size = 48;
  int Permutation_size = 32;
  uint64_t mask1, mask2;
  uint64_t left_block = *data;
  uint64_t right_block = *data;
  uint64_t temp = 0;
  uint64_t temp_bis = 0;
  
  left_block  = left_block >> 32;
  right_block = right_block << 32;
  right_block = right_block >> 32;  
  
  //
  // 1. Block expansion
  //  
  
  for(i = 0 ; i < DesExpansion_size ; i++)
  {
    mask1 = 1 << (DesExpansion[i]-1);
    mask1 = right_block & mask1;
    if(mask1)
    {
      mask2 = 1 << i;
      temp = temp | mask2;
    }
  }

  //
  // 2. Xor with the key
  //
  
   temp = temp ^ key;

  //
  // 3. Substitution
  //
   
  unsigned char coordx = 0;
  unsigned char coordy = 0;
  int block_nbr = 8;
  
  for(i = 0 ; i < block_nbr ; i++)
  {
    mask1 = 1 << (5 * i);
    mask1 = mask1 & temp;
    mask1 = mask1 >> (4 * i);
    mask2 = mask2 | mask1;
    mask1 = 1 << i;
    mask1 = mask1 & temp;
    mask1 = mask1 >> i;
    mask2 = mask2 | mask1;
    
    coordy = mask2;
    
    mask1 = 30 << (i * 6);
    mask1 = mask1 & temp;
    mask1 = mask1 >> (1 + (i * 6));
    
    coordx = mask1;
    
    temp_bis = temp_bis | (DesSbox[i][coordy][coordx] << (4 * i));
  }
  
  temp = temp_bis;

  //
  // 4. Block Expansion
  //
  
  temp_bis = 0;
  
  for(i = 0 ; i < Permutation_size ; i++)
  {
    mask1 = 1 << (Permutation[i]-1);
    mask1 = temp & mask1;
    if(mask1)
    {
      mask2 = 1 << i;
      temp_bis = mask2 | temp_bis;
    }
  }
  
  temp = temp_bis;

  //
  // 5. Xor with the left block
  //

  temp = temp ^ left_block;
  
  *data = *data << 32;
  *data = *data | temp;
}


// End of file
