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

PNo BuscarRecursivo(PNo anda, Chave C)
{
	if(anda == NULL){
            return;
	}if(ComparaChave(C, RetornaChave(anda->I)) == 0)
            return anda;
	if(ComparaChave(C, RetornaChave(anda->I)) > 0)
		return BuscarRecursivo(anda->direita, C);
	return BuscarRecursivo(anda->esquerda, C);
}
int buscaSecundaria (PNo anda, Chave C, PNo anterior){
    while(anda){ //na arvore secundaria de x
		if(ComparaChave(C, RetornaChave(anda->I)) == 0){ //compara a busca com a chave da arvore
                    if(ComparaChave(C,RetornaChave(anterior->I)) > 0 ){//olha se a chave é maior q x
                        if(anterior-> direita == NULL){
                            anterior->secundaria = RemoverIterativo(anterior->secundaria,C);
                            PNo x = CriaNo(CriaItem(C));
                            anterior->direita = x;
                            return 1;
                        }else{ //caso exista,insere secundaria direita
                        anterior->secundaria = RemoverIterativo(anterior->secundaria,C);
                        anterior = anterior->direita;

                        anterior->secundaria = InserirRecursivo(anterior->secundaria,CriaItem(C));
                        return 1;// se achou, e fez as alterações, retorna 1
                    }
                    }else if(ComparaChave(C,RetornaChave(anterior->I)) < 0 ){//olha se a chave e mnor q x
                        if (anterior->esquerda == NULL){  // se n houver esquerda, cria esquerda
                            anterior->secundaria = RemoverIterativo(anterior->secundaria,C);
                            PNo x = CriaNo(CriaItem(C));
                            anterior->esquerda = x;
                            return 1;
                        }else{  // caso exista, insere na secundaria da esquerda
                            anterior->secundaria = RemoverIterativo(anterior->secundaria,C);
                            anterior = anterior->esquerda;
                            anterior->secundaria =InserirRecursivo(anterior->secundaria,CriaItem(C));
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
	Percorrer(anterior->esquerda, C, anterior);
	Percorrer(anterior->direita, C, anterior);
}
PNo RemoverIterativo(PNo raiz, Chave C)
{
	PNo ant = NULL;
	PNo anda = raiz;

	while(anda != NULL && ComparaChave(RetornaChave(anda->I), C) != 0 )
	{
		ant = anda;
		if(ComparaChave(RetornaChave(anda->I), C) > 0)
			anda = anda->esquerda;
		else if(ComparaChave(RetornaChave(anda->I), C) < 0)
			anda = anda->direita;
	}
	if(anda == NULL)
	{
		return;
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

			if(ant == NULL){//Remoção da raiz
				raiz = prox;
			}else if(ComparaChave(C, RetornaChave(ant->I)) > 0){
				ant->direita = prox;
			}else if(ComparaChave(C, RetornaChave(ant->I)) < 0){
				ant->esquerda = prox;
                        }

			free(anda);
                        return raiz;
		}
		return raiz;
	}
}
PNo Remover(PNo anda, Chave C)
{
	if(anda == NULL) return -1;
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
		return;
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
		return raiz;
	}
}
void Remover_MultiArvore(PDicionario D, Chave C ){
    PNo anda = D->raiz;
    PNo anterior;
    if (BuscarIterativo(D, C) == -1) { //caso nao encontre na arvore principal, vá para as secundarias
            PercorrerRemocao(anda, C,anterior);
            return;
    }
    else{
            if(ComparaChave(C,RetornaChave(D->raiz->secundaria->I))== 0){

								D->raiz->secundaria = Remover(D->raiz->secundaria,RetornaChave(D->raiz->secundaria->I));
								D->raiz->I = CriaItem(C);
                return;
            }
        RemoverPrincipal(D,C);
        return;
    }
}
void PercorrerRemocao(PNo anda,Chave C, PNo anterior){//para percorrer toda a arvore
	if(anda == NULL) return;
         anterior = anda;
        if (buscaSecundariaRemocao(anda->secundaria,C,anterior) == 1){
            return;
        }
	PercorrerRemocao(anterior->esquerda, C, anterior);
	PercorrerRemocao(anterior->direita, C, anterior);
}
int buscaSecundariaRemocao (PNo anda, Chave C, PNo anterior){
    while(anda){ //na arvore secundaria
		if(ComparaChave(C, RetornaChave(anda->I)) == 0){ //compara a busca com a chave da arvore
                       anterior->secundaria = Remover(anterior->secundaria,C);
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

void RemoverPrincipal(PDicionario D, Chave C){
    // ja sabemos que esta na arvore principal o que se busca
        PNo pai = NULL;
				PNo anda = D->raiz;
        int a = 1;
	while(a==1){
			if(ComparaChave(C, RetornaChave(anda->I)) == 0){
	                    a=0;
			}else if(ComparaChave(C, RetornaChave(anda->I)) > 0){
	                        pai = anda;
	                        anda = anda->direita;
			}else{
	                        pai = anda;
													anda = anda->esquerda;
	    }
	}// meu anda é o no que quero remover
    while(anda->secundaria != NULL){ // pego a raiz e comparo com null
        InserirRecursivo(pai->secundaria,anda->secundaria->I); //INSIRO NO PAI, A RAIZ
        anda->secundaria = RemoverIterativo(anda->secundaria,RetornaChave(anda->secundaria->I)); // remove a raiz
    }
       D->raiz= RemoverIterativo(D->raiz, C); // remove da principal
}
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
