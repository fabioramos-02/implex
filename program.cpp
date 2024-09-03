#include "lib.h"
// g++ -Wall -o teste program.cpp function.cpp
// ./teste
int main()
{
    int inc = 1000, fim = 20000, stp = 1000, rpt = 10;
    
    vetorAleatorio(inc, fim, stp, rpt);
    vetorReverso(inc, fim, stp);
    vetorOrdenado(inc, fim, stp);
    vetorQuaseOrdenado(inc, fim, stp);
    

    return 0;
}