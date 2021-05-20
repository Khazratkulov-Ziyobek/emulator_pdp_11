#include "pdp_11.h"
#include <stdio.h>
#include <stdlib.h>



int N, Z, C;
void set_NZ(word w) {
    if(wb == 0)
        N = (w >> 15) & 1;
    else
        N = (w >> 7) & 1;
    Z = (w == 0);
}
void set_C(word w) {
    if(wb == 0)
        C = (w >> 15) & 1;
    else
        C = (w >> 7) & 1;
}

void print_reg() {
    printf("\nR0:%06o R2:%06o R4:%06o sp:%06o\nR1:%06o R3:%06o R5:%06o pc:%06o\n", reg[0], reg[2], reg[4], reg[6], reg[1], reg[3], reg[5], reg[7]);
}

void do_halt(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx) {
    printf("\n---------------- halted ---------------\n");
    print_reg();
    exit(0);
}

void do_mov(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx) {
    if(wb == 0)
        w_write(dd.adr, ss.val); 
    else
        b_write(dd.adr, ss.val); 
    if(dd.adr < 8) {
        reg[dd.adr] = ss.val;
    }
    set_NZ(ss.val);
    trace("       [%06o]=%06o", ss.adr, ss.val);
    trace("\n");
}

void do_movb(Argument ss, Argument dd, unsigned int nn, unsigned r, unsigned int xx) {
    b_write(dd.adr, ss.val);
    set_NZ(ss.val);
    if(dd.adr < 8) {
		if (N == 0)
            ss.val = ss.val & 0377;
        else
            ss.val = (ss.val & 0377) | 0177400;
		reg[dd.adr] = ss.val;
    }
    trace("       [%06o]=%06o", ss.adr, ss.val);
    trace("\n");
}

void do_add(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx) {
    word w = dd.val + ss.val;
    w_write(dd.adr, w);
    if(dd.adr < 8) {
        reg[dd.adr] = w;
        set_NZ(reg[dd.adr]);
        set_C(w >> 1);
    }
    trace("            R%o=%06o  R%o=%06o", ss.adr, reg[ss.adr], dd.adr, reg[dd.adr]);
    trace("\n");
}
void do_nothing(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx) {
    trace("\n");
}

void do_sob(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx) {
    reg[r] -= 1;
    if(reg[r] != 0) {
        pc -= 2*nn;
    }
    trace("\n");
}

void do_ccc(Argument dd, Argument ss, unsigned int nn, unsigned int r, unsigned int xx) {
	N = 0;
	Z = 0;
	C = 0;
};

void do_cln(Argument dd, Argument ss, unsigned int nn, unsigned int r, unsigned int xx) {
	N = 0;
};

void do_clz(Argument dd, Argument ss, unsigned int nn, unsigned int r, unsigned int xx) {
	Z = 0;
};

void do_clc(Argument dd, Argument ss, unsigned int nn, unsigned int r, unsigned int xx) {
	C = 0;
};

void do_scc(Argument dd, Argument ss, unsigned int nn, unsigned int r, unsigned int xx) {
	N = 1;
	Z = 1;
	C = 1;
};

void do_sec(Argument dd, Argument ss, unsigned int nn, unsigned int r, unsigned int xx) {
	C = 1;
};

void do_sen(Argument dd, Argument ss, unsigned int nn, unsigned int r, unsigned int xx) {
	N = 1;
};

void do_sez(Argument dd, Argument ss, unsigned int nn, unsigned int r, unsigned int xx) {
	Z = 1;
};

void do_nop(Argument dd, Argument ss, unsigned int nn, unsigned int r, unsigned int xx) {
};


void do_clr(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx) {
    w_write(dd.adr, 0);
    if(dd.adr < 8) {
        reg[dd.adr] = 0;
    }
    trace("\n");
    do_sez(ss, dd, nn, r, xx);
    do_clc(ss, dd, nn, r, xx);
    do_cln(ss, dd, nn, r, xx);
}

void do_br(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx) {
    pc = pc + 2*xx;
    trace("\n");
}

void do_beq(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx) {
    if(Z == 1) {
        do_br(ss, dd, nn, r, xx);
    }
}

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD},
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
    {0177777, 0000000, "halt", do_halt, NO_PARAMS},
    {0177000, 0077000, "sob", do_sob, HAS_R | HAS_NN},
    {0177700, 0005000, "clr", do_clr, HAS_DD},
    {0170000, 0110000, "movb", do_movb, HAS_SS | HAS_DD},
    {0177777, 0000257, "ccc", do_ccc, NO_PARAMS},
	{0177777, 0000241, "clc", do_clc, NO_PARAMS},
	{0177777, 0000250, "cln", do_cln, NO_PARAMS},
	{0177777, 0000244, "clz", do_clz, NO_PARAMS},
	{0177777, 0000277, "scc", do_scc, NO_PARAMS},
	{0177777, 0000261, "sec", do_sec, NO_PARAMS},
	{0177777, 0000270, "sen", do_sen, NO_PARAMS},
	{0177777, 0000264, "sez", do_sez, NO_PARAMS},
	{0177777, 0000240, "nop", do_nop, NO_PARAMS},
    {0177400, 0000400, "br", do_br, HAS_XX},
    {0177400, 0001400, "beq", do_beq, HAS_XX},
    {0, 0, "unknown", do_nothing, NO_PARAMS},
};