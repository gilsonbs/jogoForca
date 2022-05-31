#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura() {
	printf("/****************/\n");
	printf("/ Jogo de Forca */\n");
	printf("/****************/\n\n");
}

void chuta() {
	char chute;
	printf("\nQual letra? \n");
	scanf(" %c", &chute);

	chutes[chutesdados] = chute;
	(chutesdados)++;
}

int jachutou(char letra) {
	int achou = 0;

	for(int j = 0; j < chutesdados; j++) {
		if(chutes[j] == letra) {
			achou = 1;
			break;
		}
	}

	return achou;
}
int chuteserrados() {
	int erros = 0;

	for(int i = 0; i < chutesdados; i++){   //varrendo array
		int existe = 0;

		for (int j = 0; j < strlen(palavrasecreta); j++) {   //varrendo palavra secreta
			if(chutes[i] == palavrasecreta[j]) {

				existe = 1;
				break;
			}
		}

		if(!existe) erros++;
	}

	return erros;
}
void desenhaforca(){

	int erros = chuteserrados();
	
	printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), 
	(erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >=2 ? '|' : ' '), (erros >= 4 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ?  '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 5 ? '/' : ' '), (erros >= 6 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

            for(int i = 0; i < strlen(palavrasecreta); i++) {

				int achou = jachutou(palavrasecreta[i]);	

				if(achou){
					printf("%c ", palavrasecreta[i]);
				} 
			
		     else {
				printf("_ ");
			}

		}
		printf("\n");
}

void adicionapalavra() {

	char quer;

	printf("Voce deseja adicionar uma nova palavra ao jogo? (S/N)\n");
	scanf(" %c", &quer);

	if(quer == 'S') {

		char novapalavra[TAMANHO_PALAVRA];
		printf("Qual a nova palavra? ");
		scanf("%s", novapalavra);

		FILE* f;

		f = fopen("palavras.txt", "r+");
		if(f == 0) {
			printf("Desculpe, banco de dados nao disponivel\n\n");
			exit(1);
		}

		int qtd;
		fscanf(f, "%d", &qtd);  //ler a quantidade do arquivo
		qtd++;

		fseek(f, 0, SEEK_SET);   //volta o cabecalho no inicio do arquivo
		fprintf(f, "%d", qtd);   // escreve no comeco


		fseek(f, 0, SEEK_END);   // vai para o fim do arquivo
		fprintf(f, "\n%s", novapalavra);  // escreve a nova palavra no fim dele

		fclose(f);
	}
}

void escolhepalavra(){
    FILE* f;  //a variavel f é um ponteiro
	
	f = fopen("palavras.txt", "r");  //abre um arquivo
	if(f == 0) {
		printf("Desculpe, banco de dados nao disponivel\n\n");
		exit(1);
	}

	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras);  //vai ler no arquivo a quuantidade de palavras na primeira linha

	srand(time(0));  //escolhe uma linha aleatoria dentro do arquivo
	int randomico = rand() % qtddepalavras;

	for(int i = 0; i <= randomico; i++) {
		fscanf(f, "%s", palavrasecreta);   //fscanf le do arquivo e guarda na palavra secreta
	}

	fclose(f);
}



int acerta() {  //vai varrer todas as letras da palavra secreta, se nao tiver chutado nao ganhou
	for(int i = 0; i < strlen(palavrasecreta); i++) {
		if(!jachutou(palavrasecreta[i])) {
			return 0;
		}
	}
	return 1;
}

int enforcou(){
	
	return chuteserrados() >= 7;
}

int main() {
	
	int acertou = 0;
	

    escolhepalavra();
    abertura();

	do {
        //printf("Você já deu %d chutes\n", chutesdados);
		
		desenhaforca();

		chuta();
		

	} while (!acerta() && !enforcou());

	//adicionapalavra();

	if(acerta()) {
		printf("\nParabens, você ganhou\n\n");

		printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");



	} else {
		printf("\nPuxa, voce foi enforcado\n");
		printf("A palavra era **%s**\n\n", palavrasecreta);

		printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");


	
	}
	}
	

