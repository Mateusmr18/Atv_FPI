#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    char species[50];
} IrisData;

typedef struct {
    char nome[50];
    int contagem;
} FrequenciaEspecie;

int main() {
    int total_arquivos;

    printf("Digite a quantidade total de arquivos CSV a processar: ");
    if (scanf("%d", &total_arquivos) != 1 || total_arquivos <= 0) {
        printf("Quantidade inválida.\n");
        return 1;
    }

    for (int f_idx = 1; f_idx <= total_arquivos; f_idx++) {
        char nome_arquivo[30];

        sprintf(nome_arquivo, "/home/mrcm/Documentos/FPI/Lista 8/arquivoEx3/iris%d.csv", f_idx);

        FILE *arquivo = fopen(nome_arquivo, "r");
        if (arquivo == NULL) {
            printf("\n[ERRO] O arquivo '%s' nao foi encontrado. Pulando...\n", nome_arquivo);
            continue;
        }

        printf("\n=========================================\n");
        printf("EXIBINDO CONTEUDO DO ARQUIVO: %s\n", nome_arquivo);
        printf("=========================================\n");

        char linha[256];
        int capacidade = 10;
        int total_linhas = 0;

        IrisData *dados = (IrisData *)malloc(capacidade * sizeof(IrisData));
        if (dados == NULL) {
            printf("Erro de alocação de memória.\n");
            fclose(arquivo);
            return 1;
        }

        if (fgets(linha, sizeof(linha), arquivo) != NULL) {
            printf("%s", linha);
        }

        while (fgets(linha, sizeof(linha), arquivo) != NULL) {

            printf("%s", linha);

            IrisData atual;

            if (sscanf(linha, "%lf,%lf,%lf,%lf,%[^,\n\r]",
                       &atual.sepal_length, &atual.sepal_width,
                       &atual.petal_length, &atual.petal_width,
                       atual.species) == 5) {

                if (total_linhas >= capacidade) {
                    capacidade *= 2;
                    IrisData *temp = (IrisData *)realloc(dados, capacidade * sizeof(IrisData));
                    if (temp == NULL) {
                        printf("Erro ao realocar memória.\n");
                        free(dados);
                        fclose(arquivo);
                        return 1;
                    }
                    dados = temp;
                }

                dados[total_linhas++] = atual;
            }
        }

        fclose(arquivo);

        if (total_linhas == 0) {
            printf("[AVISO] O arquivo '%s' nao possui registros de dados validos.\n", nome_arquivo);
            free(dados);
            continue;
        }

        double soma_sl = 0, soma_sw = 0, soma_pl = 0, soma_pw = 0;

        FrequenciaEspecie freq[100]; // Suporta até 100 espécies diferentes por arquivo
        int total_especies_unicas = 0;

        for (int i = 0; i < total_linhas; i++) {
            soma_sl += dados[i].sepal_length;
            soma_sw += dados[i].sepal_width;
            soma_pl += dados[i].petal_length;
            soma_pw += dados[i].petal_width;

            int achou = 0;
            for (int j = 0; j < total_especies_unicas; j++) {
                if (strcmp(dados[i].species, freq[j].nome) == 0) {
                    freq[j].contagem++;
                    achou = 1;
                    break;
                }
            }
            if (!achou && total_especies_unicas < 100) {
                strcpy(freq[total_especies_unicas].nome, dados[i].species);
                freq[total_especies_unicas].contagem = 1;
                total_especies_unicas++;
            }
        }

        int idx_moda = 0;
        for (int j = 1; j < total_especies_unicas; j++) {
            if (freq[j].contagem > freq[idx_moda].contagem) {
                idx_moda = j;
            } else if (freq[j].contagem == freq[idx_moda].contagem) {
                // Em caso de empate, prioriza a menor ordem lexicográfica
                if (strcmp(freq[j].nome, freq[idx_moda].nome) < 0) {
                    idx_moda = j;
                }
            }
        }

        double media_sl = soma_sl / total_linhas;
        double media_sw = soma_sw / total_linhas;
        double media_pl = soma_pl / total_linhas;
        double media_pw = soma_pw / total_linhas;

        FILE *arquivo_append = fopen(nome_arquivo, "a");
        if (arquivo_append != NULL) {
            fprintf(arquivo_append, "\n--- Resultados Estatisticos ---\n");
            fprintf(arquivo_append, "Media Sepal Length: %.2f\n", media_sl);
            fprintf(arquivo_append, "Media Sepal Width: %.2f\n", media_sw);
            fprintf(arquivo_append, "Media Petal Length: %.2f\n", media_pl);
            fprintf(arquivo_append, "Media Petal Width: %.2f\n", media_pw);
            fprintf(arquivo_append, "Especie Predominante (Moda): %s\n", freq[idx_moda].nome);

            fclose(arquivo_append);
            printf("\n[SUCESSO] Estatisticas gravadas no final de '%s'.\n", nome_arquivo);
        } else {
            printf("\n[ERRO] Nao foi possivel abrir '%s' para gravacao dos resultados.\n", nome_arquivo);
        }

        free(dados);
    }

    return 0;
}
