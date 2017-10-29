/*************************************************/
/* Nome: Leonardo Zaccarias           RA: 620491 */
/* Nome: Ricardo Mendes Leal Junior   RA: 562262 */
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaCompras.h"
#include "estoque.h"

int criarListaDeCompra(LISTA_DE_COMPRA *lc)
{
	lc = (LISTA_DE_COMPRA*)malloc(sizeof(LISTA_DE_COMPRA));
	
	if (lc != NULL)
	{
		lc->quantidade_itens = 0;
		lc->total_preco = 0;
		lc->inicio = NULL;
		return 1;
	}
	
	return 0;
}

// Retorna 1 se deu certo e 0 caso contrario
int inserirCompra(LISTA_DE_COMPRA *lc, char *nomeProd, int quantidade, ESTOQUE *e)
{	
	NO_LISTA *prod, *atual, *anterior;
	int i = 0;
	atual = (*lc).inicio;
	anterior = NULL;
	prod = (NO_LISTA*)malloc(sizeof(NO_LISTA));
	prod->prod.nome_prod = (char*)malloc(sizeof(char)*30);
	strcpy(prod->prod.nome_prod, nomeProd);
	prod->prod.qtdd = quantidade;

	
	while (atual != NULL)
	{
		if (strcmp(atual->prod.nome_prod, nomeProd) == 0)
		{
			atual->prod.qtdd = atual->prod.qtdd + quantidade;
			removerDoEstoque(e, prod->prod);
			return 1;
		}

		atual = atual->prox;
	}	
	
	for (i = 0 ; i < e->tamanho ; i++)
	{
		if (strcmp(e->item[i].nome_prod, nomeProd) == 0)
		{
			prod->prod.preco = e->item[i].preco;

			if (prod->prod.qtdd > e->item[i].qtdd)
			{
				prod->prod.qtdd = e->item[i].qtdd;
			}

			removerDoEstoque(e, prod->prod);
		}
	}		
	//Se não tiver caixa, só coloca na primeira posição
	if (lc->inicio == NULL)
	{
		(*lc).inicio = prod;
		prod->prox = NULL;
		return 1;
	}

	atual = lc->inicio;
	while (atual != NULL)
	{
		//Comparo caractere a caractere das strings, quando for diferente
		for(i = 0; prod->prod.nome_prod[i] == atual->prod.nome_prod[i]; i++);
		
		//Se o caractere na posição i de PROD for menor que o caractere na posição i de ATUAL
		if (prod->prod.nome_prod[i] < atual->prod.nome_prod[i])
		{	
			//Se o anterior é nulo, coloco na primeira posição
			if (anterior == NULL)
			{
				lc->inicio = prod;
				prod->prox = atual;
				return 1;
			}

			//Se o anterior não for nulo, coloco numa posição genérica
			anterior->prox = prod;
			prod->prox = atual;
			return 1;
		}

		//Ando as duas caixas, duas a duas
		anterior = atual;
		atual = atual->prox;
	}

	anterior->prox = prod;
	prod->prox = NULL;
	return 1;
}

// Retorna 1 se deu certo e 0 caso contrario
int removerCompra(LISTA_DE_COMPRA *lc, ITEM *itemRemovido, ESTOQUE *e)
{
	NO_LISTA *atual, *anterior; 	
	atual = (*lc).inicio;
	anterior = NULL;
		
	while((atual != NULL) && (strcmp(atual->prod.nome_prod, itemRemovido->nome_prod) != 0))
	{
		anterior = atual;
		atual = atual->prox;
	}

	if(atual == NULL)
	{
		return 0;
	}

	itemRemovido->qtdd = itemRemovido->qtdd * (-1);
		
	if(itemRemovido->qtdd < atual->prod.qtdd)
	{
		atual->prod.qtdd = atual->prod.qtdd - itemRemovido->qtdd;
	}	
	else
	{		
		//remover o primeiro
		if(anterior == NULL)
		{
			itemRemovido->qtdd = atual->prod.qtdd;
			(*lc).inicio = atual->prox;
			free(atual);
		}		
		
		//remove a partir do primeiro
		else
		{
			itemRemovido->qtdd = atual->prod.qtdd;
			anterior->prox = atual->prox;
			free(atual);
		}
	}
	
	inserirNoEstoque(e, (*itemRemovido));
	
	return 1;	
}

// Libera a lista. Retorna 1 se deu certo e 0 caso contrario
int removerProdutos(LISTA_DE_COMPRA *lc)
{	
	NO_LISTA *aux;
	aux = (*lc).inicio;
	
	while(aux != NULL)
	{
		aux = aux->prox;
		free(lc->inicio);
		(*lc).inicio = aux;
	}
	
	(*lc).quantidade_itens = 0;
	(*lc).total_preco = 0;
	
	return 1;
}

// Imprime a lista. Imprime todos os itens (nome, quantidade, preco) da compra em ordem alfabetica do nome do produto. Ao final, imprimir o total a ser pago.
void imprimeCompra(LISTA_DE_COMPRA *lc)
{
	NO_LISTA *aux;
	aux = (*lc).inicio;
	
	while (aux != NULL)
	{
		printf("\n %s\t %d x %.2f = %.2f", aux->prod.nome_prod, aux->prod.qtdd, aux->prod.preco, aux->prod.qtdd * aux->prod.preco);
		(*lc).total_preco = (*lc).total_preco + aux->prod.qtdd * aux->prod.preco;
		(*lc).quantidade_itens = (*lc).quantidade_itens + aux->prod.qtdd;
		aux = aux->prox;
	}
	
	printf("\n Número de itens: %d \n Total a ser pago: R$ %.2f\n\n", (*lc).quantidade_itens, (*lc).total_preco);
}











