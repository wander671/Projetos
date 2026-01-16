#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor de itens (mochila)
Item mochila[MAX_ITENS];
int totalItens = 0;

// Função para remover o '\n' do fgets
void removerQuebraLinha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Função para listar os itens da mochila
void listarItens() {
    int i;

    printf("\n📦 ITENS NA MOCHILA 📦\n");

    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

// Função para inserir um item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n❌ Mochila cheia! Limite de 10 itens atingido.\n");
        return;
    }

    printf("\n➕ CADASTRAR ITEM\n");

    printf("Nome do item: ");
    fgets(mochila[totalItens].nome, 30, stdin);
    removerQuebraLinha(mochila[totalItens].nome);

    printf("Tipo do item (arma, munição, cura, etc): ");
    fgets(mochila[totalItens].tipo, 20, stdin);
    removerQuebraLinha(mochila[totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    getchar(); // limpar buffer

    totalItens++;

    printf("\n✅ Item cadastrado com sucesso!\n");
    listarItens();
}

// Função para buscar item por nome (busca sequencial)
void buscarItem() {
    char nomeBusca[30];
    int i;

    printf("\n🔍 BUSCAR ITEM\n");
    printf("Digite o nome do item: ");
    fgets(nomeBusca, 30, stdin);
    removerQuebraLinha(nomeBusca);

    for (i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\n❌ Item não encontrado na mochila.\n");
}

// Função para remover item pelo nome
void removerItem() {
    char nomeRemove[30];
    int i, j;

    printf("\n🗑️ REMOVER ITEM\n");
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemove, 30, stdin);
    removerQuebraLinha(nomeRemove);

    for (i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemove) == 0) {
            // Desloca os itens para preencher o espaço removido
            for (j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            totalItens--;
            printf("\n✅ Item removido com sucesso!\n");
            listarItens();
            return;
        }
    }

    printf("\n❌ Item não encontrado.\n");
}

// Função principal
int main() {
    int opcao;

    do {
        printf("\n🎮 SISTEMA DE INVENTÁRIO 🎮\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\n👋 Saindo do sistema...\n");
                break;
            default:
                printf("\n⚠️ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
