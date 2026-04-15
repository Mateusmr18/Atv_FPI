#include <stdio.h>
#include <stdlib.h>

int *lerNumeros(int *n) {
    int capacidade = 4;
    *n = 0;

    int *v = (int *)malloc(capacidade * sizeof(int));
    if (v == NULL) { fprintf(stderr, "Erro malloc\n"); exit(1); }

    int x;
    while (scanf("%d", &x) == 1) {
        /* Redimensiona se necessário */
        if (*n == capacidade) {
            capacidade *= 2;
            int *tmp = (int *)realloc(v, capacidade * sizeof(int));
            if (tmp == NULL) { free(v); fprintf(stderr, "Erro realloc\n"); exit(1); }
            v = tmp;
        }
        v[(*n)++] = x;
    }

    return v;
}
void imprimirImpares(int *v, int n) {
    for (int i = 0; i < n; i++)
        if (v[i] % 2 != 0)
            printf("%d\n", v[i]);
}

void imprimirPares(int *v, int n) {
    for (int i = 0; i < n; i++)
        if (v[i] % 2 == 0)
            printf("%d\n", v[i]);
}

int main(void) {
    int n;
    int *v = lerNumeros(&n);

    printf("Mais um bom dia de trabalho!\n");
    imprimirImpares(v, n);
    imprimirPares(v, n);
    printf("Vou visitar esses lugares de novo... algum dia.\n");

    free(v);
    v = NULL;
    return 0;
}
