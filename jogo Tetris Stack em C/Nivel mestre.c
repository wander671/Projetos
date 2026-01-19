#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* =========================
   CONFIGURAÇÕES DO JOGO
   ========================= */
#define TAM_FILA 5      // Fila de próximas peças (preview)
#define TAM_PILHA 3     // Pilha de peças reservadas (hold)

/* =========================
   STRUCT DA PEÇA TETRIS
   ========================= */
typedef struct {
    char tipo;   // I, O, T, L
    int id;      // Ordem de criação da peça
} Peca;

/* =========================
   FILA CIRCULAR (PRÓXIMAS PEÇAS)
   ========================= */
typedef struct {
    Peca fila[TAM_FILA];
    int inicio, fim, total;
} FilaPecas;

/* =========================
   PILHA (PEÇAS RESERVADAS)
   ========================= */
typedef struct {
    Peca pilha[TAM_PILHA];
    int topo;
} PilhaReserva;

/* =========================
   CONTADOR GLOBAL DE PEÇAS
   ========================= */
int idGlobal = 0;

/* =========================
   GERADOR AUTOMÁTICO DE PEÇAS
   ========================= */
Peca gerarPecaTetris() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = idGlobal++;
    return p;
}

/* =========================
   INICIALIZAÇÕES
   ========================= */
void inicializarFila(FilaPecas *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;

    // Fila sempre começa cheia
    while (f->total < TAM_FILA) {
        f->fila[f->fim] = gerarPecaTetris();
        f->fim = (f->fim + 1) % TAM_FILA;
        f->total++;
    }
}

void inicializarPilha(PilhaReserva *p) {
    p->topo = -1;
}

/* =========================
   OPERAÇÕES DA FILA
   ========================= */
Peca removerPecaAtual(FilaPecas *f) {
    Peca atual = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->total--;
    return atual;
}

void adicionarNovaPeca(FilaPecas *f) {
    if (f->total < TAM_FILA) {
        f->fila[f->fim] = gerarPecaTetris();
        f->fim = (f->fim + 1) % TAM_FILA;
        f->total++;
    }
}

/* =========================
   OPERAÇÕES DA PILHA
   ========================= */
int reservarPeca(PilhaReserva *p, Peca peca) {
    if (p->topo < TAM_PILHA - 1) {
        p->pilha[++p->topo] = peca;
        return 1;
    }
    return 0;
}

int usarPecaReservada(PilhaReserva *p) {
    if (p->topo >= 0) {
        p->topo--;
        return 1;
    }
    return 0;
}

/* =========================
   VISUALIZAÇÃO DO JOGO
   ========================= */
void exibirEstadoTetris(FilaPecas *f, PilhaReserva *p) {
    printf("\n=====================================\n");
    printf("        🎮 TETRIS STACK 🎮\n");
    printf("=====================================\n");

    printf("\nFila de Próximas Peças:\n");
    for (int i = 0; i < f->total; i++) {
        int idx = (f->inicio + i) % TAM_FILA;
        printf("[%c %d] ", f->fila[idx].tipo, f->fila[idx].id);
    }

    printf("\n\nPilha de Reserva (Topo -> Base):\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->pilha[i].tipo, p->pilha[i].id);
    }

    printf("\n=====================================\n");
}

/* =========================
   TROCA SIMPLES
   ========================= */
void trocarPecaAtual(FilaPecas *f, PilhaReserva *p) {
    if (f->total > 0 && p->topo >= 0) {
        Peca temp = f->fila[f->inicio];
        f->fila[f->inicio] = p->pilha[p->topo];
        p->pilha[p->topo] = temp;
        printf("\n🔄 Troca simples realizada!\n");
    } else {
        printf("\n❌ Troca não disponível.\n");
    }
}

/* =========================
   TROCA MÚLTIPLA (3x3)
   ========================= */
void trocaMultiplaTetris(FilaPecas *f, PilhaReserva *p) {
    if (f->total >= 3 && p->topo >= 2) {
        for (int i = 0; i < 3; i++) {
            int idxFila = (f->inicio + i) % TAM_FILA;
            Peca temp = f->fila[idxFila];
            f->fila[idxFila] = p->pilha[p->topo - i];
            p->pilha[p->topo - i] = temp;
        }
        printf("\n🔁 Troca múltipla executada com sucesso!\n");
    } else {
        printf("\n❌ Troca múltipla indisponível.\n");
    }
}

/* =========================
   MENU DO JOGO
   ========================= */
void menuTetris() {
    printf("\nAções disponíveis:\n");
    printf("1 - Jogar peça atual\n");
    printf("2 - Reservar peça atual\n");
    printf("3 - Usar peça reservada\n");
    printf("4 - Trocar peça atual com reserva\n");
    printf("5 - Troca múltipla (3 peças)\n");
    printf("0 - Encerrar jogo\n");
}

/* =========================
   FUNÇÃO PRINCIPAL
   ========================= */
int main() {
    srand(time(NULL));

    FilaPecas fila;
    PilhaReserva pilha;
    int opcao;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    do {
        exibirEstadoTetris(&fila, &pilha);
        menuTetris();
        printf("\nEscolha uma ação: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Jogar peça
                removerPecaAtual(&fila);
                adicionarNovaPeca(&fila);
                break;

            case 2: // Reservar peça
                if (reservarPeca(&pilha, removerPecaAtual(&fila))) {
                    adicionarNovaPeca(&fila);
                } else {
                    printf("\n⚠️ Pilha de reserva cheia!\n");
                }
                break;

            case 3: // Usar peça reservada
                if (!usarPecaReservada(&pilha)) {
                    printf("\n⚠️ Nenhuma peça reservada.\n");
                }
                break;

            case 4:
                trocarPecaAtual(&fila, &pilha);
                break;

            case 5:
                trocaMultiplaTetris(&fila, &pilha);
                break;

            case 0:
                printf("\n🎮 Encerrando Tetris Stack...\n");
                break;

            default:
                printf("\n❌ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
