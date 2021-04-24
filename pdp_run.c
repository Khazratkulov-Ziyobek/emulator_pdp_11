#include "pdp_11.h"
#include <stdio.h>
#include <stdlib.h>


extern Command cmd[];
extern Argument ss, dd;

Argument get_mr(word w)
{
    Argument res;
    int r = w & 7; // номер регистра
    int mode = (w >> 3) & 7; // номер мода
    switch(mode)
    {
        case 0:     // mode 0
            res.adr = r;
            res.val  = reg[r];
            trace("R%o ", r);
            break;
        
    }
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