#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define LINHAS 10
#define COLUNAS 12
#define BOMBAS 15

void inicializar();
void sortear_bombas();
void calcular_vizinhos();
void imprimir(int revelar);
void abrir_casa(int linha, int coluna);

int campo_bombas[LINHAS][COLUNAS];
int campo_aberto[LINHAS][COLUNAS];
int campo_vizinhos[LINHAS][COLUNAS];

int main() {
    int aberto = 0, total = LINHAS * COLUNAS - BOMBAS;
    int linha = -1, coluna = -1;

    srand(time(NULL));
    inicializar();
    sortear_bombas();
    calcular_vizinhos();

    while (1) {
        imprimir(0);
        printf("\nDigite linha e coluna (ex: 5 F) ou coluna e linha (ex: F 5): ");
        
        char input1[10], input2[10];
        if (scanf("%s %s", input1, input2) != 2) {
            printf("Entrada invalida.\n");
            char buffer[100];
            fgets(buffer, sizeof(buffer), stdin);
            continue;
        }

        if (isalpha(input1[0]) && isdigit(input2[0])) {
            coluna = toupper(input1[0]) - 'A';
            linha = atoi(input2);
        } 
        else if (isdigit(input1[0]) && isalpha(input2[0])) {
            linha = atoi(input1);
            coluna = toupper(input2[0]) - 'A';
        } 
        else {
            printf("Entrada invalida.\n");
            char buffer[100];
            fgets(buffer, sizeof(buffer), stdin);
            continue;
        }

        if (linha < 0 || linha >= LINHAS || coluna < 0 || coluna >= COLUNAS) {
            printf("Coordenadas fora do campo.\n");
            continue;
        }

        if (campo_aberto[linha][coluna]) {
            printf("Ja esta aberta!\n");
            continue;
        }

        if (campo_bombas[linha][coluna]) {
            printf("BOOM! Voce perdeu.\n");
            imprimir(1);
            break;
        }

        abrir_casa(linha, coluna);

        aberto = 0;
        for (int i = 0; i < LINHAS; i++)
            for (int j = 0; j < COLUNAS; j++)
                if (campo_aberto[i][j] && !campo_bombas[i][j])
                    aberto++;

        if (aberto == total) {
            printf("Parabens! Voce venceu.\n");
            imprimir(1);
            break;
        }
    }
    return 0;
}

void inicializar() {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            campo_bombas[i][j] = campo_aberto[i][j] = campo_vizinhos[i][j] = 0;
}

void sortear_bombas() {
    int cont = 0;
    while (cont < BOMBAS) {
        int i = rand() % LINHAS;
        int j = rand() % COLUNAS;
        if (!campo_bombas[i][j]) {
            campo_bombas[i][j] = 1;
            cont++;
        }
    }
}

void calcular_vizinhos() {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++) {
            int total = 0;
            for (int dL = -1; dL <= 1; dL++)
                for (int dC = -1; dC <= 1; dC++) {
                    int l = i + dL, c = j + dC;
                    if (l >= 0 && l < LINHAS && c >= 0 && c < COLUNAS)
                        total += campo_bombas[l][c];
                }
            campo_vizinhos[i][j] = total - campo_bombas[i][j];
        }
}

void imprimir(int revelar) {
    printf("   ");
    for (int j = 0; j < COLUNAS; j++) printf(" %c", 'A' + j);
    printf("\n");

    for (int i = 0; i < LINHAS; i++) {
        printf("%2d ", i);

        for (int j = 0; j < COLUNAS; j++) {
            if (!campo_aberto[i][j]) {
                if (revelar && campo_bombas[i][j]) printf(" X");
                else printf(" ~");
            } else if (campo_bombas[i][j])
                printf(" X");
            else if (campo_vizinhos[i][j])
                printf(" %d", campo_vizinhos[i][j]);
            else
                printf("  ");
        }

        printf(" %2d\n", i);
    }

    printf("   ");
    for (int j = 0; j < COLUNAS; j++) printf(" %c", 'A' + j);
    printf("\n");
}

void abrir_casa(int linha, int coluna) {
    if (linha < 0 || linha >= LINHAS || coluna < 0 || coluna >= COLUNAS) return;
    if (campo_aberto[linha][coluna]) return;
    if (campo_bombas[linha][coluna]) return;

    campo_aberto[linha][coluna] = 1;

    if (campo_vizinhos[linha][coluna] == 0) {
        for (int dL = -1; dL <= 1; dL++) {
            for (int dC = -1; dC <= 1; dC++) {
                if (dL != 0 || dC != 0) {
                    abrir_casa(linha + dL, coluna + dC);
                }
            }
        }
    }
}