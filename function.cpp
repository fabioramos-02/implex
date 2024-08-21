#include "lib.h"
#include "stdio.h"
#include "stdlib.h"
#include <chrono>
#include <sys/time.h>

// Função para calcular o tempo decorrido
float time_val(struct timeval *start, struct timeval *end) {
    return (end->tv_sec - start->tv_sec) + 1e-6 * (end->tv_usec - start->tv_usec);
}

void criarVetorAleatorio(int *vetor, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = rand() % 100; // Gera números aleatórios entre 0 e 99
    }
}


void insertionSort(int *vetor, int tamanho)
{
    int i, j, chave;
    for (i = 1; i < tamanho; i++)
    {
        chave = vetor[i];
        j = i - 1;

        while (j >= 0 && vetor[j] > chave)
        {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = chave;
    }
}

void vetorAleatorio(int inc, int fim, int stp, int rpt){
    // Imprimir rótulo [[RANDOM]]
    printf("[[RANDOM]]\n");

    // Imprimir cabeçalhos
    printf("n\tBubbleSort\tInsertionSort\tMergeSort\tHeapSort\tQuickSort\tCountingSort\n");

    for (int n = inc; n <= fim; n += stp)
    {
        double totalBubble = 0, totalInsertion = 0, totalMerge = 0;
        double totalHeap = 0, totalQuick = 0, totalCounting = 0;

        for (int i = 0; i < rpt; i++)
        {
            int *vetor = new int[n]; // Aloca o vetor com tamanho n
            criarVetorAleatorio(vetor, n); // Função que gera os vetores aleatórios

             // Medir o tempo do InsertionSort
            struct timeval start, end;
            gettimeofday(&start, NULL);
            insertionSort(vetor, n);
            gettimeofday(&end, NULL);
            totalInsertion += time_val(&start, &end);

         
            // // Medir o tempo do MergeSort
            // start = std::chrono::high_resolution_clock::now();
            // mergeSort(vetor, 0, n - 1);
            // totalMerge += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();

            // // Medir o tempo do HeapSort
            // start = std::chrono::high_resolution_clock::now();
            // heapSort(vetor, n);
            // totalHeap += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();

            // // Medir o tempo do QuickSort
            // start = std::chrono::high_resolution_clock::now();
            // quickSort(vetor, 0, n - 1);
            // totalQuick += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();

            // // Medir o tempo do CountingSort
            // start = std::chrono::high_resolution_clock::now();
            // countingSort(vetor, n);
            // totalCounting += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();

            delete[] vetor; // Libera a memória alocada para o vetor
        }

        // Imprimir os resultados
        printf("%d\t%f\t%f\t%f\t%f\t%f\t%f\n", 
               n, 
               totalBubble / rpt, 
               totalInsertion / rpt, 
               totalMerge / rpt, 
               totalHeap / rpt, 
               totalQuick / rpt, 
               totalCounting / rpt);
    }


}