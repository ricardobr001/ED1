/*************************************************/
/* Nome: Leonardo Zaccarias           RA: 620491 */
/* Nome: Ricardo Mendes Leal Junior   RA: 562262 */
/*************************************************/

/*
* Implementacao de Pilha 
*/

#ifndef PILHA_H
#define PILHA_H
#include "fila.h"

typedef struct noPilha{
  Coordenada info;
  struct noPilha *prox;
} No_Pilha;

typedef No_Pilha Pilha;

/* Inicializa uma Pilha */
void inicPilha(Pilha *p_l);

/* Verifica se a Pilha está vazia ou nao */
int PilhaVazia(Pilha *p_l);

/* Insere um elemento na Pilha */
void push(Pilha *p_l, Coordenada e);

/* Remove um elemento da Pilha */
Coordenada pop(Pilha *p_l);

#endif