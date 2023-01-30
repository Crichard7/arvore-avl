#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

//Cria um novo nó com o valor a ser inserido
no* novoNo(int valor){
    no *novo = malloc(sizeof(no));

    if(novo){
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
    }
    //Retorna o endereço do nó criado
    return novo;
}

//Compara e retorna o maior valor(altura)
int maior(int a, int b){
    return (a > b)? a: b;
}

//Calcula e retorna a altura de um nó
int alturaDoNo(no *No){
    //Caso o nó seja NULL será retornado o valor: -1
    if(No == NULL)
        return -1;
    else
        return No->altura;
}

//Calcula o fator de balanço de um nó
int fatorDeBalanco(no *No){
    //Se o No != NULL
    if(No)
        return (alturaDoNo(No->esq) - alturaDoNo(No->dir));
    else
        return 0;
}

//Rotaciona à esquerda
no* rotacaoSimplesEsq(no *r){
    no *y, *f;

    y = r->dir;
    f = y->esq;

    y->esq = r;
    r->dir = f;

    //Recalcula a alura dos nós
    r->altura = maior(alturaDoNo(r->esq), alturaDoNo(r->dir)) + 1;
    y->altura = maior(alturaDoNo(y->esq), alturaDoNo(y->dir)) + 1;

    return y;
}

//Rotaciona à direita
no* rotacaoSimplesDir(no *r){
    no *y, *f;

    y = r->esq;
    f = y->dir;

    y->dir = r;
    r->esq = f;

    //Recalcula a alura dos nós
    r->altura = maior(alturaDoNo(r->esq), alturaDoNo(r->dir)) + 1;
    y->altura = maior(alturaDoNo(y->esq), alturaDoNo(y->dir)) + 1;

    return y;
}

//Rotaciona à esquerda e à direita(rotação dupla esquerda)
no* rotacaoDuplaEsq(no *r){
    r->esq = rotacaoSimplesEsq(r->esq);
    return rotacaoSimplesDir(r);
}

//Rotaciona à direita e à esquerda(rotação dupla direita)
no* rotacaoDuplaDir(no *r){
    r->dir = rotacaoSimplesDir(r->dir);
    return rotacaoSimplesEsq(r);
}

//Insere elementos na árvore
no* inserir(no *raiz, int valor){
    //Árvore vazia
    if(raiz == NULL)
        return novoNo(valor);
    else{
        if(valor > raiz->valor)
            raiz->dir = inserir(raiz->dir, valor);
        else
            raiz->esq = inserir(raiz->esq, valor);
    }
    //Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;

    //verifica a necessidade de balancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

//Balancear a árvore
no* balancear(no *raiz){
    int fb = fatorDeBalanco(raiz);

    //Rotação Simples à esquerda
    if(fb < -1 && fatorDeBalanco(raiz->dir) <= 0)
        raiz = rotacaoSimplesEsq(raiz);

    //Rotação Simples à direita
    else if(fb > 1 && fatorDeBalanco(raiz->esq) >= 0)
        raiz = rotacaoSimplesDir(raiz);

    //Rotação Dupla à esquerda
    else if(fb > 1 && fatorDeBalanco(raiz->esq) < 0)
        raiz = rotacaoDuplaEsq(raiz);

    //Rotação Dupla à direita
    else if(fb < -1 && fatorDeBalanco(raiz->dir) > 0)
        raiz = rotacaoDuplaDir(raiz);

    return raiz;

}

//Remover elementos da árvore
no* remover(no *raiz, int valor){
    //Raiz nula, valor não encontrado
    if(raiz == NULL)
        return NULL;
    else
        //Procura o nó a ser removido
        if(raiz->valor == valor){
            //Remove nós sem filhos(nós folhas)
            if(raiz->esq == NULL && raiz->dir == NULL){
                free(raiz);
                return NULL;
            }
            else{
                //remoove nós que possuem 2 filhos
                if(raiz->esq != NULL && raiz->dir != NULL){
                    no *aux = raiz->esq;
                    while(aux->dir != NULL)
                        aux = aux->dir;
                    raiz->valor = aux->valor;
                    //Elemento encontrado
                    aux->valor = valor;
                    raiz->esq = remover(raiz->esq, valor);
                    return raiz;
                }
                else{
                    //Remove nós que possuem apenas 1 filhos
                    no *aux;
                    if(raiz->esq != NULL)
                        aux = raiz->esq;
                    else
                        aux = raiz->dir;
                    //Remove o elemento
                    free(raiz);
                    return aux;
                }

            }
        }
        else{
            if(valor < raiz->valor)
                raiz->esq = remover(raiz->esq, valor);
            else
                raiz->dir = remover(raiz->dir, valor);
        }

        //Recalcula a altura de todos os nós da árvore
        raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;

        //Verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
}

void preOrder(no *raiz){
    if(raiz != NULL){
        printf("[%d]", raiz->valor);
        preOrder(raiz->esq);
        preOrder(raiz->dir);
    }
}

void inOrder(no *raiz){
    if(raiz != NULL){
        inOrder(raiz->esq);
        printf("[%d]", raiz->valor);
        inOrder(raiz->dir);
    }
}

void posOrder(no *raiz){
    if(raiz != NULL){
        posOrder(raiz->esq);
        posOrder(raiz->dir);
        printf("[%d]", raiz->valor);
    }
}
