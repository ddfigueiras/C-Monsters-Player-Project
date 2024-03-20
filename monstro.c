//este operador serve para dizer ao compilador de C, que este ficheiro header so deve ser processado
//se ainda nao sido processado anteriormente
//le-se "se ainda nao tiver sido definido MONSTRO_H, define MONSTRO_H".
//Se o teste falhar (i.e. o MONSTRO_H ja foi definido), o compilador salta para o #endif e tudo o que esta
//dentro do #if e ignorado
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#ifndef MONSTRO_H
#define MONSTRO_H


//Definicao do enumerado Tamanho
typedef enum e_Tam {Tiny,Small,Medium,Large,Huge,Gargantuan} Tamanho;


//Dada uma string, retorna o tamanho (valor enumerado) correspondente a string recebida
Tamanho string_to_tamanho(char *s) 
{
    if (strcmp(s, "Tiny") == 0)
        return Tiny;
    else if (strcmp(s, "Small") == 0)
        return Small;
    else if (strcmp(s, "Medium") == 0)
        return Medium;
    else if (strcmp(s, "Large") == 0)
        return Large;
    else if (strcmp(s, "Huge") == 0)
        return Huge;
    else
        return Gargantuan;
}

//Dada um tamanho, retorna uma String que descreve o tamanho
const char * tamanho_to_string(Tamanho t) 
{
    switch (t) 
    {
        case Tiny:
            return "Tiny";
        case Small:
            return "Small";
        case Medium:
            return "Medium";
        case Large:
            return "Large";
        case Huge:
            return "Huge";
        default:
            return "Gargantuan";
    }
}

//Define o Tipo Estruturado Monstro, e os seus membros
//para os mais distraidos, existe um membro novo
typedef struct S_Monstro 
{
    char *nome;
    char *tipo;
    Tamanho tam;
    int ac;
    int hp;
    double cr;
    //string que representa uma habilidade especial da criatura
    char *trait;
} Monstro;

//Construtor do tipo Monstro, recebe os membros, e cria um novo monstro, e inicializa-o. Devolve
//um ponteiro para o monstro criado
Monstro *monstro(char *nome, char *tipo, Tamanho tam, int ac, int hp, double cr, char *trait) 
{
    Monstro *m = malloc(sizeof(Monstro));
    m->nome = strdup(nome);
    m->tipo = strdup(tipo);
    m->tam = tam;
    m->ac = ac;
    m->hp = hp;
    m->cr = cr;
    m->trait = strdup(trait);

    return m;
}

//Recebe um ponteiro para um monstro, e liberta a memória usada pelo tipo
void free_monstro(Monstro *m) 
{
    free(m->nome);
    free(m->tipo);
    free(m->trait);
    free(m); 
}

//Recebe um ponteiro para um monstro, e cria uma copia (ou clone) profunda do monstro. Devolve um
//ponteiro para o monstro criado
Monstro *monstro_dup(Monstro *m) 
{
    Monstro *m_dup = malloc(sizeof(Monstro));
    m_dup->nome = strdup(m->nome);
    m_dup->tipo = strdup(m->tipo);
    m_dup->tam = m->tam;
    m_dup->ac = m->ac;
    m_dup->hp = m->hp;
    m_dup->cr = m->cr;
    m_dup->trait = strdup(m->trait); // copia a string trait

    return m_dup;
}

//Recebe um ponteiro para um monstro, e atualiza algum dos seus membros com os valores recebidos
void atualiza_stats(Monstro *m, int ac, int hp, double cr) 
{
    m->ac = ac;
    m->hp = hp;
    m->cr = cr;
}

//Imprime um monstro para o Standard Output, usando o seguinte formato:
//<Nome do Monstro> - <Tamanho> <Tipo Criatura>, AC:<Armor Class>, HP:<Hit Points>, CR: <Challenge Rating>, Trait: <trait>\n
//por exemplo:
//Imp – Tiny Fiend, AC:13, HP:10, CR:1.00, Trait:Shapechanger\n
void println_monstro(Monstro *m) 
{
    printf("%s - %s %s, AC:%d, HP:%d, CR:%.2f, Trait:%s\n", m->nome, tamanho_to_string(m->tam), m->tipo, m->ac, m->hp, m->cr, m->trait);
}

//Recebe um array de ponteiros para monstros, e o numero de elementos no array n, e imprime
//todos os monstros, pela ordem em que aparecem no array. Caso nao existam elementos no array
//imprime "None\n"
void println_monstros(Monstro *monstros[], int n) 
{
    if (n <= 0)
    {
        printf("None\n"); 
        return;
    }
    for (int i = 0; i < n; i++)
        println_monstro(monstros[i]);
}


//Dado um array de ponteiros para monstros, e um numero n de monstros a ler, le do standard input os n monstros.
//cada monstro deve ser lido numa unica linha, com todos os membros separados por espaco, pela seguinte ordem
//<Nome do Monstro> <Tipo Criatura> <Tamanho> <Armor Class> <Hit Points> <Challenge Rating> <Trait>.
//Os membros que correspondem a cadeias de caracteres (strings) nao excederao os 100 caracteres cada.
//O metodo retorna o numero de monstros efetivamente lidos.
int get_monstros(Monstro *monstros[], int n) 
{
    int lidos = 0; 
    for (int i = 0; i < n; i++) 
    {
        char nome[100], tipo[100], trait[100];
        char tamanho_str[100], ac_str[100], hp_str[100], cr_str[100];
        Tamanho tamanho;
        int ac, hp;
        double cr;
        scanf("%s %s %s %s %s %s %s", nome, tipo, tamanho_str, ac_str, hp_str, cr_str, trait);
        tamanho = string_to_tamanho(tamanho_str);
        ac = atoi(ac_str);
        hp = atoi(hp_str);
        cr = atof(cr_str);
        Monstro *m = monstro(nome, tipo, tamanho, ac, hp, cr, trait);
        monstros[lidos++] = m;
    }

    return lidos;
}

//Dado um ponteiro para um ficheiro, um array de ponteiros para monstros, e um numero n de monstros a ler, le do ficheiro os n monstros.
//cada monstro deve ser lido numa unica linha, com todos os membros separados pelo separador "," pela seguinte ordem
//<Nome do Monstro>,<Tipo Criatura>,<Tamanho>,<Armor Class>,<Hit Points>,<Challenge Rating>,<Trait>
//Os membros que correspondem a cadeias de caracteres (strings) podem ter espaços e nao excederao os 100 caracteres cada.
//O metodo retorna o numero de monstros efetivamente lidos.
int get_monstros_from_file(FILE *f, Monstro *monstros[], int n) 
{
    int num_monstros = 0;
    fscanf(f, "%d", &num_monstros);

    n = num_monstros;
    //para mudar de linha para a 2ª
    fgetc(f);
    for (int i = 0; i < n; i++) 
    {
        char linha[200]; 
        
        fgets(linha, sizeof(linha), f);
        
        char *nome = strtok(linha, ",");
        char *tipo = strtok(NULL, ",");
        char *tamanho = strtok(NULL, ",");
        int ac = atoi(strtok(NULL, ","));
        int hp = atoi(strtok(NULL, ","));
        double cr = atof(strtok(NULL, ","));
        char *trait = strtok(NULL, "\n");
        
        
        monstros[i] = monstro(nome, tipo, string_to_tamanho(tamanho), ac, hp, cr, trait);
    }
    
    return num_monstros;
}

//Dado um array de ponteiros para monstros, um numero n de monstros, uma string com o nome, 
//esta funcao procura no array monstros pelo primeiro monstro com nome igual ao nome recebido,
// e retorna o ponteiro para esse monstro.
//Caso nao exista tal monstro, retorna-se o ponteiro NULL
Monstro *pesquisa_monstro(Monstro *monstros[], int n, char *nome) 
{
    for (int i = 0; i < n; i++) 
        if (strcmp(monstros[i]->nome, nome) == 0) 
            return monstros[i];
    return NULL;
}

//Dado um array de ponteiros para monstros, um numero n de monstros nesse array, retorna o monstro
//com maior numero de hit points. Caso nao exista nenhum monstro, retorna-se NULL
Monstro *pesquisa_monstro_mais_duro(Monstro *monstros[], int n) 
{
    Monstro *monstro_mais_duro = monstros[0];
    for (int i = 1; i < n; i++)
        if (monstros[i]->hp > monstro_mais_duro->hp)
            monstro_mais_duro = monstros[i];
    return monstro_mais_duro;
}

//dado um array de entrada de ponteiros de monstros in, e um array de saida de ponteiros de monstros out,
//um inteiro n que corresponde ao numero de elementos de in, e um Predicado sobre Monstros
//esta funcao procura no array in todos os monstros que satisfaze o predicado, colocando-os no 
//array de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int pesquisa_monstros(Monstro *in[], Monstro *out[], int n, int (*p)(Monstro*)) 
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

int medium_hp_predicado(Monstro *m) 
{
    return (strcmp(tamanho_to_string(m->tam), "Medium") == 0 && m->hp >= 10);
}
//dado um array de entrada de ponteiros de monstros in, e um array de saida de ponteiros de monstros out,
//um inteiro n que corresponde ao numero de elementos de in, e uma string com um nome de um tipo de monstro
//esta funcao procura no array in todos os monstros com o tipo recebido, colocando-os no 
//array de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int pesquisa_monstros_tipo(Monstro *in[], Monstro *out[], int n, char *tipo) 
{
    int count = 0;
    for (int i = 0; i < n; i++) 
        if (strcmp(in[i]->tipo, tipo) == 0) 
            out[count++] = in[i]; 
    return count;
}

int cmp_monstros(const void *a, const void *b) 
{
    Monstro *ma = *(Monstro **)a;
    Monstro *mb = *(Monstro **)b;

    // ordena primeiro por CR (decrescente)
    if (ma->cr > mb->cr)
        return -1;
    else if (ma->cr < mb->cr)
        return 1;
    else         
        return strcmp(ma->nome, mb->nome);
}


//dado um array de entrada de ponteiros de monstros in, um array de saida de ponteiros de monstros out,
//um inteiro n que corresponde ao numero de elementos de in, e dois inteiros que correspondem
//a um numero minimo e maximo do challenge rating, esta funcao procura no array in todos
//os monstros com challenge rating compreendido entre os valores minimo e maximo (inclusive),
//colocando-os no array de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int pesquisa_monstros_cr(Monstro *in[], Monstro *out[], int n, double cr_min, double cr_max) 
{
    int num_monstros_encontrados = 0;

    for (int i = 0; i < n; i++) 
    {
        if (in[i]->cr >= cr_min && in[i]->cr <= cr_max) 
        {
            out[num_monstros_encontrados] = in[i];
            num_monstros_encontrados++;
        }
    }

    return num_monstros_encontrados;
}

void test_Monstro_File_Loading(void) 
{
    Monstro **array_tipo;
    Monstro **array_cr;
    double cr_max;
    char tipo[100], cr_min[100];

    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    
    Monstro *monstros[1000];
    int n_monstros = get_monstros_from_file(f, monstros, 2000);

    fclose(f);

    array_tipo = malloc(n_monstros * sizeof(Monstro));
    array_cr = malloc(n_monstros * sizeof(Monstro));

    while (scanf("%s %s", tipo, cr_min) != EOF)
    {
        int temp = pesquisa_monstros_tipo(monstros, array_tipo, n_monstros, tipo);
        if(!strcmp(cr_min, "*"))
        {
            println_monstros(array_tipo, temp);
        }else
        {
            scanf("%lf", &cr_max);
            array_cr = malloc(temp * sizeof(Monstro));
            temp = pesquisa_monstros_cr(array_tipo, array_cr, temp, atof(cr_min), cr_max);
            println_monstros(array_cr, temp);
        }
    }
    free(array_tipo);
    free(array_cr);
}

void test_Monstro_Sorting(void) 
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    
    Monstro *monstros[1000];
    int n_monstros = get_monstros_from_file(f, monstros, 2000);
    fclose(f);

    qsort(monstros, n_monstros, sizeof(Monstro *), cmp_monstros);
    println_monstros(monstros, n_monstros);
}

void test_Monstro_Pesquisa(void) 
{
    char filename[100];
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    
    Monstro *monstros[100];
    int n_monstros = get_monstros_from_file(f, monstros, 2000);
    fclose(f);

    Monstro *medium_hp_monstros[100];
    int num_medium_hp_monstros = pesquisa_monstros(monstros, medium_hp_monstros, n_monstros, medium_hp_predicado);

    println_monstros(medium_hp_monstros, num_medium_hp_monstros);
}

#endif
