/*************************************************/
/* Nome: Leonardo Zaccarias           RA: 620491 */
/* Nome: Ricardo Mendes Leal Junior   RA: 562262 */
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"
#include "listaCompras.h"

int main()
{
	char a = 'S';
	char *nome;
	int op;
	ESTOQUE e;
	FILE *fpRead;
	ITEM prod;
	LISTA_DE_COMPRA lc;
	nome = (char*)malloc(sizeof(char)*30);
	prod.nome_prod = malloc(30*sizeof(char*));

	fpRead = fopen("mercadorias.txt", "r");

	criarListaDeEstoque(&e);
	criarListaDeCompra(&lc);

	fscanf(fpRead, "%d", &op);

	while (!feof(fpRead))
	{
		if (op == 1)
		{
			fscanf(fpRead, "%s %f %d", prod.nome_prod, &prod.preco, &prod.qtdd);
			inserirNoEstoque(&e, prod);
		}
		else if (op == 2)
		{
			fscanf(fpRead, "%s %d", prod.nome_prod, &prod.qtdd);
			prod.preco = 0;
			removerDoEstoque(&e, prod);
		}

		fscanf(fpRead, "%d", &op);
	}

	while(a == 'S' || a == 's')
	{
	 	printf("Deseja iniciar uma nova compra? (S/N)");
		scanf("\n%[^\n]s", &a);

		if ((a == 'N') || (a == 'n'))
		{
			return 0;
		}

		scanf("%d", &op);

		while (op != 0)
		{
			scanf("%s", nome);

			if (op > 0)
			{
				inserirCompra(&lc, nome, op, &e);
			}
			else if (op < 0)
			{
				strcpy(prod.nome_prod, nome);
				prod.qtdd = op;
				removerCompra(&lc, &prod, &e);
			}

			scanf("%d", &op);
		}

		imprimeCompra(&lc);
		removerProdutos(&lc);
	}

	return 0;
}
