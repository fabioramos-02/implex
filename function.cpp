#include "lib.h"
#include "stdio.h"
#include "stdlib.h"


void criarVetorAleatorio(int *vetor, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = rand() % 100; // Gera números aleatórios entre 0 e 99
    }
    imprimirVetor(vetor, tamanho);
}

void imprimirVetor(int *vetor, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}