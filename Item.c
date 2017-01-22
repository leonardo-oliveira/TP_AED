#include "Item.h"

struct Item
{
	Chave C;
	//Nome, endereço, notas, preço, etc...
};

PItem CriaItem(Chave C)
{
	PItem I = malloc(sizeof( struct Item ));
	I->C = C;
	return I;
}
PItem ItemValido(){
    return CriaItem(1);
}
PItem ItemNulo()
{
	return CriaItem(-1);
}

Chave RetornaChave(PItem I)
{
	return I->C;
}

int ComparaChave(Chave A, Chave B)
{
	if(A > B)
		return 1;
	else if(A == B)
		return 0;
	else
		return -1;
}

void ImprimeItem(PItem I)
{
	printf("%d", RetornaChave(I));
}



