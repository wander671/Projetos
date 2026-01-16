#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUCTS
   ========================= */

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/* =========================
   VARIÁVEIS GLOBAIS
   ========================= */

#define MAX 50

Item mochilaVetor[MAX];
int totalItens = 0;

No* mochilaLista = NULL;

/* Contadores de comparações */
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

/* =========================
   FUNÇÕES DE MENU (FREE FIRE)
   ========================= */

void menuPrincipal() {
    printf("\n====================================\n");
    printf("        🎒 MOCHILA FREE FIRE 🎒       \n");
    printf("====================================\n");
    printf("1 - Mochila Rápida (VETOR)\n");
    printf("   ➤ Ideal para loot rápido\n");
    printf("2 - Mochila Estratégica (LISTA)\n");
    printf("   ➤ Flexível na zona de perigo\n");
    printf("0 - Sair do jogo\n");
    printf("====================================\n");
    printf("Escolha: ");
}

void menuMochila(int estrutura) {
    printf("\n------------------------------------\n");
    printf("        AÇÕES DA MOCHILA\n");
    printf("------------------------------------\n");
    printf("1 - Coletar item (Adicionar loot)\n");
    printf("2 - Descartar item\n");
    printf("3 - Ver itens da mochila\n");
    printf("4 - Procurar item\n");

    if (estrutura == 1) {
        printf("5 - Organizar mochila (Ordenar)\n");
        printf("6 - Busca rápida (Busca Binária)\n");
    }

    printf("0 - Voltar\n");
    printf("------------------------------------\n");
    printf("Opção: ");
}

/* =========================
   FUNÇÕES DO VETOR
   ========================= */

void inserirItemVetor(Item item) {
    if (totalItens < MAX) {
        mochilaVetor[totalItens++] = item;
        printf("🎯 Item coletado com sucesso!\n");
    } else {
        printf("❌ Mochila cheia!\n");
    }
}

void listarVetor() {
    printf("\n🎒 ITENS NA MOCHILA (VETOR)\n");
    for (int i = 0; i < totalItens; i++) {
        printf("%s | %s | %d\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

int buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < totalItens; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

void removerItemVetor(char nome[]) {
    int pos = buscarSequencialVetor(nome);
    if (pos != -1) {
        for (int i = pos; i < totalItens - 1; i++) {
            mochilaVetor[i] = mochilaVetor[i + 1];
        }
        totalItens--;
        printf("🗑 Item descartado!\n");
    } else {
        printf("❌ Item não encontrado!\n");
    }
}

void ordenarVetor() {
    Item aux;
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                aux = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = aux;
            }
        }
    }
    printf("📦 Mochila organizada!\n");
}

int buscarBinariaVetor(char nome[]) {
    int inicio = 0, fim = totalItens - 1;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochilaVetor[meio].nome, nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

/* =========================
   FUNÇÕES DA LISTA
   ========================= */

void inserirItemLista(Item item) {
    No* novo = (No*)malloc(sizeof(No));
    novo->dados = item;
    novo->proximo = mochilaLista;
    mochilaLista = novo;
    printf("🎯 Item coletado com sucesso!\n");
}

void listarLista() {
    printf("\n🎒 ITENS NA MOCHILA (LISTA)\n");
    No* atual = mochilaLista;
    while (atual != NULL) {
        printf("%s | %s | %d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
}

No* buscarSequencialLista(char nome[]) {
    comparacoesSequencial = 0;
    No* atual = mochilaLista;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void removerItemLista(char nome[]) {
    No *atual = mochilaLista, *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("❌ Item não encontrado!\n");
        return;
    }

    if (anterior == NULL)
        mochilaLista = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("🗑 Item descartado!\n");
}

/* =========================
   MAIN
   ========================= */

int main() {
    int estrutura, opcao;
    Item item;
    char nomeBusca[30];

    do {
        menuPrincipal();
        scanf("%d", &estrutura);

        if (estrutura == 0) {
            printf("🏁 Fim de jogo!\n");
            break;
        }

        do {
            menuMochila(estrutura);
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Nome do item: ");
                    scanf(" %[^\n]", item.nome);
                    printf("Tipo (arma, munição, kit, etc): ");
                    scanf(" %[^\n]", item.tipo);
                    printf("Quantidade: ");
                    scanf("%d", &item.quantidade);

                    if (estrutura == 1)
                        inserirItemVetor(item);
                    else
                        inserirItemLista(item);
                    break;

                case 2:
                    printf("Nome do item: ");
                    scanf(" %[^\n]", nomeBusca);
                    if (estrutura == 1)
                        removerItemVetor(nomeBusca);
                    else
                        removerItemLista(nomeBusca);
                    break;

                case 3:
                    if (estrutura == 1)
                        listarVetor();
                    else
                        listarLista();
                    break;

                case 4:
                    printf("Nome do item: ");
                    scanf(" %[^\n]", nomeBusca);

                    if (estrutura == 1) {
                        int pos = buscarSequencialVetor(nomeBusca);
                        printf("Comparações: %d\n", comparacoesSequencial);
                        printf(pos != -1 ? "🔍 Item encontrado!\n" : "❌ Item não encontrado!\n");
                    } else {
                        No* achou = buscarSequencialLista(nomeBusca);
                        printf("Comparações: %d\n", comparacoesSequencial);
                        printf(achou ? "🔍 Item encontrado!\n" : "❌ Item não encontrado!\n");
                    }
                    break;

                case 5:
                    if (estrutura == 1)
                        ordenarVetor();
                    break;

                case 6:
                    if (estrutura == 1) {
                        printf("Nome do item: ");
                        scanf(" %[^\n]", nomeBusca);
                        int pos = buscarBinariaVetor(nomeBusca);
                        printf("Comparações: %d\n", comparacoesBinaria);
                        printf(pos != -1 ? "⚡ Item encontrado rapidamente!\n" : "❌ Item não encontrado!\n");
                    }
                    break;
            }

        } while (opcao != 0);

    } while (1);

    return 0;
}
