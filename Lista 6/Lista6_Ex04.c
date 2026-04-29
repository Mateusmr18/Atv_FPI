#include <stdio.h>
#include <stdlib.h>

int calibracao(int v) { return v + 5; }
int saturacao(int v)  { return (v > 80) ? 80 : v; }
int amplificador(int v) { return v * 2; }

typedef int (*Filtro)(int);

void modificar(int **matriz, int N, int M, Filtro *pipeline, int k) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // Aplica cada filtro do pipeline em ordem no sensor atual
            for (int f = 0; f < k; f++) {
                matriz[i][j] = pipeline[f](matriz[i][j]);
            }
        }
    }
}

int** alocar_matriz(int N, int M) {
    int **m = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) m[i] = (int *)malloc(M * sizeof(int));
    return m;
}

void liberar_matriz(int **m, int N) {
    for (int i = 0; i < N; i++) free(m[i]);
    free(m);
}

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    int **matriz = alocar_matriz(N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    int comando;

    Filtro catalogo[] = {NULL, calibracao, saturacao, amplificador};

    while (scanf("%d", &comando) && comando != 0) {
        Filtro *pipeline_atual = NULL;
        int k = 0;

        if (comando >= 1 && comando <= 3) {

            k = 1;
            pipeline_atual = (Filtro *)malloc(k * sizeof(Filtro));
            pipeline_atual[0] = catalogo[comando];
        }
        else if (comando == 4) {

            scanf("%d", &k);
            pipeline_atual = (Filtro *)malloc(k * sizeof(Filtro));
            for (int i = 0; i < k; i++) {
                int id_filtro;
                scanf("%d", &id_filtro);
                pipeline_atual[i] = catalogo[id_filtro];
            }
        }

        if (pipeline_atual != NULL) {
            modificar(matriz, N, M, pipeline_atual, k);
            free(pipeline_atual);
        }
    }


    int critico = matriz[0][0];
    int posL = 0, posC = 0;

    printf("Matriz processada:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d%s", matriz[i][j], (j == M - 1) ? "" : " ");
            if (matriz[i][j] > critico) {
                critico = matriz[i][j];
                posL = i;
                posC = j;
            }
        }
        printf("\n");
    }

    printf("\nSensor critico: %d\n", critico);
    printf("Posicao: (%d,%d)\n", posL, posC);

    liberar_matriz(matriz, N);
    return 0;
}