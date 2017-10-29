/* Estrutura da lista de compras */
#ifndef _listaCompras_h
#define _listaCompras_h

#include "estoque.h"

typedef struct lista {
	
	ITEM prod; // qtdd aqui representa a quantidade do item que sera comprado e nao do estoque
	struct lista *prox;

} NO_LISTA;

typedef struct lista_de_compra {

	int quantidade_itens;
	float total_preco;

	NO_LISTA *inicio;

} LISTA_DE_COMPRA;

int criarListaDeCompra(LISTA_DE_COMPRA *lc); 

int inserirCompra(LISTA_DE_COMPRA *lc, char *nomeProd, int quantidade, ESTOQUE *e); // Retorna 1 se deu certo e 0 caso contrario

int removerCompra(LISTA_DE_COMPRA *lc, ITEM *itemRemovido, ESTOQUE *e); // Retorna 1 se deu certo e 0 caso contrario

int removerProdutos(LISTA_DE_COMPRA *lc); // Libera a lista. Retorna 1 se deu certo e 0 caso contrario

void imprimeCompra(LISTA_DE_COMPRA *lc); // Imprime a lista. Imprime todos os itens (nome, quantidade, preco) da compra em ordem alfabetica do nome do produto. Ao final, imprimir o total a ser pago.

#endif