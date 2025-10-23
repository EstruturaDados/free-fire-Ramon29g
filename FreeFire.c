#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10 // capacidade máxima da mochila

// ----------------------------
// Definição da struct Item
// ----------------------------
typedef struct {
    char nome[30];     // nome do item
    char tipo[20];     // tipo (arma, munição, cura, etc)
    int quantidade;    // quantidade disponível
} Item;

// ----------------------------
// Protótipos das funções
// ----------------------------
void inserirItem(Item mochila[], int *contador);
void removerItem(Item mochila[], int *contador);
void listarItens(Item mochila[], int contador);
void buscarItem(Item mochila[], int contador);

// ----------------------------
// Função principal
// ----------------------------
int main() {
    Item mochila[MAX_ITENS]; // vetor de structs (a mochila)
    int contador = 0;        // quantidade atual de itens
    int opcao;

    printf("=====================================\n");
    printf("     MOCHILA DE LOOT - FREE FIRE\n");
    printf("=====================================\n");

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); // consome o '\n' do buffer

        switch(opcao) {
            case 1:
                inserirItem(mochila, &contador);
                listarItens(mochila, contador);
                break;
            case 2:
                removerItem(mochila, &contador);
                listarItens(mochila, contador);
                break;
            case 3:
                listarItens(mochila, contador);
                break;
            case 4:
                buscarItem(mochila, contador);
                break;
            case 0:
                printf("\nSaindo do sistema... Boa sorte no campo de batalha!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}

// ----------------------------
// Função: Inserir item
// ----------------------------
void inserirItem(Item mochila[], int *contador) {
    if (*contador >= MAX_ITENS) {
        printf("\nA mochila esta cheia! Remova algum item antes de adicionar outro.\n");
        return;
    }

    Item novoItem;
    printf("\n=== CADASTRO DE ITEM ===\n");
    printf("Nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; // remove '\n'

    printf("Tipo (arma, municao, cura, etc): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar();

    mochila[*contador] = novoItem;
    (*contador)++;

    printf("\nItem adicionado com sucesso!\n");
}

// ----------------------------
// Função: Remover item
// ----------------------------
void removerItem(Item mochila[], int *contador) {
    if (*contador == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nome[30];
    printf("\nInforme o nome do item que deseja remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    int encontrado = -1;
    for (int i = 0; i < *contador; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        for (int i = encontrado; i < *contador - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        (*contador)--;
        printf("\nItem '%s' removido da mochila.\n", nome);
    } else {
        printf("\nItem nao encontrado!\n");
    }
}

// ----------------------------
// Função: Listar itens
// ----------------------------
void listarItens(Item mochila[], int contador) {
    printf("\n=== ITENS NA MOCHILA ===\n");

    if (contador == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (int i = 0; i < contador; i++) {
        printf("Item %d:\n", i + 1);
        printf(" Nome: %s\n", mochila[i].nome);
        printf(" Tipo: %s\n", mochila[i].tipo);
        printf(" Quantidade: %d\n", mochila[i].quantidade);
        printf("-----------------------------\n");
    }
}

// ----------------------------
// Função: Buscar item (busca sequencial)
// ----------------------------
void buscarItem(Item mochila[], int contador) {
    if (contador == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item para buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for (int i = 0; i < contador; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf(" Nome: %s\n", mochila[i].nome);
            printf(" Tipo: %s\n", mochila[i].tipo);
            printf(" Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado.\n");
}