#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 10

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];      // arma, municao, cura, ferramenta
    int quantidade;
} Item;

// Função para listar os itens da mochila
void listarItens(Item mochila[], int total) {
    int i;

    if (total == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n--- ITENS NA MOCHILA ---\n");
    for (i = 0; i < total; i++) {
        printf("Item %d\n", i + 1);
        printf("Nome: %s", mochila[i].nome);
        printf("Tipo: %s", mochila[i].tipo);
        printf("Quantidade: %d\n\n", mochila[i].quantidade);
    }
}

// Função para inserir um item na mochila
void inserirItem(Item mochila[], int *total) {
    if (*total >= TAM) {
        printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    fgets(mochila[*total].nome, 30, stdin);

    printf("Digite o tipo do item (arma, municao, cura, ferramenta): ");
    fgets(mochila[*total].tipo, 20, stdin);

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    getchar(); // limpar buffer

    (*total)++;

    printf("\nItem adicionado com sucesso!\n");
    listarItens(mochila, *total);
}

// Função para remover um item pelo nome
void removerItem(Item mochila[], int *total) {
    char nomeBusca[30];
    int i, encontrado = 0;

    if (*total == 0) {
        printf("\nMochila vazia. Nada para remover.\n");
        return;
    }

    printf("\nDigite o nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);

    for (i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;

            // Desloca os itens
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*total)--;

            printf("\nItem removido com sucesso!\n");
            listarItens(mochila, *total);
            return;
        }
    }

    if (!encontrado) {
        printf("\nItem não encontrado.\n");
    }
}

// Função de busca sequencial
void buscarItem(Item mochila[], int total) {
    char nomeBusca[30];
    int i;

    if (total == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\nDigite o nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);

    for (i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s", mochila[i].nome);
            printf("Tipo: %s", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem não encontrado.\n");
}

// Função principal
int main() {
    Item mochila[TAM];
    int total = 0;
    int opcao;

    do {
        printf("\n=== MINI GAME - MOCHILA FREE FIRE ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                inserirItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
