#include "encrypt.h"



void encrypt(FILE * inputFile)
{
	int i;
	char block[8];
	while (fgets(block, 8, inputFile) != NULL) 
        {
		for(i=0;i<8;i++)
		{
			fprintf(stdout,"%c",block[i]);
		}
        }
}
