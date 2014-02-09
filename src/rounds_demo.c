#include <stdio.h>
#include <stdlib.h>



// Affichage en bits
char* bin(unsigned long int i)
{
    int a = 8;
    static char buffer [1+sizeof (unsigned long int)*8] = { 0 };
    char *p=buffer-1+sizeof (unsigned long int)*8;
    do { *--p = '0' + (i & 1); i >>= 1; a--;} while (a);
    return p;
}



char* bin6(unsigned long int i)
{
    int a = 6;
    static char buffer [1+sizeof (unsigned long int)*8] = { 0 };
    char *p=buffer-1+sizeof (unsigned long int)*8;
    do { *--p = '0' + (i & 1); i >>= 1; a--;} while (a);
    return p;
}



char* bin4(unsigned long int i)
{
    int a = 4;
    static char buffer [1+sizeof (unsigned long int)*8] = { 0 };
    char *p=buffer-1+sizeof (unsigned long int)*8;
    do { *--p = '0' + (i & 1); i >>= 1; a--;} while (a);
    return p;
}



int
main(int argc, char* argv[])
{
  // Boucler 16 rounds
  
  // BLOCK EXPANSION
  
  unsigned char init[] = {'a', 'b', 'c', 'd'}; // 4 char de 8 bits = 32 bits
  unsigned char final[] = { 0, 0, 0, 0, 0, 0 }; // 6 char de 8 bits = 48 bits
  
  printf("\n=========================================\n");
  printf(" Block expansion\n=========================================\n\n");
  printf ("%s\n",bin(init[0]));
  printf ("%s\n",bin(init[1]));
  printf ("%s\n",bin(init[2]));
  printf ("%s\n\nTo :\n\n",bin(init[3]));
  
  int a, b, i, x, y;
  
  int n = 48; // Taille de DesExpansion
  const int DesExpansion[] = {
    32,  1,  2,  3,  4,  5,  4,  5,
     6,  7,  8,  9,  8,  9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32,  1
  }; 
  
  for(i = 0 ; i < n ; i++)
  {
    // Exemples en  commentaires
    // Copier bit 32 de init dans bit 1 de final
    a = (DesExpansion[i]-1)/8; // 31/8 = 3;
    b = (DesExpansion[i]-1)%8; // 31%8 = 7;
    // init[3], bit 7
    x = i/8;
    y = i%8;
    // final[0], bit 0

    // Mettre init[3], bit 7 dans final[0], bit 0
    unsigned char mask1 = 0;
    mask1 = (1 << 7-b);
    mask1 = mask1 & init[a];
    
    if(mask1 != 0)
    {
      unsigned char mask2 = 0;
      mask2 = (1 << 7-y);
      final[x] = final[x] | mask2;
    }
  }
  
  printf ("%s\n",bin(final[0]));
  printf ("%s\n",bin(final[1]));
  printf ("%s\n",bin(final[2]));
  printf ("%s\n",bin(final[3]));
  printf ("%s\n",bin(final[4]));
  printf ("%s\n",bin(final[5]));



  // XOR WITH KEY

  n = 6;
  unsigned char key[] = {'I', 'A', 'M', 'K', 'E', 'Y'};
  
  printf("\n=========================================\n");
  printf(" Xor with the key\n=========================================\n\n");
  printf ("Block : %s", bin(final[0])); printf(" Key : %s\n", bin(key[0]));
  printf ("        %s", bin(final[1])); printf("       %s\n", bin(key[1]));
  printf ("        %s", bin(final[2])); printf("       %s\n", bin(key[2]));
  printf ("        %s", bin(final[3])); printf("       %s\n", bin(key[3]));
  printf ("        %s", bin(final[4])); printf("       %s\n", bin(key[4]));
  printf ("        %s", bin(final[5])); printf("       %s\n\nTo :\n\n", bin(key[5]));
  
  for(i = 0 ; i < n ; i++)
    final[i] = final[i]^key[i];
  
  printf ("%s\n",bin(final[0]));
  printf ("%s\n",bin(final[1]));
  printf ("%s\n",bin(final[2]));
  printf ("%s\n",bin(final[3]));
  printf ("%s\n",bin(final[4]));
  printf ("%s\n",bin(final[5]));



  // SUBSTITUTION

  n = 6;
  unsigned char temp[] = {0, 0, 0, 0, 0, 0, 0, 0};
  int m = 48;
  const int Splitting[] = {
     1,  2,  3,  4,  5,  6,  7,  8,
     9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48
  }; 
  
  printf("\n=========================================\n");
  printf(" Substitution\n=========================================\n\n");
  printf ("%s\n",bin(final[0]));
  printf ("%s\n",bin(final[1]));
  printf ("%s\n",bin(final[2]));
  printf ("%s\n",bin(final[3]));
  printf ("%s\n",bin(final[4]));
  printf ("%s\n\nTo :\n\n",bin(final[5]));
  
  for(i = 0 ; i < m ; i++) // Voir fonction expansion
  {
    a = (Splitting[i]-1)/8;
    b = (Splitting[i]-1)%8;

    x = i/6;
    y = i%6;

    unsigned char mask1 = 0;
    mask1 = (1 << 7-b);
    mask1 = mask1 & final[a];
    
    if(mask1 != 0)
    {
      unsigned char mask2 = 0;
      mask2 = (1 << 5-y);
      temp[x] = temp[x] | mask2;
    }
  }
  
  printf ("%s\n",bin6(temp[0]));
  printf ("%s\n",bin6(temp[1]));
  printf ("%s\n",bin6(temp[2]));
  printf ("%s\n",bin6(temp[3]));
  printf ("%s\n",bin6(temp[4]));
  printf ("%s\n",bin6(temp[5]));
  printf ("%s\n",bin6(temp[6]));
  printf ("%s\n\nThen :\n\n",bin6(temp[7]));
  
  // Suite substitution à vérifier
  
  static const int DesSbox[8][4][16] = {
 
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
  
  char finalbis[] = { 0, 0, 0, 0, 0, 0, 0, 0};
  char coordx = 0;
  char coordy = 0;
  char mask1 = 0;
  char mask2 = 0;
  
  for(i = 0 ; i < 8 ; i++)
  {
    mask1 = 1 << 5;
    mask1 = mask1 & temp[i];
    mask1 = mask1 >> 4;
    mask2 = mask2 | mask1;
    mask1 = 1;
    mask1 = mask1 & temp[i];
    mask2 = mask2 | mask1;
    
    coordy = mask2;
    
    mask1 = 30;
    mask1 & temp[i];
    mask1 = mask1 >> 1;
    
    coordx = mask1;
    
    temp[i];
    finalbis[i] = DesSbox[i][coordy][coordx];
  }
  
  printf ("%s\n",bin4(finalbis[0]));
  printf ("%s\n",bin4(finalbis[1]));
  printf ("%s\n",bin4(finalbis[2]));
  printf ("%s\n",bin4(finalbis[3]));
  printf ("%s\n",bin4(finalbis[4]));
  printf ("%s\n",bin4(finalbis[5]));
  printf ("%s\n",bin4(finalbis[6]));
  printf ("%s\n",bin4(finalbis[7]));



  // BLOCKS COMBINATION

  unsigned char temp2[] = {0, 0, 0, 0};
  n = 32;
  const int Combination[] = {
     5,  6,  7,  8, 13, 14, 15, 16,
    21, 22, 23, 24, 29, 30, 31, 32,
    37, 38, 39, 40, 45, 46, 47, 48,
    53, 54, 55, 56, 61, 62, 63, 64
  }; 
  
  printf("\n=========================================\n");
  printf(" Combination\n=========================================\n\n");
  printf ("%s\n",bin4(finalbis[0]));
  printf ("%s\n",bin4(finalbis[1]));
  printf ("%s\n",bin4(finalbis[2]));
  printf ("%s\n",bin4(finalbis[3]));
  printf ("%s\n",bin4(finalbis[4]));
  printf ("%s\n",bin4(finalbis[5]));
  printf ("%s\n",bin4(finalbis[6]));
  printf ("%s\n\nTo :\n\n",bin4(finalbis[7]));
  
  for(i = 0 ; i < n ; i++) // Voir fonction expansion
  {
    a = (Combination[i]-1)/8;
    b = (Combination[i]-1)%8;

    x = i/8;
    y = i%8;

    mask1 = 0;
    mask1 = (1 << 7-b);
    mask1 = mask1 & finalbis[a];
    
    if(mask1 != 0)
    {
      mask2 = 0;
      mask2 = (1 << 7-y);
      temp2[x] = temp2[x] | mask2;
    }
  }
  
  printf ("%s\n",bin(temp2[0]));
  printf ("%s\n",bin(temp2[1]));
  printf ("%s\n",bin(temp2[2]));
  printf ("%s\n",bin(temp2[3]));



  // PERMUTATION

  unsigned char temp3[] = {0, 0, 0, 0};
  n = 32;
  const int Permutation[] = {
    16,  7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9,
    19, 13, 30,  6, 22, 11,  4, 25
  }; 
  
  printf("\n=========================================\n");
  printf(" Permutation\n=========================================\n\n");
  printf ("%s\n",bin(temp2[0]));
  printf ("%s\n",bin(temp2[1]));
  printf ("%s\n",bin(temp2[2]));
  printf ("%s\n\nTo :\n\n",bin(temp2[3]));;
  
  for(i = 0 ; i < n ; i++) // Voir fonction expansion
  {
    a = (Permutation[i]-1)/8;
    b = (Permutation[i]-1)%8;

    x = i/8;
    y = i%8;

    mask1 = 0;
    mask1 = (1 << 7-b);
    mask1 = mask1 & temp2[a];
    
    if(mask1 != 0)
    {
      mask2 = 0;
      mask2 = (1 << 7-y);
      temp3[x] = temp3[x] | mask2;
    }
  }
  
  printf ("%s\n",bin(temp3[0]));
  printf ("%s\n",bin(temp3[1]));
  printf ("%s\n",bin(temp3[2]));
  printf ("%s\n",bin(temp3[3]));



  // XOR WITH LEFT

  n = 4;
  unsigned char left[] = {'L', 'E', 'F', 'T'};
  
  printf("\n=========================================\n");
  printf(" Xor with the left block\n=========================================\n\n");
  printf ("Block : %s", bin(temp3[0])); printf(" Left block : %s\n", bin(left[0]));
  printf ("        %s", bin(temp3[1])); printf("              %s\n", bin(left[1]));
  printf ("        %s", bin(temp3[2])); printf("              %s\n", bin(left[2]));
  printf ("        %s", bin(temp3[3])); printf("              %s\n\nTo :\n\n", bin(left[3]));
  
  for(i = 0 ; i < n ; i++)
    temp3[i] = temp3[i]^left[i];
  
  printf ("%s\n",bin(temp3[0]));
  printf ("%s\n",bin(temp3[1]));
  printf ("%s\n",bin(temp3[2]));
  printf ("%s\n",bin(temp3[3]));


  printf("\n");
}
