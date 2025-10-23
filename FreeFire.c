#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// ===============================================
// 1. Struct principal
// ===============================================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ===============================================
// Variáveis globais para contagem de comparações
// ===============================================
long long comparacoes = 0;

// ===============================================
// Funções auxiliares
// ===============================================
void mostrarComponentes(Componente lista[], int n) {
    printf("\n=== LISTA DE COMPONENTES ===\n");
    for (int i = 0; i < n; i++) {
        printf("Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
}

// ===============================================
// 2. Algoritmos de Ordenação
// ===============================================

// Bubble Sort -> Ordena por nome (string)
void bubbleSortNome(Componente lista[], int n) {
    comparacoes = 0;
    Componente temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort -> Ordena por tipo (string)
void insertionSortTipo(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = lista[i];
        int j = i - 1;
        while (j >= 0 && strcmp(lista[j].tipo, chave.tipo) > 0) {
            lista[j + 1] = lista[j];
            j--;
            comparacoes++;
        }
        lista[j + 1] = chave;
    }
}

// Selection Sort -> Ordena por prioridade (int)
void selectionSortPrioridade(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (lista[j].prioridade < lista[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = lista[i];
            lista[i] = lista[min];
            lista[min] = temp;
        }
    }
}

// ===============================================
// 3. Busca Binária (após ordenação por nome)
// ===============================================
int buscaBinariaPorNome(Componente lista[], int n, char chave[]) {
    int inicio = 0, fim = n - 1, meio;
    int comparacoesBusca = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBusca++;
        int cmp = strcmp(lista[meio].nome, chave);

        if (cmp == 0) {
            printf("\nComponente encontrado!\n");
            printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                   lista[meio].nome, lista[meio].tipo, lista[meio].prioridade);
            printf("Comparacoes realizadas (busca binaria): %d\n", comparacoesBusca);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\nComponente nao encontrado.\n");
    printf("Comparacoes realizadas (busca binaria): %d\n", comparacoesBusca);
    return -1;
}

// ===============================================
// 4. Função de medição de tempo de execução
// ===============================================
void medirTempo(void (*algoritmo)(Componente[], int), Componente lista[], int n, const char *nomeAlgoritmo) {
    Componente copia[MAX_COMPONENTES];
    memcpy(copia, lista, n * sizeof(Componente)); // copia do vetor original

    clock_t inicio = clock();
    algoritmo(copia, n);
    clock_t fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n=== %s ===\n", nomeAlgoritmo);
    printf("Tempo de execucao: %.6f segundos\n", tempo);
    printf("Comparacoes realizadas: %lld\n", comparacoes);
    mostrarComponentes(copia, n);
}

// ===============================================
// 5. Função principal
// ===============================================
int main() {
    Componente componentes[MAX_COMPONENTES];
    int n = 0;
    int opcao;
    char chave[30];

    printf("===============================================\n");
    printf("   SISTEMA DE MONTAGEM DE TORRE - COMPONENTES\n");
    printf("===============================================\n");

    // Entrada dos componentes
    printf("\nQuantos componentes deseja cadastrar (max %d)? ", MAX_COMPONENTES);
    scanf("%d", &n);
    getchar();

    if (n > MAX_COMPONENTES) n = MAX_COMPONENTES;

    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Componente %d ---\n", i + 1);
        printf("Nome: ");
        fgets(componentes[i].nome, 30, stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = 0;

        printf("Tipo: ");
        fgets(componentes[i].tipo, 20, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = 0;

        printf("Prioridade (1 a 10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar();
    }

    do {
        printf("\n===============================================\n");
        printf("                MENU PRINCIPAL\n");
        printf("===============================================\n");
        printf("1 - Ordenar por NOME (Bubble Sort)\n");
        printf("2 - Ordenar por TIPO (Insertion Sort)\n");
        printf("3 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("4 - Buscar componente (Binaria - por Nome)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                medirTempo(bubbleSortNome, componentes, n, "Bubble Sort (por Nome)");
                break;
            case 2:
                medirTempo(insertionSortTipo, componentes, n, "Insertion Sort (por Tipo)");
                break;
            case 3:
                medirTempo(selectionSortPrioridade, componentes, n, "Selection Sort (por Prioridade)");
                break;
            case 4:
                printf("\nDigite o nome do componente para busca: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = 0;
                bubbleSortNome(componentes, n); // garantir ordenação por nome antes da busca
                buscaBinariaPorNome(componentes, n, chave);
                break;
            case 0:
                printf("\nEncerrando sistema de montagem...\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    printf("\nSistema finalizado. Todos os componentes foram processados com sucesso!\n");
    return 0;
}
