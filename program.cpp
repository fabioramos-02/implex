#include "lib.h"
// g++ -Wall -o teste program.cpp function.cpp
// ./teste
int main()
{
    srand(time(NULL)); // inicializa a semente do gerador de numeros aleatorios
    int inc = 2000, fim = 30000, stp = 2000, rpt = 20;

    vetorAleatorio(inc, fim, stp, rpt);
    vetorReverso(inc, fim, stp);
    vetorOrdenado(inc, fim, stp);
    vetorQuaseOrdenado(inc, fim, stp);

    return 0;
}