#include "Dicionario.h"
struct No
{
	PItem I;
	struct No * esquerda;
	struct No * direita;
        struct No * secundaria;
};

typedef struct No * PNo;

struct Dicionario//Árvore binária de busca
{
	struct No* raiz;
}; 

PDicionario CriaDicionario()
{
	PDicionario D = malloc(sizeof(struct Dicionario));
	D->raiz = NULL;

	return D;
}

PNo  CriaNo(PItem I)
{
	PNo x = malloc(sizeof(struct No));
	x->I = I;
	x->esquerda = NULL;
	x->direita = NULL;
        x->secundaria = NULL;
	return x;
}
// inserção normal, sempre na secundaria da raiz, ou na raiz
void InserirSecundaria(PDicionario D, PItem I){
    PNo anda = D->raiz;
    if (D->raiz == NULL){      // caso a raiz seja nulo, criar raiz
        D->raiz = CriaNo(I);
        return;
    }
    else{
        if (anda->secundaria == NULL){
            anda->secundaria = CriaNo(I);
            return;
        }
        InserirRecursivo(anda->secundaria, I); //se n for nulo, inserir como ABB na secundaria da raiz
    }
}
PNo InserirRecursivo(PNo anda, PItem I)
{   
    
	if(anda == NULL){
		anda = CriaNo(I);
	}else if(ComparaChave(RetornaChave(I), RetornaChave(anda->I)) > 0){    
            anda->direita = InserirRecursivo(anda->direita, I);
                
	}else if(ComparaChave(RetornaChave(I), RetornaChave(anda->I)) < 0){	
            anda->esquerda = InserirRecursivo(anda->esquerda, I);
        }
	return anda;
}

int BuscarIterativo(PDicionario D, Chave C)
{
	PNo anda = D->raiz;	

	while(anda)
		if(ComparaChave(C, RetornaChave(anda->I)) == 0){
			return 1;
		}else if(ComparaChave(C, RetornaChave(anda->I)) > 0){
			anda = anda->direita;
		}else{
			anda = anda->esquerda;
                }
	return -1;
}

PItem BuscarRecursivo(PNo anda, Chave C)
{
	if(anda == NULL){
            return ItemNulo();
	}if(ComparaChave(C, RetornaChave(anda->I)) == 0)	
            return anda->I;
	if(ComparaChave(C, RetornaChave(anda->I)) > 0)
		return BuscarRecursivo(anda->direita, C);
	return BuscarRecursivo(anda->esquerda, C);
}
int buscaSecundaria (PNo anda, Chave C, PNo anterior){
    while(anda){ //na arvore secundaria de x
		if(ComparaChave(C, RetornaChave(anda->I)) == 0){ //compara a busca com a chave da arvore
                    if(ComparaChave(C,RetornaChave(anterior->I)) > 0 ){//olha se a chave é maior q x
                        if(anterior-> direita == NULL){
                            PNo x = CriaNo(RemoverIterativo(anterior->secundaria,C));
                            anterior->direita = x;
                            return 1;
                        }else{ //caso exista,insere secundaria direita
                        anda= anterior->secundaria;
                        anterior = anterior->direita;     
                        anterior->secundaria = InserirRecursivo(anterior->secundaria,RemoverIterativo(anda,C));  
                        return 1;// se achou, e fez as alterações, retorna 1
                    }
                    }else if(ComparaChave(C,RetornaChave(anterior->I)) < 0 ){//olha se a chave e mnor q x
                        if (anterior->esquerda == NULL){  // se n houver esquerda, cria esquerda
                            PNo x = CriaNo(RemoverIterativo(anterior->secundaria,C));
                            anterior->esquerda = x;
                            return 1;
                        }else{  // caso exista, insere na secundaria da esquerda
                            anda = anterior->secundaria;
                            anterior = anterior->esquerda;
                            anterior->secundaria =InserirRecursivo(anterior->secundaria,RemoverIterativo(anda,C));
                            return 1;
                        }    
                    }
                }else if(ComparaChave(C, RetornaChave(anda->I)) > 0){
			anda = anda->direita;
		}else{
			anda = anda->esquerda;
                }
    }
	return -1;
}
void Buscar(PDicionario D, Chave C)
{
    PNo anda = D->raiz;
    PNo anterior;
        if (BuscarIterativo(D, C) == -1){ //caso nao encontre na arvore principal, vá para as secundarias
            Percorrer(anda, C,anterior);
            return;
        }
    else{
            return;
    }
}

void Percorrer(PNo anda,Chave C, PNo anterior){//para percorrer toda a arvore
	if(anda == NULL) return;
        anterior = anda;
        anda = anda->secundaria;
        
        if (buscaSecundaria(anda,C,anterior) == 1){
            return;
        }
	Percorrer(anda->esquerda, C, anterior);
	Percorrer(anda->direita, C, anterior);
}
PItem RemoverIterativo(PNo raiz, Chave C)
{
	PNo anterior = NULL;
	PNo anda = raiz;

	while(anda != NULL && ComparaChave(RetornaChave(anda->I), C) != 0 )
	{
		anterior = anda;
		if(ComparaChave(RetornaChave(anda->I), C) > 0)
			anda = anda->esquerda;
		else if(ComparaChave(RetornaChave(anda->I), C) < 0)
			anda = anda->direita;
	}
	if(anda == NULL)
	{
		return ItemNulo();
	}
	else	
	{
		PItem I = anda->I;

		//Se o nó possui dois filhos
		if(anda->direita != NULL && anda->esquerda != NULL)
		{
			//encontrar o maior da esquerda		
			PNo maioresquerda = anda->esquerda;
			while(maioresquerda->direita != NULL)
				maioresquerda = maioresquerda->direita;

			anda->I = RemoverIterativo(raiz, RetornaChave(maioresquerda->I));
		}
		else
		{
			PNo prox = NULL;
			if(anda->direita != NULL && anda->esquerda == NULL)
				prox = anda->direita;
			else if(anda->direita == NULL && anda->esquerda != NULL)
				prox = anda->esquerda;

			if(anterior == NULL){//Remoção da raiz
				raiz = prox;
                                raiz = NULL;
			}else if(ComparaChave(C, RetornaChave(anterior->I)) > 0){
				anterior->direita = prox;
			}else if(ComparaChave(C, RetornaChave(anterior->I)) < 0){
				anterior->esquerda = prox;
                        }
                        
			free(anda);
		}
		return I;
	}
}
PItem Remover(PNo anda, Chave C)
{
	if(anda == NULL) return ItemNulo();
        PNo raiz = anda;
        PNo anterior = NULL;
        PNo pai;
	while(anda != NULL && ComparaChave(RetornaChave(anda->I), C) != 0 )
	{
		anterior = anda;
		if(ComparaChave(RetornaChave(anda->I), C) > 0)
			anda = anda->esquerda;
		else if(ComparaChave(RetornaChave(anda->I), C) < 0)
			anda = anda->direita;
	}
	if(anda == NULL)
	{
		return ItemNulo();
	}
	else	
	{
		PItem I = anda->I;

		//Se o nó possui dois filhos
		if(anda->direita != NULL && anda->esquerda != NULL)
		{
			//encontrar o maior da esquerda		
			PNo maioresquerda = anda->esquerda;
			while(maioresquerda->direita != NULL)
				maioresquerda = maioresquerda->direita;

			anda->I = RemoverIterativo(raiz, RetornaChave(maioresquerda->I));
		}
		else
		{
			PNo prox = NULL;
			if(anda->direita != NULL && anda->esquerda == NULL)
				prox = anda->direita;
			else if(anda->direita == NULL && anda->esquerda != NULL)
				prox = anda->esquerda;

			if(anterior == NULL)//Remoção da raiz
				raiz = prox;
			else if(ComparaChave(C, RetornaChave(anterior->I)) > 0)
				anterior->direita = prox;
			else if(ComparaChave(C, RetornaChave(anterior->I)) < 0)
				anterior->esquerda = prox;

			free(anda);
		}
		return I;
	}
}
void Remover_MultiArvore(PDicionario D, Chave C ){
    PNo anda = D->raiz;
    PNo anterior;
    if (BuscarRecursivo(anda, C) == ItemNulo()) { //caso nao encontre na arvore principal, vá para as secundarias
            PercorrerRemocao(anda, C,anterior);
            return;
    }
    else{
        //RemoverPrincipal(anda,C);
            return;
    }
}
void PercorrerRemocao(PNo anda,Chave C, PNo anterior){//para percorrer toda a arvore
	if(anda == NULL) return;
         anterior = anda;
        anda = anda->secundaria;
        if (buscaSecundariaRemocao(anda,C,anterior) == 1){
            return;
        }
	PercorrerRemocao(anda->esquerda, C, anterior);
	PercorrerRemocao(anda->direita, C, anterior);
}
int buscaSecundariaRemocao (PNo anda, Chave C, PNo anterior){
    while(anda){ //na arvore secundaria
		if(ComparaChave(C, RetornaChave(anda->I)) == 0){ //compara a busca com a chave da arvore
                        Remover(anda,C);
                        return 1;// se achou, e removeu
                }else if(ComparaChave(C, RetornaChave(anda->I)) > 0){ 
                    anda = anda->direita;
		}else{
                    anda = anda->esquerda;
                }
    }
        anda = anterior;
	return -1;
}
/*void RemoverPrincipal(PNo anda, Chave C){
    while (anda){
        PNo pai = anda;
        if (ComparaChave(C,RetornaChave(anda->I)) == 0){
            anda = anda->secundaria;
            InserirSecundaria();
        }else if (ComparaChave(C,RetornaChave(anda->I)) > 0){
            anda = anda->direita;
        }else if(ComparaChave(C,RetornaChave(anda->I)) < 0){
            anda = anda->esquerda;
        }
    }
}
*/
/* se achar na principal, mover elementos da sua secundaria
 para a secundaria de seu pai. e depois ser removido */
void Imprimir(PDicionario D)
{
	if(D == NULL) return;

	InOrdem(D->raiz);	
	
}
void InOrdem(PNo anda)
{
	if(anda == NULL) return;

	InOrdem(anda->esquerda);
	ImprimeItem(anda->I);
        printf("(");
        InOrdemSecundaria(anda->secundaria);
	printf(")");
        InOrdem(anda->direita);
}
void InOrdemSecundaria(PNo anda)
{
	if(anda == NULL) return;
	InOrdemSecundaria(anda->esquerda);
	ImprimeItem(anda->I);
        printf(" ");
	InOrdemSecundaria(anda->direita);
}
