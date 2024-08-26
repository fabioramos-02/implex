#include <chrono>
#include <sys/time.h>
#include "stdio.h"
#include "stdlib.h"
#include <ctime>
// Autor: Fabio Ramos, 202319060712
// Autor: Gustavo Florentin, colocar o RGA


// funcao para medir o tempo
void salvarDados(int n, float totalBubble, float totalInsertion, float totalMerge, float totalHeap, float totalQuick, float totalCounting, const char *nomeArquivo);
float time_val(struct timeval *start, struct timeval *end);

// implementacao de funções de ordenação
// Gustavo implementar
void bubbleSort(int *vetor, int tamanho, bool crescente);
void countingSort(int *vetor, int tamanho, bool crescente);

void quickSort(int *vetor, int inicio, int fim, bool crescente);
int particionar(int *vetor, int inicio, int fim, bool crescente);

// Fabio implementar
void insertionSort(int *vetor, int tamanho, bool crescente);

void heapSort(int *vetor, int tamanho, bool crescente);
void heapify(int *vetor, int tamanho, int i, bool crescente);

void mergeSort(int *vetor, int left, int right, bool crescente);
void merge(int *vetor, int left, int mid, int right, bool crescente);

// Função para criar vetores aleatórios
int *criarVetorAleatorio(int n);
int *criarCopiaVetor(int *vetor, int n);

// impementar os 4 conjuntos de dados
void vetorAleatorio(int inc, int fim, int stp, int rpt);
void vetorReverso(int inc, int fim, int stp, int rpt);
void vetorOrdenado(int inc, int fim, int stp, int rpt);