#include <stdio.h>

// ==============================
// Funções Recursivas
// ==============================

// Função recursiva para a Torre
void moverTorre(int casas) {
    if (casas <= 0) return;   // Caso base: nenhum movimento restante
    printf("Direita\n");       // Movimento da Torre
    moverTorre(casas - 1);     // Chamada recursiva para a próxima casa
}

// Função recursiva para a Rainha
void moverRainha(int casas) {
    if (casas <= 0) return;   // Caso base
    printf("Esquerda\n");      // Movimento da Rainha
    moverRainha(casas - 1);    // Recursão
}

// Função recursiva para o Bispo com loops aninhados
void moverBispo(int casasVertical, int casasHorizontal) {
    if (casasVertical <= 0) return; // Caso base vertical

    // Loop interno para simular a horizontal
    int i = 1;
    while (i <= casasHorizontal) {
        printf("Cima Direita\n");  // Cada passo diagonal
        i++;
    }

    // Chamada recursiva para a próxima linha vertical
    moverBispo(casasVertical - 1, casasHorizontal);
}

// ==============================
// Função para o Cavalo com loops complexos
// ==============================
void moverCavalo(int movimentosVertical, int movimentosHorizontal) {
    int v = 0, h = 0;  // Variáveis para contar movimentos vertical e horizontal

    while (v < movimentosVertical) {   // Loop externo: vertical
        printf("Cima\n");
        v++;

        // Loop interno: horizontal
        h = 0;
        while (h < movimentosHorizontal) {
            if (v != movimentosVertical) { // Só move horizontal depois do vertical
                h++;
                continue;  // Espera completar vertical antes de mover horizontal
            }
            printf("Direita\n"); 
            h++;
            break;  // Apenas uma casa na horizontal, depois sai
        }
    }
}

// ==============================
// Função principal
// ==============================
int main() {
    // Definição das casas para cada peça
    int casasTorre = 5;
    int casasRainha = 8;
    int casasBispoVertical = 5;
    int casasBispoHorizontal = 1; // cada linha diagonal move 1 casa horizontal
    int cavaloVertical = 2;
    int cavaloHorizontal = 1;

    // Movimentos da Torre
    printf("Movimento da Torre:\n");
    moverTorre(casasTorre);

    printf("\nMovimento do Bispo:\n");
    moverBispo(casasBispoVertical, casasBispoHorizontal);

    printf("\nMovimento da Rainha:\n");
    moverRainha(casasRainha);

    printf("\nMovimento do Cavalo:\n");
    moverCavalo(cavaloVertical, cavaloHorizontal);

    return 0;
}