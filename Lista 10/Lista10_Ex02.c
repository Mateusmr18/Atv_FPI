#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {

    long long mat;
    int pri;
    double cr;
    long long L;
    long long R;
    struct  No* next;
} No;

typedef struct {
    No* head;
    No* tail;
}Fila;

void iniciarFila(Fila* f) {
    f->head = NULL;
    f->tail = NULL;
}

void finalFila(Fila* f, long long mat, int pri, double cr, long long L, long long R) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->mat = mat;
    novoNo->pri = pri;
    novoNo->cr = cr;
    novoNo->L = L;
    novoNo->R = R;
    novoNo->next = NULL;

    if (f->tail == NULL) {
        f->head = novoNo;
        f->tail = novoNo;
    } else {
        f->tail->next = novoNo;
        f->tail = novoNo;
    }
}

No* comecoFila(Fila* f) {
    if (f->head == NULL) return NULL;

    No* temp = f->head;
    f->head = f->head->next;

    if (f->head == NULL) {
        f->tail = NULL;
    }
    return temp;
}

void limparFila(Fila* f) {

    No* atual = f->head;
    while (atual != NULL) {
        No* next = atual->next;
        free(atual);
        atual = next;
    }
    f->head = NULL;
    f->tail = NULL;
}

int main() {
    char cmd[20];
    char nome_disciplina[55];
    int vagas = 0;
    long long tempo_atual = 1;

    Fila solicitarFila;
    Fila confirmaFila;

    iniciarFila(&solicitarFila);
    iniciarFila(&confirmaFila);

    while (scanf("%s", cmd)!=EOF) {
        if (strcmp(cmd,"START")==0) {
            scanf("%s %d",nome_disciplina, &vagas);

            limparFila(&solicitarFila);
            limparFila(&confirmaFila);
            tempo_atual = 1;
        }
        else if (strcmp(cmd, "ADD") ==0) {
            long long mat, L, R;
            int pri;
            double cr;
            scanf("%lld %d %lf %lld %lld", &mat, &pri, &cr, &L, &R);
            finalFila(&solicitarFila, mat, pri, cr, L, R);
        }
        else if (strcmp(cmd, "PROC")==0) {
            int qtd;
            scanf("%d", &qtd);

            int processo = 0 ;

            while (processo<qtd&&solicitarFila.head!=NULL) {
                No* estudante = solicitarFila.head;


                if (tempo_atual<estudante->L) {
                    tempo_atual = estudante->L;
                }
                if (tempo_atual>estudante->R) {
                    printf("[TIMEOUT] mat=%lld | Desconectado da fila.\n", estudante->mat);
                    No* remover = comecoFila(&solicitarFila);
                    free(remover);
                }

                else {
                    No* remover = comecoFila(&solicitarFila);

                    int score = (int)round(remover->cr*100) / remover->pri;

                    if (vagas>0) {
                        printf("[ALOCADO] mat=%lld | score=%d | Processado no seg: %lld\n", remover->mat, score, tempo_atual);
                        vagas--;
                        finalFila(&confirmaFila, remover->mat, remover->pri, remover->cr, remover->L, remover->R);
                    }else {
                        printf("[LOTADO] mat=%lld | score=%d | Processado no seg: %lld\n", remover->mat,score,remover->R);
                    }
                    tempo_atual++;
                    free(remover);
                }
                processo++;
            }
        }else if (strcmp(cmd,"FIM")==0) {

            printf(("--- LISTA OFICIAL: %s ---\n"), nome_disciplina);
            int idx = 1;
            No* curr = confirmaFila.head;
            while (curr!=NULL) {
                printf("%d. Matricula: %lld\n", idx++, curr->mat);
                curr = curr->next;
            }

            limparFila(&solicitarFila);
            limparFila(&confirmaFila);
        }
    }
    return 0;
}