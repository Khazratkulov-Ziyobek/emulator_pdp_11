#include "pdp_11.h"
#include <stdio.h>
#include <stdlib.h>

void print_reg()
{
    trace("\nR0:%06o R1:%06o R2:%06o R3:%06o\nR4:%06o R5:%06o R6:%06o R7:%06o\n", reg[0], reg[1], reg[2], reg[3], reg[4], reg[5], reg[6], reg[7]);
}

void do_halt(Argument ss, Argument dd)
{
    trace("\n---------------- halted ---------------\n");
    print_reg();
    exit(0);
}

void do_mov(Argument ss, Argument dd) {
    w_write(dd.adr, ss.val);
    trace("    [%06o] = %06o\n", pc - 2, ss.val);
    if(dd.adr < 8)
    {
        reg[dd.adr] = ss.val;
    }
}
void do_add(Argument ss, Argument dd) {
    word w = dd.val + ss.val;
    w_write(dd.adr, w);
    if(dd.adr < 8)
    {
        reg[dd.adr] = w;
    }
    trace("\n");
}
void do_nothing(Argument ss, Argument dd) { }

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov, HAS_SS + HAS_DD},
    {0170000, 0060000, "add", do_add, HAS_SS + HAS_DD},
    {0177777, 0000000, "halt", do_halt, NO_PARAMS},
    {0, 0, "unknown", do_nothing, NO_PARAMS},
};