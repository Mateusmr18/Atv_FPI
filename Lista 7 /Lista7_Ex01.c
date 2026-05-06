#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char titulo[100];
	char genero[100];
	char estudio[100];
	char console[100];
	int nota;
	int anoLancamento;
} Jogo;

void lerJogos(Jogo *colecao, int n){

	for (int i = 0;i<n;i++){
		scanf("%s %s %s %s %d %d",
			colecao[i].titulo,
            colecao[i].genero,
            colecao[i].estudio,
            colecao[i].console,
            &colecao[i].nota,
            &colecao[i].anoLancamento);

		if(colecao[i].nota >7){
			printf("AWESOME! Mais um GOTY pra minha coleção!\n");
		}else if(colecao[i].nota <4){
			printf("Era melhor jogar mais um jogo de Mahjong.\n");
		}
	}
}

void printAno(Jogo *colecao, int n, int anoBusca){

	int count = 0;
	for (int i=0;i<n;i++){
		if(colecao[i].anoLancamento == anoBusca){
			printf("%s\n", colecao[i].titulo);
			count++;
		}
	}
	if(count>0){
		printf("Tenho %d jogos || %d.\n",count, anoBusca);
	}else{
		printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
	}
}

void printLetra(Jogo *colecao, int n, char letraBusca){
	int count = 0;
	for(int i=0; i<n;i++){
		if(colecao[i].titulo[0] == letraBusca){
			printf("%s\n", colecao[i].titulo);
			count++;
		}
	}
	if(count >0){
		printf("Tenho %d jogos || %c.\n", count, letraBusca);
	} else{
		printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
	}
}

void printStudio(Jogo *colecao, int n, char studioBusca[]){
	int count = 0;
	for(int i=0;i<n;i++){
		if(strcmp(colecao[i].estudio, studioBusca) ==0){
			printf("%s\n", colecao[i].titulo);
			count++;
		}
	}
	if(count>0){
		printf("Tenho %d jogos || %s.\n", count, studioBusca);
    }else{
		printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
	}
}

void printConsole(Jogo *colecao, int n, char consoleBusca[]) {

	int count = 0;
	for(int i=0; i<n; i++){
		if(strcmp(colecao[i].console, consoleBusca)==0){
			printf("%s\n", colecao[i].titulo);
			count++;
		}
	}
	if(count >0){
		printf("Tenho %d jogos || %s.\n", count, consoleBusca);
	}else{
		printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
	}
}

void printColecao(Jogo *colecao, int n){
	for(int i = 0; i<n; i++){
		printf("%s %d\n",colecao[i].titulo, colecao[i].nota);
	}
}
int main(){

	int n;

	if(scanf("%d", &n) != 1) return 0;

	Jogo *jogos = (Jogo *) malloc(n * sizeof(Jogo));

	if(jogos == NULL){
		return 1;
	}

	lerJogos(jogos,n);

	char comando[50];

	while(scanf("%s", comando) != EOF){

		if(strcmp(comando,"printAno")==0){

			int ano;
			scanf("%d", &ano);
			printAno(jogos,n,ano);
		} else if(strcmp(comando,"printLetra")==0){

			char letra;
			scanf(" %c",&letra);
			printLetra(jogos, n, letra);
		} else if(strcmp(comando,"printStudio")==0){
			char studio[100];
			scanf("%s", studio);
			printStudio(jogos, n, studio);
		} else if(strcmp(comando, "printConsole") ==0){
			char console[100];
			scanf("%s", console);
			printConsole(jogos, n, console);
		} else if(strcmp(comando, "printColecao") ==0){
			printColecao(jogos, n);
		}
	}

	printf("Enjoei de jogar, agora vou ver TV.\n");

	free(jogos);

	return 0;
}