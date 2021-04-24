#include "pdp_11.h"
#include <stdio.h>
#include <stdlib.h>

void print_reg()
{
    trace("R0:%o R1:%o R2:%o R3:%o R4:%o R5:%o R6:%o R7:%o\n", reg[0], reg[1], reg[2], reg[3], reg[4], reg[5], reg[6], reg[7]);
}

void do_halt()
{
    trace("THE END!!!\n");
    print_reg();
    exit(0);
}

void do_mov() {
    w_write(dd.adr, ss.val);
}
void do_add() {}
void do_nothing() 
{
    trace("UNKNOWN FUNCTION\n");
    exit(0);
}

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov},
    {0170000, 0060000, "add", do_add},

};