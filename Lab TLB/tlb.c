#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>

int main(int argc, char *argv[])
{

	/*para rodar na mesma CPU*/
	/*
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(0, &mask);
	sched_setaffinity(0, sizeof(cpu_set_t), &mask);
	*/

	int *v;	   /*estrutura para acessar as paginas*/
	int salto; /*armazena tamanho do salto*/
	int j, k;
	double tempo, total;
	clock_t inicio, fim;

	struct timeval
	{
		int P, I; /*paginas, iteracoes*/
	};

	/*print("Carregando arquivo %s\n", argv[1]);*/
	FILE *f = fopen(argv[1], "r");

	while (fscanf(f, "%d %d", &P, &I) != EOF)
	{
		/*printf("%d %d\n", P, I);*/
		v = (int *)malloc(4096 * P); /*cria vetor ocupando P paginas;*/
		salto = 4096 / sizeof(int);	 /*1024 eh o tamanho do salto*/

		for (j = 0; j < I; j++) /*realiza I iteracoes*/
		{
			for (k = 0; k < (P * salto); k += salto) /*acessando P paginas*/
			{
				inicio = clock();
				v[k] = j; /* realizando acesso*/
				fim = clock();
				tempo = (double)(fim - inicio);
				total += tempo;
			}
		}

		total /= I * P;
		printf("%d %.15lf\n", P, total);
		free(v);
	}
	fclose(f);

	return 0;
}