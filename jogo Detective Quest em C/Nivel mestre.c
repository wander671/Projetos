#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

/* =====================================================
   STRUCTS
   ===================================================== */

/* Estrutura da árvore binária de salas */
typedef struct Sala {
    char nome[30];
    char pista[50]; // pista associada à sala
    struct Sala *esq, *dir;
} Sala;

/* Estrutura da BST de pistas coletadas */
typedef struct Pista {
    char descricao[50];
    struct Pista *esq, *dir;
} Pista;

/* Estrutura da tabela hash (pista -> suspeito) */
typedef struct Hash {
    char pista[50];
    char suspeito[30];
    struct Hash *prox;
} Hash;

/* =====================================================
   VARIÁVEIS GLOBAIS
   ===================================================== */

Hash* tabelaHash[TAM_HASH];

/* =====================================================
   FUNÇÃO HASH
   ===================================================== */
int funcaoHash(char *chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++)
        soma += chave[i];
    return soma % TAM_HASH;
}

/* =====================================================
   criarSala()
   Cria dinamicamente um cômodo da mansão
   ===================================================== */
Sala* criarSala(char *nome, char *pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esq = nova->dir = NULL;
    return nova;
}

/* =====================================================
   inserirPista() / adicionarPista()
   Insere pista na BST de pistas coletadas
   ===================================================== */
Pista* inserirPista(Pista* raiz, char *descricao) {
    if (raiz == NULL) {
        Pista* nova = (Pista*) malloc(sizeof(Pista));
        strcpy(nova->descricao, descricao);
        nova->esq = nova->dir = NULL;
        return nova;
    }

    if (strcmp(descricao, raiz->descricao) < 0)
        raiz->esq = inserirPista(raiz->esq, descricao);
    else if (strcmp(descricao, raiz->descricao) > 0)
        raiz->dir = inserirPista(raiz->dir, descricao);

    return raiz;
}

/* =====================================================
   inserirNaHash()
   Associa pista a um suspeito na tabela hash
   ===================================================== */
void inserirNaHash(char *pista, char *suspeito) {
    int indice = funcaoHash(pista);
    Hash* novo = (Hash*) malloc(sizeof(Hash));

    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabelaHash[indice];
    tabelaHash[indice] = novo;
}

/* =====================================================
   encontrarSuspeito()
   Retorna o suspeito associado a uma pista
   ===================================================== */
char* encontrarSuspeito(char *pista) {
    int indice = funcaoHash(pista);
    Hash* atual = tabelaHash[indice];

    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0)
            return atual->suspeito;
        atual = atual->prox;
    }
    return NULL;
}

/* =====================================================
   explorarSalas()
   Permite navegação interativa pela mansão
   ===================================================== */
void explorarSalas(Sala *atual, Pista **bstPistas) {
    char opcao;

    while (atual != NULL) {
        printf("\n🏠 Você está no cômodo: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("🔎 Pista encontrada: %s\n", atual->pista);
            *bstPistas = inserirPista(*bstPistas, atual->pista);
        }

        printf("\nPara onde deseja ir?\n");
        printf("[e] Esquerda | [d] Direita | [s] Sair\n");
        scanf(" %c", &opcao);

        if (opcao == 'e')
            atual = atual->esq;
        else if (opcao == 'd')
            atual = atual->dir;
        else if (opcao == 's')
            break;
        else
            printf("Opção inválida!\n");
    }
}

/* =====================================================
   listarPistas()
   Percorre a BST e exibe pistas coletadas
   ===================================================== */
void listarPistas(Pista *raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esq);
        printf("- %s\n", raiz->descricao);
        listarPistas(raiz->dir);
    }
}

/* =====================================================
   contarPistasSuspeito()
   Conta quantas pistas apontam para um suspeito
   ===================================================== */
int contarPistasSuspeito(Pista *raiz, char *suspeito) {
    if (raiz == NULL)
        return 0;

    int cont = contarPistasSuspeito(raiz->esq, suspeito);

    char *s = encontrarSuspeito(raiz->descricao);
    if (s != NULL && strcmp(s, suspeito) == 0)
        cont++;

    cont += contarPistasSuspeito(raiz->dir, suspeito);
    return cont;
}

/* =====================================================
   verificarSuspeitoFinal()
   Fase final do julgamento
   ===================================================== */
void verificarSuspeitoFinal(Pista *bstPistas) {
    char acusado[30];
    printf("\n⚖️ Digite o nome do suspeito acusado: ");
    scanf(" %s", acusado);

    int qtd = contarPistasSuspeito(bstPistas, acusado);

    if (qtd >= 2)
        printf("\n✅ CULPADO! Há %d pistas contra %s.\n", qtd, acusado);
    else
        printf("\n❌ INOCENTE! Apenas %d pista(s) encontradas.\n", qtd);
}

/* =====================================================
   MAIN
   ===================================================== */
int main() {
    Pista *bstPistas = NULL;

    for (int i = 0; i < TAM_HASH; i++)
        tabelaHash[i] = NULL;

    /* Montagem fixa da mansão */
    Sala *entrada = criarSala("Entrada", "");
    Sala *biblioteca = criarSala("Biblioteca", "Livro rasgado");
    Sala *cozinha = criarSala("Cozinha", "Faca ensanguentada");
    Sala *quarto = criarSala("Quarto", "Pegadas suspeitas");
    Sala *escritorio = criarSala("Escritório", "Carta ameaçadora");

    entrada->esq = biblioteca;
    entrada->dir = cozinha;
    biblioteca->esq = quarto;
    biblioteca->dir = escritorio;

    /* Associações pista -> suspeito */
    inserirNaHash("Livro rasgado", "Carlos");
    inserirNaHash("Faca ensanguentada", "Ana");
    inserirNaHash("Pegadas suspeitas", "Carlos");
    inserirNaHash("Carta ameaçadora", "Ana");

    printf("🕵️ Bem-vindo ao Detective Quest!\n");

    explorarSalas(entrada, &bstPistas);

    printf("\n📜 Pistas coletadas:\n");
    listarPistas(bstPistas);

    verificarSuspeitoFinal(bstPistas);

    return 0;
}
