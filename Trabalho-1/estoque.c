#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

int criarListaDeEstoque(ESTOQUE *e)
{
	e->tamanho = 0;
}

// Retorna 1 se deu certo e 0 caso contrario
int inserirNoEstoque(ESTOQUE *e, ITEM prod)
{
	int i = 0;
	if (!estoqueCheio(e))
	{
		for (i = 0 ; i < e->tamanho ; i++)
		{
			if (strcmp(e->item[i].nome_prod, prod.nome_prod) == 0)
			{
				e->item[i].qtdd = e->item[i].qtdd + prod.qtdd;
				return 1;
			}
		}

		e->item[e->tamanho].nome_prod = (char*)malloc(sizeof(char)*30);
		strcpy(e->item[e->tamanho].nome_prod, prod.nome_prod);
		e->item[e->tamanho].preco = prod.preco;
		e->item[e->tamanho].qtdd = e->item[e->tamanho].qtdd + prod.qtdd;
		e->tamanho++;

		return 1;
	}

	return 0;
}

// Retorna 1 se deu certo e 0 caso contrario
int removerDoEstoque(ESTOQUE *e, ITEM itemRemovido)
{
	int i = 0, j = 0;

	if (!estoqueVazio(e))
	{
		for (i = 0 ; i < e->tamanho ; i++)
		{
			if (strcmp(e->item[i].nome_prod, itemRemovido.nome_prod) == 0)
			{

				e->item[i].qtdd = e->item[i].qtdd - itemRemovido.qtdd;

				if (e->item[i].qtdd == 0)
				{
					for (j = i ; j < e->tamanho-1 ; j++)
					{
						e->item[j] = e->item[j+1]; 
					}

					e->tamanho--;
				}

				return 1;
			}			
		}
	}
	return 0;
}

// Retorna 1 se o vetor estiver cheio e 0 caso contrario
int estoqueCheio(ESTOQUE *e)
{
	if (e->tamanho == MAX)
	{
		return 1;
	}

	return 0;
}

// Retorna 1 se o vetor estiver vazio e 0 caso contrario
int estoqueVazio(ESTOQUE *e)
{
	if (e->tamanho == 0)
	{
		return 1;
	}

	return 0;
}