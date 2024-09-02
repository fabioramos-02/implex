#include "lib.h"
// g++ -Wall -o teste program.cpp function.cpp
// ./teste
int main()
{
    int inc = 2000, fim = 30000, stp = 2000, rpt = 10;
    
    // vetorAleatorio(inc, fim, stp, rpt);
    // vetorReverso(inc, fim, stp);
    // vetorOrdenado(inc, fim, stp);
    vetorQuaseOrdenado(inc, fim, stp);
    

    return 0;
}
