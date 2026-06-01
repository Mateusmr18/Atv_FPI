#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *items;
    int top;
    int capacidade;
} Pilha;

Pilha* criandoPilha(int capacidade_inicial) {

    Pilha *s = (Pilha*) malloc(sizeof(Pilha));
    s->capacidade = capacidade_inicial;
    s->top = 0;
    s->items = (char*) malloc(s->capacidade * sizeof(char));
    return s;
}

void push(Pilha *s, char elementos) {

    if (s->top == s->capacidade) {

        s->capacidade *= 2;
        s->items = (char*) realloc(s->items, s->capacidade * sizeof(char));
    }

    s->items[s->top++] = elementos;

}

void processoRegras(Pilha *s) {

    int carregando = 1;

    while (carregando) {

        carregando = 0;

        if(s->top >=3 &&
            s->items[s->top-1] == s->items[s->top-2] &&
            s->items[s->top-2] == s->items[s->top-3]) {
            s->top -=3;
            carregando =1;
        }
        else if (s->top >= 2) {
            char a = s->items [s->top-1];
            char b = s->items [s->top-2];

            if ((a == 'g' && b == 'b') || (a =='b' && b == 'g')) {
                s->top -=2;
                push(s,'c');
                carregando = 1;
            }
            else if ((a == 'r' && b == 'b') || (a == 'b' && b == 'r')) {
                s->top -= 2;
                push(s,'m');
                carregando = 1;
            }
            else if ((a == 'r' && b == 'g') || (a == 'g' && b == 'r')) {
                s->top -= 2;
                push(s,'y');
                carregando = 1;
            }
        }
    }
}

void printPilha(Pilha *s) {
    if (s->top == 0) {
        printf("Pilha vazia!\n");
    }else {
        for (int i = s->top -1; i>=0; i--) {
            printf("%c\n", s->items[i]);
        }
    }
    printf("\n");
}


void freePilha(Pilha *s) {

    free(s->items);
    free(s);
}

int main() {

    Pilha *jogoPilha = criandoPilha(4);
    char c;

    while (scanf(" %c",&c) != EOF) {
        push(jogoPilha,c);
        processoRegras(jogoPilha);
        printPilha(jogoPilha);
    }

    printf("Thank You So Much For Playing My Game!\n");

    freePilha(jogoPilha);

    return 0;

}
