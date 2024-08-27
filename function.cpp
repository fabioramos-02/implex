#include "lib.h"

void salvarDados(int n, float totalBubble, float totalInsertion, float totalMerge, float totalHeap, float totalQuick, float totalCounting, const char *nomeArquivo)
{
    FILE *arq;
    arq = fopen(nomeArquivo, "a");
    fprintf(arq, "%d;%f;%f;%f;%f;%f;%f\n",
            n,
            totalBubble,
            totalInsertion,
            totalMerge,
            totalHeap,
            totalQuick,
            totalCounting);
    fclose(arq);
}

// Função para calcular o tempo decorrido
float time_val(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6 * (end->tv_usec - start->tv_usec);
}

// funcao que devolve vetor aleatorio para vector
std::vector<int> criarVetorAleatorio(int n)
{
    std::vector<int> vet(n);
    for (int i = 0; i < n; i++)
    {
        vet[i] = rand();
    }
    return vet;
}

// funcao que cria uma copia do vetor
int *criarCopiaVetor(const std::vector<int> &vetor)
{
    int n = vetor.size();
    int *copia = new int[n];
    for (int i = 0; i < n; i++)
    {
        copia[i] = vetor[i];
    }
    return copia;
}

// Função para ordenar um vetor de inteiros em ordem crescente ou decrescente
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

    int i = 0;    // Índice inicial do primeiro subarray
    int j = 0;    // Índice inicial do segundo subarray
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

void heapify(int *vetor, int tamanho, int i, bool crescente)
{
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
// funcao particionar
int particionar(int *vetor, int inicio, int fim, bool crescente)
{
    int pivo = vetor[fim];
    int m = inicio - 1;

    for (int i = inicio; i < fim; i++)
    {
        if (crescente)
        {
            if (vetor[i] <= pivo)
            {
                m++;
                std::swap(vetor[m], vetor[i]);
            }
        }
        else
        {
            if (vetor[i] >= pivo)
            {
                m++;
                std::swap(vetor[m], vetor[i]);
            }
        }
    }
    std::swap(vetor[m + 1], vetor[fim]);
    return m + 1;
}
void quickSort(int *vetor, int inicio, int fim, bool crescente)
{
    if (inicio < fim)
    {
        int p = particionar(vetor, inicio, fim, crescente);
        quickSort(vetor, inicio, p - 1, crescente);
        quickSort(vetor, p + 1, fim, crescente);
    }
}

void countingSort(int *vetor, int tamanho, bool crescente)
{
    int maior = vetor[0];
    for (int i = 1; i < tamanho; i++)
    {
        if (vetor[i] > maior)
            maior = vetor[i];
    }

    int *count = new int[maior + 1];
    int *output = new int[tamanho];

    for (int i = 0; i <= maior; i++)
        count[i] = 0;

    for (int i = 0; i < tamanho; i++)
        count[vetor[i]]++;

    for (int i = 1; i <= maior; i++)
        count[i] += count[i - 1];

    if (crescente)
    {
        // Preenche o vetor de saída para ordenação crescente
        for (int i = tamanho - 1; i >= 0; i--)
        {
            output[count[vetor[i]] - 1] = vetor[i];
            count[vetor[i]]--;
        }
    }
    else
    {
        // Preenche o vetor de saída para ordenação decrescente
        for (int i = 0; i < tamanho; i++)
        {
            output[tamanho - count[vetor[i]]] = vetor[i];
            count[vetor[i]]--;
        }
    }

    for (int i = 0; i < tamanho; i++)
        vetor[i] = output[i];

    delete[] count;
    delete[] output;
}

void quaseOrdenado(std::vector<int> &vetor, int n)
{
    int qtd = n * 0.1; // 10% do vetor
    for (int i = 0; i < qtd; i++)
    {
        int pos1 = rand() % n;
        int pos2 = rand() % n;
        std::swap(vetor[pos1], vetor[pos2]);
    }
}

void vetorAleatorio(int inc, int fim, int stp, int rpt)
{
    FILE *arq = fopen("vetor_aleatorio.csv", "w");
    fclose(arq);

    // Imprimir cabeçalhos
    printf("[[RANDOM]]\n");
    printf("n\tBubble\t\tInsertion\tMerge\t\tHeap\t\tQuick\t\tCounting\n");
    printf("------------------------------------------------------------------------------------------------\n");

    // exportar dados do tempo de execucao dos algoritmos em formato csv
    // sempre apagando os dados antigos e escrevendo novos

    for (int n = inc; n <= fim; n += stp)
    {
        double totalBubble = 0, totalInsertion = 0, totalMerge = 0;
        double totalHeap = 0, totalQuick = 0, totalCounting = 0;

        for (int i = 0; i < rpt; i++)
        {
            std::vector<int> vetor = criarVetorAleatorio(n);
            int *vetBubble = criarCopiaVetor(vetor);
            int *vetInsertion = criarCopiaVetor(vetor);
            int *vetMerge = criarCopiaVetor(vetor);
            int *vetHeap = criarCopiaVetor(vetor);
            int *vetQuick = criarCopiaVetor(vetor);
            int *vetCounting = criarCopiaVetor(vetor);

            // Medir o tempo do insertionSort
            struct timeval start, end;
            gettimeofday(&start, NULL);
            insertionSort(vetInsertion, n, true);
            gettimeofday(&end, NULL);
            totalInsertion += time_val(&start, &end);

            // // Medir o tempo do BubbleSort
            gettimeofday(&start, NULL);
            bubbleSort(vetBubble, n, true);
            gettimeofday(&end, NULL);
            totalBubble += time_val(&start, &end);

            // // Medir o tempo do MergeSort
            gettimeofday(&start, NULL);
            mergeSort(vetMerge, 0, n - 1, true);
            gettimeofday(&end, NULL);
            totalMerge += time_val(&start, &end);

            // // Medir o tempo do HeapSort
            gettimeofday(&start, NULL);
            heapSort(vetHeap, n, true);
            gettimeofday(&end, NULL);
            totalHeap += time_val(&start, &end);

            // // Medir o tempo do QuickSort
            gettimeofday(&start, NULL);
            quickSort(vetQuick, 0, n - 1, true);
            gettimeofday(&end, NULL);
            totalQuick += time_val(&start, &end);

            // // Medir o tempo do CountingSort
            gettimeofday(&start, NULL);
            countingSort(vetCounting, n, true);
            gettimeofday(&end, NULL);
            totalCounting += time_val(&start, &end);

            delete[] vetBubble;
            delete[] vetInsertion;
            delete[] vetMerge;
            delete[] vetHeap;
            delete[] vetQuick;
            delete[] vetCounting;
        }

        // salvar no arquivo csv
        salvarDados(n, totalBubble / rpt, totalInsertion / rpt, totalMerge / rpt, totalHeap / rpt, totalQuick / rpt, totalCounting / rpt, "vetor_aleatorio.csv");

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

void vetorReverso(int inc, int fim, int stp, int rpt)
{
    FILE *arq = fopen("vetor_reverso.csv", "w");
    fclose(arq);

    // Imprimir cabeçalhos
    printf("\n[[REVERSE]]\n");
    printf("n\tBubble\t\tInsertion\tMerge\t\tHeap\t\tQuick\t\tCounting\n");
    printf("------------------------------------------------------------------------------------------------\n");

    for (int n = inc; n <= fim; n += stp)
    {
        double totalBubble = 0, totalInsertion = 0, totalMerge = 0;
        double totalHeap = 0, totalQuick = 0, totalCounting = 0;

        for (int i = 0; i < rpt; i++)
        {
            std::vector<int> vetor = criarVetorAleatorio(n);
            int *vetBubble = criarCopiaVetor(vetor);
            int *vetInsertion = criarCopiaVetor(vetor);
            int *vetMerge = criarCopiaVetor(vetor);
            int *vetHeap = criarCopiaVetor(vetor);
            int *vetQuick = criarCopiaVetor(vetor);
            int *vetCounting = criarCopiaVetor(vetor);

            struct timeval start, end; // Estrutura para medir o tempo

            // // Medir o tempo do BubbleSort
            gettimeofday(&start, NULL);
            bubbleSort(vetBubble, n, false);
            gettimeofday(&end, NULL);
            totalBubble += time_val(&start, &end);

            // Medir o tempo do insertionSort
            gettimeofday(&start, NULL);
            insertionSort(vetInsertion, n, false);
            gettimeofday(&end, NULL);
            totalInsertion += time_val(&start, &end);

            // // Medir o tempo do MergeSort
            gettimeofday(&start, NULL);
            mergeSort(vetMerge, 0, n - 1, false);
            gettimeofday(&end, NULL);
            totalMerge += time_val(&start, &end);

            // // Medir o tempo do HeapSort
            gettimeofday(&start, NULL);
            heapSort(vetHeap, n, false);
            gettimeofday(&end, NULL);
            totalHeap += time_val(&start, &end);

            // // Medir o tempo do QuickSort
            gettimeofday(&start, NULL);
            quickSort(vetQuick, 0, n - 1, false);
            gettimeofday(&end, NULL);
            totalQuick += time_val(&start, &end);

            // // Medir o tempo do CountingSort
            gettimeofday(&start, NULL);
            countingSort(vetCounting, n, false);
            gettimeofday(&end, NULL);
            totalCounting += time_val(&start, &end);

            delete[] vetBubble;
            delete[] vetInsertion;
            delete[] vetMerge;
            delete[] vetHeap;
            delete[] vetQuick;
            delete[] vetCounting;
        }
        // salvar no arquivo csv
        salvarDados(n, totalBubble / rpt, totalInsertion / rpt, totalMerge / rpt, totalHeap / rpt, totalQuick / rpt, totalCounting / rpt, "vetor_reverso.csv");

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
    FILE *arq = fopen("vetor_ordenado.csv", "w");
    fclose(arq);

    // Imprimir cabeçalhos
    printf("\n[[SORTED]]\n");
    printf("n\tBubble\t\tInsertion\tMerge\t\tHeap\t\tQuick\t\tCounting\n");
    printf("------------------------------------------------------------------------------------------------\n");

    // exportar dados do tempo de execucao dos algoritmos em formato csv

    for (int n = inc; n <= fim; n += stp)
    {
        double totalBubble = 0, totalInsertion = 0, totalMerge = 0;
        double totalHeap = 0, totalQuick = 0, totalCounting = 0;

        for (int i = 0; i < rpt; i++)
        {
            std::vector<int> vetor = criarVetorAleatorio(n);
            int *vetBubble = criarCopiaVetor(vetor);
            int *vetInsertion = criarCopiaVetor(vetor);
            int *vetMerge = criarCopiaVetor(vetor);
            int *vetHeap = criarCopiaVetor(vetor);
            int *vetQuick = criarCopiaVetor(vetor);
            int *vetCounting = criarCopiaVetor(vetor);

            struct timeval start, end; // Estrutura para medir o tempo

            // // Medir o tempo do BubbleSort
            bubbleSort(vetBubble, n, true);
            gettimeofday(&start, NULL);
            bubbleSort(vetBubble, n, true);
            gettimeofday(&end, NULL);
            totalBubble += time_val(&start, &end);

            // Medir o tempo do insertionSort
            insertionSort(vetInsertion, n, true);
            gettimeofday(&start, NULL);
            insertionSort(vetInsertion, n, true);
            gettimeofday(&end, NULL);
            totalInsertion += time_val(&start, &end);

            // // Medir o tempo do MergeSort
            mergeSort(vetMerge, 0, n - 1, true);
            gettimeofday(&start, NULL);
            mergeSort(vetMerge, 0, n - 1, true);
            gettimeofday(&end, NULL);
            totalMerge += time_val(&start, &end);

            // // Medir o tempo do HeapSort
            heapSort(vetHeap, n, true);
            gettimeofday(&start, NULL);
            heapSort(vetHeap, n, true);
            gettimeofday(&end, NULL);
            totalHeap += time_val(&start, &end);

            // // Medir o tempo do QuickSort
            quickSort(vetQuick, 0, n - 1, true);
            gettimeofday(&start, NULL);
            quickSort(vetQuick, 0, n-1, true);
            gettimeofday(&end, NULL);
            totalQuick += time_val(&start, &end);


            // // Medir o tempo do CountingSort
            countingSort(vetCounting, n, true);
            gettimeofday(&start, NULL);
            countingSort(vetCounting, n, true);
            gettimeofday(&end, NULL);
            totalCounting += time_val(&start, &end);

            delete[] vetBubble;
            delete[] vetInsertion;
            delete[] vetMerge;
            delete[] vetHeap;
            delete[] vetQuick;
            delete[] vetCounting;
        }

        // salvar no arquivo csv
        salvarDados(n, totalBubble / rpt, totalInsertion / rpt, totalMerge / rpt, totalHeap / rpt, totalQuick / rpt, totalCounting / rpt, "vetor_ordenado.csv");

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

void vetorQuaseOrdenado(int inc, int fim, int stp, int rpt)
{
    FILE *arq = fopen("vetor_quaseOrdenado.csv", "w");
    fclose(arq);

    // Imprimir cabeçalhos
    printf("\n[[[NEARLY SORTED]]\n");
    printf("n\tBubble\t\tInsertion\tMerge\t\tHeap\t\tQuick\t\tCounting\n");
    printf("------------------------------------------------------------------------------------------------\n");

    // exportar dados do tempo de execucao dos algoritmos em formato csv

    for (int n = inc; n <= fim; n += stp)
    {
        double totalBubble = 0, totalInsertion = 0, totalMerge = 0;
        double totalHeap = 0, totalQuick = 0, totalCounting = 0;

        for (int i = 0; i < rpt; i++)
        {
            std::vector<int> vetor = criarVetorAleatorio(n);
            countingSort(vetor.data(), n, true);
            quaseOrdenado(vetor, n);
            int *vetBubble = criarCopiaVetor(vetor);
            int *vetInsertion = criarCopiaVetor(vetor);
            int *vetMerge = criarCopiaVetor(vetor);
            int *vetHeap = criarCopiaVetor(vetor);
            int *vetQuick = criarCopiaVetor(vetor);
            int *vetCounting = criarCopiaVetor(vetor);

            

            struct timeval start, end; // Estrutura para medir o tempo

            // // Medir o tempo do BubbleSort
            gettimeofday(&start, NULL);
            bubbleSort(vetBubble, n, true);
            gettimeofday(&end, NULL);
            totalBubble += time_val(&start, &end);

            // Medir o tempo do insertionSort
            gettimeofday(&start, NULL);
            insertionSort(vetInsertion, n, true);
            gettimeofday(&end, NULL);
            totalInsertion += time_val(&start, &end);

            // // Medir o tempo do MergeSort
            gettimeofday(&start, NULL);
            mergeSort(vetMerge, 0, n - 1, true);
            gettimeofday(&end, NULL);
            totalMerge += time_val(&start, &end);

            // // Medir o tempo do HeapSort
            gettimeofday(&start, NULL);
            heapSort(vetHeap, n, true);
            gettimeofday(&end, NULL);
            totalHeap += time_val(&start, &end);

            // // Medir o tempo do QuickSort
            gettimeofday(&start, NULL);
            quickSort(vetQuick, 0, n - 1, true);
            gettimeofday(&end, NULL);
            totalQuick += time_val(&start, &end);

            // // Medir o tempo do CountingSort
            gettimeofday(&start, NULL);
            countingSort(vetCounting, n, true);
            gettimeofday(&end, NULL);
            totalCounting += time_val(&start, &end);

            delete[] vetBubble;
            delete[] vetInsertion;
            delete[] vetMerge;
            delete[] vetHeap;
            delete[] vetQuick;
            delete[] vetCounting;
        }

        // salvar no arquivo csv
        salvarDados(n, totalBubble / rpt, totalInsertion / rpt, totalMerge / rpt, totalHeap / rpt, totalQuick / rpt, totalCounting / rpt, "vetor_quaseOrdenado.csv");

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