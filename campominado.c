#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 20
#define COLUNAS 24
#define BOMBAS 100

void inicializar();
void sortear_bombas();
void calcular_vizinhos();
void imprimir(int revelar);
void abrir_casa(int linha, int coluna);

int campo_bombas[LINHAS][COLUNAS];
int campo_aberto[LINHAS][COLUNAS];
int campo_vizinhos[LINHAS][COLUNAS];

int main() {
    int aberto = 0;
    int total = LINHAS * COLUNAS - BOMBAS;
    int linha, coluna;

    srand(time(NULL));
    inicializar();
    sortear_bombas();
    calcular_vizinhos();

    while (1) {
        imprimir(0);
        printf("\nDigite linha e coluna (ex: 5 10): ");
        if (scanf("%d%d", &linha, &coluna) != 2 ||
            linha < 0 || linha >= LINHAS ||
            coluna < 0 || coluna >= COLUNAS) {
            printf("Entrada inválida.\n");
            char buffer[100];
            fgets(buffer, sizeof(buffer), stdin);  // Limpa o restante da linha no buffer
            continue;
        }

        if (campo_aberto[linha][coluna]) {
            printf("Já está aberta!\n");
            continue;
        }

        if (campo_bombas[linha][coluna]) {
            printf("BOOM! Você perdeu.\n");
            imprimir(1);
            break;
        }

        abrir_casa(linha, coluna);

        aberto = 0;
        for (int i = 0; i < LINHAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                if (campo_aberto[i][j] && !campo_bombas[i][j]) {
                    aberto++;
                }
            }
        }

        if (aberto == total) {
            printf("Parabéns! Você venceu.\n");
            imprimir(1);
            break;
        }
    }
    return 0;
}

void inicializar() {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            campo_bombas[i][j] = 0;
            campo_aberto[i][j] = 0;
            campo_vizinhos[i][j] = 0;
        }
    }
}

void sortear_bombas() {
    int cont = 0;
    while (cont < BOMBAS) {
        int i = rand() % LINHAS;
        int j = rand() % COLUNAS;
        if (campo_bombas[i][j] == 0) {
            campo_bombas[i][j] = 1;
            cont++;
        }
    }
}

void calcular_vizinhos() {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            int total = 0;
            for (int deltaLinha = -1; deltaLinha <= 1; deltaLinha++) {
                for (int deltaColuna = -1; deltaColuna <= 1; deltaColuna++) {
                    int linhaVizinha = i + deltaLinha;
                    int colunaVizinha = j + deltaColuna;
                    if (linhaVizinha >= 0 && linhaVizinha < LINHAS &&
                        colunaVizinha >= 0 && colunaVizinha < COLUNAS) {
                        total += campo_bombas[linhaVizinha][colunaVizinha];
                    }
                }
            }
            campo_vizinhos[i][j] = total - campo_bombas[i][j];
        }
    }
}

void imprimir(int revelar) {
    printf("   ");
    for (int j = 0; j < COLUNAS; j++) {
        printf("%2d", j);
    }
    printf("\n");

    for (int i = 0; i < LINHAS; i++) {
        printf("%2d ", i);
        for (int j = 0; j < COLUNAS; j++) {
            if (!campo_aberto[i][j]) {
                if (revelar && campo_bombas[i][j]) {
                    printf(" *");
                } else {
                    printf(" ■");
                }
            }
            else if (campo_bombas[i][j]) {
                printf(" *");
            }
            else if (campo_vizinhos[i][j]) {
                printf(" %d", campo_vizinhos[i][j]);
            }
            else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void abrir_casa(int linha, int coluna) {
    if (linha < 0 || linha >= LINHAS || coluna < 0 || coluna >= COLUNAS) {
        return;
    }
    if (campo_aberto[linha][coluna]) {
        return;
    }

    campo_aberto[linha][coluna] = 1;

    if (campo_vizinhos[linha][coluna] == 0 && campo_bombas[linha][coluna] == 0) {
        for (int deltaLinha = -1; deltaLinha <= 1; deltaLinha++) {
            for (int deltaColuna = -1; deltaColuna <= 1; deltaColuna++) {
                if (deltaLinha != 0 || deltaColuna != 0) {
                    abrir_casa(linha + deltaLinha, coluna + deltaColuna);
                }
            }
        }
    }
}