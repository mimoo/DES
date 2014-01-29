#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#include "genkey.h"

static int genkey()
{
    srand(time(NULL));
    int rr;
    bool key[64];

    for(int ii = 0; ii < 64; ii++)
    {
	rr = rand();
	key[ii] = rr;
    }

}

int main()
{
    bool truc[64] = genkey();
    printf("%s", truc);
}
