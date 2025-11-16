//Christiano Gonçalves Araujo
//Gabriel Felicio
//Joao Francisco
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define limites min e max para linhas e colunas do tabuleiro
#define MIN_LINHAS 5
#define MAX_LINHAS 15
#define MIN_COLUNAS 5
#define MAX_COLUNAS 15

int totalLinhas, totalColunas, totalBombas;

// Matrizes que guardam o estado do jogo
int campoBombas[MAX_LINHAS][MAX_COLUNAS];
int campoAberto[MAX_LINHAS][MAX_COLUNAS];
int campoBandeira[MAX_LINHAS][MAX_COLUNAS];
int campoVizinhos[MAX_LINHAS][MAX_COLUNAS];

// Declaração das funções usadas
void inicializarCampo();
void sortearBombas();
void calcularBombasVizinhas();
void imprimirCampo(int revelarTudo);
void abrirCasa(int linha, int coluna);
int verificarVitoria();
int colunaParaIndice(char coluna);

// Converte letra da coluna para índice numérico (0 a n-1)
int colunaParaIndice(char coluna) {
    if (coluna >= 'a' && coluna <= 'z') {
        return coluna - 'a';
    } else if (coluna >= 'A' && coluna <= 'Z') {
        return coluna - 'A';
    } else {
        return -1;
    }
}

int main() {
    // Inicializa gerador de números aleatórios para posicionar bombas
    srand(time(NULL));

    // Entrada e validação do número de linhas do tabuleiro
    do {
        printf("Digite o numero de linhas (%d-%d): ", MIN_LINHAS, MAX_LINHAS);
        if (scanf("%d", &totalLinhas) != 1) {
            printf("Entrada invalida!\n");
            while(getchar() != '\n');
            totalLinhas = 0;
        }
    } while (totalLinhas < MIN_LINHAS || totalLinhas > MAX_LINHAS);

    // Entrada e validação do número de colunas do tabuleiro
    do {
        printf("Digite o numero de colunas (%d-%d): ", MIN_COLUNAS, MAX_COLUNAS);
        if (scanf("%d", &totalColunas) != 1) {
            printf("Entrada invalida!\n");
            while(getchar() != '\n');
            totalColunas = 0;
        }
    } while (totalColunas < MIN_COLUNAS || totalColunas > MAX_COLUNAS);

    // Entrada e validação da quantidade de bombas, garantindo que caibam no tabuleiro
    int maxBombas = totalLinhas * totalColunas - 1;
    do {
        printf("Digite o numero de bombas (1-%d): ", maxBombas);
        if (scanf("%d", &totalBombas) != 1) {
            printf("Entrada invalida!\n");
            while(getchar() != '\n');
            totalBombas = 0;
        }
    } while (totalBombas < 1 || totalBombas > maxBombas);

    // Inicializa o tabuleiro e configura bombas e números
    inicializarCampo();
    sortearBombas();
    calcularBombasVizinhas();

    // Loop principal do jogo, até vitória ou derrota
    while (1) {
        imprimirCampo(0); // Mostra tabuleiro sem revelar tudo

        // Leitura da ação do jogador
        printf("\nDigite a acao (R para revelar, F para bandeira): ");
        char acao;
        while (1) {
            scanf(" %c", &acao);
            if (acao == 'R' || acao == 'r' || acao == 'F' || acao == 'f') {
                break;
            } else {
                printf("Acao invalida. Digite R para revelar ou F para bandeira: ");
                while(getchar() != '\n'); // Limpa buffer
            }
        }
        acao = (acao == 'r' ? 'R' : (acao == 'f' ? 'F' : acao));

        // Leitura e validação da linha escolhida
        int linhaDigitada = -1;
        do {
            printf("Digite o numero da linha (0 a %d): ", totalLinhas - 1);
            if (scanf("%d", &linhaDigitada) != 1 || linhaDigitada < 0 || linhaDigitada >= totalLinhas) {
                printf("Linha invalida.\n");
                while(getchar() != '\n');
                linhaDigitada = -1;
            }
        } while (linhaDigitada == -1);

        // Leitura e validação da coluna escolhida
        char colunaChar;
        int colunaDigitada = -1;
        do {
            printf("Digite a letra da coluna (A a %c): ", 'A' + totalColunas - 1);
            scanf(" %c", &colunaChar);
            colunaDigitada = colunaParaIndice(colunaChar);
            if (colunaDigitada == -1 || colunaDigitada >= totalColunas) {
                printf("Coluna invalida.\n");
                while(getchar() != '\n');
                colunaDigitada = -1;
            }
        } while (colunaDigitada == -1);

        // Atua conforme a ação escolhida
        if (acao == 'R') {
            if (campoAberto[linhaDigitada][colunaDigitada]) {
                printf("Casa ja esta aberta!\n");
                continue;
            }
            if (campoBombas[linhaDigitada][colunaDigitada]) {
                printf("BOOM! Voce perdeu.\n");
                imprimirCampo(1); // Revela tudo após perder
                break;
            }
            abrirCasa(linhaDigitada, colunaDigitada);
        } else { // F para bandeira
            if (campoAberto[linhaDigitada][colunaDigitada]) {
                printf("Nao pode colocar bandeira em casa aberta!\n");
                continue;
            }
            campoBandeira[linhaDigitada][colunaDigitada] = !campoBandeira[linhaDigitada][colunaDigitada];
        }

        // Verifica se o jogador venceu
        if (verificarVitoria()) {
            printf("Parabens! Voce venceu.\n");
            imprimirCampo(1); // Revela o tabuleiro todo na vitória
            break;
        }
    }

    return 0;
}

// Inicializa as matrizes do tabuleiro zeradas
void inicializarCampo() {
    int i, j;
    for (i = 0; i < totalLinhas; i++) {
        for (j = 0; j < totalColunas; j++) {
            campoBombas[i][j] = 0;
            campoAberto[i][j] = 0;
            campoBandeira[i][j] = 0;
            campoVizinhos[i][j] = 0;
        }
    }
}

// Posiciona bombas aleatoriamente no tabuleiro
void sortearBombas() {
    int cont = 0;
    while (cont < totalBombas) {
        int i = rand() % totalLinhas;
        int j = rand() % totalColunas;
        if (!campoBombas[i][j]) {
            campoBombas[i][j] = 1;
            cont++;
        }
    }
}

// Calcula a quantidade de bombas ao redor de cada célula
void calcularBombasVizinhas() {
    int i, j, deltaLinha, deltaColuna;
    for (i = 0; i < totalLinhas; i++) {
        for (j = 0; j < totalColunas; j++) {
            int total = 0;
            for (deltaLinha = -1; deltaLinha <= 1; deltaLinha++) {
                for (deltaColuna = -1; deltaColuna <= 1; deltaColuna++) {
                    int lin = i + deltaLinha;
                    int col = j + deltaColuna;
                    if (lin >= 0 && lin < totalLinhas && col >= 0 && col < totalColunas) {
                        total += campoBombas[lin][col];
                    }
                }
            }
            campoVizinhos[i][j] = total - campoBombas[i][j];
        }
    }
}

// Imprime o tabuleiro no console, com símbolos representando estados das células
void imprimirCampo(int revelarTudo) {
    int i, j;
    printf("   ");
    for (j = 0; j < totalColunas; j++) printf(" %c", 'A' + j);
    printf("\n");
    for (i = 0; i < totalLinhas; i++) {
        printf("%2d ", i);
        for (j = 0; j < totalColunas; j++) {
            if (campoAberto[i][j]) {
                if (campoBombas[i][j]) printf(" X");
                else if (campoVizinhos[i][j] > 0) printf(" %d", campoVizinhos[i][j]);
                else printf("  ");
            } else if (campoBandeira[i][j]) {
                printf(" F");
            } else {
                if (revelarTudo && campoBombas[i][j]) printf(" X");
                else printf(" ~");
            }
        }
        printf(" %2d\n", i);
    }
    printf("   ");
    for (j = 0; j < totalColunas; j++) printf(" %c", 'A' + j);
    printf("\n");
}

// Abre casa e suas vizinhas recursivamente se não tiver bombas adjacentes
void abrirCasa(int linha, int coluna) {
    int deltaLinha, deltaColuna;
    if (linha < 0 || linha >= totalLinhas || coluna < 0 || coluna >= totalColunas) return;
    if (campoAberto[linha][coluna] || campoBandeira[linha][coluna]) return;
    if (campoBombas[linha][coluna]) return;

    campoAberto[linha][coluna] = 1;

    if (campoVizinhos[linha][coluna] == 0) {
        for (deltaLinha = -1; deltaLinha <= 1; deltaLinha++) {
            for (deltaColuna = -1; deltaColuna <= 1; deltaColuna++) {
                if (deltaLinha != 0 || deltaColuna != 0) {
                    abrirCasa(linha + deltaLinha, coluna + deltaColuna);
                }
            }
        }
    }
}

// Verifica se o jogador venceu: todas as casas sem bombas abertas e todas as bombas marcadas
int verificarVitoria() {
    int i, j;
    for (i = 0; i < totalLinhas; i++) {
        for (j = 0; j < totalColunas; j++) {
            if (!campoBombas[i][j] && !campoAberto[i][j]) return 0;
            if (campoBombas[i][j] && !campoBandeira[i][j]) return 0;
        }
    }
    return 1;
}