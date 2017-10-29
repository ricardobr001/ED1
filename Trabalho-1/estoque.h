/* Estrutura do estoque */
#ifndef _estrutura_h
#define _estrutura_h

#define MAX 100000


typedef struct item {
	
	char *nome_prod;
	float preco;
	int qtdd;

} ITEM;

typedef struct estoque {

	ITEM item[MAX];
	int tamanho;

} ESTOQUE;


int criarListaDeEstoque(ESTOQUE *e); 

int inserirNoEstoque(ESTOQUE *e, ITEM prod); // Retorna 1 se deu certo e 0 caso contrario

int removerDoEstoque(ESTOQUE *e, ITEM itemRemovido); // Retorna 1 se deu certo e 0 caso contrario

int estoqueCheio(ESTOQUE *e); // Retorna 1 se o vetor estiver cheio e 0 caso contrario

int estoqueVazio(ESTOQUE *e); // Retorna 1 se o vetor estiver vazio e 0 caso contrario

#endif