/*************************************************/
/* Nome: Leonardo Zaccarias           RA: 620491 */
/* Nome: Ricardo Mendes Leal Junior   RA: 562262 */
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int main()
{
	//Declarando as variáveis
	char a = 'S';
	char nome[31];
	int op, qtdd, itens = 0;
	float preco, total = 0;
	Arvore estoque, compra;
	FILE *fpRead, *fpWrite;

	//Abertura do fluxo de leitura
	fpRead = fopen("estoque.data", "r");

	//Criando as duas arvores
	cria_arvore(&estoque);
	cria_arvore(&compra);

	//Lendo os dados do arquivo
	fscanf(fpRead, "%d", &op);

	while (!feof(fpRead))
	{
		if (op == 1)
		{
			fscanf(fpRead, "%s %f %d", nome, &preco, &qtdd);
			insere_item(&estoque, nome, qtdd, preco);
		}
		else if (op == 2)
		{
			fscanf(fpRead, "%s %d", nome, &qtdd);
			//find = busca_item(estoque, nome);
			remove_item(&estoque, nome, qtdd);
		}

		fscanf(fpRead, "%d", &op);
	}

	//Fechando o fluxo de leitura
	fclose(fpRead);

	//Laço de repetição para iniciar uma compra
	while(a == 'S' || a == 's')
	{
	 	printf("Deseja iniciar uma nova compra? (S/N)\n");
		scanf("\n%[^\n]s", &a);

		//Se o usuario digitar N ou n, ele não quer efetuar uma nova compra, para o laço
		if ((a == 'N') || (a == 'n'))
		{
			break;
		}

		//Lendo a operação
		scanf("%d", &op);

		//Enquanto o usuário não digitar 0, insere na lista de compras
		while (op != 0)
		{
			scanf("%s", nome);			
			insere_item_compra(&compra, &estoque, nome, op);
			scanf("%d", &op);
		}

		//Imprimindo a lista de compras e liberando a arvore
		imprimeCompra(compra, &itens, &total);
		liberaArvore(compra);				
		printf(TOTAL, itens, total);
	}

	//Imprimindo o novo estoque no arquivo "estoque.data"
	fpWrite = fopen("estoque.data", "w+");
	imprimeArquivo(estoque, fpWrite);
	fclose(fpWrite);

	//Liberando a arvore do estoque
	liberaArvore(estoque);

	return 0;
}