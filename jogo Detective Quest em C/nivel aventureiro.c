#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================
   STRUCTS
   ============================ */

/* Estrutura que representa uma sala da mansão */
typedef struct Sala {
    char nome[50];
    char pista[100];           // pista pode estar vazia
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

/* Nó da árvore BST de pistas */
typedef struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

/* ============================
   FUNÇÃO: criarSala
   Cria dinamicamente uma sala
   ============================ */
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));

    strcpy(nova->nome, nome);

    if (pista != NULL)
        strcpy(nova->pista, pista);
    else
        nova->pista[0] = '\0'; // sala sem pista

    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

/* ============================
   FUNÇÃO: inserirPista
   Insere pista na BST
   ============================ */
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

/* ============================
   FUNÇÃO: explorarSalasComPistas
   Navegação pela mansão
   ============================ */
void explorarSalasComPistas(Sala* atual, PistaNode** pistasColetadas) {
    char escolha;

    while (atual != NULL) {
        printf("\n=================================\n");
        printf("Você está em: %s\n", atual->nome);

        /* Se houver pista, coleta automaticamente */
        if (strlen(atual->pista) > 0) {
            printf("🔎 Pista encontrada: %s\n", atual->pista);
            *pistasColetadas = inserirPista(*pistasColetadas, atual->pista);
            atual->pista[0] = '\0'; // evita coletar novamente
        }

        printf("\nCaminhos disponíveis:\n");
        if (atual->esquerda) printf(" (e) Esquerda\n");
        if (atual->direita)  printf(" (d) Direita\n");
        printf(" (s) Sair da exploração\n");

        printf("Escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda)
            atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita)
            atual = atual->direita;
        else if (escolha == 's')
            break;
        else
            printf("❌ Opção inválida!\n");
    }
}

/* ============================
   FUNÇÃO: exibirPistas
   Exibe pistas em ordem alfabética
   ============================ */
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

/* ============================
   FUNÇÃO PRINCIPAL
   ============================ */
int main() {
    /* Construção do mapa da mansão */
    Sala* hall = criarSala("Hall de Entrada", NULL);
    Sala* salaEstar = criarSala("Sala de Estar", "Pegadas suspeitas no tapete");
    Sala* cozinha = criarSala("Cozinha", "Faca com manchas estranhas");
    Sala* escritorio = criarSala("Escritório", "Carta rasgada na gaveta");
    Sala* quarto = criarSala("Quarto", "Relógio quebrado no chão");

    /* Montagem da árvore binária (mapa fixo) */
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = escritorio;
    salaEstar->direita = quarto;

    /* Árvore BST de pistas coletadas */
    PistaNode* pistasColetadas = NULL;

    printf("🕵️ Bem-vindo ao Detective Quest!\n");
    explorarSalasComPistas(hall, &pistasColetadas);

    /* Exibição final das pistas */
    printf("\n=================================\n");
    printf("📂 Pistas coletadas (ordem alfabética):\n");
    exibirPistas(pistasColetadas);

    printf("\nInvestigação encerrada.\n");

    return 0;
}
