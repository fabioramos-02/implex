// Autor: Fabio Ramos, 202319060712
// Autor: Gustavo Florentin, colocar o RGA




// funcao para medir o tempo
float time_val(struct timeval *start, struct timeval *end);

// implementacao de funções de ordenação

// Gustavo implementar
// void bubbleSort(int *vetor, int tamanho);
// void countingSort(int *vetor, int tamanho);
// void quickSort(int *vetor, int inicio, int fim);

// Fabio implementar
void insertionSortCrescente(int *vetor, int tamanho);
void insertionSortDecrescente(int *vetor, int tamanho);

void heapSort(int *vetor, int tamanho);
void heapify(int *vetor, int tamanho, int i);
void mergeSort(int *vetor, int left, int right);
void merge(int *vetor, int inicio, int meio, int fim);

// Função para criar vetores aleatórios
void criarVetorAleatorio(int *vetor, int tamanho);

// impementar os 4 conjuntos de dados
void vetorAleatorio(int inc, int fim, int stp, int rpt);
void vetorReverso(int inc, int fim, int stp, int rpt);