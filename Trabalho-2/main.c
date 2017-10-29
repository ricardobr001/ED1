/*************************************************/
/* Nome: Leonardo Zaccarias           RA: 620491 */
/* Nome: Ricardo Mendes Leal Junior   RA: 562262 */
/*************************************************/

#include <stdio.h>
#include "pilha.h"
#include "fila.h"
#include <stdlib.h>
#include <string.h>

typedef struct posicao {
char tipo;
int visitado;
} Posicao;

typedef struct labirinto {
Posicao **p;
} Labirinto;

int verificaEsquerda(int x, int y, Posicao **matriz);
int verificaDireita(int x, int y, Posicao **matriz);
int verificaCima(int x, int y, Posicao **matriz);
int verificaBaixo(int x, int y, Posicao **matriz);

int main()
{
	char trab2[20];
	FILE *fpRead;
	Fila f;
	Pilha p;
	Coordenada coord;
	int i, j, nLin, nCol, x, y, nPremios = 0, premioEncontrado = 0;
	Posicao **matriz;
	fpRead = fopen("labirinto.txt", "r");
	fscanf(fpRead, "%s", trab2);
	inicFila(&f);
	inicPilha(&p);


	if (strcmp(trab2, "T2ROBO") != 0)
	{
		return 0;
	}

	//Pegando o tamanho da matriz
	fscanf(fpRead, "%d %d", &nLin, &nCol);

	//Alocando a matriz dinamicamente
	matriz = malloc(nLin*sizeof(Posicao*));

	for (i = 0 ; i < nLin ; i++)
	{
		matriz[i] = malloc(nCol*sizeof(Posicao));		
	}

	//Lendo o labirinto do arquivo e vendo se na posição i, j é a da origem
	for (i = 0 ; i < nLin ; i++)
	{
		for (j = 0 ; j < nCol ; j++)
		{
			do{
				fscanf(fpRead, "%c", &matriz[i][j].tipo);
			}while(matriz[i][j].tipo == '\n');

			if (matriz[i][j].tipo == 'p')
			{
				nPremios++;
			}

			if (matriz[i][j].tipo == 'x')
			{
				matriz[i][j].visitado = 1;
			}
			else if (matriz[i][j].tipo == 'b')
			{
				matriz[i][j].visitado = 1;
			}
			else if (matriz[i][j].tipo == 'o')
			{
				x = i;
				y = j;
				matriz[i][j].visitado = 1;

			}
			else
			{
				matriz[i][j].visitado = 0;
			}
		}
	}

	fclose(fpRead);

	i = 0;

	while (1)
	{
		if (verificaEsquerda(x, y, matriz) + verificaDireita(x, y, matriz) + verificaCima(x, y, matriz) + verificaBaixo(x, y, matriz) > 1)
		{	
			coord.x = x;
			coord.y = y;

			push(&p, coord);
		}

		if (verificaEsquerda(x, y, matriz))
		{
			y--;
		}
		else if (verificaDireita(x, y, matriz))
		{
			y++;
		}
		else if (verificaCima(x, y, matriz))
		{
			x--;
		}
		else if (verificaBaixo(x, y, matriz))
		{
			x++;
		}
		else
		{
			if (PilhaVazia(&p))
			{
				break;
			}

			coord = pop(&p);
			x = coord.x;
			y = coord.y;
		}

		if (matriz[x][y].tipo == 'p')
		{
			if (matriz[x][y].visitado == 0)
			{
				premioEncontrado++;
				coord.x = x;
				coord.y = y;
			
				insereFila(&f, coord);
			}
		}

		matriz[x][y].visitado = 1;
	}

	i = 0;

	while (!filaVazia(&f))
	{
		coord = removeFila(&f);
		printf("(%d,%d) ", coord.x, coord.y); //imprimir linha e coluna de cada premio encontrado
	}
	printf("\nPremios encontrados: %d\n", premioEncontrado); //quantidade de premios encontrados
	printf("Total de premios no labirinto: %d\n", nPremios); //quantidade total de premios no labirinto

}

int verificaEsquerda(int x, int y, Posicao **matriz)
{
	y--;

	if (matriz[x][y].visitado == 0)
	{
		return 1;
	}

	return 0;
}
int verificaDireita(int x, int y, Posicao **matriz)
{
	y++;

	if (matriz[x][y].visitado == 0)
	{
		return 1;
	}

	return 0;
}
int verificaCima(int x, int y, Posicao **matriz)
{
	x--;

	if (matriz[x][y].visitado == 0)
	{
		return 1;
	}

	return 0;
}
int verificaBaixo(int x, int y, Posicao **matriz)
{
	x++;

	if (matriz[x][y].visitado == 0)
	{
		return 1;
	}

	return 0;
}