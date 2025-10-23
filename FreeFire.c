#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// ===============================================
// 1. Definição das structs
// ===============================================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// ===============================================
// Variáveis globais para contadores de comparações
// ===============================================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ===============================================
// Funções para a MOCHILA VETORIAL
// ===============================================

void inserirItemVetor(Item mochila[], int *contador) {
    if (*contador >= MAX_ITENS) {
        printf("\nA mochila vetorial esta cheia!\n");
        return;
    }

    Item novo;
    printf("\n=== Inserir Item (Vetor) ===\n");
    printf("Nome: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Tipo: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*contador] = novo;
    (*contador)++;

    printf("Item inserido com sucesso no vetor!\n");
}

void listarItensVetor(Item mochila[], int contador) {
    printf("\n=== Itens na Mochila (Vetor) ===\n");
    if (contador == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }
    for (int i = 0; i < contador; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void removerItemVetor(Item mochila[], int *contador) {
    if (*contador == 0) {
        printf("\nA mochila vetorial esta vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    for (int i = 0; i < *contador; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *contador - 1; j++)
                mochila[j] = mochila[j + 1];
            (*contador)--;
            printf("Item '%s' removido.\n", nome);
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

// --------------------
// Ordenação (Bubble Sort)
// --------------------
void ordenarVetor(Item mochila[], int contador) {
    Item temp;
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("\nItens ordenados por nome (Bubble Sort).\n");
}

// --------------------
// Busca sequencial (vetor)
// --------------------
void buscarSequencialVetor(Item mochila[], int contador) {
    comparacoesSequencial = 0;
    char nome[30];
    printf("\nDigite o nome do item para busca sequencial: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    for (int i = 0; i < contador; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado!\nNome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
            return;
        }
    }
    printf("\nItem nao encontrado.\nComparacoes realizadas: %d\n", comparacoesSequencial);
}

// --------------------
// Busca binária (vetor)
// --------------------
void buscarBinariaVetor(Item mochila[], int contador) {
    if (contador == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item para busca binaria: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    int inicio = 0, fim = contador - 1, meio;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochila[meio].nome, nome);
