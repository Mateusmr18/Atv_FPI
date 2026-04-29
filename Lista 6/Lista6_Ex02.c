#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int obter_camada(int r, int c, int x, int y) {
    int dr = abs(r - x);
    int dc = abs(c - y);
    if (dr + dc <= 1) return 1;
    if (dr <= 2 && dc <= 2) return 2;
    return 0;
}

typedef void (*TipoAtaque)(int **, int, int, int, int);

void explosao_arcana(int **m, int L, int C, int x, int y) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            int camada = obter_camada(i, j, x, y);
            if (camada == 1) {
                m[i][j] -= 50;
            } else if (camada == 2) {
                m[i][j] -= 25;
            }
            if (m[i][j] < 0) m[i][j] = 0;
        }
    }
}

void nuvem_venenosa(int **m, int L, int C, int x, int y) {
    for (int t = 0; t < 3; t++) {
        int alguem_vivo_na_area = 0;


        int **temp = (int **)malloc(L * sizeof(int *));
        for (int i = 0; i < L; i++) {
            temp[i] = (int *)malloc(C * sizeof(int));
            for (int j = 0; j < C; j++) temp[i][j] = m[i][j];
        }

        for (int i = 0; i < L; i++) {
            for (int j = 0; j < C; j++) {
                if (obter_camada(i, j, x, y) > 0) {
                    int vizinhos_vivos = 0;
                    for (int dr = -1; dr <= 1; dr++) {
                        for (int dc = -1; dc <= 1; dc++) {
                            if (dr == 0 && dc == 0) continue;
                            int ni = i + dr, nj = j + dc;
                            if (ni >= 0 && ni < L && nj >= 0 && nj < C && temp[ni][nj] > 0)
                                vizinhos_vivos++;
                        }
                    }
                    m[i][j] -= (5 + 8 * vizinhos_vivos);
                    if (m[i][j] < 0) m[i][j] = 0;
                    if (m[i][j] > 0) alguem_vivo_na_area = 1;
                }
            }
        }


        for (int i = 0; i < L; i++) free(temp[i]);
        free(temp);


        printf("\n");
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < C; j++) {
                printf("%d%s", m[i][j], (j == C - 1) ? "" : " ");
            }
            printf("\n");
        }

        if (!alguem_vivo_na_area) break;
    }
}

int** alocar_matriz(int L, int C) {
    int **m = (int **)malloc(L * sizeof(int *));
    for (int i = 0; i < L; i++) m[i] = (int *)malloc(C * sizeof(int));
    return m;
}

void liberar_matriz(int **m, int L) {
    for (int i = 0; i < L; i++) free(m[i]);
    free(m);
}

int main() {
    int L, C, x, y;
    if (scanf("%d %d", &L, &C) != 2) return 0;

    int **mapa = alocar_matriz(L, C);
    for (int i = 0; i < L; i++)
        for (int j = 0; j < C; j++)
            scanf("%d", &mapa[i][j]);

    scanf("%d %d", &x, &y);
    char tipo_magia[30];
    scanf("%s", tipo_magia);

    printf("Estado inicial do mapa:\n");
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            printf("%d%s", mapa[i][j], (j == C - 1) ? "" : " ");
        }
        printf("\n");
    }

    TipoAtaque executar_ataque = NULL;

    if (strcmp(tipo_magia, "EXPLOSAO_ARCANA") == 0) {
        executar_ataque = explosao_arcana;
        printf("\nEstado do mapa após usar a Explosão Arcana:\n");
        executar_ataque(mapa, L, C, x, y);

        for (int i = 0; i < L; i++) {
            for (int j = 0; j < C; j++) {
                printf("%d%s", mapa[i][j], (j == C - 1) ? "" : " ");
            }
            printf("\n");
        }
    } else if (strcmp(tipo_magia, "NUVEM_VENENOSA") == 0) {
        printf("\nEstado do mapa, por turno, após usar a Nuvem Venenosa:");
        nuvem_venenosa(mapa, L, C, x, y);

    }

    liberar_matriz(mapa, L);
    return 0;
}
