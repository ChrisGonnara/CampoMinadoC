#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void preenchendo_bombas(int cm[20][24], int quantidade_bombas){
    int cont = 0, i, j;
    while(cont<quantidade_bombas){
        i = rand()%20;
        j = rand()%24;
        if (cm[i][j] == 0){
            cm[i][j] = 1;
            cont ++;
        }
    }
}

int main(){

    int campo_minado[20][24];
    int quantidade_bomba = 100;

        srand(time(NULL));

        for (int i = 0; i < 20; i++) {        // linhas
            for (int j = 0; j < 24; j++) {    // colunas
                campo_minado[i][j] = 0;
                printf(" %d", campo_minado[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        preenchendo_bombas(campo_minado, quantidade_bomba);

        for (int i = 0; i < 20; i++) {        // linhas
            for (int j = 0; j < 24; j++) {    // colunas
                printf(" %d", campo_minado[i][j]);
            }
            printf("\n");
        }

    return 0;
}