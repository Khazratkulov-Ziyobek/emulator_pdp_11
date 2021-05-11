#include "pdp_11.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



Argument get_mr(word w)
{
    Argument res;
    int r = w & 7; // номер регистра
    int mode = (w >> 3) & 7; // номер мода
    int x;
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
            if (r == 7)
            {
                res.val  = w_read(res.adr);
                reg[r] += 2;
                trace("#%06o ", res.val);
            }
            else if(wb == 0 || r == 6)
            {
                res.val  = w_read(res.adr);
                reg[r] += 2;
                trace("(R%o)+ ", r);
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
                trace("@#%06o ", res.adr);
            }
            else 
            {
                trace("@(R%o)+ ", r);
            }
            break;
        case 4:         //mode 4 -(R3)
            if(wb == 0 || r == 6 || r == 7)
            {
                reg[r] -= 2;
                res.adr = reg[r];
                res.val = w_read(res.adr);
            }
            else
            {
                reg[r] -= 1;
                res.adr = reg[r];
                res.val = b_read(res.adr);
            }
            trace("-(R%o) ", r);
            break;
        case 5:         // mode 5 @-(R3)
            reg[r] -= 2;
            res.adr = reg[r];
            res.adr = w_read(res.adr);
            res.val = w_read(res.adr);
            if(r == 7)
            {
                trace("@-#%06o ", res.adr);
            }
            else
            {
                trace("@-(R%o) ", r);
            }
            break;
        case 6:         // mode 6 X(R3)
            x = w_read(pc);
            pc += 2;
            res.adr = x + reg[r];
            res.val = w_read(res.adr);
            if(r == 7)
            {
                trace("%o ", res.adr);
            }
            else
            {
                trace("%o(R%o) ", x, r);
            }
            break;
        case 7:         // mode 7 @X(R3)
            x = w_read(pc);
            pc += 2;
            res.adr = x + reg[r];
            res.adr = w_read(res.adr);
            res.val = w_read(res.adr);
            if(r == 7)
            {
                trace("@%o ", res.adr);
            }
            else
            {
                trace("@%o(R%o) ", x, r);
            }
            break;
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
        trace("%06o: ", pc);
        pc += 2;
        int i = 0;
        while(1)
        {
            if((w & cmd[i].mask) == cmd[i].opcode)
            {
                trace("%s ", cmd[i].name);
                if(cmd[i].params == HAS_SS + HAS_DD)
                {
                    ss = get_mr(w >> 6);
                    dd = get_mr(w);
                }
                cmd[i].do_func(ss, dd);
                break;
            }
            i++;
        }
    }
    
}