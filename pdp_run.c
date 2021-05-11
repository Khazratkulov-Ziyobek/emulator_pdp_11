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
            if( wb == 0 || r == 7 || r == 6)
            {
                res.val  = w_read(res.adr);
            }
            else
            {
                res.val = b_read(res.adr);
            }      
            trace("(R%o) ", r);
            break;
        case 2:     // mode 2 (R3)+ #3
            res.adr = reg[r];
            if (wb == 0 || r == 6)
            {
                res.val  = w_read(res.adr);
                reg[r] += 2;
                trace("(R%o)+ ", r);
            }
            else if(r == 7)
            {
                res.val  = w_read(res.adr);
                reg[r] += 2;
                trace("#%o ", res.val);
            }
            else
            {
                res.val = b_read(res.adr);
                reg[r] += 1;
                trace("(R%o)+ ", r);
            }
            break;
        case 3:         //mode 3 @(R3)+ 
            res.adr = reg[r];
            res.adr = w_read(res.adr);
            res.val = w_read(res.adr);
            reg[r] += 2;
            if(r == 7) 
            {
                trace("@#%o ", res.adr);
            }
            else 
            {
                trace("@(R%o)+ ", r);
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
    trace("---------------- running --------------\n");
    pc = 01000;
    Argument ss, dd;
    while(1)
    {
        word w = w_read(pc);
        trace("%06o %06o: ", pc, w);
        pc += 2;
        int i = 0;
        while(1)
        {
            if((w & cmd[i].mask) == cmd[i].opcode)
            {
                trace("%s \n", cmd[i].name);
                cmd[i].do_func(ss, dd);
                if(cmd[i].params == HAS_SS)
                {
                    ss = get_mr(w >> 6);
                }
                if(cmd[i].params == HAS_DD)
                {
                    dd = get_mr(w);
                }
                // trace("\n");
                break;
            }
            i++;
        }
    }
    
}