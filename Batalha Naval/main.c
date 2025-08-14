#include <stdio.h>

#define TAM_TAB 10
#define TAM_NAVIO 3

// Função para validar posição dentro do tabuleiro
int posicao_valida(int linha, int coluna) {
    return linha >= 0 && linha < TAM_TAB && coluna >= 0 && coluna < TAM_TAB;
}

// Funções para posicionar navios (horizontal, vertical, diagonal)
void posicionar_navio_horizontal(int tab[TAM_TAB][TAM_TAB], int linha, int coluna) {
    for(int i = 0; i < TAM_NAVIO; i++) {
        if(posicao_valida(linha, coluna + i))
            tab[linha][coluna + i] = 3;
    }
}

void posicionar_navio_vertical(int tab[TAM_TAB][TAM_TAB], int linha, int coluna) {
    for(int i = 0; i < TAM_NAVIO; i++) {
        if(posicao_valida(linha + i, coluna))
            tab[linha + i][coluna] = 3;
    }
}

void posicionar_navio_diagonal_desc(int tab[TAM_TAB][TAM_TAB], int linha, int coluna) {
    for(int i = 0; i < TAM_NAVIO; i++) {
        if(posicao_valida(linha + i, coluna + i))
            tab[linha + i][coluna + i] = 3;
    }
}

void posicionar_navio_diagonal_asc(int tab[TAM_TAB][TAM_TAB], int linha, int coluna) {
    for(int i = 0; i < TAM_NAVIO; i++) {
        if(posicao_valida(linha - i, coluna + i))
            tab[linha - i][coluna + i] = 3;
    }
}

// Função para aplicar habilidade no tabuleiro
void aplicar_habilidade(int tab[TAM_TAB][TAM_TAB], int origem_linha, int origem_coluna, int tamanho, char tipo) {
    int metade = tamanho / 2;
    
    for(int i = 0; i < tamanho; i++) {
        for(int j = 0; j < tamanho; j++) {
            int linha_tab = origem_linha - metade + i;
            int col_tab = origem_coluna - metade + j;
            
            if(!posicao_valida(linha_tab, col_tab))
                continue;

            // Definir matriz de habilidade usando condicionais
            int afeta = 0;
            if(tipo == 'C') { // Cone descendente
                // Cria um cone com topo na origem
                if(i >= j - metade && i >= metade - j) afeta = 1;
            } else if(tipo == 'X') { // Cruz
                if(i == metade || j == metade) afeta = 1;
            } else if(tipo == 'O') { // Octaedro (losango)
                if(i + j >= metade && i + j <= 3*metade && j - i <= metade && i - j <= metade) afeta = 1;
            }

            if(afeta && tab[linha_tab][col_tab] == 0)
                tab[linha_tab][col_tab] = 5; // Marca área de efeito
        }
    }
}

// Função para exibir o tabuleiro
void exibir_tabuleiro(int tab[TAM_TAB][TAM_TAB]) {
    printf("Tabuleiro com Navios e Habilidades:\n");
    for(int i = 0; i < TAM_TAB; i++) {
        for(int j = 0; j < TAM_TAB; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB];

    // Inicializa tabuleiro com água (0)
    for(int i = 0; i < TAM_TAB; i++)
        for(int j = 0; j < TAM_TAB; j++)
            tabuleiro[i][j] = 0;

    // Posiciona navios
    posicionar_navio_horizontal(tabuleiro, 1, 1);
    posicionar_navio_vertical(tabuleiro, 5, 4);
    posicionar_navio_diagonal_desc(tabuleiro, 0, 6);
    posicionar_navio_diagonal_asc(tabuleiro, 9, 0);

    // Aplica habilidades
    aplicar_habilidade(tabuleiro, 2, 2, 5, 'C'); // Cone
    aplicar_habilidade(tabuleiro, 7, 5, 5, 'X'); // Cruz
    aplicar_habilidade(tabuleiro, 5, 7, 5, 'O'); // Octaedro

    // Exibe tabuleiro final
    exibir_tabuleiro(tabuleiro);

    return 0;
}
