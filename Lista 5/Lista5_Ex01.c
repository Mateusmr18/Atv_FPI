#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 10001

void lerStrings(int n, char strings[][MAX_LEN]) {
    for (int i = 0; i < n; i++) {
        scanf("%s", strings[i]);
    }
}

int calcularTamanhoMesclado(int n, char strings[][MAX_LEN]) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += (int)strlen(strings[i]);
    }
    return total;
}

int calcularMaxLen(int n, char strings[][MAX_LEN]) {
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        int len = (int)strlen(strings[i]);
        if (len > maxLen) {
            maxLen = len;
        }
    }
    return maxLen;
}

char *mesclarStrings(int n, char strings[][MAX_LEN]) {
    int totalLen = calcularTamanhoMesclado(n, strings);
    int maxLen   = calcularMaxLen(n, strings);

    char *mesclar = (char *)malloc((totalLen + 1) * sizeof(char));
    if (mesclar == NULL) {
        printf("Erro ao alocar mesclar string\n");
        exit(1);
    }

    int pos = 0;
    for (int col = 0; col < maxLen; col++) {
        for (int i = 0; i < n; i++) {
            /* Só adiciona se a string ainda tem caractere nessa posição */
            if (col < (int)strlen(strings[i])) {
                mesclar[pos++] = strings[i][col];
            }
        }
    }
    mesclar[pos] = '\0';
    return mesclar;
}

void fundirCaracteres(char *mesclar) {
    int i = 0;
    while (mesclar[i] != '\0' && mesclar[i + 1] != '\0') {
        if (mesclar[i] == mesclar[i + 1]) {
            /* Fusão: z+z=a, qualquer outro: próximo caractere ASCII */
            mesclar[i] = (mesclar[i] == 'z') ? 'a' : mesclar[i] + 1;

            /* Remove mesclar[i+1] deslocando o restante do vetor */
            for (int j = i + 1; mesclar[j] != '\0'; j++) {
                mesclar[j] = mesclar[j + 1];
            }

            /* Retrocede para detectar novas fusões geradas */
            if (i > 0) i--;

        } else {
            /* Sem fusão: só avança. Sem esse else, o while travaria! */
            i++;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    /* Matriz alocada dinamicamente com ponteiro para array */
    char (*strings)[MAX_LEN] = (char (*)[MAX_LEN])malloc(n * MAX_LEN * sizeof(char));
    if (strings == NULL) {
        printf("Erro ao alocar matriz de strings\n");
        exit(1);
    }

    lerStrings(n, strings);

    char *mesclar = mesclarStrings(n, strings);

    printf("%s\n", mesclar);

    fundirCaracteres(mesclar);
    printf("%s\n", mesclar);

    free(mesclar);
    mesclar = NULL;
    free(strings);
    strings = NULL;

    return 0;
}//
// Created by mrcm on 12/04/2026.
//
