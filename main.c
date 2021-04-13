#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include "pdp_11.h"

void test_mem() {
	byte b0 = 0x0a;
	b_write(2, b0);
	byte bres = b_read(2);
    printf("%02hhx = %02hhx\n", b0, bres);
	assert(b0 == bres);
	Address a = 4;
	byte b1 = 0xcb;
	b0 = 0x0a;
	word w = 0xcb0a;
	b_write(a, b0);
	b_write(a+1, b1);
	word wres = w_read(a);
    printf("ww/br \t %04hx=%02hhx%02hhx\n", wres, b1, b0);
	assert(w == wres);
	w = 0x0a0b;
	w_write(a, w);
	wres = w_read(a);
    printf("%02hx=%02hx\n", wres, w);
	assert(w == wres);
}


int main(int argc, char *argv[])
{
    test_mem();
	FILE * fin  = fopen(argv[1], "r");
    load_file();
    fclose(fin);
    return 0;
}

