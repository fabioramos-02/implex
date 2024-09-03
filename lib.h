#include <chrono>
#include <sys/time.h>
#include "stdio.h"
#include "stdlib.h"
#include <chrono>
#include <algorithm>
// Autor: Fabio Ramos, 202319060712
// Autor: Gustavo Florentin, 202319060232


// funcao para medir o tempo
void salvarDados(int n, float totalBubble, float totalInsertion, float totalMerge, float totalHeap, float totalQuick, float totalCounting, const char *nomeArquivo);
float medirTempoOrdenacao(void (*sortFunc)(int *, int), int *vetor, int tamanho);

// Gustavo implementar
void bubbleSort(int *vetor, int tamanho);
void countingSort(int *vetor, int tamanho);

void quickSort(int *vetor, int inicio, int fim);
void quickSortWrapper(int *vetor, int tamanho);
int particionar(int *vetor, int inicio, int fim);

void quaseOrdenado(int *vetor, int n);

// Fabio implementar
void insertionSort(int *vetor, int tamanho);

void heapSort(int *vetor, int tamanho);
void heapify(int *vetor, int tamanho, int i);

void mergeSort(int *vetor, int left, int right);
void merge(int *vetor, int left, int mid, int right);
void mergeSortWrapper(int *vetor, int tamanho);


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