#ifndef AVL_H
#define AVL_H

typedef struct no {
    int valor;
    struct no *esq, *dir;
    int altura;
} no;

//opção - Criar novo nó
no* novoNo(int valor);

//opção - Comparar altura
int maior(int a, int b);

//opção - Calcular altura de um nó
int alturaDoNo(no *No);

//opção - Calcular o fator de balanço de um nó
int fatorDeBalanco(no *No);

//opção - Rotacionar uma vez à esquerda
no* rotacaoSimplesEsq(no *r);

//opção - Rotacionar um vez à direita
no* rotacaoSimplesDir(no *r);

//opção - Rotacionar à esquerda e à direita(rotação dupla esquerda)
no* rotacaoDuplaEsq(no *r);

//opção - Rotacionar à direita e à esquerda(rotação dupla direita)
no* rotacaoDuplaDir(no *r);

//opção - Inserir
no* inserir(no *raiz, int valor);

//opção - Balancear
no* balancear(no *raiz);

//opção - Remover
no* remover(no *raiz, int valor);

//opção - Imprimir pré ordem
void preOrder(no *raiz);

//opção - Imprimir em ordem
void inOrder(no *raiz);

//opção - Imprimir pós ordem
void posOrder(no *raiz);

/*
//opção 1 - Inserir
no* inserir(no *raiz, int valor int *cresceu);

//opção 2 - Imprimir pré ordem
void preOrder(no *raiz);

//opção 3 - Imprimir em ordem
void inOrder(no *raiz);

//opção 4 - Imprimir pós ordem
void posOrder(no *raiz);

//opção 5 - Buscar elementos na árvore bst
no* buscar(no* raiz, int valor);

//opção 6 - Calcular altura da árvore bst
int altura(no *raiz);

// opção 7 - Calcular quantidade de nós da árvore bst
int qtd_nos(no *raiz);

// opção 8 - Calcular a quantidade de folhas da árvore bst
int qtd_folhas(no *raiz);

// opção 9 - remover nó da árvore bst
no* remover(no *raiz, int valor);

int maior(int  a, int b);

int maiorElemento(no *raiz);

int menorElemento(no *raiz);

no* rotacionar(no *raiz);

no* rotacaoSimplesEsq(no *raiz);

no* rotacaoSimplesDir(no *raiz);

no* rotacaoDuplaEsq(no *raiz);

no* rotacaoDuplaDir(no *raiz);*/


#endif
