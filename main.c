#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include "pdp_11.h"

byte mem[MEMSIZE];

void test_mem() {
	byte b0 = 0x0a;
	b_write(2, b0);
	byte bres = b_read(2);
	assert(b0 == bres);
	Address a = 4;
	byte b1 = 0xcb;
	b0 = 0x0a;
	word w = 0xcb0a;
	b_write(a, b0);
	b_write(a+1, b1);
	word wres = w_read(a);
	assert(w == wres);
	w = 0x0a0b;
	w_write(a, w);
	wres = w_read(a);
	assert(w == wres);
}

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

