#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUCT SALA (NÓ DA ÁRVORE)
   ========================= */

/*
 Cada sala da mansão é representada
 como um nó de uma árvore binária.
*/
typedef struct Sala {
    char nome[50];            // Nome do cômodo
    struct Sala* esquerda;    // Caminho à esquerda
    struct Sala* direita;     // Caminho à direita
} Sala;

/* =========================
   FUNÇÃO criarSala
   ========================= */
/*
 Cria dinamicamente uma nova sala,
 alocando memória e inicializando
 seus caminhos como NULL.
*/
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

/* =========================
   FUNÇÃO explorarSalas
   ========================= */
/*
 Permite que o jogador explore a mansão,
 navegando pela árvore binária a partir
 do Hall de entrada.
*/
void explorarSalas(Sala* atual) {
    char opcao;

    while (atual != NULL) {
        printf("\n====================================\n");
        printf("Você está no cômodo: %s\n", atual->nome);
        printf("====================================\n");

        /* Verifica se é uma sala final (nó-folha) */
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Este cômodo não possui mais caminhos.\n");
            printf("Fim da exploração!\n");
            break;
        }

        /* Exibe opções disponíveis */
        printf("Escolha um caminho:\n");

        if (atual->esquerda != NULL)
            printf(" [e] Ir para a esquerda\n");

        if (atual->direita != NULL)
            printf(" [d] Ir para a direita\n");

        printf(" [s] Sair da exploração\n");
        printf("Opção: ");
        scanf(" %c", &opcao);

        /* Controle das decisões do jogador */
        if (opcao == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        }
        else if (opcao == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        }
        else if (opcao == 's') {
            printf("\nExploração encerrada pelo jogador.\n");
            break;
        }
        else {
            printf("\nOpção inválida! Tente novamente.\n");
        }
    }
}

/* =========================
   FUNÇÃO main
   ========================= */
/*
 Monta o mapa da mansão (árvore binária)
 e inicia a exploração a partir do Hall.
*/
int main() {

    /* =========================
       CRIAÇÃO DO MAPA DA MANSÃO
       ========================= */

    Sala* hall = criarSala("Hall de Entrada");

    hall->esquerda = criarSala("Sala de Estar");
    hall->direita  = criarSala("Corredor Principal");

    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita  = criarSala("Cozinha");

    hall->direita->esquerda = criarSala("Escritório");
    hall->direita->direita  = criarSala("Jardim");

    /* =========================
       INÍCIO DO JOGO
       ========================= */

    printf("====================================\n");
    printf("  🕵️‍♂️ DETECTIVE QUEST - MANSÃO 🏰\n");
    printf("====================================\n");

    explorarSalas(hall);

    printf("\nObrigado por jogar Detective Quest!\n");

    return 0;
}
