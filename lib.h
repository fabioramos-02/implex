#include <chrono>
#include <sys/time.h>
#include "stdio.h"
#include "stdlib.h"
#include <ctime>
#include <algorithm>
// Autor: Fabio Ramos, 202319060712
// Autor: Gustavo Florentin, 202319060232


// funcao para medir o tempo
void salvarDados(int n, float totalBubble, float totalInsertion, float totalMerge, float totalHeap, float totalQuick, float totalCounting, const char *nomeArquivo);
float time_val(struct timeval *start, struct timeval *end);
float medirTempoOrdenacao(void (*sortFunc)(int*, int, bool), int *vetor, int tamanho, bool crescente);

// Gustavo implementar
void bubbleSort(int *vetor, int tamanho, bool crescente);
void countingSort(int *vetor, int tamanho, bool crescente);

void quickSort(int *vetor, int inicio, int fim, bool crescente);
void quickSortWrapper(int *vetor, int tamanho, bool crescente);
int particionar(int *vetor, int inicio, int fim, bool crescente);

void quaseOrdenado(int *vetor, int n);

// Fabio implementar
void insertionSort(int *vetor, int tamanho, bool crescente);

void heapSort(int *vetor, int tamanho, bool crescente);
void heapify(int *vetor, int tamanho, int i, bool crescente);

void mergeSort(int *vetor, int left, int right, bool crescente);
void merge(int *vetor, int left, int mid, int right, bool crescente);
void mergeSortWrapper(int *vetor, int tamanho, bool crescente);


// Função para criar vetores aleatórios
int *criarVetorAleatorio(int n);
int *criarCopiaVetor(int *vet, int n);

// impementar os 4 conjuntos de dados
void vetorAleatorio(int inc, int fim, int stp, int rpt);
void vetorReverso(int inc, int fim, int stp);
void vetorOrdenado(int inc, int fim, int stp);
void vetorQuaseOrdenado(int inc, int fim, int stp);

void imprimir(int n, float timeBubble, float timeInsertion, float timeMerge, float timeHeap, float timeQuick, float timeCounting);
int *preencherVet(int n, bool crescente);