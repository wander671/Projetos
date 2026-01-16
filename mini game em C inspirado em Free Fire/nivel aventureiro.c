#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

/* ---------- STRUCTS ---------- */

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/* ---------- VARIÁVEIS GLOBAIS ---------- */

Item mochilaVetor[MAX];
int totalVetor = 0;

No* inicioLista = NULL;

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

/* ---------- FUNÇÕES DO VETOR ---------- */

void inserirItemVetor(Item item) {
    if (totalVetor < MAX) {
        mochilaVetor[totalVetor++] = item;
    }
}

void listarVetor() {
    for (int i = 0; i < totalVetor; i++) {
        printf("%s | %s | %d\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

int buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

void removerItemVetor(char nome[]) {
    int pos = buscarSequencialVetor(nome);
    if (pos != -1) {
        for (int i = pos; i < totalVetor - 1; i++) {
            mochilaVetor[i] = mochilaVetor[i + 1];
        }
        totalVetor--;
    }
}

void ordenarVetor() {
    Item aux;
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = i + 1; j < totalVetor; j++) {
            if (strcmp(mochilaVetor[i].nome, mochilaVetor[j].nome) > 0) {
                aux = mochilaVetor[i];
                mochilaVetor[i] = mochilaVetor[j];
                mochilaVetor[j] = aux;
            }
        }
    }
}

int buscaBinariaVetor(char nome[]) {
    int inicio = 0, fim = totalVetor - 1;
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

/* ---------- FUNÇÕES DA LISTA ENCADEADA ---------- */

void inserirLista(Item item) {
    No* novo = (No*)malloc(sizeof(No));
    novo->dados = item;
    novo->proximo = inicioLista;
    inicioLista = novo;
}

void listarLista() {
    No* atual = inicioLista;
    while (atual != NULL) {
        printf("%s | %s | %d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
}

No* buscarLista(char nome[]) {
    comparacoesSequencial = 0;
    No* atual = inicioLista;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void removerLista(char nome[]) {
    No* atual = inicioLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                inicioLista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

/* ---------- MENU PRINCIPAL ---------- */

int main() {
    Item item;
    char nomeBusca[30];
    int opcao;

    do {
        printf("\n1 - Inserir item (Vetor)");
        printf("\n2 - Inserir item (Lista)");
        printf("\n3 - Listar Vetor");
        printf("\n4 - Listar Lista");
        printf("\n5 - Buscar Sequencial Vetor");
        printf("\n6 - Ordenar Vetor");
        printf("\n7 - Busca Binária Vetor");
        printf("\n0 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            scanf("%s %s %d", item.nome, item.tipo, &item.quantidade);
            inserirItemVetor(item);
            break;

        case 2:
            scanf("%s %s %d", item.nome, item.tipo, &item.quantidade);
            inserirLista(item);
            break;

        case 3:
            listarVetor();
            break;

        case 4:
            listarLista();
            break;

        case 5:
            scanf("%s", nomeBusca);
            buscarSequencialVetor(nomeBusca);
            printf("Comparações: %d\n", comparacoesSequencial);
            break;

        case 6:
            ordenarVetor();
            break;

        case 7:
            scanf("%s", nomeBusca);
            buscaBinariaVetor(nomeBusca);
            printf("Comparações (Binária): %d\n", comparacoesBinaria);
            break;
        }
    } while (opcao != 0);

    return 0;
}
