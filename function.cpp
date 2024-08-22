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

// Função para ordenar um vetor de inteiros em ordem decrescente ou decrescente
void insertionSort(int *vetor, int tamanho, bool crescente)
{
    int i, j, chave;
    for (i = 1; i < tamanho; i++)
    {
        chave = vetor[i];
        j = i - 1;

        if (crescente)
        {
            while (j >= 0 && vetor[j] > chave)
            {
                vetor[j + 1] = vetor[j];
                j = j - 1;
            }
        }
        else
        {
            while (j >= 0 && vetor[j] < chave)
            {
                vetor[j + 1] = vetor[j];
                j = j - 1;
            }
        }

        vetor[j + 1] = chave;
    }
}


void bubbleSort(int *vetor, int tamanho, bool crescente)
{
    int i, j, aux;
    for (i = 0; i < tamanho - 1; i++)
    {
        for (j = 0; j < tamanho - i - 1; j++)
        {
            if (crescente)
            {
                if (vetor[j] > vetor[j + 1])
                {
                    aux = vetor[j];
                    vetor[j] = vetor[j + 1];
                    vetor[j + 1] = aux;
                }
            }
            else
            {
                if (vetor[j] < vetor[j + 1])
                {
                    aux = vetor[j];
                    vetor[j] = vetor[j + 1];
                    vetor[j + 1] = aux;
                }
            }
        }
    }
}


void merge(int *vetor, int left, int mid, int right, bool crescente)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Alocando dinamicamente as sub-arrays
    int *L = new int[n1];
    int *R = new int[n2];

    // Copiando dados para os arrays temporários L[] e R[]
    for (int i = 0; i < n1; i++)
        L[i] = vetor[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = vetor[mid + 1 + j];

    int i = 0; // Índice inicial do primeiro subarray
    int j = 0; // Índice inicial do segundo subarray
    int k = left; // Índice inicial do subarray mesclado

    // Mesclando os arrays temporários de volta para o vetor[]
    while (i < n1 && j < n2)
    {
        if (crescente)
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
        }
        else
        {
            if (L[i] >= R[j])
            {
                vetor[k] = L[i];
                i++;
            }
            else
            {
                vetor[k] = R[j];
                j++;
            }
        }
        k++;
    }

    // Copiando os elementos restantes de L[], se houver
    while (i < n1)
    {
        vetor[k] = L[i];
        i++;
        k++;
    }

    // Copiando os elementos restantes de R[], se houver
    while (j < n2)
    {
        vetor[k] = R[j];
        j++;
        k++;
    }

    // Liberando a memória alocada dinamicamente
    delete[] L;
    delete[] R;
}

void mergeSort(int *vetor, int left, int right, bool crescente)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // Ordenando recursivamente as metades
        mergeSort(vetor, left, mid, crescente);
        mergeSort(vetor, mid + 1, right, crescente);

        // Mesclando as duas metades ordenadas
        merge(vetor, left, mid, right, crescente);
    }
}


void heapify(int *vetor, int tamanho, int i, bool crescente){
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (crescente)
    {
        if (esq < tamanho && vetor[esq] > vetor[maior])
            maior = esq;

        if (dir < tamanho && vetor[dir] > vetor[maior])
            maior = dir;
    }
    else
    {
        if (esq < tamanho && vetor[esq] < vetor[maior])
            maior = esq;

        if (dir < tamanho && vetor[dir] < vetor[maior])
            maior = dir;
    }

    if (maior != i)
    {
        int temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;

        heapify(vetor, tamanho, maior, crescente);
    }
}

void heapSort(int *vetor, int tamanho, bool crescente)
{
    for (int i = tamanho / 2 - 1; i >= 0; i--)
        heapify(vetor, tamanho, i, crescente);

    for (int i = tamanho - 1; i > 0; i--)
    {
        int temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;

        heapify(vetor, i, 0, crescente);
    }
}


void vetorAleatorio(int inc, int fim, int stp, int rpt)
{
    // Imprimir rótulo [[RANDOM]]
    printf("[[RANDOM]]\n");

    // Imprimir cabeçalhos
    printf("n\tBubble\t\tInsertion\tMerge\t\tHeap\t\tQuick\t\tCounting\n");

    for (int n = inc; n <= fim; n += stp)
    {
        double totalBubble = 0, totalInsertion = 0, totalMerge = 0;
        double totalHeap = 0, totalQuick = 0, totalCounting = 0;

        for (int i = 0; i < rpt; i++)
        {
            int *vetor = new int[n];       // Aloca o vetor com tamanho n
            criarVetorAleatorio(vetor, n); // Função que gera os vetores aleatórios

            // Medir o tempo do insertionSort
            struct timeval start, end;
            gettimeofday(&start, NULL);
            insertionSort(vetor, n, true);
            gettimeofday(&end, NULL);
            totalInsertion += time_val(&start, &end);

            // // Medir o tempo do BubbleSort
            gettimeofday(&start, NULL);
            bubbleSort(vetor, n, true);
            gettimeofday(&end, NULL);
            totalBubble += time_val(&start, &end);

            // // Medir o tempo do MergeSort
            gettimeofday(&start, NULL);
            mergeSort(vetor, 0, n - 1, true);
            gettimeofday(&end, NULL);
            totalMerge += time_val(&start, &end);

            // // Medir o tempo do HeapSort
            gettimeofday(&start, NULL);
            heapSort(vetor, n, true);
            gettimeofday(&end, NULL);
            totalHeap += time_val(&start, &end);

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

/*Vetor reverso: cada conjunto de entrada A deve conter números inteiros não negativos escolhidos (pseudo)aleatoriamente e arranjados em ordem decrescente. Um tal conjunto de
números A deve ter n números. Os valores de n variam, para cada conjunto construído, de
acordo com os parâmetros inc (valor inicial), fim (valor final) e stp (intervalo entre dois
tamanhos), assim como descrito no caso anterior (vetor aleatório).
Para cada caso de teste, você deve executar os seis algoritmos mencionados na seção 1 para
ordenar esse conjunto A de n números inteiros. Neste caso, não é necessário repetir a execução dos algoritmos, isto é, cada caso de teste é executado uma única vez, obtendo então
os tempos medidos.
A saída deste experimento consiste de uma primeira linha contendo o rótulo [[REVERSE]],
especificando o conjunto de dados sendo usado, uma segunda linha contendo os rótulos da
quantidade de elementos n e a identificação de cada um dos algoritmos. Cada linha a seguir
contém o valor da quantidade de elementos n de um caso de teste e os tempos gastos da
execução de cada algoritmo.
*/
void vetorReverso(int inc, int fim, int stp, int rpt)
{
    printf("\n");
    // Imprimir rótulo [[REVERSE]]
    printf("[[REVERSE]]\n");

    // Imprimir cabeçalhos
    printf("n\tBubble\t\tInsertion\tMerge\t\tHeap\t\tQuick\t\tCounting\n");

    for (int n = inc; n <= fim; n += stp)
    {
        double totalBubble = 0, totalInsertion = 0, totalMerge = 0;
        double totalHeap = 0, totalQuick = 0, totalCounting = 0;

        for (int i = 0; i < rpt; i++)
        {
            int *vetor = new int[n];       // Aloca o vetor com tamanho n
            criarVetorAleatorio(vetor, n); // Função que gera os vetores aleatórios

            // Medir o tempo do insertionSort
            struct timeval start, end;
            gettimeofday(&start, NULL);
            insertionSort(vetor, n, false);
            gettimeofday(&end, NULL);
            totalInsertion += time_val(&start, &end);

            // // Medir o tempo do BubbleSort
            gettimeofday(&start, NULL);
            bubbleSort(vetor, n, false);
            gettimeofday(&end, NULL);
            totalBubble += time_val(&start, &end);

            // // Medir o tempo do MergeSort
            gettimeofday(&start, NULL);
            mergeSort(vetor, 0, n - 1, false);
            gettimeofday(&end, NULL);
            totalMerge += time_val(&start, &end);

            // // Medir o tempo do HeapSort
            gettimeofday(&start, NULL);
            heapSort(vetor, n, false);
            gettimeofday(&end, NULL);
            totalHeap += time_val(&start, &end);

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

void vetorOrdenado(int inc, int fim, int stp, int rpt)
{
    // Imprimir rótulo [[SORTED]]
    printf("[[SORTED]]\n");

    // Imprimir cabeçalhos
    printf("n\tBubble\t\tInsertion\tMerge\t\tHeap\t\tQuick\t\tCounting\n");

    for (int n = inc; n <= fim; n += stp)
    {
        double totalBubble = 0, totalInsertion = 0, totalMerge = 0;
        double totalHeap = 0, totalQuick = 0, totalCounting = 0;

        for (int i = 0; i < rpt; i++)
        {
            int *vetor = new int[n];       // Aloca o vetor com tamanho n
            criarVetorAleatorio(vetor, n); // Função que gera os vetores aleatórios

            // Medir o tempo do insertionSort
            struct timeval start, end;
            insertionSort(vetor, n, true);
            gettimeofday(&start, NULL);
            insertionSort(vetor, n, true);
            gettimeofday(&end, NULL);
            totalInsertion += time_val(&start, &end);

            // // Medir o tempo do BubbleSort
            bubbleSort(vetor, n, true);
            gettimeofday(&start, NULL);
            bubbleSort(vetor, n, true);
            gettimeofday(&end, NULL);
            totalBubble += time_val(&start, &end);

            // // Medir o tempo do MergeSort
            mergeSort(vetor, 0, n - 1, true);
            gettimeofday(&start, NULL);
            mergeSort(vetor, 0, n - 1, true);
            gettimeofday(&end, NULL);
            totalMerge += time_val(&start, &end);

            // // Medir o tempo do HeapSort
            heapSort(vetor, n, true);
            gettimeofday(&start, NULL);
            heapSort(vetor, n, true);
            gettimeofday(&end, NULL);
            totalHeap += time_val(&start, &end);

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