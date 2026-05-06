#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;
    int atrib2;
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;
    SubSistema sistemas[];
};

void rotina_defesa(Mecha *m, int slot, int input, int *output) {
    int dano = input - m->sistemas[slot].atrib1 - (slot * m->sistemas[slot].atrib2);
    if (dano < 0) {
        dano = 0;
    }
    *output = dano;
}

void rotina_utilidade(Mecha *m, int slot, int input, int *output) {
    int recuperado = m->sistemas[slot].atrib1 + (slot * m->sistemas[slot].atrib2);
    m->energia_atual += recuperado;
    *output = recuperado;
}

void rotina_ataque(Mecha *m, int slot, int input, int *output) {
    int custo = m->sistemas[slot].atrib2;

    if (m->energia_atual < custo) {
        *output = 0; // Ataque cancelado
    } else {
        int dano = m->sistemas[slot].atrib1 + m->energia_atual + slot - input;
        m->energia_atual -= custo;
        *output = dano;
    }
}

int compara_mecha(const void *a, const void *b) {
    Mecha *m1 = *(Mecha **)a;
    Mecha *m2 = *(Mecha **)b;
    return m1->id - m2->id;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    Mecha **esquadrao = (Mecha **)malloc(N * sizeof(Mecha *));

    for (int i = 0; i < N; i++) {
        int id, energia, num_sis;
        char modelo[50];
        scanf("%d %s %d %d", &id, modelo, &energia, &num_sis);

        size_t tamanho_total = sizeof(Mecha) + (num_sis * sizeof(SubSistema));
        Mecha *m = (Mecha *)malloc(tamanho_total);
        
        m->id = id;
        strcpy(m->modelo, modelo);
        m->energia_atual = energia;
        m->num_sistemas = num_sis;

        for (int j = 0; j < num_sis; j++) {
            char tipo;
            scanf(" %c %s %d %d", &tipo, m->sistemas[j].nome, &m->sistemas[j].atrib1, &m->sistemas[j].atrib2);

            if (tipo == 'D') {
                m->sistemas[j].subrotina = rotina_defesa;
            } else if (tipo == 'U') {
                m->sistemas[j].subrotina = rotina_utilidade;
            } else if (tipo == 'A') {
                m->sistemas[j].subrotina = rotina_ataque;
            }
        }

        scanf("%d", &m->valor_wintermute);
        esquadrao[i] = m;
    }

    qsort(esquadrao, N, sizeof(Mecha *), compara_mecha);

    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for (int i = 0; i < N; i++) {
        Mecha *m = esquadrao[i];
        
        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", m->id, m->modelo, m->energia_atual);

        for (int j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == rotina_defesa) {
                int output;
                m->sistemas[j].subrotina(m, j, m->valor_wintermute, &output);
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->sistemas[j].nome, output);
            }
        }

        for (int j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == rotina_utilidade) {
                int output;
                m->sistemas[j].subrotina(m, j, m->valor_wintermute, &output);
                printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->sistemas[j].nome, m->energia_atual);
            }
        }

        for (int j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == rotina_ataque) {
                int output;
                int custo = m->sistemas[j].atrib2;
                int energia_anterior = m->energia_atual;
                
                m->sistemas[j].subrotina(m, j, m->valor_wintermute, &output);
                
                if (energia_anterior < custo) {
                    printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[j].nome);
                } else {
                    printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", m->sistemas[j].nome, output, m->energia_atual);
                }
            }
        }

        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        printf("-----------------------------------------\n");

        free(m); 
    }

    printf("Esquadrao pronto para o combate.\n");

    free(esquadrao);

    return 0;
}