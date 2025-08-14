#include <stdio.h>
#include <string.h>

struct Carta {
    char estado[3];
    char codigo[4];
    char nomeCidade[50];
    int populacao;
    float area;
    float pib;
    int numPontosTuristicos;
    float densidadePop;
    float pibPerCapita;
};

// Função para exibir menu e retornar escolha
int menuEscolha() {
    int opcao;
    printf("\nEscolha o atributo para comparar:\n");
    printf("1 - Populacao (maior vence)\n");
    printf("2 - Area (maior vence)\n");
    printf("3 - PIB (maior vence)\n");
    printf("4 - Densidade Populacional (menor vence)\n");
    printf("5 - PIB per Capita (maior vence)\n");
    printf("6 - Pontos Turisticos (maior vence)\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

// Função para comparar um atributo
int comparar(struct Carta c1, struct Carta c2, int atributo) {
    switch (atributo) {
        case 1: return (c1.populacao > c2.populacao) ? 1 : (c2.populacao > c1.populacao) ? 2 : 0;
        case 2: return (c1.area > c2.area) ? 1 : (c2.area > c1.area) ? 2 : 0;
        case 3: return (c1.pib > c2.pib) ? 1 : (c2.pib > c1.pib) ? 2 : 0;
        case 4: return (c1.densidadePop < c2.densidadePop) ? 1 : (c2.densidadePop < c1.densidadePop) ? 2 : 0;
        case 5: return (c1.pibPerCapita > c2.pibPerCapita) ? 1 : (c2.pibPerCapita > c1.pibPerCapita) ? 2 : 0;
        case 6: return (c1.numPontosTuristicos > c2.numPontosTuristicos) ? 1 : (c2.numPontosTuristicos > c1.numPontosTuristicos) ? 2 : 0;
        default: return -1; // inválido
    }
}

int main() {
    struct Carta carta1, carta2;

    // Cadastro interativo das cartas
    printf("Cadastro da Carta 1:\n");
    printf("Estado: "); scanf("%s", carta1.estado);
    printf("Codigo: "); scanf("%s", carta1.codigo);
    printf("Cidade: "); scanf(" %[^\n]", carta1.nomeCidade);
    printf("Populacao: "); scanf("%d", &carta1.populacao);
    printf("Area (km2): "); scanf("%f", &carta1.area);
    printf("PIB (em bilhões): "); scanf("%f", &carta1.pib);
    printf("Pontos Turisticos: "); scanf("%d", &carta1.numPontosTuristicos);

    printf("\nCadastro da Carta 2:\n");
    printf("Estado: "); scanf("%s", carta2.estado);
    printf("Codigo: "); scanf("%s", carta2.codigo);
    printf("Cidade: "); scanf(" %[^\n]", carta2.nomeCidade);
    printf("Populacao: "); scanf("%d", &carta2.populacao);
    printf("Area (km2): "); scanf("%f", &carta2.area);
    printf("PIB (em bilhões): "); scanf("%f", &carta2.pib);
    printf("Pontos Turisticos: "); scanf("%d", &carta2.numPontosTuristicos);

    // Cálculos automáticos
    carta1.densidadePop = carta1.populacao / carta1.area;
    carta2.densidadePop = carta2.populacao / carta2.area;
    carta1.pibPerCapita = (carta1.pib * 123000000) / carta1.populacao;
    carta2.pibPerCapita = (carta2.pib * 600000000) / carta2.populacao;

    // Jogador escolhe dois atributos
    printf("\n=== Escolha do primeiro atributo ===\n");
    int attr1 = menuEscolha();

    printf("\n=== Escolha do segundo atributo ===\n");
    int attr2 = menuEscolha();

    // Comparação
    int pontos1 = 0, pontos2 = 0;

    int res1 = comparar(carta1, carta2, attr1);
    (res1 == 1) ? pontos1++ : (res1 == 2) ? pontos2++ : 0;

    int res2 = comparar(carta1, carta2, attr2);
    (res2 == 1) ? pontos1++ : (res2 == 2) ? pontos2++ : 0;

    // Resultado final
    printf("\n--- RESULTADO FINAL ---\n");
    printf("%s: %d pontos\n", carta1.nomeCidade, pontos1);
    printf("%s: %d pontos\n", carta2.nomeCidade, pontos2);

    if (pontos1 > pontos2) {
        printf("Vencedor: %s\n", carta1.nomeCidade);
    } else if (pontos2 > pontos1) {
        printf("Vencedor: %s\n", carta2.nomeCidade);
    } else {
        printf("Empate!\n");
    }

    return 0;
}
