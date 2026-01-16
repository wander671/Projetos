#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20   // Tamanho máximo do vetor de componentes

// =====================================================
// ESTRUTURA PRINCIPAL
// Representa um componente da torre de fuga
// =====================================================
typedef struct {
    char nome[30];     // Nome do componente
    char tipo[20];     // Tipo do componente
    int prioridade;    // Prioridade (quanto menor, mais importante)
} Componente;

// =====================================================
// VARIÁVEIS GLOBAIS
// =====================================================
int comparacoes = 0;   // Contador de comparações dos algoritmos

// =====================================================
// FUNÇÃO UTILITÁRIA
// Remove o '\n' inserido pelo fgets
// =====================================================
void limparQuebraLinha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// =====================================================
// FUNÇÃO PARA EXIBIR OS COMPONENTES
// =====================================================
void mostrarComponentes(Componente v[], int n) {
    printf("\n🏗️ COMPONENTES DA TORRE DE FUGA\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }

    printf("---------------------------------------------\n");
}

// =====================================================
// BUBBLE SORT
// Ordena os componentes pelo NOME (ordem alfabética)
// =====================================================
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;

            // Compara os nomes dos componentes
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                // Troca os elementos
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// =====================================================
// INSERTION SORT
// Ordena os componentes pelo TIPO
// =====================================================
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        // Move os elementos maiores para a direita
        while (j >= 0) {
            comparacoes++;
            if (strcmp(v[j].tipo, chave.tipo) > 0) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
}

// =====================================================
// SELECTION SORT
// Ordena os componentes pela PRIORIDADE
// =====================================================
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        // Procura o menor valor de prioridade
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[menor].prioridade) {
                menor = j;
            }
        }

        // Realiza a troca
        if (menor != i) {
            Componente temp = v[i];
            v[i] = v[menor];
            v[menor] = temp;
        }
    }
}

// =====================================================
// BUSCA BINÁRIA
// Procura um componente pelo NOME
// OBS: O vetor DEVE estar ordenado por nome
// =====================================================
int buscaBinariaPorNome(Componente v[], int n, char nomeBusca[]) {
    int inicio = 0;
    int fim = n - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(v[meio].nome, nomeBusca);

        if (cmp == 0) {
            return meio;  // Elemento encontrado
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1; // Não encontrado
}

// =====================================================
// FUNÇÃO PRINCIPAL
// =====================================================
int main() {
    Componente componentes[MAX]; // Vetor de componentes
    int total = 0;               // Quantidade cadastrada
    int opcao;
    int pos;                     // Posição da busca binária
    clock_t inicio, fim;
    double tempo;
    char nomeBusca[30];

    do {
        printf("\n🔥 ÚLTIMA SAFE ZONE – TORRE DE FUGA 🔥\n");
        printf("1 - Cadastrar componentes da torre\n");
        printf("2 - Ordenar por NOME (Bubble Sort)\n");
        printf("3 - Ordenar por TIPO (Insertion Sort)\n");
        printf("4 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5 - Buscar componente-chave (Busca Binária)\n");
        printf("0 - Abandonar a ilha\n");
        printf("Escolha sua ação: ");
        scanf("%d", &opcao);
        getchar(); // Limpa buffer

        switch (opcao) {

        case 1:
            if (total >= MAX) {
                printf("⚠️ Mochila cheia! Não cabe mais componentes.\n");
                break;
            }

            printf("\nNome do componente: ");
            fgets(componentes[total].nome, 30, stdin);
            limparQuebraLinha(componentes[total].nome);

            printf("Tipo do componente: ");
            fgets(componentes[total].tipo, 20, stdin);
            limparQuebraLinha(componentes[total].tipo);

            printf("Prioridade (1 a 10): ");
            scanf("%d", &componentes[total].prioridade);
            getchar();

            total++;
            printf("✅ Componente coletado com sucesso!\n");
            break;

        case 2:
            inicio = clock();
            bubbleSortNome(componentes, total);
            fim = clock();

            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            mostrarComponentes(componentes, total);
            printf("🔍 Comparações: %d\n", comparacoes);
            printf("⏱️ Tempo: %.6f segundos\n", tempo);
            break;

        case 3:
            inicio = clock();
            insertionSortTipo(componentes, total);
            fim = clock();

            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            mostrarComponentes(componentes, total);
            printf("🔍 Comparações: %d\n", comparacoes);
            printf("⏱️ Tempo: %.6f segundos\n", tempo);
            break;

        case 4:
            inicio = clock();
            selectionSortPrioridade(componentes, total);
            fim = clock();

            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            mostrarComponentes(componentes, total);
            printf("🔍 Comparações: %d\n", comparacoes);
            printf("⏱️ Tempo: %.6f segundos\n", tempo);
            break;

        case 5:
            // Garante ordenação antes da busca binária
            bubbleSortNome(componentes, total);

            printf("\nDigite o NOME do componente-chave: ");
            fgets(nomeBusca, 30, stdin);
            limparQuebraLinha(nomeBusca);

            pos = buscaBinariaPorNome(componentes, total, nomeBusca);

            if (pos != -1) {
                printf("✅ COMPONENTE ENCONTRADO!\n");
                printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                       componentes[pos].nome,
                       componentes[pos].tipo,
                       componentes[pos].prioridade);
                printf("🚀 Torre de fuga ATIVADA!\n");
            } else {
                printf("❌ Componente não encontrado.\n");
            }
            break;

        case 0:
            printf("🏝️ Você abandonou a missão...\n");
            break;

        default:
            printf("❌ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
