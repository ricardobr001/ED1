/*************************************************/
/* Nome: Leonardo Zaccarias           RA: 620491 */
/* Nome: Ricardo Mendes Leal Junior   RA: 562262 */
/*************************************************/

/*
* Implementacao de Pilha 
*/

#include "pilha.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

/* Inicializa uma Pilha */
void inicPilha(Pilha *p_l){
	p_l->prox = NULL;
}

/* Verifica se a Pilha está vazia ou nao */
int PilhaVazia(Pilha *p_l){
	if (p_l->prox == NULL)
		return 1;
	return 0;
}

/* Insere um elemento na Pilha */
void push(Pilha *p_l, Coordenada e){
	No_Pilha *novo;
	novo = malloc(sizeof(No_Pilha));
	novo->info = e;
	novo->prox = p_l->prox;
	p_l->prox = novo;
}


/* Remove um elemento da Pilha.
   Retorna 0 caso a Pilha esteja vazia */
Coordenada pop(Pilha *p_l){
	No_Pilha *topo;
	Coordenada ret;

	// o usuario da pilha deveria testar se a pilha nao esta vazia antes da chamada desta funcao
	if (PilhaVazia(p_l))
	{
		ret.x = -1;
		ret.y = -1;

		return ret;
	}

	topo = p_l->prox;
	p_l->prox = topo->prox;
	ret = topo->info;
	free (topo);
	return ret;	
}