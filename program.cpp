#include "stdio.h"
#include "stdlib.h"
#include <ctime>
#include "lib.h"
#include <sys/time.h>

int main()
{
    // int inc = 10, fim = 50, stp = 5, rpt = 10;
    int inc = 1000, fim = 10000, stp = 1000, rpt = 10;
    srand(time(0)); // Inicializa a semente do gerador de números aleatórios

    
    vetorAleatorio(inc, fim, stp, rpt);
    vetorReverso(inc, fim, stp, rpt);
    vetorOrdenado(inc, fim, stp, rpt);
    return 0;
}
