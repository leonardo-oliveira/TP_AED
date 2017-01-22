#ifndef ITEM_H
#define ITEM_H

#include <stdlib.h>
#include <stdio.h>


typedef struct Item * PItem;

typedef int Chave;

PItem CriaItem(Chave C);
PItem ItemNulo();

Chave RetornaChave(PItem I);
int ComparaChave(Chave A, Chave B);
void ImprimeItem(PItem I);
PItem ItemValido();

#endif