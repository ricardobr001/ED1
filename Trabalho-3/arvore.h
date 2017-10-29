/*************************************************/
/* Nome: Leonardo Zaccarias           RA: 620491 */
/* Nome: Ricardo Mendes Leal Junior   RA: 562262 */
/*************************************************/

/**
 * Estrutura e metodos da arvore
 */

#ifndef ARVORE_H
#define ARVORE_H

#define TAM_NOME 31
#define ITEM_LISTA "%s\t %d x %.2f = %.2f\n"
#define TOTAL "Numero de itens: %d\nTotal a ser pago: R$ %.2f\n\n"
#define ITEM_INSUFICIENTE "Numero insuficiente de %s em estoque\n"
#define ITEM_N_ENCONTRADO "Item não encontrado no estoque\n"

//Estrutura da arvore
typedef struct no {
	char nome_prod[TAM_NOME];
	float preco;
	int quantidade;
	struct no *esq, *dir;
} No;

typedef No *Arvore;

void cria_arvore(Arvore *t); //Inicializa a arvore

No *busca_item(Arvore t, char *nomeItem); //Busca item. Retorna o endereço do nó se for encontrado, NULL caso não seja encontrado

int arvoreVazia(Arvore *t); //Retorna 1 se a arvore estiver vazia, 0 caso tenha pelo menos 1 item

int insere_item(Arvore *t, char *nomeItem, int quantidade, float preco); //Aumenta quantidade do item na arvore ou cria o item caso não exista.

//Aumenta quantidade do item na arvore ou cria o item caso não exista e diminui a quantidade na outra arvore ou remove completamente
int insere_item_compra(Arvore *t, Arvore *p, char *nomeItem, int quantidade);

int remove_item(Arvore *t, char *nomeItem, int quantidade); //Diminui quantidade do item na arvore.

int liberaArvore(Arvore t); //Desaloca os nós da arvore

int imprimeCompra(Arvore t, int *itens, float *total); //Faz a impressao da lista de compras conforme a especificacao do trabalho

//Imprime a arvore em um arquivo
int imprimeArquivo(Arvore t, FILE *fpWrite);

#endif