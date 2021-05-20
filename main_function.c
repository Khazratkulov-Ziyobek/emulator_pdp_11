#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "pdp_11.h"


int check = 0;

void b_write(Address adr, byte b)
{
    mem[adr] = b;
}

byte b_read(Address adr)
{
    return mem[adr];
}

word w_read(Address adr)
{
    word w = ((word)mem[adr + 1]) << 8;
    w = w | mem[adr];
    return w; 
}

void w_write(Address adr, word b)
{
    mem[adr] = b;
    mem[adr + 1] = b >> 8;
}

void load_file(int argc, char  * argv[])
{
    FILE *fin = fopen(argv[argc - 1], "r");
    if(strcmp(argv[argc - 1], "-t") == 0) {
        usage_print();
        exit(0);
    }
    else if(strcmp(argv[argc - 1], "-T") == 0) {
        usage_print();
        exit(0);
    }
    else if(fin == NULL) {
        printf("can't open %s for reading\n", argv[argc - 1]);
		exit(0);
    }
        
    unsigned short int adr_start;
    unsigned short int quantity;
    while(fscanf(fin,"%hx%hx", &adr_start, &quantity) == 2)
    {
        for(unsigned int i = 0; i < quantity; i++)
        {
            unsigned int t;
            fscanf(fin, "%x", &t);
            b_write(adr_start + i, t);
        }
    }
    fclose(fin);
}

void mem_dump(Address adr, word n)
{
    for(unsigned int i = 0; i < n; i += 2)
    {
        printf("%06o : %06o\n", adr + i, w_read(adr + i)); 
    }
}

void usage_print() {
	printf("Usage:\n ./pdp [options] initial-core-file [options to emulated program]\n\n");
	printf("Options:\n\t-t\tshow trace to stderr\n");
    printf("\t-T\tshow verbose trace to stderr\n");
}

void trace(const char *fmt, ...)
{
    if(check == 1 || check == 2) {
        va_list ap;
        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
    }
}

void check_trace(int argc, char * argv[])
{
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-t") == 0)
            check = 1;
    }
}

void check_bigtrace(int argc, char * argv[])
{
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-T") == 0)
            check = 2;
    }
}