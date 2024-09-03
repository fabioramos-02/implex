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


// funcao que devolve vetor aleatorio para vector que varia de 0  a n²
int *criarVetorAleatorio(int n){
    int *vet = new int[n];
    for (int i = 0; i < n; i++)
    {
        vet[i] = rand() % (n * n);
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
void insertionSort(int *vetor, int tamanho){
    int chave, j;
    for (int i = 1; i < tamanho; i++)
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

void bubbleSort(int *vetor, int tamanho){
    for (int i = 0; i < tamanho - 1; i++)
    {
        for (int j = 0; j < tamanho - i - 1; j++)
        {
            if (vetor[j] > vetor[j + 1])
            {
                std::swap(vetor[j], vetor[j + 1]);
            }
        }
    }
}

void merge(int *vetor, int left, int mid, int right){
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Vetores temporários
    int L[n1], R[n2];

    // Copia os dados para os vetores temporários L[] e R[]
    for (i = 0; i < n1; i++)
        L[i] = vetor[left + i];
    for (j = 0; j < n2; j++)
        R[j] = vetor[mid + 1 + j];

    // Merge dos vetores temporários de volta para vetor[left..right]
    i = 0; // Índice inicial do primeiro subvetor
    j = 0; // Índice inicial do segundo subvetor
    k = left; // Índice inicial do subvetor fundido
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

    // Copia os elementos restantes de L[], se houver
    while (i < n1)
    {
        vetor[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2)
    {
        vetor[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *vetor, int left, int right){
    if (left < right)
    {
        // O mesmo que (l+r)/2, mas evita overflow para grandes l e r
        int mid = left + (right - left) / 2;

        // Ordena a primeira e a segunda metade
        mergeSort(vetor, left, mid);
        mergeSort(vetor, mid + 1, right);

        merge(vetor, left, mid, right);
    }
}
// Função para reorganizar uma parte do vetor em um heap máximo
void heapify(int *vetor, int tamanho, int i){
    int maior = i; // Inicializa o maior como raiz
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    // Se o filho esquerdo é maior que a raiz
    if (esq < tamanho && vetor[esq] > vetor[maior])
        maior = esq;

    // Se o filho direito é maior que o maior até agora
    if (dir < tamanho && vetor[dir] > vetor[maior])
        maior = dir;

    // Se o maior não é a raiz
    if (maior != i)
    {
        std::swap(vetor[i], vetor[maior]);

        // Recursivamente heapify a subárvore afetada
        heapify(vetor, tamanho, maior);
    }
}

// Função principal do HeapSort
void heapSort(int *vetor, int tamanho){
    for (int i = tamanho / 2 - 1; i >= 0; i--)
        heapify(vetor, tamanho, i);

    // Extrai um por um os elementos do heap
    for (int i = tamanho - 1; i > 0; i--)
    {
        // Move a raiz atual para o final
        std::swap(vetor[0], vetor[i]);

        // Chama o heapify na heap reduzida
        heapify(vetor, i, 0);
    }
}
// funcao particionar
int particionar(int *vetor, int inicio, int fim){
    int pivo = vetor[fim];
    int i = inicio - 1;
    for (int j = inicio; j < fim; j++)
    {
        if (vetor[j] < pivo)
        {
            i++;
            std::swap(vetor[i], vetor[j]);
        }
    }
    std::swap(vetor[i + 1], vetor[fim]);
    return i + 1;
}
void quickSort(int *vetor, int inicio, int fim)
{
    if (inicio < fim)
    {
        int p = particionar(vetor, inicio, fim);
        quickSort(vetor, inicio, p - 1);
        quickSort(vetor, p + 1, fim);
    }
}

void countingSort(int *vetor, int tamanho){
    int maior = vetor[0];
    for (int i = 1; i < tamanho; i++)
    {
        if (vetor[i] > maior)
        {
            maior = vetor[i];
        }
    }
    int *copia = new int[maior + 1];
    for (int i = 0; i < maior + 1; i++)
    {
        copia[i] = 0;
    }
    for (int i = 0; i < tamanho; i++)
    {
        copia[vetor[i]]++;
    }
    int j = 0;
    for (int i = 0; i < maior + 1; i++)
    {
        while (copia[i] > 0)
        {
            vetor[j] = i;
            j++;
            copia[i]--;
        }
    }
    delete[] copia;
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

float medirTempoOrdenacao(void (*sortFunc)(int *, int), int *vetor, int tamanho)
{
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(vetor, tamanho);
    auto end = std::chrono::high_resolution_clock::now();

    // Captura o tempo em microsegundos
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Converte para segundos como ponto flutuante
    return duration.count() / 1e6;
}

void mergeSortWrapper(int *vetor, int tamanho)
{
    mergeSort(vetor, 0, tamanho - 1);
}

void quickSortWrapper(int *vetor, int tamanho)
{
    quickSort(vetor, 0, tamanho - 1);
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
            totalTimes[0] += medirTempoOrdenacao(bubbleSort, copia, n);
            delete[] copia;


            // Medir o tempo do insertionSort
            copia = criarCopiaVetor(vetor, n);
            totalTimes[1] += medirTempoOrdenacao(insertionSort, copia, n);
            delete[] copia;


            // // Medir o tempo do MergeSort
            copia = criarCopiaVetor(vetor, n);
            totalTimes[2] += medirTempoOrdenacao(mergeSortWrapper, copia, n);
            delete[] copia;


            // // Medir o tempo do HeapSort
            copia = criarCopiaVetor(vetor, n);
            totalTimes[3] += medirTempoOrdenacao(heapSort, copia, n);
            delete[] copia;


            // // Medir o tempo do QuickSort
            copia = criarCopiaVetor(vetor, n);
            totalTimes[4] += medirTempoOrdenacao(quickSortWrapper, copia, n);
            delete[] copia;


            // // Medir o tempo do CountingSort
            copia = criarCopiaVetor(vetor, n);
            totalTimes[5] += medirTempoOrdenacao(countingSort, copia, n);
            delete[] copia;


            delete[] vetor;
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
        int *copia;
        float totalTimes[6] = {0};

         // Medir o tempo dos algoritmos de ordenação
        // BubbleSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[0] = medirTempoOrdenacao(bubbleSort, copia, n);
        delete[] copia;

        // InsertionSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[1] = medirTempoOrdenacao(insertionSort, copia, n);
        delete[] copia;

        // MergeSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[2] = medirTempoOrdenacao(mergeSortWrapper, copia, n);
        delete[] copia;

        // HeapSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[3] = medirTempoOrdenacao(heapSort, copia, n);
        delete[] copia;

        // QuickSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[4] = medirTempoOrdenacao(quickSortWrapper, copia, n);
        delete[] copia;

        // CountingSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[5] = medirTempoOrdenacao(countingSort, copia, n);

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
        int *copia;
        float totalTimes[6] = {0};

          // Medir o tempo dos algoritmos de ordenação
        // BubbleSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[0] = medirTempoOrdenacao(bubbleSort, copia, n);
        delete[] copia;

        // InsertionSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[1] = medirTempoOrdenacao(insertionSort, copia, n);
        delete[] copia;

        // MergeSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[2] = medirTempoOrdenacao(mergeSortWrapper, copia, n);
        delete[] copia;

        // HeapSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[3] = medirTempoOrdenacao(heapSort, copia, n);
        delete[] copia;

        // QuickSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[4] = medirTempoOrdenacao(quickSortWrapper, copia, n);
        delete[] copia;

        // CountingSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[5] = medirTempoOrdenacao(countingSort, copia, n);

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
        countingSort(vetor, n);
        quaseOrdenado(vetor, n);
        int *copia;
        float totalTimes[6] = {0};

    
        // Medir o tempo dos algoritmos de ordenação
        // BubbleSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[0] = medirTempoOrdenacao(bubbleSort, copia, n);
        delete[] copia;

        // InsertionSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[1] = medirTempoOrdenacao(insertionSort, copia, n);
        delete[] copia;

        // MergeSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[2] = medirTempoOrdenacao(mergeSortWrapper, copia, n);
        delete[] copia;

        // HeapSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[3] = medirTempoOrdenacao(heapSort, copia, n);
        delete[] copia;

        // QuickSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[4] = medirTempoOrdenacao(quickSortWrapper, copia, n);
        delete[] copia;

        // CountingSort
        copia = criarCopiaVetor(vetor, n);
        totalTimes[5] = medirTempoOrdenacao(countingSort, copia, n);

        delete[] vetor;
        delete[] copia;

        // salvar no arquivo csv
        salvarDados(n, totalTimes[0], totalTimes[1], totalTimes[2], totalTimes[3], totalTimes[4], totalTimes[5], "vetor_quaseOrdenado.csv");

        // imprimir tupla da tabela
        imprimir(n, totalTimes[0], totalTimes[1], totalTimes[2], totalTimes[3], totalTimes[4], totalTimes[5]);
    }
}