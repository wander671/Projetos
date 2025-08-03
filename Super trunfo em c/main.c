#include <stdio.h>

int main() {
    // Carta 1
    char estado1[3], codigo1[10], nome1[100];
    unsigned long int populacao1;
    float area1, pib1;
    int pontos1;
    float densidade1, pibPerCapita1, superPoder1;

    // Carta 2
    char estado2[3], codigo2[10], nome2[100];
    unsigned long int populacao2;
    float area2, pib2;
    int pontos2;
    float densidade2, pibPerCapita2, superPoder2;

    // Leitura Carta 1
    printf("Carta 1:\n");
    printf("Estado: ");
    scanf("%s", estado1);
    printf("Código: ");
    scanf("%s", codigo1);
    printf("Nome da Cidade: ");
    scanf(" %[^\n]", nome1);
    printf("População: ");
    scanf("%lu", &populacao1);
    printf("Área (km²): ");
    scanf("%f", &area1);
    printf("PIB (em bilhões de reais): ");
    scanf("%f", &pib1);
    printf("Número de Pontos Turísticos: ");
    scanf("%d", &pontos1);

    // Leitura Carta 2
    printf("\nCarta 2:\n");
    printf("Estado: ");
    scanf("%s", estado2);
    printf("Código: ");
    scanf("%s", codigo2);
    printf("Nome da Cidade: ");
    scanf(" %[^\n]", nome2);
    printf("População: ");
    scanf("%lu", &populacao2);
    printf("Área (km²): ");
    scanf("%f", &area2);
    printf("PIB (em bilhões de reais): ");
    scanf("%f", &pib2);
    printf("Número de Pontos Turísticos: ");
    scanf("%d", &pontos2);

    // Cálculos
    densidade1 = populacao1 / area1;
    pibPerCapita1 = (pib1 * 1000000000) / populacao1;
    superPoder1 = (float)populacao1 + area1 + (pib1 * 1000000000) + pontos1 + pibPerCapita1 + (1.0f / densidade1);

    densidade2 = populacao2 / area2;
    pibPerCapita2 = (pib2 * 1000000000) / populacao2;
    superPoder2 = (float)populacao2 + area2 + (pib2 * 1000000000) + pontos2 + pibPerCapita2 + (1.0f / densidade2);

    // Exibição dos dados 
    printf("\nCarta 1:\n");
    printf("Acre: %s\n", estado1);
    printf("A01: %s\n", codigo1);
    printf("Rio Branco: %s\n", nome1);
    printf("880.631: %lu\n", populacao1);
    printf("152.581 : %.2f km²\n", area1);
    printf("55.247: %.2f bilhões de reais\n", pib1);
    printf("6: %d\n", pontos1);
    printf("41.3: %.2f hab/km²\n", densidade1);
    printf("R$ 55247.45: %.2f reais\n", pibPerCapita1);
    printf("830.018: %.2f\n", superPoder1);

    printf("\nCarta 2:\n");
    printf("Alagoas: %s\n", estado2);
    printf("A02: %s\n", codigo2);
    printf("maceió: %s\n", nome2);
    printf("964.631: %lu\n", populacao2);
    printf("265.581: %.2f km²\n", area2);
    printf("77.248: %.2f bilhões de reais\n", pib2);
    printf("7: %d\n", pontos2);
    printf("56.4: %.2f hab/km²\n", densidade2);
    printf("R$ 65784.64: %.2f reais\n", pibPerCapita2);
    printf("787.987: %.2f\n", superPoder2);

    // Comparações
    printf("\nComparação de Cartas:\n");
    printf("População: Carta 1 venceu (%d)\n", populacao1 > populacao2);
    printf("Área: Carta 1 venceu (%d)\n", area1 > area2);
    printf("PIB: Carta 1 venceu (%d)\n", pib1 > pib2);
    printf("Pontos Turísticos: Carta 1 venceu (%d)\n", pontos1 > pontos2);
    printf("Densidade Populacional: Carta 1 venceu (%d)\n", densidade1 < densidade2);
    printf("PIB per Capita: Carta 1 venceu (%d)\n", pibPerCapita1 > pibPerCapita2);
    printf("Super Poder: Carta 1 venceu (%d)\n", superPoder1 > superPoder2);

    return 0;
}
