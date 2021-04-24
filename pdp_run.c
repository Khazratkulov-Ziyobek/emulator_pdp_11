#include "pdp_11.h"
#include <stdio.h>
#include <stdlib.h>




Argument get_mr(word w)
{
    Argument res;
    int r = w & 7; // номер регистра
    int mode = (w >> 3) & 7; // номер мода
    switch(mode)
    {
        case 0:     // mode 0 R3
            res.adr = r;
            res.val  = reg[r];
            trace("R%o ", r);
            break;
        case 1:     // mode 1 (R3)
            res.adr = reg[r];
            res.val  = w_read(res.adr); //b_read тоже нудно написать
            trace("(R%o) ", r);
            break;
        case 2:     // mode 2 (R3)+ #3
            res.adr = reg[r];
            res.val  = w_read(res.adr); //to do b_read
            reg[r] += 2; //to do +1
            if(r == 7)
            {
                trace("#%o ", res.val);
            }
            else
            {
                trace("(R%o)+ ", r);
            }
            break;
        default:
            fprintf(stderr, "Mode %o NOT IMPLEMENTED YET!\n", mode);
            exit(1);
        
    }
    return res;
}

void run()
{
    pc = 01000;
    Argument ss, dd;
    while(1)
    {
        word w = w_read(pc);
        trace("%06o %06o: \n", pc, w);
        pc += 2;
        if(w == 0)
        {
            trace("halt \n");
            do_halt(ss, dd);
        }
        else if((w & 0170000) == 0010000)
        {
            trace("mov "); //01SSDD
            ss = get_mr(w >> 6);
            dd = get_mr(w);
            do_mov(ss, dd);
        }
        else if((w & 0170000) == 0060000)
        {
            trace("add ");
            do_add(ss, dd);
        }
    }
    
}