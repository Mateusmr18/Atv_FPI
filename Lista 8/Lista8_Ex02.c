#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int id          : 10;
    unsigned int status      : 3;
    unsigned int bat_baixa   : 1;
    signed int temperatura   : 12;
    unsigned int paridade    : 6;
} PacoteCampos;

typedef union {
    unsigned int raw;
    PacoteCampos campos;
} Telemetria;

int main() {
    int capacidade = 2;
    int total_pacotes = 0;


    unsigned int *vetor = (unsigned int *)malloc(capacidade * sizeof(unsigned int));
    if (vetor == NULL) {
        return 1;
    }

    unsigned int entrada;


    while (scanf("%x", &entrada) == 1 && entrada != 0) {


        if (total_pacotes >= capacidade) {
            capacidade *= 2;
            unsigned int *temp = (unsigned int *)realloc(vetor, capacidade * sizeof(unsigned int));
            if (temp == NULL) {
                free(vetor);
                return 1;
            }
            vetor = temp;
        }

        vetor[total_pacotes++] = entrada;
    }

    for (int i = 0; i < total_pacotes; i++) {
        Telemetria t;
        t.raw = vetor[i];


        printf("Pacote [%d] - Dado Bruto: 0x%08X\n", i + 1, t.raw);
        printf("ID do Sensor : %u\n", t.campos.id);
        printf("Status : %u\n", t.campos.status);
        printf("Bateria Baixa: %s\n", t.campos.bat_baixa ? "SIM (ALERTA)" : "Nao");
        printf("Temperatura : %d graus\n", t.campos.temperatura);
        printf("-------------------------------------------------\n");
    }

    free(vetor);

    return 0;
}