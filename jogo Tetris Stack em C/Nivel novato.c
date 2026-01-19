#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ============================
   CONSTANTES
   ============================ */

// Tamanho máximo da fila de peças
#define TAM_FILA 5

/* ============================
   STRUCT DA PEÇA
   ============================ */

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome; // Tipo da peça: I, O, T ou L
    int id;    // Identificador único da peça
} Peca;

/* ============================
   VARIÁVEIS DA FILA
   ============================ */

Peca fila[TAM_FILA]; // Array que representa a fila circular
int inicio = 0;      // Índice do início da fila
int fim = 0;         // Índice do final da fila
int total = 0;       // Quantidade atual de elementos na fila
int proximoId = 0;   // Controla o ID único das peças

/* ============================
   FUNÇÃO: GERAR PEÇA
   ============================ */

// Gera automaticamente uma nova peça
Peca gerarPeca() {
    Peca p;

    // Tipos possíveis de peças
    char tipos[] = {'I', 'O', 'T', 'L'};

    // Escolhe um tipo aleatório
    p.nome = tipos[rand() % 4];

    // Define um ID único
    p.id = proximoId++;

    return p;
}

/* ============================
   FUNÇÃO: ENQUEUE (INSERIR)
   ============================ */

// Insere uma peça no final da fila
void enqueue() {
    // Verifica se a fila está cheia
    if (total == TAM_FILA) {
        printf("\n⚠️ Fila cheia! Não é possível inserir nova peça.\n");
        return;
    }

    // Gera uma nova peça automaticamente
    fila[fim] = gerarPeca();

    // Atualiza o índice do fim (fila circular)
    fim = (fim + 1) % TAM_FILA;

    // Incrementa o total de peças
    total++;

    printf("\n✅ Nova peça inserida na fila!\n");
}

/* ============================
   FUNÇÃO: DEQUEUE (REMOVER)
   ============================ */

// Remove a peça do início da fila
void dequeue() {
    // Verifica se a fila está vazia
    if (total == 0) {
        printf("\n⚠️ Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }

    // Mostra a peça que está sendo jogada
    printf("\n🎮 Jogando peça: [%c %d]\n",
           fila[inicio].nome,
           fila[inicio].id);

    // Atualiza o índice do início (fila circular)
    inicio = (inicio + 1) % TAM_FILA;

    // Decrementa o total de peças
    total--;
}

/* ============================
   FUNÇÃO: EXIBIR FILA
   ============================ */

// Exibe o estado atual da fila
void exibirFila() {
    printf("\n📦 Fila de peças\n");

    // Se a fila estiver vazia
    if (total == 0) {
        printf("[ Fila vazia ]\n");
        return;
    }

    // Percorre a fila do início até o total de elementos
    int i, indice;
    for (i = 0; i < total; i++) {
        indice = (inicio + i) % TAM_FILA;
        printf("[%c %d] ", fila[indice].nome, fila[indice].id);
    }

    printf("\n");
}

/* ============================
   FUNÇÃO: MENU
   ============================ */

// Exibe o menu de opções
void menu() {
    printf("\nOpções de ação:\n");
    printf("1 - Jogar peça \n");
    printf("2 - Inserir nova peça \n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

/* ============================
   FUNÇÃO PRINCIPAL
   ============================ */

int main() {
    int opcao;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue();
    }

    // Loop principal do programa
    do {
        // Exibe a fila atual
        exibirFila();

        // Mostra o menu
        menu();

        // Lê a opção do usuário
        scanf("%d", &opcao);

        // Processa a opção escolhida
        switch (opcao) {
            case 1:
                dequeue();
                break;

            case 2:
                enqueue();
                break;

            case 0:
                printf("\n👋 Encerrando o jogo. Até a próxima!\n");
                break;

            default:
                printf("\n❌ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
