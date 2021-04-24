#include "pdp_11.h"
#include <stdio.h>
#include <stdlib.h>

void do_halt()
{
    trace("THE END!!!\n");
    exit(0);
}

void do_mov() {}
void do_add() {}
void do_nothing() 
{
    trace("UNKNOWN FUNCTION\n");
    exit(0);
}

