#include "pdp_11.h"
#include <stdio.h>
#include <stdlib.h>


extern Command cmd[];
extern Argument ss, dd;

Argument get_mr(word w)
{
    Argument res;
    int reg = w & 7;

    return res;
}

void run()
{
    pc = 01000;
    while(1)
    {
        word w = w_read(pc);
        trace("%06o %06o: ", pc, w);
        pc += 2;
        if(w == 0)
        {
            trace("halt ");
            do_halt();
        }
        else if((w & 0170000) == 0010000)
        {
            trace("mov "); //01SSDD
            ss = get_mr(w);
            dd = get_mr(w);
            do_mov();
        }
    }
    
}