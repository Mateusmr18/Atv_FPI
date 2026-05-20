#include <stdio.h>


typedef struct {
    unsigned char erro    : 1;
    unsigned char modo    : 3;
    unsigned char leitura : 4;
} SensorBits;


typedef union {
    unsigned char rawByte;
    SensorBits campos;
} RegistroSensor;

int main() {
    int valorEntrada;

    while (scanf("%d", &valorEntrada) == 1) {
        RegistroSensor sensor;

        sensor.rawByte = (unsigned char)valorEntrada;

        printf("Byte bruto: %u | Erro: %u | Modo: %u | Leitura: %u\n",
               sensor.rawByte,
               sensor.campos.erro,
               sensor.campos.modo,
               sensor.campos.leitura);
    }

    return 0;
}