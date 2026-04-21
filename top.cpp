#include "Vtop.h"
#include "verilated.h"
#include "verilated_fst_c.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv, char **env){
    Verilated::commandArgs(argc, argv);
    Vtop* top = new Vtop;
    VerilatedFstC* tfc = nullptr;
    Verilated::traceEverOn(true);
    tfc = new VerilatedFstC;
    top->trace(tfc, 99);
    tfc->open("waveform.fst");

    
    
    for (int vtime = 0; vtime < 300; vtime++) {
            int a = rand()&1;
            int b = rand()&1;
            top->a = a;
            top->b = b;
            top->eval();
            tfc->dump(vtime);
            printf("a=%d b=%d f=%d\n", top->a, top->b, top->f);
            //std::cout << "a = "<< top->a << " b = " << top->b << " f = " << top->f << endl;
            assert(top->f == (a^b));
        
    }
    tfc->close();
    delete tfc;
    delete top;
    return 0;
}