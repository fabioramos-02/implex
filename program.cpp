#include "stdio.h"
#include "stdlib.h"
#include <ctime>
#include "lib.h"

int main()
{
    int inc = 10, fim = 50, stp = 5, rpt = 10;
    srand(time(0)); // Inicializa a semente do gerador de números aleatórios

    vetorAleatorio(inc, fim, stp, rpt);
    return 0;
}
