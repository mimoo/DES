#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <inttypes.h>
#include <getopt.h> 

#include "DES.h"

//////////////////////////////////////////////////////
//                 GLOBAL VARIABLES                //
////////////////////////////////////////////////////

static FILE * output = NULL;

//////////////////////////////////////////////////////
//                 FUNCTIONS                       //
////////////////////////////////////////////////////

// usage 
static void usage(int status)
{
    if(status == EXIT_SUCCESS)
    {
	fprintf(stdout,"Usage: app [OPTION] FILE\n"
		"Encrypt or Descrypt DES.\n\n"
		" -d, --decrypt     decrypt DES from input file\n"
		" -e, --encrypt     encrypt DES from input file\n"
		" -h, --help        display this help\n"
		" -o, --output=FILE write result to FILE\n"
		" -k, --key=KEY     required 64bits key\n");
    }
    else
    {
	fprintf(stderr, "Try 'app --help' for more information.\n");
    }
    exit(status);
}

int main(int argc, char ** argv)
{
    // vars
    char * c_key;
    uint64_t key = 0;
    bool encrypt = true;
    FILE * inputFile = NULL; //inputFile
    uint64_t data;
    uint64_t next_key;

    //////////////////////////////////////////////////////
    //                 OPTION PARSER                   //
    ////////////////////////////////////////////////////

    int optc = 0;

    const char* short_opts = "dehk:o:";

    const struct option long_opts[] = 
	{ 
	    {"decrypt",        no_argument, NULL, 'd'},
	    {"encrypt",        no_argument, NULL, 'e'},
	    {"help",           no_argument, NULL, 'h'},
	    {"key",      required_argument, NULL, 'k'},
	    {"output",   required_argument, NULL, 'o'},
	    {NULL,                       0, NULL,   0}
	}; 

    while((optc = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1)
    { 
	switch(optc)
	{ 
	case 'd': // decrypt mode
	    encrypt = false;
	    break;

	case 'h': // help
	    usage(EXIT_SUCCESS);
	    break;

	case 'o': // output file
	    output = fopen(optarg, "w");
	    if(output == NULL)
	    {
		// weird error
		// what about: "don't have permission to write output file"?
		fprintf(stderr, "Can't open ouput file\n");
		return EXIT_FAILURE;
	    }
	    break;

	case 'k': // key
	    if(optarg)
	    {
		c_key = optarg;
	    }
	    else
	    {
		usage(EXIT_FAILURE);
	    }
	    break;

	default : // no arguments
	    usage(EXIT_FAILURE); 
	}
    }	

    // Check if there is a input file and if we can open it
    if(argv[optind] == NULL)
    {
	fprintf(stderr, "Missing input file argument\n");
	usage(EXIT_FAILURE);
    }

    inputFile = fopen(argv[optind], "r");
    if(inputFile == NULL)
    {
	fprintf(stderr, "Can't find input file\n");
	usage(EXIT_FAILURE);
    }

    

    //////////////////////////////////////////////////////
    //                      APP                        //
    ////////////////////////////////////////////////////
    
    //
    // 1. Convert: (char)key -> (uint64_t)key
    // 

    for(int ii = 0; c_key[ii] != '\0'; ii++)
    {
	if(ii > 63)
	{
	    printf("Error: key is longer than 64bits \n");
	    exit(EXIT_FAILURE);
	}
	if(c_key[ii] == '1')
	    key += (FIRSTBIT >> ii);
    }

    //
    // 2. Verify parity key
    //
    
    if(!key_parity_verify(key))
    {
	printf("The key you used is malformated\n"); // more error msg in function
	exit(EXIT_FAILURE);
    }
    
    //
    // 3. Rounds
    //

    // read input file
    input = fopen(inputFile, "rb");

    if(!input)
    {
	printf("Error: can't open input file");
	usage(EXIT_FAILURE);
    }
    
    // default output file
    if(output == NULL) 
	outputFile = fopen("output.txt", "w");

    size_t amount; 
    
    uint64_t a_key[16];
    a_key[0] = *key;

    for(int ii = 0; ii < 16; ii++)
    {
        key_schedule(&a_key[ii], &next_key, ii);
        if(ii != 15)
            a_key[ii + 1] = next_key;
    }
    
    while((amount = fread(&data, 1, 8, input)) > 0)
    {
	// initial permutation
	Permutation(&data, true);

        if(encrypt)
        {
            // rounds
            for(int ii = 0; ii < 16; ii++)
            {
                // one round  
                rounds(&data, a_key[ii]);
            }
        }
        else
        {
            // rounds
            for(int ii = 15; ii >= 0; ii--)
            {
                // one round  
                rounds(&data, a_key[ii]);
            }
        }
	// final permutation
	Permutation(&data, false);

	// write output
	fwrite(&data, 1, amount, output);
	data = 0;
    }

    fclose(input);
    fclose(output);

    //
    // Code de Jacques :D ?
    //
    /*
    unsigned char input[8];

    while(fgets(input, 9, inputFile)!=NULL)
    {
        int i,j;
        uint64_t paquet=0;
	for( i = 0; i <= 7; ++i )
	{
		paquet= paquet << 8;
    		paquet |= (uint64_t)input[i];
    		
	}
    }
    */

    //paquet est le block de 64 bits à encrypter

    //
    return EXIT_SUCCESS;
}
