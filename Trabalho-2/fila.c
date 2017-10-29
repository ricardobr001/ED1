/*************************************************/
/* Nome: Leonardo Zaccarias           RA: 620491 */
/* Nome: Ricardo Mendes Leal Junior   RA: 562262 */
/*************************************************/

/*
* Implementacao de Fila
*/

#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

/* Inicializa uma Fila */
void inicFila(Fila *p_l){
	p_l->head = NULL;
	p_l->tail = NULL;
}

/* Verifica se a Fila está vazia ou nao */
int filaVazia(Fila *p_l){
	if (p_l->head == NULL)
		return 1;
	return 0;
}

/* Insere um elemento na Fila */
void insereFila(Fila *p_l, Coordenada e){
	tipo_elem *novo, *aux;
	novo = malloc(sizeof(tipo_elem));
	novo->info = e;
	aux = p_l->tail;

	if (p_l->head != NULL)
	{
		p_l->tail->lig = novo;
		p_l->tail = novo;
		novo->lig = NULL;
	}
	else
	{
		p_l->head = novo;
		p_l->tail = novo;
		novo->lig = NULL;
	}
}

/* Remove um elemento da Fila */
Coordenada removeFila(Fila *p_l){
	tipo_elem *aux;
	Coordenada info;
	aux = p_l->head;

	if (aux != NULL)
	{
		info = aux->info;
		p_l->head = aux->lig;
		free(aux);
		return info;
	}
	
	info.x = 0;
	info.y = 0;

	return info;
}