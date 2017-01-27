#include <stdio.h>
#include "Dicionario.h"
#include "Item.h"
#include <string.h>


int main()
{
	PDicionario D = CriaDicionario();
	while(1)
	{
		char comando[20];
		if(scanf("%s", comando) < 1 || strcmp(comando, "SAIR") == 0)
			break;

		if(strcmp(comando, "INSERIR") == 0)
		{
			Chave c;
			scanf("%d", &c);
			PItem I = CriaItem(c);
			InserirSecundaria(D, I);
		}
		else if(strcmp(comando, "BUSCAR") == 0)
		{
			Chave c;
			scanf("%d", &c);

			Buscar(D,c);
		}
		else if(strcmp(comando, "REMOVER") == 0)
		{
			Chave c;
			scanf("%d", &c);

			Remover_MultiArvore(D,c);
		}
		else if(strcmp(comando, "IMPRIMIR") == 0)
		{
			Imprimir(D);
		}
	}
	return 0;
}
