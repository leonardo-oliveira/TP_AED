#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <stdlib.h>
#include "Item.h"

typedef struct Dicionario * PDicionario;
typedef struct No * PNo;

PDicionario CriaDicionario();
void Inserir(PDicionario D, PItem I);
int Remover(PNo anda, Chave C);
void Imprimir(PDicionario D);
void InserirSecundaria(PDicionario D, PItem I);
void Percorrer(PNo anda,Chave C, PNo anterior);
void Buscar(PDicionario D, Chave C);
int buscaSecundaria (PNo anda, Chave C, PNo anterior);
PNo InserirRecursivo(PNo anda, PItem I);
int buscaSecundariaRemocao (PNo anda, Chave C, PNo anterior);
void PercorrerRemocao(PNo anda,Chave C, PNo anterior);
void Remover_MultiArvore(PDicionario D, Chave C );
void Imprimir(PDicionario D);
void InOrdem(PNo anda);
void InOrdemSecundaria(PNo anda);
void InserirIterativo(PNo anda, PItem I);
PNo CriaNo(PItem I);
PNo RemoverIterativo(PNo raiz, Chave C);
PNo InserirPai(PNo pai, PItem C);
void RemoverPrincipal(PDicionario D, Chave C);
#endif