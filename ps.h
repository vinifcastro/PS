// Vinicius de Freitas Castro 202103783
// Lucas Bernardes Feitosa 202103751

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define QTDMACA 40

typedef struct Fila{
    char nome[80];
    int idade, gravidade;
    char sintomas[300];
    struct Fila *proximo;
}Fila;

typedef struct Alta{
  int tam;
  Fila alta[5000];
} Alta;

int verifica_vazia(Fila * fila); // Verifica se a fila esta vazia.

void enfileira_pessoa_ps(Fila ** fila, char * nome, int idade, char * sintomas, int gravidade); // Enfileira um paciente e armazena nome, idade, gravidade e sintomas.

void desenfileirar(Fila ** fila, int triagem, Fila ** filaps, Fila * mapa); // Retira um paciente da fila.

void libera_fila(Fila ** fila); // Libera toda a memoria alocada para a fila.

void mostra_fila(Fila *fila); // Mostra a fila de espera do pronto socorro.

int qtd_fila(Fila *fila); // Quantas pessoas há na fila.

void enfileira_pessoa_triagem(Fila **fila, char * nome, int idade); // Enfileira um paciente e armazena nome, idade.

void mostramapa(Fila *maca); // Mostra o mapa de ocupacao das macas disponiveis no PS, alem de possibilitar ver mais informacoes sobre o paciente

void guia(void); // Pequeno tutorial referente ao programa.

void pesquisalistabin(Fila * lista, int num); // Realiza a pesquisa no mapa de macas de forma binaria.

void buscanomeseq(Fila * maca, char * nome); // Realiza a pesquisa por nome de forma sequencial.

void printalta(Alta x); // Mostra todos os pacientes que foram de alta médica.

void quick_sort(Fila *a, int inicio, int fim); // Faz a ordenação.

void select_sort(Fila * a, int n); // Faz a ordenação.