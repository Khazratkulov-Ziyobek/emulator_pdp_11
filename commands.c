#include "pdp_11.h"
#include <stdio.h>
#include <stdlib.h>

void print_reg()
{
    trace("\nR0:%06o R2:%06o R4:%06o sp:%06o\nR1:%06o R3:%06o R5:%06o pc:%06o\n", reg[0], reg[2], reg[4], reg[6], reg[1], reg[3], reg[5], reg[7]);
}

void do_halt(Argument ss, Argument dd, unsigned int nn, unsigned int r)
{
    trace("\n---------------- halted ---------------\n");
    print_reg();
    exit(0);
}

void do_mov(Argument ss, Argument dd, unsigned int nn, unsigned int r) {
    w_write(dd.adr, ss.val);
    if(dd.adr < 8)
    {
        reg[dd.adr] = ss.val;
    }
    trace("\n");
}

void do_movb(Argument ss, Argument dd, unsigned int nn, unsigned r) {
    b_write(dd.adr, ss.val);
    if(dd.adr < 8)
    {
        reg[dd.adr] = ss.val;
    }
    trace("\n");
}

void do_add(Argument ss, Argument dd, unsigned int nn, unsigned int r) {
    word w = dd.val + ss.val;
    w_write(dd.adr, w);
    if(dd.adr < 8)
    {
        reg[dd.adr] = w;
    }
    trace("\n");
}
void do_nothing(Argument ss, Argument dd, unsigned int nn, unsigned int r) {
    trace("\n");
 }

void do_sob(Argument ss, Argument dd, unsigned int nn, unsigned int r)
{
    reg[r] -= 1;
    if(reg[r] != 0)
    {
        pc -= 2*nn;
    }
    trace("\n");
}

void do_clr(Argument ss, Argument dd, unsigned int nn, unsigned int r)
{
    w_write(dd.adr, 0);
    if(dd.adr < 8)
    {
        reg[dd.adr] = 0;
    }
    trace("\n");
}

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD},
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
    {0177777, 0000000, "halt", do_halt, NO_PARAMS},
    {0177000, 0077000, "sob", do_sob, HAS_R | HAS_NN},
    {0177700, 0005000, "clr", do_clr, HAS_DD},
    {0170000, 0110000, "movb", do_movb, HAS_SS | HAS_DD},
    {0, 0, "unknown", do_nothing, NO_PARAMS},
};