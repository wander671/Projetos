#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ==============================
   CONSTANTES DO JOGO
   ============================== */
#define TAM_FILA 5
#define TAM_PILHA 3

/* ==============================
   STRUCT DA PEÇA
   ============================== */
typedef struct {
    char nome;   // Tipo da peça: I, O, T, L
    int id;      // Identificador único
} Peca;

/* ==============================
   FILA CIRCULAR
   ============================== */
typedef struct {
    Peca dados[TAM_FILA];
    int inicio;
    int fim;
    int tamanho;
} Fila;

/* ==============================
   PILHA DE RESERVA
   ============================== */
typedef struct {
    Peca dados[TAM_PILHA];
    int topo;
} Pilha;

/* ==============================
   VARIÁVEL GLOBAL DE ID
   ============================== */
int contadorID = 0;

/* ==============================
   FUNÇÃO: GERAR PEÇA ALEATÓRIA
   ============================== */
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;

    p.nome = tipos[rand() % 4];
    p.id = contadorID++;

    return p;
}

/* ==============================
   FUNÇÕES DA FILA
   ============================== */
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;

    // Preenche a fila inicialmente
    for (int i = 0; i < TAM_FILA; i++) {
        f->dados[f->fim] = gerarPeca();
        f->fim = (f->fim + 1) % TAM_FILA;
        f->tamanho++;
    }
}

void enqueue(Fila *f, Peca p) {
    f->dados[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
}

Peca dequeue(Fila *f) {
    Peca removida = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    return removida;
}

void mostrarFila(Fila *f) {
    printf("Fila de peças:\t");
    int i = f->inicio;

    for (int count = 0; count < TAM_FILA; count++) {
        printf("[%c %d] ", f->dados[i].nome, f->dados[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

/* ==============================
   FUNÇÕES DA PILHA
   ============================== */
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca pec) {
    p->topo++;
    p->dados[p->topo] = pec;
}

Peca pop(Pilha *p) {
    return p->dados[p->topo--];
}

void mostrarPilha(Pilha *p) {
    printf("Pilha de reserva\t(Topo -> Base): ");

    if (pilhaVazia(p)) {
        printf("Vazia");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->dados[i].nome, p->dados[i].id);
        }
    }
    printf("\n");
}

/* ==============================
   EXIBIR ESTADO ATUAL
   ============================== */
void mostrarEstado(Fila *f, Pilha *p) {
    printf("\n====================================\n");
    printf("ESTADO ATUAL DO JOGO - TETRIS STACK\n");
    printf("====================================\n");
    mostrarFila(f);
    mostrarPilha(p);
    printf("====================================\n");
}

/* ==============================
   MENU
   ============================== */
void menu() {
    printf("\nOpções de Ação:\n");
    printf("1 - Jogar peça\n");
    printf("2 - Reservar peça\n");
    printf("3 - Usar peça reservada\n");
    printf("0 - Sair\n");
    printf("Opção: ");
}

/* ==============================
   FUNÇÃO PRINCIPAL
   ============================== */
int main() {
    Fila fila;
    Pilha pilha;
    int opcao;

    srand(time(NULL));

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    do {
        mostrarEstado(&fila, &pilha);
        menu();
        scanf("%d", &opcao);

        if (opcao == 1) {
            // Jogar peça
            Peca jogada = dequeue(&fila);
            printf("🎮 Peça jogada: [%c %d]\n", jogada.nome, jogada.id);

            enqueue(&fila, gerarPeca());
        }
        else if (opcao == 2) {
            // Reservar peça
            if (pilhaCheia(&pilha)) {
                printf("⚠️ Pilha de reserva cheia!\n");
            } else {
                Peca reservada = dequeue(&fila);
                push(&pilha, reservada);
                printf("📦 Peça reservada: [%c %d]\n", reservada.nome, reservada.id);

                enqueue(&fila, gerarPeca());
            }
        }
        else if (opcao == 3) {
            // Usar peça reservada
            if (pilhaVazia(&pilha)) {
                printf("⚠️ Pilha de reserva vazia!\n");
            } else {
                Peca usada = pop(&pilha);
                printf("🔥 Peça da reserva usada: [%c %d]\n", usada.nome, usada.id);
            }
        }
        else if (opcao == 0) {
            printf("Encerrando o jogo...\n");
        }
        else {
            printf("❌ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
