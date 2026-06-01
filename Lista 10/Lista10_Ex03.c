#include <stdio.h>
#include <stdlib.h>

typedef struct Tarefa {
    int id;
    int prioridade;
    struct Tarefa* prox;
} Tarefa;

typedef struct {
    Tarefa* head;
    Tarefa* tail;
} Fila;

void iniciarFila(Fila* f) {
    f->head = NULL;
    f->tail = NULL;
}

void inserir(Fila* f, int id, int prioridade) {
    Tarefa* novaTarefa = (Tarefa*)malloc(sizeof(Tarefa));
    novaTarefa->id = id;
    novaTarefa->prioridade = prioridade;
    novaTarefa->prox = NULL;

    if (f->tail == NULL) {
        f->head = novaTarefa;
        f->tail = novaTarefa;
    } else {

        f->tail->prox = novaTarefa;
        f->tail = novaTarefa;
    }
}


void remover(Fila* f) {
    // Caso a fila esteja vazia
    if (f->head == NULL) {
        printf("Fila vazia\n");
        return;
    }

    Tarefa* temp = f->head;

    printf("Removida: id=%d prioridade=%d\n", temp->id, temp->prioridade);

    f->head = f->head->prox;

    if (f->head == NULL) {
        f->tail = NULL;
    }

    free(temp);
}

void listar(Fila* f) {
    if (f->head == NULL) {
        printf("Fila vazia\n");
        return;
    }

    Tarefa* atual = f->head;
    while (atual != NULL) {
        printf("id=%d prioridade=%d\n", atual->id, atual->prioridade);
        atual = atual->prox;
    }
}

void limparFila(Fila* f) {
    Tarefa* atual = f->head;
    while (atual != NULL) {
        Tarefa* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    f->head = NULL;
    f->tail = NULL;
}

int main() {
    Fila filaTarefas;
    iniciarFila(&filaTarefas);

    char comando;

    while (scanf(" %c", &comando) != EOF) {
        if (comando == 'I') {
            int id, prioridade;
            scanf("%d %d", &id, &prioridade);
            inserir(&filaTarefas, id, prioridade);
        }
        else if (comando == 'R') {
            remover(&filaTarefas);
        }
        else if (comando == 'L') {
            listar(&filaTarefas);
        }
        else if (comando == 'F') {

            break;
        }
    }

    limparFila(&filaTarefas);

    return 0;
}