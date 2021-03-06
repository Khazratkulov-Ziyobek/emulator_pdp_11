#include "pdp_11.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



Argument get_mr(word w) {
    Argument res;
    int r = w & 7; // номер регистра
    int mode = (w >> 3) & 7; // номер мода
    int x;
    switch(mode) {
        case 0:     // mode 0 R3
            res.adr = r;
            res.val  = reg[r];
            trace("R%o ", r);
            break;
        case 1:     // mode 1 (R3)
            res.adr = reg[r];
            res.val = wb == 0 ? w_read(res.adr) : b_read(res.adr);     
            trace("(R%o) ", r);
            break;
        case 2:     // mode 2 (R3)+ #3
            res.adr = reg[r];
			res.val = wb == 0 ? w_read(res.adr) : b_read(res.adr);
            if (wb == 0 || r == 6 || r == 7)
                reg[r] += 2;
			else
				reg[r] ++;
						
            if(r == 7)
              trace("#%06o ", res.val);
            else
              trace("(R%o)+ ", r);
            break;
        case 3:         //mode 3 @(R3)+ 
            res.adr = reg[r];
            res.adr = w_read(res.adr);
            res.val = w_read(res.adr);
            reg[r] += 2;
            if(r == 7) 
                trace("@#%06o ", res.adr);
            else 
                trace("@(R%o)+ ", r);
            break;
        case 4:         //mode 4 -(R3)
            if (wb == 0 || r == 6 || r == 7)
                reg[r] -= 2;
			else
				reg[r] --;
            res.adr = reg[r];
            res.val = wb == 0 ? w_read(res.adr) : b_read(res.adr);
            
            if(r == 7)
                trace("-(pc)");
            else
                trace("-(R%o) ", r);
            break;
        case 5:         // mode 5 @-(R3)
            reg[r] -= 2;
            res.adr = reg[r];
            res.adr = w_read(res.adr);
            res.val = w_read(res.adr);
            if(r == 7)
                trace("@-#%06o ", res.adr);
            else
                trace("@-(R%o) ", r);
            break;
        case 6:         // mode 6 X(R3)
            x = w_read(pc);
            pc += 2;
            res.adr = x + reg[r];
            res.val = w_read(res.adr);
            if(r == 7)
                trace("%o ", res.adr);
            else
                trace("%o(R%o) ", x, r);
            break;
        case 7:         // mode 7 @X(R3)
            x = w_read(pc);
            pc += 2;
            res.adr = x + reg[r];
            res.adr = w_read(res.adr);
            res.val = w_read(res.adr);
            if(r == 7)
                trace("@%o ", res.adr);
            else
                trace("@%o(R%o) ", x, r);
            break;
        }
    return res;
}

void run() {
    
    printf("---------------- running --------------\n");
    pc = 01000;
    Argument ss, dd;
    unsigned int nn, r, xx;
    while(1) {
        word w = w_read(pc);
        trace("%06o: ", pc);
        pc += 2;
        int i = 0;
        wb = (w >> 15);
        while(1) {
            if((w & cmd[i].mask) == cmd[i].opcode) {
                trace("%s     ", cmd[i].name);
                if(cmd[i].params & HAS_SS) {
                    ss = get_mr(w >> 6);
                }
                if(cmd[i].params & HAS_DD) {
                    dd = get_mr(w);
                }
                if(cmd[i].params & HAS_R) {
                    r = (w >> 6) & 7;
                    trace("R%o, %06o ", r, pc - 6);
                }
                if(cmd[i].params & HAS_NN) {
                    nn = w & 077;
                }
                if(cmd[i].params & HAS_XX) {
                    if((w & 0377) >> 7 == 1)
                        xx = (w & 0377) - 0400;
                    else 
                        xx = w & 0377;
                    
                }
                cmd[i].do_func(ss, dd, nn, r, xx);
                if(check == 2)
                    print_reg();
                break;
            }
            i++;
        }
    }
    
}