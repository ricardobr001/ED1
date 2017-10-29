/*************************************************/
/* Nome: Leonardo Zaccarias           RA: 620491 */
/* Nome: Ricardo Mendes Leal Junior   RA: 562262 */
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

void cria_arvore(Arvore *t) //Inicializa a arvore
{
	*t = NULL;
}

No *busca_item(Arvore t, char *nomeItem) //Busca item. Retorna o endereço do nó se for encontrado, NULL caso não seja encontrado
{
	int i;

	//Se t for nulo, ou a arvore está vazia ou não encontrou o item
	if (t == NULL)
	{
		return NULL;
	}

	//Se o nome do item na arvore for igual ao procurado, retorna t
	if (strcmp(t->nome_prod, nomeItem) == 0)
	{
		return t;
	}

	//Comparo caractere a caractere das strings, quando for diferente, paramos o laço
	for (i = 0 ; t->nome_prod[i] == nomeItem[i] ; i++);

	//Se o caractere na arvore for maior que o do nomeItem, vai para o próximo nó da esquerda
	if (t->nome_prod[i] > nomeItem[i])
	{
		return busca_item(t->esq, nomeItem);
	}
	else
	{
		return busca_item(t->dir, nomeItem);
	}
}

int arvoreVazia(Arvore *t) //Retorna 1 se a arvore estiver vazia, 0 caso tenha pelo menos 1 item
{
	if ((*t) == NULL)
	{
		return 1;
	}

	return 0;
}

int insere_item(Arvore *t, char *nomeItem, int quantidade, float preco) //Aumenta quantidade do item na arvore ou cria o item caso não exista.
{
	int i = 0;
	No *novo;

	//Se o conteudo de t for nulo, ou o novo nó é uma raiz ou sera uma nova folha
	if ((*t) == NULL)
	{
		novo = malloc(sizeof(No));
		strcpy(novo->nome_prod, nomeItem);
		novo->preco = preco;
		novo->quantidade = quantidade;
		novo->esq = NULL;
		novo->dir = NULL;
		*t = novo;
		return 1;
	}
	//Se não, pode ser que o item já está na arvore, assim, vemos se o item da arvore é igual ao que vai ser inserido
	else if ((*t)->nome_prod[i] == nomeItem[i])
	{
		if (strcmp((*t)->nome_prod, nomeItem) == 0)
		{
			(*t)->preco = (*t)->preco + preco;
			(*t)->quantidade = (*t)->quantidade + quantidade;
			return 1;
		}
	}

	//Comparo caractere a caractere das strings, quando for diferente, paramos o laço
	for (i = 0 ; (*t)->nome_prod[i] == nomeItem[i] ; i++);

	//Se o caractere na arvore for maior que o do nomeItem, vai para o próximo nó da esquerda
	if ((*t)->nome_prod[i] > nomeItem[i])
	{
		return insere_item(&(*t)->esq, nomeItem, quantidade, preco);
	}
	else
	{
		return insere_item(&(*t)->dir, nomeItem, quantidade, preco);
	}
}

//Aumenta quantidade do item na arvore ou cria o item caso não exista e diminui a quantidade na outra arvore ou remove completamente
int insere_item_compra(Arvore *t, Arvore *p, char *nomeItem, int quantidade)
{
	No *encontra;

	//Econtra o item na arvore de estoque
	encontra = busca_item((*p), nomeItem);

	//Se o ponteiro for nulo, o item não está na arvore do estoque
	if (encontra == NULL)
	{
		printf(ITEM_N_ENCONTRADO);
		return 0;
	}
	//Se a quantidade da arvore for menor do que a solicidada, não há quantidade suficiente
	else if (encontra->quantidade < quantidade)
	{
		printf(ITEM_INSUFICIENTE, nomeItem);
		return 0;
	}

	//Remove item do estoque e coloca na lista de compras
	insere_item(t, nomeItem, quantidade, encontra->preco);
	remove_item(p, nomeItem, quantidade);

	return 1;
}

int remove_item(Arvore *t, char *nomeItem, int quantidade) //Diminui quantidade do item na arvore.
{
	No *retira, *aux;
	No **aux2;
	int i;

	//Andando a arvore e encontrando o nó que queremos retirar
	while(*t != NULL && strcmp((*t)->nome_prod, nomeItem) != 0)
	{
		for (i = 0 ; (*t)->nome_prod[i] == nomeItem[i] ; i++);

		if ((*t)->nome_prod[i] > nomeItem[i])
		{
			t = &(*t)->esq;
		}
		else
		{	
			t = &(*t)->dir;
		}
	}

	retira = *t;

	//Efetua a subtração da quantidade
	retira->quantidade = retira->quantidade - quantidade;

	//Se a quantidade for menor que 0
	if (retira->quantidade == 0)
	{
		//Nó folha
		if (retira->esq == NULL && retira->dir == NULL)
		{
			*t = NULL;
		}
		//Um unico filho
		else if (retira->esq == NULL && retira->dir != NULL)
		{
			*t = retira->dir;
		}
		else if (retira->esq != NULL && retira->dir == NULL)
		{
			*t = retira->esq;
		}
		//Dois filhos
		else
		{
			aux2 = &retira->dir;

			//Encontrando o maior nó da esquerda
			while ((*aux2)->esq != NULL)
			{
				aux2 = &(*aux2)->esq;
			}

			//Atribuições dos ponteiros
			aux = *aux2;
			*aux2 = aux->dir;
			aux->esq = retira->esq;
			aux->dir = retira->dir;
			*t = aux;
		}
		
		//Liberando o nó encontrado
		free(retira);
		return 1;
	}

	return 1;
}

int liberaArvore(Arvore t) //Desaloca os nós da arvore
{
	if (!arvoreVazia(&t))
	{
		liberaArvore(t->esq);
		liberaArvore(t->dir);
		free(t);
		t = NULL;
	}

	return 1;
}

int imprimeCompra(Arvore t, int *itens, float *total) //Faz a impressao da lista de compras conforme a especificacao do trabalho
{
	if (t != NULL)
	{
		imprimeCompra(t->esq, itens, total);
		printf(ITEM_LISTA, t->nome_prod, t->quantidade, t->preco, t->quantidade * t->preco);
		*total = *total + t->quantidade * t->preco;
		*itens = *itens + 1;
		imprimeCompra(t->dir, itens, total);
	}

	return 1;
}

//Imprime a arvore em um arquivo
int imprimeArquivo(Arvore t, FILE *fpWrite)
{
	if (t != NULL)
	{
		fprintf(fpWrite, "1 %s %.2f %d\n", t->nome_prod, t->preco, t->quantidade);
		imprimeArquivo(t->esq, fpWrite);
		imprimeArquivo(t->dir, fpWrite);	
	}

	return 1;	
}