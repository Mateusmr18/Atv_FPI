// Tive problema com IDE que estou usando e o próprio Ubuntu, a forma mais facil foi usar e colocar todo o caminho até o arquivo.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    double preco;
} Produto;

typedef struct {
    int codigo;
    char tipo;
    int quantidade;
    char motivo[30];
} Inconsistencia;

int main() {

    FILE *arq_produtos = fopen("/home/mrcm/Documentos/FPI/Lista 8/arquivosEx4/produtos.txt", "r");
    if (arq_produtos == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    int cap_produtos = 5;
    int total_produtos = 0;
    Produto *produtos = (Produto *)malloc(cap_produtos * sizeof(Produto));
    if (produtos == NULL) return 1;

    while (fscanf(arq_produtos, "%d %s %d %lf", 
                  &produtos[total_produtos].codigo, 
                  produtos[total_produtos].nome, 
                  &produtos[total_produtos].quantidade, 
                  &produtos[total_produtos].preco) == 4) {
        
        total_produtos++;

        if (total_produtos >= cap_produtos) {
            cap_produtos *= 2;
            Produto *temp = (Produto *)realloc(produtos, cap_produtos * sizeof(Produto));
            if (temp == NULL) {
                free(produtos);
                fclose(arq_produtos);
                return 1;
            }
            produtos = temp;
        }
    }
    fclose(arq_produtos);

    FILE *arq_movimentos = fopen("/home/mrcm/Documentos/FPI/Lista 8/arquivosEx4/movimentos.txt", "r");
    if (arq_movimentos == NULL) {
        printf("Erro ao abrir arquivo.\n");
        free(produtos);
        return 1;
    }


    int mov_aplicados = 0;
    int saidas_recusadas = 0;
    int mov_sem_cadastro = 0;

    int cap_inconsistencias = 5;
    int total_inconsistencias = 0;
    Inconsistencia *inconsistencias = (Inconsistencia *)malloc(cap_inconsistencias * sizeof(Inconsistencia));
    if (inconsistencias == NULL) {
        free(produtos);
        fclose(arq_movimentos);
        return 1;
    }

    int mov_codigo;
    char mov_tipo;
    int mov_qtd;


    while (fscanf(arq_movimentos, "%d %c %d", &mov_codigo, &mov_tipo, &mov_qtd) == 3) {
        int encontrado = 0;
        int idx_produto = -1;


        for (int i = 0; i < total_produtos; i++) {
            if (produtos[i].codigo == mov_codigo) {
                encontrado = 1;
                idx_produto = i;
                break;
            }
        }

        if (!encontrado) {

            mov_sem_cadastro++;
            

            inconsistencias[total_inconsistencias].codigo = mov_codigo;
            inconsistencias[total_inconsistencias].tipo = mov_tipo;
            inconsistencias[total_inconsistencias].quantidade = mov_qtd;
            strcpy(inconsistencias[total_inconsistencias].motivo, "PRODUTO_INEXISTENTE");
            total_inconsistencias++;
        } else {

            if (mov_tipo == 'E') {
                produtos[idx_produto].quantidade += mov_qtd;
                mov_aplicados++;
            } else if (mov_tipo == 'S') {
                if (produtos[idx_produto].quantidade >= mov_qtd) {
                    produtos[idx_produto].quantidade -= mov_qtd;
                    mov_aplicados++;
                } else {

                    saidas_recusadas++;

                    inconsistencias[total_inconsistencias].codigo = mov_codigo;
                    inconsistencias[total_inconsistencias].tipo = mov_tipo;
                    inconsistencias[total_inconsistencias].quantidade = mov_qtd;
                    strcpy(inconsistencias[total_inconsistencias].motivo, "ESTOQUE_INSUFICIENTE");
                    total_inconsistencias++;
                }
            }
        }

        if (total_inconsistencias >= cap_inconsistencias) {
            cap_inconsistencias *= 2;
            Inconsistencia *temp = (Inconsistencia *)realloc(inconsistencias, cap_inconsistencias * sizeof(Inconsistencia));
            if (temp == NULL) {
                free(produtos);
                free(inconsistencias);
                fclose(arq_movimentos);
                return 1;
            }
            inconsistencias = temp;
        }
    }
    fclose(arq_movimentos);

    FILE *arq_estoque_atualizado = fopen("/home/mrcm/Documentos/FPI/Lista 8/arquivoEx4/estoque_atualizado.txt", "w");
    if (arq_estoque_atualizado == NULL) {
        printf("Erro ao abrir arquivo.\n");
        free(produtos);
        free(inconsistencias);
        return 1;
    }

    for (int i = 0; i < total_produtos; i++) {
        fprintf(arq_estoque_atualizado, "%d %s %d %.2f\n", 
                produtos[i].codigo, 
                produtos[i].nome, 
                produtos[i].quantidade, 
                produtos[i].preco);
    }
    fclose(arq_estoque_atualizado);

    FILE *arq_relatorio = fopen("/home/mrcm/Documentos/FPI/Lista 8/arquivoEx4/relatorio.txt", "w");
    if (arq_relatorio == NULL) {
        printf("Erro ao abrir arquivo.\n");
        free(produtos);
        free(inconsistencias);
        return 1;
    }

    fprintf(arq_relatorio, "PRODUTOS PROCESSADOS: %d\n", total_produtos);
    fprintf(arq_relatorio, "MOVIMENTOS APLICADOS: %d\n", mov_aplicados);
    fprintf(arq_relatorio, "SAIDAS RECUSADAS: %d\n", saidas_recusadas);
    fprintf(arq_relatorio, "MOVIMENTOS SEM CADASTRO: %d\n", mov_sem_cadastro);

    fprintf(arq_relatorio, "ESTOQUE BAIXO:\n");
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].quantidade <= 5) {
            fprintf(arq_relatorio, "%d %s %d\n", produtos[i].codigo, produtos[i].nome, produtos[i].quantidade);
        }
    }

    fprintf(arq_relatorio, "INCONSISTENCIAS:\n");
    for (int i = 0; i < total_inconsistencias; i++) {
        fprintf(arq_relatorio, "%d %c %d %s\n", 
                inconsistencias[i].codigo, 
                inconsistencias[i].tipo, 
                inconsistencias[i].quantidade, 
                inconsistencias[i].motivo);
    }
    fclose(arq_relatorio);


    free(produtos);
    free(inconsistencias);

    return 0;
}