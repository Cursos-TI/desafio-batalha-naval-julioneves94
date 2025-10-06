#include <stdio.h>
#include <stdlib.h> // Necessário para usar abs()

#define TAM 10
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5
#define TAM_NAVIO 3
#define TAM_HAB 5 // Tamanho das matrizes de habilidade (5x5)

// -------------------------------------------
// Função para exibir o tabuleiro com cabeçalho A–J e linhas numeradas
// -------------------------------------------
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    int i, j;
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");

    printf("    ");
    for (j = 0; j < TAM; j++) printf("%c ", 'A' + j);
    printf("\n   ---------------------\n");

    for (i = 0; i < TAM; i++) {
        if (i < 9)
            printf(" %d | ", i + 1);
        else
            printf("%d | ", i + 1);
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// -------------------------------------------
// Construir matriz de habilidade em forma de cone (↧)
// -------------------------------------------
void construirCone(int cone[TAM_HAB][TAM_HAB]) {
    int i, j;
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            // O cone começa estreito no topo e alarga embaixo
            if (j >= (TAM_HAB / 2 - i) && j <= (TAM_HAB / 2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// -------------------------------------------
// Construir matriz de habilidade em forma de cruz (+)
// -------------------------------------------
void construirCruz(int cruz[TAM_HAB][TAM_HAB]) {
    int i, j;
    int centro = TAM_HAB / 2;
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (i == centro || j == centro)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// -------------------------------------------
// Construir matriz de habilidade em forma de octaedro (losango)
// -------------------------------------------
void construirOctaedro(int octaedro[TAM_HAB][TAM_HAB]) {
    int i, j;
    int centro = TAM_HAB / 2;
    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            int manhattan = abs(i - centro) + abs(j - centro);
            if (manhattan <= centro)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// -------------------------------------------
// Aplica a área de habilidade no tabuleiro centralizando no ponto de origem
// -------------------------------------------
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int i, j;
    int offset = TAM_HAB / 2;

    for (i = 0; i < TAM_HAB; i++) {
        for (j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = origemLinha + (i - offset);
                int colunaTab = origemColuna + (j - offset);

                // Verifica se está dentro dos limites do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM) {
                    // Proteção opcional: não sobrescrever navios (3)
                    if (tabuleiro[linhaTab][colunaTab] != NAVIO)
                        tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                }
            }
        }
    }
}

// -------------------------------------------
// Função principal
// -------------------------------------------
int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // Inicializar o tabuleiro com água (0)
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // -------------------------------------------
    // POSICIONAMENTO DE NAVIOS
    // -------------------------------------------

    // Navio Horizontal
    int linhaH = 2, colH = 4;
    for (j = 0; j < TAM_NAVIO; j++)
        tabuleiro[linhaH][colH + j] = NAVIO;

    // Navio Vertical
    int linhaV = 6, colV = 1;
    for (i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaV + i][colV] = NAVIO;

    // Diagonal ↘
    int linhaD1 = 0, colD1 = 0;
    for (i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaD1 + i][colD1 + i] = NAVIO;

    // Diagonal ↙
    int linhaD2 = 0, colD2 = 9;
    for (i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaD2 + i][colD2 - i] = NAVIO;

    // -------------------------------------------
    // CRIAÇÃO DAS MATRIZES DE HABILIDADE
    // -------------------------------------------
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // -------------------------------------------
    // APLICAÇÃO DAS HABILIDADES NO TABULEIRO
    // -------------------------------------------

    aplicarHabilidade(tabuleiro, cone, 4, 4);       // Cone centrado em E5
    aplicarHabilidade(tabuleiro, cruz, 7, 7);       // Cruz centrada em H8
    aplicarHabilidade(tabuleiro, octaedro, 5, 2);   // Octaedro centrado em C6

    // -------------------------------------------
    // EXIBIÇÃO FINAL DO TABULEIRO
    // -------------------------------------------
    exibirTabuleiro(tabuleiro);

    return 0;
}