#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOOL_FMT(bool_expr) "%s",  (bool_expr) ? "1" : "0"

struct sBlock
{
	bool bit[64];
};
typedef struct sBlock Block;

struct sMessage
{
	Block * block;
	int taille;
};
typedef struct sMessage Message;

void encrypt()
{
	int i;
	Message * m = malloc(sizeof(Message));
	FILE * fichier = fopen("a.txt", "rb");
	if(fichier == NULL)
		exit(EXIT_FAILURE);
	m[0].block=malloc(sizeof(Block));
        for(i=0;i<64;i++)
	{
		fread(&m[0].block->bit[i],1, 1, fichier);
		printf(BOOL_FMT(m[0].block->bit[i]));
	}
}
