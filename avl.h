#ifndef AVL_H
#define AVL_H

typedef struct no {
    int valor;
    struct no *esq, *dir;
    int fb;
} no;

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

no* rotacaoDuplaDir(no *raiz);


#endif
