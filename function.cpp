#include "lib.h"
#include "stdio.h"
#include "stdlib.h"
#include <chrono>
#include <sys/time.h>

// Função para calcular o tempo decorrido
float time_val(struct timeval *start, struct timeval *end)
{
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

void bubbleSort(int *vetor, int tamanho)
{
    int i, j, aux;
    for (i = 0; i < tamanho - 1; i++)
    {
        for (j = 0; j < tamanho - i - 1; j++)
        {
            if (vetor[j] > vetor[j + 1])
            {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void merge(int *vetor, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    int *L, *R;
    L = new int[n1];
    R = new int[n2];

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = vetor[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = vetor[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            vetor[k] = L[i];
            i++;
        }
        else
        {
            vetor[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        vetor[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        vetor[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *vetor, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(vetor, left, mid);
    mergeSort(vetor, mid + 1, right);
    merge(vetor, left, mid, right);
}

void heapify(int *vetor, int tamanho, int i)
{
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tamanho && vetor[esquerda] > vetor[maior])
        maior = esquerda;

    if (direita < tamanho && vetor[direita] > vetor[maior])
        maior = direita;

    if (maior != i)
    {
        int temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;

        heapify(vetor, tamanho, maior);
    }
}

void heapSort(int *vetor, int tamanho)
{
    for (int i = tamanho / 2 - 1; i >= 0; i--)
        heapify(vetor, tamanho, i);

    for (int i = tamanho - 1; i > 0; i--)
    {
        int temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;

        heapify(vetor, i, 0);
    }
}

void vetorAleatorio(int inc, int fim, int stp, int rpt)
{
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
            int *vetor = new int[n];       // Aloca o vetor com tamanho n
            criarVetorAleatorio(vetor, n); // Função que gera os vetores aleatórios

            // Medir o tempo do InsertionSort
            struct timeval start, end;
            gettimeofday(&start, NULL);
            insertionSort(vetor, n);
            gettimeofday(&end, NULL);
            totalInsertion += time_val(&start, &end);

            // // Medir o tempo do BubbleSort
            gettimeofday(&start, NULL);
            bubbleSort(vetor, n);
            gettimeofday(&end, NULL);
            totalBubble += time_val(&start, &end);

            // // Medir o tempo do MergeSort
            gettimeofday(&start, NULL);
            mergeSort(vetor, 0, n - 1);
            gettimeofday(&end, NULL);
            totalMerge += time_val(&start, &end);

            // // Medir o tempo do HeapSort
            gettimeofday(&start, NULL);
            heapSort(vetor, n);
            gettimeofday(&end, NULL);
            totalHeap += time_val(&start, &end);

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