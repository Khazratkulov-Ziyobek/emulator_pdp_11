#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include "pdp_11.h"



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

void load_file()
{
    Address adr;
    word N;
    while(scanf("%hx%hx", &adr, &N) == 2)
    {
        for(unsigned int i = 0; i < N; i++)
        {
            unsigned int t;
            scanf("%x", &t);
            b_write(adr + i, t);
        }
    }
}

void mem_dump(Address adr, word n)
{
    for(unsigned int i = 0; i < n; i += 2)
    {
        printf("%06o : %06o\n", adr + i, w_read(adr + i)); 
    }
}

void trace(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}