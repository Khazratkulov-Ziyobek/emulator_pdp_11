#include "pdp_11.h"
#include <stdio.h>
#include <stdlib.h>

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
    }
    
}