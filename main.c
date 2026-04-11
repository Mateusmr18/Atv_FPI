#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);

    while (T > 0) {
        int N;
        scanf("%d", &N);

        int v[100];
        int i;
        for (i = 0; i < N; i++)
            scanf("%d", &v[i]);

        int melhor_inicio = 0;
        int melhor_tam = 1;
        int atual_inicio = 0;
        int atual_tam = 1;

        for (i = 1; i < N; i++) {
            if (v[i] < v[i - 1]) {
                atual_tam++;
            } else {
                if (atual_tam > melhor_tam) {
                    melhor_tam = atual_tam;
                    melhor_inicio = atual_inicio;
                }
                atual_inicio = i;
                atual_tam = 1;
            }
        }

        /* Verifica ultima sequencia */
        if (atual_tam > melhor_tam) {
            melhor_tam = atual_tam;
            melhor_inicio = atual_inicio;
        }

        if (melhor_tam == 1) {
            printf("0\n");
        } else {
            printf("%d\n", melhor_tam);
            for (i = melhor_inicio; i < melhor_inicio + melhor_tam; i++) {
                if (i == melhor_inicio + melhor_tam - 1)
                    printf("%d\n", v[i]);
                else
                    printf("%d ", v[i]);
            }
        }

        T--;
    }

    return 0;
}