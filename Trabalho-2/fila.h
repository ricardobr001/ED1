/*************************************************/
/* Nome: Leonardo Zaccarias           RA: 620491 */
/* Nome: Ricardo Mendes Leal Junior   RA: 562262 */
/*************************************************/

/*
* Implementacao de Fila
*/

#ifndef FILA_H
#define FILA_H

typedef struct coordenada
{
	int x;
	int y;
} Coordenada;

typedef struct elem{
	Coordenada info;
	struct elem *lig;
}tipo_elem;

typedef struct fila{
  tipo_elem *head;
  tipo_elem *tail;
} Fila;

/* Inicializa uma Fila */
void inicFila(Fila *p_l);

/* Verifica se a Fila está vazia ou nao */
int filaVazia(Fila *p_l);

/* Insere um elemento na Fila */
void insereFila(Fila *p_l, Coordenada e);

/* Remove um elemento da Fila */
Coordenada removeFila(Fila *p_l);

#endif
