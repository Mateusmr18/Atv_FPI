#include <stdio.h>
#include <stdlib.h>
#include <string.h>


double calcularMedia(double *notas, int n) {
    double soma = 0.0;
    for (int i = 0; i < n; i++)
        soma += notas[i];
    return soma / n;
}

/* ---------------------------------------------------------------
 * Encontra o índice da maior nota (primeiro em caso de empate)
 * --------------------------------------------------------------- */
int indiceMaior(double *notas, int n) {
    int idx = 0;
    for (int i = 1; i < n; i++)
        if (notas[i] > notas[idx])
            idx = i;
    return idx;
}

/* ---------------------------------------------------------------
 * Encontra o índice da menor nota (primeiro em caso de empate)
 * --------------------------------------------------------------- */
int indiceMenor(double *notas, int n) {
    int idx = 0;
    for (int i = 1; i < n; i++)
        if (notas[i] < notas[idx])
            idx = i;
    return idx;
}

/* ---------------------------------------------------------------
 * Conta alunos com nota estritamente acima da média
 * --------------------------------------------------------------- */
int acimaDaMedia(double *notas, int n, double media) {
    int count = 0;
    for (int i = 0; i < n; i++)
        if (notas[i] > media)
            count++;
    return count;
}

/* ---------------------------------------------------------------
 * Comparador para qsort (ordem crescente)
 * --------------------------------------------------------------- */
int comparar(const void *a, const void *b) {
    double da = *(double *)a;
    double db = *(double *)b;
    if (da < db) return -1;
    if (da > db) return  1;
    return 0;
}

/* ---------------------------------------------------------------
 * Calcula a mediana (copia e ordena para não alterar original)
 * --------------------------------------------------------------- */
double calcularMediana(double *notas, int n) {
    double *copia = (double *)malloc(n * sizeof(double));
    if (copia == NULL) { fprintf(stderr, "Erro malloc mediana\n"); exit(1); }

    for (int i = 0; i < n; i++)
        copia[i] = notas[i];

    qsort(copia, n, sizeof(double), comparar);

    double mediana;
    if (n % 2 == 1)
        mediana = copia[n / 2];
    else
        mediana = (copia[n/2 - 1] + copia[n/2]) / 2.0;

    free(copia);
    return mediana;
}

/* ---------------------------------------------------------------
 * Calcula a moda.
 * Imprime "Nao ha moda unica" se não houver moda única.
 * Retorna 1 se há moda única (e preenche *moda), 0 caso contrário.
 * --------------------------------------------------------------- */
int calcularModa(double *notas, int n, double *moda) {
    double *copia = (double *)malloc(n * sizeof(double));
    if (copia == NULL) { fprintf(stderr, "Erro malloc moda\n"); exit(1); }

    for (int i = 0; i < n; i++)
        copia[i] = notas[i];

    qsort(copia, n, sizeof(double), comparar);

    double notaModa = copia[0];
    int maxFreq = 1, freqAtual = 1;
    int empate = 0; /* há outra nota com a mesma frequência máxima? */

    for (int i = 1; i < n; i++) {
        if (copia[i] == copia[i-1]) {
            freqAtual++;
        } else {
            freqAtual = 1;
        }

        if (freqAtual > maxFreq) {
            maxFreq = freqAtual;
            notaModa = copia[i];
            empate = 0;
        } else if (freqAtual == maxFreq && copia[i] != notaModa) {
            empate = 1;
        }
    }

    free(copia);

    /* Se frequência máxima for 1, todos aparecem igual → sem moda */
    if (maxFreq == 1 || empate) {
        return 0;
    }

    *moda = notaModa;
    return 1;
}

/* ---------------------------------------------------------------
 * Imprime o relatório completo
 * --------------------------------------------------------------- */
void imprimirRelatorio(double *notas, int n, const char *titulo) {
    double media   = calcularMedia(notas, n);
    int    iMaior  = indiceMaior(notas, n);
    int    iMenor  = indiceMenor(notas, n);
    int    acima   = acimaDaMedia(notas, n, media);
    double mediana = calcularMediana(notas, n);
    double moda;
    int    temModa = calcularModa(notas, n, &moda);

    printf("%s\n", titulo);
    printf("Media: %.2f\n",          media);
    printf("Maior nota: %.2f (aluno %d)\n", notas[iMaior], iMaior + 1);
    printf("Menor nota: %.2f (aluno %d)\n", notas[iMenor], iMenor + 1);
    printf("Acima da media: %d\n",   acima);
    printf("Mediana: %.2f\n",        mediana);

    if (temModa)
        printf("Moda: %.2f\n",       moda);
    else
        printf("Moda: Nao ha moda unica\n");

    printf("\n");
}

/* ---------------------------------------------------------------
 * Lê n notas e armazena no vetor (já alocado)
 * --------------------------------------------------------------- */
void lerNotas(double *notas, int inicio, int quantidade) {
    for (int i = 0; i < quantidade; i++)
        scanf("%lf", &notas[inicio + i]);
}

/* ---------------------------------------------------------------
 * Função principal
 * --------------------------------------------------------------- */
int main(void) {
    int n;
    scanf("%d", &n);

    /* Alocação inicial */
    double *notas = (double *)malloc(n * sizeof(double));
    if (notas == NULL) { fprintf(stderr, "Erro malloc inicial\n"); return 1; }

    lerNotas(notas, 0, n);

    /* Relatório inicial */
    imprimirRelatorio(notas, n, "Relatorio inicial");

    /* Novas notas */
    int k;
    scanf("%d", &k);

    if (k > 0) {
        /* Redimensiona com realloc + ponteiro temporário */
        double *tmp = (double *)realloc(notas, (n + k) * sizeof(double));
        if (tmp == NULL) {
            fprintf(stderr, "Erro realloc\n");
            free(notas);
            return 1;
        }
        notas = tmp;

        lerNotas(notas, n, k);
        n += k;
    }

    /* Relatório atualizado (impresso mesmo se k = 0) */
    imprimirRelatorio(notas, n, "Relatorio atualizado");

    free(notas);
    notas = NULL;
    return 0;
}//
// Created by mrcm on 15/04/2026.
//
