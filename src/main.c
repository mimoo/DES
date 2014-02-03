#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include <getopt.h> 

#include "DES.h"



bool encryp=false;
bool decryp=false;
static FILE * outputFile;

static void usage(int status)
{
    if(status == EXIT_SUCCESS)
    {
	fprintf(stdout,"Usage: des [OPTION] FILE\n"
		"Encrypt or Descrypt DES.\n\n"
		" -d, --decrypt     decrypt DES from input file\n"
		" -e, --encrypt     encrypt DES from input file\n"
		" -h, --help        display this help\n"
		" -o, --output=FILE write result to FILE\n"
		" -k, --key=KEY     required key to be used\n");
    }
    else
    {
	fprintf(stderr, "Try 'des --help' for more information.\n");
    }
    exit(status);
}

int main(int argc, char ** argv)
{
    //
    // OPTION PARSER
    //

    FILE * inputFile = NULL; //inputFile

    // Initialising of output file
    outputFile = stdout;

    // Parser
    int optc = 0;

    //short options
    const char* short_opts = "edo:";

    //long options 
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

	case 'e': // -e or --encrypt
	    encryp = true;
	    break;

	case 'd': // -d or --decrypt
	    decryp = true;
	    break;

	case 'h': // -h or --help
	    usage(EXIT_SUCCESS);
	    break;

	case 'o': // output file
	    outputFile=fopen(optarg, "w");
	    if(outputFile == NULL)
	    {
		fprintf(stderr, "Can't open ouput file\n");
		return EXIT_FAILURE;
	    }
	    break;

	case 'k': // key
	    if(optarg)
	    {
		uint64_t u_key = atoi(optarg); // will this work?
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

    //Check if there is a input file and if we can open it
    if(argv[optind]==NULL)
    {
	fprintf(stderr,"Missing input file argument\n");
	usage(EXIT_FAILURE);
    }

    inputFile=fopen(argv[optind],"r");
    if(inputFile==NULL)
    {
	fprintf(stderr, "Can't find input file\n");
	usage(EXIT_FAILURE);
    }

    if(encryp) encrypt(inputFile);

    //
    // APP
    // 

    // 1. put the uint64_t key into a 

    // 2. key schedule

    // 3. encrypt or decrypt ?
    
    // 4. initial permutation

    // 5. read file and rounds

    // 6. final permutation

    // 7. output

    //
    return EXIT_SUCCESS;
}
