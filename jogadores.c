//este operador serve para dizer ao compilador de C, que este ficheiro header so deve ser processado
//se ainda nao sido processado anteriormente
//le-se "se ainda nao tiver sido definido JOGADOR_H, define JOGADOR_H".
//Se o teste falhar (i.e. o JOGADOR_H ja foi definido), o compilador salta para o #endif e tudo o que esta
//dentro do #if e ignorado
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#ifndef JOGADOR_H
#define JOGADOR_H

//Definicao do enumerado Posicao
typedef enum e_Posicao 
{
    GR,
    Defesa,
    Medio,
    Avancado
}Posicao;

//Dada uma string, retorna a posicao (valor enumerado) correspondente a string recebida

Posicao string_to_posicao(char *s)
{
	if(strcmp("Guarda-redes", s) == 0)
		return GR;
	else if(strcmp("Defesa", s) == 0)
		return Defesa;
	else if (strcmp( "Medio", s)== 0)
		return Medio;
	else
		return Avancado;
} 
//Dada uma posicao, retorna uma String que descreve a posição
const char * posicao_to_string(Posicao p)
{
	if (p == GR)
		return "Guarda-redes";
	else if(p == Defesa)
		return "Defesa";
	else if (p == Medio)
		return "Medio";
	else
		return "Avancado";
}

//Define o Tipo Estruturado Jogador, e os seus membros
typedef struct S_Jogador
{
    char *primeiro_nome;
    char *ultimo_nome;
    char *clube;
    int ano;
    Posicao pos;
    int internacionalizacoes;
    int golos;
} Jogador;

//Construtor do tipo Jogador, recebe os membros, e cria um novo jogador, e inicializa-o. Devolve
//um ponteiro para o jogador criado
Jogador *jogador(char *primeiro_nome,char *ultimo_nome, int ano, Posicao p, int inter, int golos, char *clube)
{
    Jogador *j = malloc(sizeof(Jogador));
    j->primeiro_nome = strdup(primeiro_nome);
    j->ultimo_nome = strdup(ultimo_nome);
    j->ano = ano;
    j->pos = p;
    j->internacionalizacoes = inter;
    j->golos = golos;
    j->clube = strdup(clube);

    return j;
}
//Recebe um ponteiro para um jogador, e liberta a memória usada pelo tipo
void free_jogador(Jogador *j) 
{
    free(j->primeiro_nome);
    free(j->ultimo_nome);
    free(j->clube);
    free(j); 
}

//Recebe um ponteiro para um jogador, e cria uma copia (ou clone) profunda do jogador. Devolve um
//ponteiro para o jogador criado
Jogador *jogador_dup(Jogador *j)
{
	Jogador *copia = malloc(sizeof(Jogador));
	*copia= *j;
	copia->primeiro_nome = strdup(j->primeiro_nome);
	copia->ultimo_nome = strdup(j->ultimo_nome);
	copia->clube = strdup(j->clube);
	return copia;
}

//Recebe um ponteiro para um jogador, e o numero de golos marcados num jogo, e adiciona um jogo (internacionalizacao) ao
//jogador, e atualiza o numero de golos marcados pelo jogador
void adiciona_internacionalizacao(Jogador *j, int golos)
{
	j->internacionalizacoes+=1;
	j->golos += golos;
}

//Imprime um jogador para o standard output, usando o formato:
//[<Primeiro Nome>][<Ultimo Nome>][<Ano>][<Posição>][<Internacionalizações>][Golos][Clube Atual]\n
//Exemplo:
//[Cristiano][Ronaldo][1985][Avancado][196][118][Al_Nassr]
void println_jogador(Jogador *j)
{
	printf("[%s][%s][%d][%s][%d][%d][%s]\n" , j->primeiro_nome, j->ultimo_nome, j->ano, posicao_to_string(j->pos), j->internacionalizacoes, j->golos, j->clube);
}

//Recebe um array de ponteiros para jogadores, e o numero de elementos no array n, e imprime
//todos os jogadores, pela ordem em que aparecem no array. Caso nao existam elementos no array
//imprime "*\n"
void println_jogadores(Jogador *jogadores[], int n)
{
	if(n == 0)
		printf("*\n");
	else
		println_jogadores(jogadores, n);
}

//Dado um array de ponteiros para jogadores, e um numero n de jogadores a ler, le do standard input os n jogadores.
//cada jogador deve ser lido numa unica linha, com todos os membros separados por espaco, pela seguinte ordem
//<Primeiro Nome> <Ultimo Nome> <Ano Nascimento> <Posicao> <Internacionalizacoes> <Golos> <Clube Atual>
//Os membros que correspondem a cadeias de caracteres (strings) nao excederao os 100 caracteres cada.
//O metodo retorna o numero de jogadores efetivamente lidos.
int get_jogadores(Jogador *jogadores[], int n)
{
	int i = 0;
	char primeiro_nome[100];
	char ultimo_nome[100];
	int ano;
	int internacionalizacoes;
	int golos;
	char posicao[100];
	char clube[100];
	while(i < n && scanf("%s %s %d %s %d %d %s", primeiro_nome, ultimo_nome, &ano, posicao, &internacionalizacoes, &golos, clube)!=EOF)
	{
		jogadores[i] = jogador(primeiro_nome, ultimo_nome, ano, string_to_posicao(posicao),internacionalizacoes, golos, clube);
		i++;
	}
	return i;
}
//Dado um array de ponteiros para jogadores, e um numero n de jogadores a ler, le do ficheiro os n jogadores.
//cada jogador deve ser lido numa unica linha, com todos os membros separados pelo caracter tab "\t", pela seguinte ordem
//<Primeiro Nome>   <Ultimo Nome>   <Ano Nascimento>    <Posicao>   <Internacionalizacoes>  <Golos> <Clube Atual>
//Os membros que correspondem a cadeias de caracteres (strings) podem ter espaços e nao excederao os 100 caracteres cada.
//O metodo retorna o numero de jogadores efetivamente lidos.

int get_jogadores_from_file(FILE *f, Jogador *jogadores[], int n) 
{
    char primeiro_nome[100], ultimo_nome[100], posicao[100], clube[100];
    int ano, internacionalizacoes, golos;
    int i = 0;
    while (i < n && fscanf(f, "%s\t%s\t%d\t%s\t%d\t%d\t%[^\n]\n", primeiro_nome, ultimo_nome, &ano, posicao, &internacionalizacoes, &golos, clube)!= EOF)
        jogadores[i++] = jogador(primeiro_nome, ultimo_nome, ano, string_to_posicao(posicao), internacionalizacoes, golos, clube);
    return i;
}
//Dado um array de ponteiros para jogadores, um numero n de jogadores, uma string com o primeiro nome,
//e uma string com o ultimo nome, este metodo procura no array jogadores pelo primeiro jogador
//que tenha o primeiro e ultimo nome iguais aos nomes recebidos, e retorna o ponteiro para esse jogador.
//Caso nao exista tal jogador, retorna-se o ponteiro NULL
Jogador *pesquisa_jogador(Jogador *jogadores[], int n, char *primeiro_nome, char *ultimo_nome)
{
	for(int i = 0 ; i < n ; i++)
		if(strcmp(jogadores[i]->primeiro_nome, primeiro_nome) == 0 && strcmp(jogadores[i]->ultimo_nome , ultimo_nome) == 0)
			return jogadores[i];
	return NULL;
}

//Dado um array de ponteiros para jogadores, um numero n de jogadores nesse array, retorna o jogador
//com maior numero de golos marcados. Caso nao exista nenhum jogador, retorna-se NULL
Jogador *pesquisa_melhor_marcador(Jogador *jogadores[], int n)
{	
	if (n == 0)
		return NULL;
	int melhor_marcador = -1;
	Jogador*j;
	for(int i = 0; i < n ; i++)
	{
		if(jogadores[i]->golos > melhor_marcador)
		{
			j = jogadores[i];
			melhor_marcador = jogadores[i]->golos;
		}
	}
	return j;
}

//dado um array de entrada de ponteiros de jogadores in, e um array de saida de ponteiros de jogadores out,
//um inteiro n que corresponde ao numero de elementos de in, e um Predicado sobre Jogadores
//esta funcao procura no array in todos os jogadores que satisfaze o predicado, colocando-os no 
//array de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int pesquisa_jogadores(Jogador *in[], Jogador *out[], int n, int (*p) (Jogador*))
{
    int count = 0;
    for (int i = 0; i < n; i++) 
    {
        if (p(in[i]) == 1) 
        {
            out[count] = in[i];
            count++;
        }
    }
    return count;
}

int avancado_e_golos20menos(Jogador *j) 
{
    return strcmp(posicao_to_string(j->pos), "Avançado") == 0 && j->golos < 20 ? 1 : 0;
}

int cmp_jogadores(const void *a, const void *b) 
{
    Jogador *ja = *(Jogador **)a;
    Jogador *jb = *(Jogador **)b;

    if (ja->internacionalizacoes > jb->internacionalizacoes)
        return 1;
    else if (ja->internacionalizacoes < jb->internacionalizacoes)
        return -1;
    else         
        return ja->golos > jb->golos ? 1 : -1;
}
//dado um array de entrada de ponteiros de jogadores in, e um array de saida de ponteiros de jogadores out,
//um inteiro n que corresponde ao numero de elementos de in, e uma string com um nome de um clube
//esta funcao procura no array in todos os jogadores que pertencam ao clube recebido, colocando-os no 
//array de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int pesquisa_jogadores_clube(Jogador *in[], Jogador *out[], int n, char* clube)
{
	int contador = 0;
	for(int i = 0 ; i < n ; i++)
	{
		if (strcmp(in[i]->clube, clube) == 0)
		{
			out[contador] = in[i];
			contador++;
		}

	}
	return contador;
}

//dado um array de entrada de ponteiros de jogadores in, um array de saida de ponteiros de jogadores out,
//um inteiro n que corresponde ao numero de elementos de in, e dois inteiros que correspondem
//a um numero minimo e maximo de internacionalizacoes, esta funcao procura no array in todos
//os jogadores com numero de internacionalizacoes compreendido entre os valores minimo e maximo (inclusive),
//colocando-os no array de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int pesquisa_jogadores_inter(Jogador *in[], Jogador *out[], int n, int min_inter, int max_inter)
{
	int contador = 0;
	for(int i = 0 ; i < n ; i++)
	{
		if(min_inter <= in[i]->internacionalizacoes && in[i]->internacionalizacoes <= max_inter)
		{
			out[contador] = in[i];
			contador++;
		}
	}
	return contador;
}


void test_Jogador_File_Loading(void)
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    int n = 0;
    fscanf(f, "%d", &n);
    fgetc(f);
    
    Jogador *jogadores[n];
    int n_jogadores = get_jogadores_from_file(f, jogadores, n);
    fclose(f);

    qsort(jogadores, n_jogadores, sizeof(Jogador *), cmp_jogadores);
    println_jogadores(jogadores, n_jogadores);
}

void test_Jogador_Sorting(void)
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    int n = 0;
    fscanf(f, "%d", &n);
    fgetc(f);

    Jogador *jogadores[n];
    int n_jogadores = get_jogadores_from_file(f, jogadores, n);
    fclose(f);

    qsort(jogadores, n_jogadores, sizeof(Jogador *), cmp_jogadores);
    println_jogadores(jogadores, n_jogadores);
}

void test_Jogador_Pesquisa(void)
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    int n = 0;
    fscanf(f, "%d", &n);
    fgetc(f);
    
    Jogador *jogadores[n];
    int n_jogadores = get_jogadores_from_file(f, jogadores, n);
    fclose(f);

    Jogador *jogadores_out[100];
    int num_jogadores_out = pesquisa_jogadores(jogadores, jogadores_out, n_jogadores, avancado_e_golos20menos);

    println_jogadores(jogadores_out, num_jogadores_out);
}

#endif