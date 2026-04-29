#include <stdio.h>
#include <stdlib.h>

int dobro(int n) {return n * 2;}
int quadrado(int n){return n * n;}
int absoluto(int n) {return n < 0 ? -n : n;}

int** alocar_matriz(int L, int C) {

    int** matriz = (int **)malloc(sizeof(int*) * L);
    for (int i = 0; i < L; i++) {
        matriz[i] = (int *)malloc(sizeof(int) * C);
    }
    return matriz;
}

void ler_matriz(int **m, int L, int C) {

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &m[i][j]);
        }
    }
}

void imprimir_matriz(int **m, int L, int C) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void liberar_matriz(int **m, int L) {
    for (int i = 0; i < L; i++) {
        free(m[i]);
    }
    free(m);
}



void aplicar_operacao(int **m, int L, int C, int(*operacao)(int)) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            m[i][j] = operacao(m[i][j]);
        }
    }
}
int main() {
    int L,C, op;
    scanf("%d %d", &L, &C);

    int **matriz = alocar_matriz(L, C);
    ler_matriz(matriz, L, C);

    scanf("%d", &op);

    int (*escolhida)(int) = NULL;

    if (op == 1) escolhida = dobro;
    else if (op == 2) escolhida = quadrado;
    else if (op == 3) escolhida = absoluto;

    if (escolhida!= NULL) {
        aplicar_operacao(matriz, L, C, escolhida);
    }

    imprimir_matriz(matriz, L, C);
    liberar_matriz(matriz, L);

    return 0;
}