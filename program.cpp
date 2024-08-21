#include "stdio.h"
#include "stdlib.h"
#include <ctime>
#include "lib.h"

int main()
{
    int inc = 10, fim = 50, stp = 5, rpt = 10;
    srand(time(0)); // Inicializa a semente do gerador de números aleatórios


    for (int n = inc; n <= fim; n += stp)
    {
        for (int i = 0; i < rpt; i++)
        {
            int *vetor = new int[n]; // Aloca o vetor com tamanho n

            criarVetorAleatorio(vetor, n);

            // Aqui você pode descomentar para testar cada algoritmo de ordenação
            // bubbleSort(vetor, n);
            // insertionSort(vetor, n);
            // mergeSort(vetor, 0, n-1);
            // heapSort(vetor, n);
            // quickSort(vetor, 0, n-1);
            // countingSort(vetor, n);

            delete[] vetor; // Libera a memória alocada para o vetor
        }
    }

    return 0;
}

