#include <stdio.h>
#include "Dicionario.h"
#include "Item.h"
#include <string.h>


int main()
{
	PDicionario D = CriaDicionario();
        Chave c;
        c = 5;
	PItem I = CriaItem(c);
        InserirSecundaria(D, I);
        c = 3;
        PItem K = CriaItem(c);
        InserirSecundaria(D, K);
        c = 6;
        PItem J = CriaItem(c);
        InserirSecundaria(D, J);
        c = 4;
        PItem Y = CriaItem(c);
        InserirSecundaria(D,Y);
        c=7;
        PItem o = CriaItem(c);
        InserirSecundaria(D,o);
	Buscar(D,3);
        Buscar(D,4);
        Remover_MultiArvore(D,3);

        Imprimir(D);
	return 0;
}
