#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char nome[250];
    int populacao;
    int periculosidade;
    char funcao[250];
} Cidadela;

void formatarString(char *str) {
    if (str[0] == '\0') return;

    if (str[0] >= 'a' && str[0] <= 'z') {
        str[0] = str[0] - 32;
    }

    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

//Implementação de uma função Qsort  em duvida se podia usar a função da própria biblioteca ou não
void trocar(Cidadela *a, Cidadela *b) {
    Cidadela temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(Cidadela arr[], int baixo, int alto) {
    Cidadela pivo = arr[alto];
    int i = (baixo - 1);

    for (int j = baixo; j < alto; j++) {
        int deve_ficar_antes = 0;

        if (arr[j].populacao > pivo.populacao) {
            deve_ficar_antes = 1;
        }

        else if (arr[j].populacao == pivo.populacao) {
            if (arr[j].periculosidade > pivo.periculosidade) {
                deve_ficar_antes = 1;
            }

            else if (arr[j].periculosidade == pivo.periculosidade) {
                if (strcmp(arr[j].nome, pivo.nome) < 0) {
                    deve_ficar_antes = 1;
                }
            }
        }

        if (deve_ficar_antes) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }

    trocar(&arr[i + 1], &arr[alto]);

    return (i + 1);
}

void meu_qsort(Cidadela arr[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(arr, baixo, alto);

        meu_qsort(arr, baixo, pi - 1);
        meu_qsort(arr, pi + 1, alto);
    }
}

int main() {
    char linha[300];
    Cidadela cidadelas[1000];
    int q_cid = 0;
    int chave = -1;

    while (fgets(linha, sizeof(linha), stdin) != NULL) {


        linha[strcspn(linha, "\n")] = '\0';
        linha[strcspn(linha, "\r")] = '\0';

        if (strlen(linha) == 0) continue;

        // Verifica se é a mensagem especial (contém '!')
        if (strchr(linha, '!') != NULL) {
            int temp_chave = 0;
            for (int i = 0; linha[i] != '\0'; i++) {
                if (linha[i] >= '0' && linha[i] <= '9') {
                    temp_chave = temp_chave * 10 + (linha[i] - '0');
                }
            }
            chave = temp_chave;
        }
        else {

            Cidadela c;
            c.populacao = 0;
            c.periculosidade = 0;
            int n_idx = 0;
            int f_idx = 0;

            for (int i = 0; linha[i] != '\0'; i++) {
                // Monta o nome (letras maiúsculas)
                if (linha[i] >= 'A' && linha[i] <= 'Z') {
                    c.nome[n_idx++] = linha[i];
                }
                // Calcula a população (números)
                if (linha[i] >= '0' && linha[i] <= '9') {
                    c.populacao = c.populacao * 10 + (linha[i] - '0');
                }
                // Conta a periculosidade (asteriscos)
                if (linha[i] == '*') {
                    c.periculosidade++;
                }
                // Monta a função (letra após um espaço duplo)
                if (linha[i] == ' ' && linha[i+1] == ' ') {
                    int j = i + 2;
                    if (linha[j] != '\0' && linha[j] != ' ') {
                        c.funcao[f_idx++] = linha[j];
                    }
                    i++; // Avança um espaço extra para evitar dupla contagem
                }
            }

            // Finaliza as strings com o caractere nulo ('\0')
            c.nome[n_idx] = '\0';
            c.funcao[f_idx] = '\0';

            // Aplica a formatação Maiúscula/minúscula
            formatarString(c.nome);
            formatarString(c.funcao);

            cidadelas[q_cid++] = c; // Adiciona à matriz
        }
    }

    if (chave == -1) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
    } else {

        meu_qsort(cidadelas, 0, q_cid - 1);

        if (chave > 0 && chave <= q_cid) {
            Cidadela alvo = cidadelas[chave - 1];

            printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade ",
                   alvo.nome, alvo.populacao, alvo.funcao);

            // Imprime os asteriscos de periculosidade
            for (int i = 0; i < alvo.periculosidade; i++) {
                printf("*");
            }
            printf(".");

            if (alvo.populacao >= 1000 && alvo.periculosidade > 3) {
                printf(" Talvez seja melhor desistir...\n");
            } else if (alvo.populacao >= 1000) {
                printf(" Um lugar denso, vai ser difícil achar ela.\n");
            } else if (alvo.periculosidade > 3) {
                printf(" Vai ser complicado entrar lá.\n");
            } else {
                printf("\n");
            }
        } else {

             printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
        }
    }

    return 0;
}