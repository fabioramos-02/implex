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
int *criarVetorAleatorio(int n)
{
    srand(time(0)); // Seed para números aleatórios
    int *vet = new int[n];
    for (int i = 0; i < n; i++)
    {
        vet[i] = rand() % (n * n); // 0 a n^2
    }
    return vet;
}

// Função que devolve um vetor em ordem reversa (decrescente) ou ordenado (crescente)
int *preencherVet(int n, bool crescente)
{
    int *vet = new int[n];
    if (crescente)
    {
        for (int i = 0; i < n; i++)
        {
            vet[i] = i + 1; // Preenche com 1, 2, 3, ..., n
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            vet[i] = n - i; // Preenche com n, n-1, n-2, ..., 1
        }
    }
    return vet;
}


// funcao que cria uma copia do vetor
int *criarCopiaVetor(int *vet, int n)
{

    int *copia = new int[n];
    for (int i = 0; i < n; i++)
    {
        copia[i] = vet[i];
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

// Função para reorganizar uma parte do vetor em um heap máximo
void heapify(int *vetor, int tamanho, int i, bool crescente)
{
    int maiorMenor = i;       // Inicializa maiorMenor como raiz
    int esquerda = 2 * i + 1; // filho à esquerda = 2*i + 1
    int direita = 2 * i + 2;  // filho à direita = 2*i + 2

    // Se o filho à esquerda for maior/menor que a raiz
    if (crescente)
    {
        if (esquerda < tamanho && vetor[esquerda] > vetor[maiorMenor])
            maiorMenor = esquerda;

        // Se o filho à direita for maior/menor que o maior/menor até agora
        if (direita < tamanho && vetor[direita] > vetor[maiorMenor])
            maiorMenor = direita;
    }
    else
    {
        if (esquerda < tamanho && vetor[esquerda] < vetor[maiorMenor])
            maiorMenor = esquerda;

        // Se o filho à direita for maior/menor que o maior/menor até agora
        if (direita < tamanho && vetor[direita] < vetor[maiorMenor])
            maiorMenor = direita;
    }

    // Se o maior/menor não for a raiz
    if (maiorMenor != i)
    {
        std::swap(vetor[i], vetor[maiorMenor]);

        // Recursivamente heapifica a subárvore afetada
        heapify(vetor, tamanho, maiorMenor, crescente);
    }
}

// Função principal do HeapSort
void heapSort(int *vetor, int tamanho, bool crescente)
{
    // Constrói o heap (rearranja o vetor)
    for (int i = tamanho / 2 - 1; i >= 0; i--)
        heapify(vetor, tamanho, i, crescente);

    // Extrai um por um os elementos do heap
    for (int i = tamanho - 1; i >= 0; i--)
    {
        // Move a raiz atual para o final
        std::swap(vetor[0], vetor[i]);

        // Chama o heapify na heap reduzida
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
    if (tamanho <= 0)
        return;

    // Encontrar o valor máximo no array para determinar o tamanho do vetor de contagem
    int max_val = *std::max_element(vetor, vetor + tamanho);

    // Criar um array de contagem inicializado com zero
    int *count = new int[max_val + 1]{0};

    // Contar a ocorrência de cada elemento
    for (int i = 0; i < tamanho; i++)
        count[vetor[i]]++;

    // Modificar o array de contagem para armazenar as posições finais de cada elemento
    if (crescente)
    {
        for (int i = 1; i <= max_val; i++)
            count[i] += count[i - 1];
    }
    else
    {
        for (int i = max_val - 1; i >= 0; i--)
            count[i] += count[i + 1];
    }

    // Criar um array de saída para os elementos ordenados
    int *output = new int[tamanho];

    // Construir o array de saída
    for (int i = tamanho - 1; i >= 0; i--)
    {
        output[count[vetor[i]] - 1] = vetor[i];
        count[vetor[i]]--;
    }

    // Copiar os elementos ordenados de volta para o array original
    for (int i = 0; i < tamanho; i++)
        vetor[i] = output[i];

    // Liberar a memória alocada
    delete[] count;
    delete[] output;
}

void quaseOrdenado(int *vetor, int n)
{
    int qtd = n * 0.1; // 10% do vetor
    for (int i = 0; i < qtd; i++)
    {
        int pos1 = rand() % n;
        int pos2 = rand() % n;
        std::swap(vetor[pos1], vetor[pos2]);
    }
}
void imprimir(int n, float timeBubble, float timeInsertion, float timeMerge, float timeHeap, float timeQuick, float timeCounting)
{
    // Imprimir os resultados
    printf("%d\t%f\t%f\t%f\t%f\t%f\t%f\n",
           n,
           timeBubble,
           timeInsertion,
           timeMerge,
           timeHeap,
           timeQuick,
           timeCounting);
}

float medirTempoOrdenacao(void (*sortFunc)(int *, int, bool), int *vetor, int tamanho, bool crescente)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    sortFunc(vetor, tamanho, crescente);
    gettimeofday(&end, NULL);
    return time_val(&start, &end);
}

void mergeSortWrapper(int *vetor, int tamanho, bool crescente)
{
    mergeSort(vetor, 0, tamanho - 1, crescente);
}

void quickSortWrapper(int *vetor, int tamanho, bool crescente)
{
    quickSort(vetor, 0, tamanho - 1, crescente);
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
        float totalTimes[6] = {0};

        for (int i = 0; i < rpt; i++)
        {
            int *vetor = criarVetorAleatorio(n);
            int *copia;

            // // Medir o tempo do BubbleSort
            copia = criarCopiaVetor(vetor, n);
            totalTimes[0] += medirTempoOrdenacao(bubbleSort, copia, n, true);

            // Medir o tempo do insertionSort
            copia = criarCopiaVetor(vetor, n);
            totalTimes[1] += medirTempoOrdenacao(insertionSort, copia, n, true);

            // // Medir o tempo do MergeSort
            copia = criarCopiaVetor(vetor, n);
            totalTimes[2] += medirTempoOrdenacao(mergeSortWrapper, copia, n, true);

            // // Medir o tempo do HeapSort
            copia = criarCopiaVetor(vetor, n);
            totalTimes[3] += medirTempoOrdenacao(heapSort, copia, n, true);

            // // Medir o tempo do QuickSort
            copia = criarCopiaVetor(vetor, n);
            totalTimes[4] += medirTempoOrdenacao(quickSortWrapper, copia, n, true);

            // // Medir o tempo do CountingSort
            copia = criarCopiaVetor(vetor, n);
            totalTimes[5] += medirTempoOrdenacao(countingSort, copia, n, true);

            delete[] vetor;
            delete[] copia;
        }
        // calcular a media dos tempos
        for (int j = 0; j < 6; j++)
        {
            totalTimes[j] /= rpt;
        }

        // salvar no arquivo csv
        salvarDados(n, totalTimes[0], totalTimes[1], totalTimes[2], totalTimes[3], totalTimes[4], totalTimes[5], "vetor_aleatorio.csv");

        // imprimir tupla da tabela
        imprimir(n, totalTimes[0], totalTimes[1], totalTimes[2], totalTimes[3], totalTimes[4], totalTimes[5]);
    }
}

void vetorReverso(int inc, int fim, int stp)
{
    FILE *arq = fopen("vetor_reverso.csv", "w");
    fclose(arq);

    // Imprimir cabeçalhos
    printf("\n[[REVERSE]]\n");
    printf("n\tBubble\t\tInsertion\tMerge\t\tHeap\t\tQuick\t\tCounting\n");
    printf("------------------------------------------------------------------------------------------------\n");

    for (int n = inc; n <= fim; n += stp)
    {
        int *vetor = preencherVet(n, false);
        countingSort(vetor, n, false);
        int *copia;
        float totalTimes[6] = {0};

        // Medir o tempo dos algoritmos de ordenação
        // BubbleSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[0] = medirTempoOrdenacao(bubbleSort, copia, n, true);
        // InsertionSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[1] = medirTempoOrdenacao(insertionSort, copia, n, true);
        // MergeSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[2] = medirTempoOrdenacao(mergeSortWrapper, copia, n, true);
        // HeapSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[3] = medirTempoOrdenacao(heapSort, copia, n, true);
        // QuickSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[4] = medirTempoOrdenacao(quickSortWrapper, copia, n, true);
        // CountingSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[5] = medirTempoOrdenacao(countingSort, copia, n, true);

        delete[] vetor;
        delete[] copia;

        // salvar no arquivo csv
        salvarDados(n, totalTimes[0], totalTimes[1], totalTimes[2], totalTimes[3], totalTimes[4], totalTimes[5], "vetor_reverso.csv");

        imprimir(n, totalTimes[0], totalTimes[1], totalTimes[2], totalTimes[3], totalTimes[4], totalTimes[5]);
    }
}

void vetorOrdenado(int inc, int fim, int stp)
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
        int *vetor = preencherVet(n, true);
        countingSort(vetor, n, true);
        int *copia;
        float totalTimes[6] = {0};

        // Medir o tempo dos algoritmos de ordenação
        // BubbleSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[0] = medirTempoOrdenacao(bubbleSort, copia, n, true);
        // InsertionSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[1] = medirTempoOrdenacao(insertionSort, copia, n, true);
        // MergeSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[2] = medirTempoOrdenacao(mergeSortWrapper, copia, n, true);
        // HeapSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[3] = medirTempoOrdenacao(heapSort, copia, n, true);
        // QuickSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[4] = medirTempoOrdenacao(quickSortWrapper, copia, n, true);
        // CountingSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[5] = medirTempoOrdenacao(countingSort, copia, n, true);

        delete[] vetor;
        delete[] copia;

        // salvar no arquivo csv
        salvarDados(n, totalTimes[0], totalTimes[1], totalTimes[2], totalTimes[3], totalTimes[4], totalTimes[5], "vetor_ordenado.csv");

        // imprimir tupla da tabela
        imprimir(n, totalTimes[0], totalTimes[1], totalTimes[2], totalTimes[3], totalTimes[4], totalTimes[5]);
    }
}

void vetorQuaseOrdenado(int inc, int fim, int stp)
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
        int *vetor = criarVetorAleatorio(n);
        countingSort(vetor, n, true);
        quaseOrdenado(vetor, n);
        int *copia;
        float totalTimes[6] = {0};

    
        // Medir o tempo dos algoritmos de ordenação
        // BubbleSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[0] = medirTempoOrdenacao(bubbleSort, copia, n, true);
        // InsertionSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[1] = medirTempoOrdenacao(insertionSort, copia, n, true);
        // MergeSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[2] = medirTempoOrdenacao(mergeSortWrapper, copia, n, true);
        // HeapSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[3] = medirTempoOrdenacao(heapSort, copia, n, true);
        // QuickSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[4] = medirTempoOrdenacao(quickSortWrapper, copia, n, true);
        // CountingSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[5] = medirTempoOrdenacao(countingSort, copia, n, true);

        delete[] vetor;
        delete[] copia;

        // salvar no arquivo csv
        salvarDados(n, totalTimes[0], totalTimes[1], totalTimes[2], totalTimes[3], totalTimes[4], totalTimes[5], "vetor_quaseOrdenado.csv");

        // imprimir tupla da tabela
        imprimir(n, totalTimes[0], totalTimes[1], totalTimes[2], totalTimes[3], totalTimes[4], totalTimes[5]);
    }
}