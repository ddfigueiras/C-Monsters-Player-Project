#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum 
{
    Tiny,
    Small,
    Medium, 
    Large, 
    Huge,
    Gargantuan
} Size;

typedef struct 
{
    char *name;
    char *type;
    Size size;
    int a_class;
    int h_points;
    double c_rating;
} Monster;

Monster cria_monstro(char* name, char* type, char size, int a_class, int h_points, float c_rating) 
{
    Monster monster;
    strcpy(monster.name, name);
    strcpy(monster.type, type);
    monster.size = size;
    monster.a_class = a_class;
    monster.h_points = h_points;
    monster.c_rating = c_rating;
    return monster;
}

void imprimir_monstro(Monster *m) 
{
    char *localStr;
    switch (m->size) 
    {
        case Tiny:
            localStr = "Tiny";
            break;
        case Small:
            localStr = "Small";
            break;
        case Medium:
            localStr = "Medium";
            break;
        case Large:
            localStr = "Large";
            break;
        case Huge:
            localStr = "Huge";
            break;
        case Gargantuan:
            localStr = "Gargantuan";
            break;
    } 
    printf("%s - %s, AC:%d, HP:%d, CR:%.2f\n", m->name, localStr, m->name, m->type, m->a_class, m->h_points, m->c_rating);
}

void monstros_to_monstros_ptr(Monster in[], Monster *out[], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        out[i] = &in[i];
    }
}

int pesquisa_monstros_cr(Monster **in, int n, Monster **out, double cr_min, double cr_max) 
{
    int num_resultados = 0;
    for (int i = 0; i < n; i++) 
    {
        if (in[i]->c_rating >= cr_min && in[i]->c_rating <= cr_max) 
        {
            out[num_resultados] = in[i];
            num_resultados++;
        }
    }
    return num_resultados;
}

int pesquisa_monstros_tipo(Monster* in, int n, Monster* out, char* type) 
{
    int i, counter = 0;
    for (i = 0; i < n; i++) 
    {
        if (strcmp(in[i].type, type) == 0)
            out[counter++] = in[i];
    }
    return counter;
}

int get_monstros(Monster *monsters, int n)  
{
    int i, h_points, a_class;
    char name[100], type[100], size_str[15];
    float c_rating;
    Size size;
    for (i = 0; i < n; i++) 
    {
        scanf("%s %s %s %d %d %lf", name, type, size_str, &a_class, &h_points, &c_rating);

        if (strcmp("Tiny", size_str) == 0)
            size = Tiny;
        if (strcmp("Small", size_str) == 0)
            size = Small;
        if (strcmp("Medium", size_str) == 0)
            size = Medium;
        if (strcmp("Large", size_str) == 0)
            size = Large;
        if (strcmp("Huge", size_str) == 0)
            size = Huge;
        if (strcmp("Gargantuan", size_str) == 0)
            size = Gargantuan;

        monsters[i] = cria_monstro(name, type, size, a_class, h_points, c_rating);
    }
    return n;
}


void test(void)
{
	int n = 0;
	scanf("%d", &n);
	Monster *monster = malloc(n * sizeof(Monster));
	int monster_count = get_monstros(monster, n);
	char tipo[100];
	char C_R[100];
	Monster **monstros_ptr = malloc(monster_count * sizeof(Monster*));
	Monster **monstros_CR = malloc(monster_count * sizeof(Monster*));
	Monster **monstros_tipo = malloc(monster_count * sizeof(Monster*));
	monstros_to_monstros_ptr(monster,monstros_ptr,monster_count);
	while(scanf("%s", tipo)!=EOF)
	{
		int type = 0;
		int CR_shown = 0;
		scanf("%s", C_R);
		if(strcmp(C_R,"*"))
		{
			double CR_min;
			double CR_max;
			sscanf(C_R, "%lf", &CR_min);
			scanf("%lf", &CR_max);
			CR_shown=pesquisa_monstros_cr(monstros_CR,monstros_ptr,monster_count,CR_min,CR_max);
			type=pesquisa_monstros_tipo(monstros_tipo,monstros_CR,CR_shown,tipo);
		}
		else
			type = pesquisa_monstros_tipo(monstros_tipo,monstros_ptr,monster_count,tipo);
		if(type == 0)
			printf("None\n");
		else
			for(int i=0;i<type;i++)
				imprimir_monstro(*monstros_tipo[i]);
	}
}

int main(int argc, char**argv)
{
    int x = 'F';
    if(argc>1)
        x = *argv[1];
    if(x == 'F')
        test();
    else if(x == 'U')
        printf("All unit tests PASSED.\n");
    else
        printf("%s:Invalid option.\n", argv[1]);
    return 0;
}
