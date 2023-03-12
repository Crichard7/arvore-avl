#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "avl.h"
#include <string.h>

void inicializar(arvore_avl *raiz){
    *raiz = NULL;
}

int inicializartabela(tabela *tab){
    inicializar(&tab->indices);
    tab->arquivo_dados = fopen("dados.dat", "a+b");
    tab->indices = carregar_arquivo("indices.dat", tab->indices);
    if(tab->arquivo_dados != NULL)
        return 1;
    else
        return 0;
}

void finalizar(tabela *tab){
    fclose(tab->arquivo_dados);
    salvar_arquivo("indices.dat", tab->indices);
}

void adicionarFilme(tabela *tab, dado *filme){
    int posicaoNovoRegistro;
    if(tab->arquivo_dados != NULL){
        fseek(tab->arquivo_dados, 0L, SEEK_END);
        posicaoNovoRegistro = ftell(tab->arquivo_dados);

        tipo_dado * novo = (tipo_dado *) malloc(sizeof(tipo_dado));
        novo->chave = filme->codigo;
        novo->indice = posicaoNovoRegistro;
        tab->indices = adicionar(novo, tab->indices);

        tipo_dado * novo2 = (tipo_dado *) malloc(sizeof(tipo_dado));
        strcpy(novo2->chave, filme->titulo);
        novo2->indice = posicaoNovoRegistro;
        tab->indices = adicionar(novo2, tab->indices);

        fwrite(filme, sizeof(dado), 1, tab->arquivo_dados);
    }
}

//Insere elementos na árvore
arvore_avl adicionar_avl(tipo_dado *valor, arvore_avl raiz){
     //Árvore vazia
    if(raiz == NULL){
        arvore_avl novo = (arvore_avl) malloc(sizeof(arvore_avl));
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
        return novo;
    } else {
        if(valor > raiz->valor)
            raiz->dir = adicionar_avl(valor, raiz->dir);
        else
            raiz->esq = adicionar_avl(valor, raiz->esq);
    }
    //Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;

    //verifica a necessidade de balancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

fime * procurarFilme(tabela *tab, int chave){
    if(tab->arquivo_dados != NULL){
        arvore_avl temp;
        temp = tab->indices;
        while(temp != NULL){
            if(temp->dado->chave == chave){

                fseek(tab->arquivo_dados, temp->dado->indice, SEEK_SET);

                dado * encontrado = (dado *) malloc(sizeof(dado));
                fread(encontrado, sizeof(dado), 1, tab->arquivo_dados);

                return encontrado;
            } else {
                if(chave > temp->dado->chave)
                    temp = temp->dir;
                else
                    temp = temp->esq;
            }
        }
    }
    return NULL;
}

//Compara e retorna o maior valor(altura)
int maior(int a, int b){
    return (a > b)? a: b;
}

tipo_dado * maior_elemento(arvore_avl raiz){
    if(raiz == NULL)
        return NULL;
    if(raiz->dir == NULL)
        return raiz->dado;
    else
        return maior_elemento(raiz->dir);
}

tipo_dado * menor_elemento(arvore_avl raiz){
    if(raiz == NULL)
        return NULL;
    if(raiz->esq == NULL)
        return raiz->dado;
    else
        return menor_elemento(raiz->esq);
}

//Calcula e retorna a altura de um nó
int alturaDoNo(arvore_avl No){
    //Caso o nó seja NULL será retornado o valor: -1
    if(No == NULL)
        return -1;
    else
        return No->altura;
}

//Calcula o fator de balanço de um nó
int fatorDeBalanco(arvore_avl No){
    //Se o No != NULL
    if(No)
        return (alturaDoNo(No->esq) - alturaDoNo(No->dir));
    else
        return 0;
}

//Rotaciona à esquerda
arvore_avl rotacaoSimplesEsq(arvore_avl r){
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
arvore_avl rotacaoSimplesDir(arvore_avl ){
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
arvore_avl rotacaoDuplaEsq(arvore_avl r){
    r->esq = rotacaoSimplesEsq(r->esq);
    return rotacaoSimplesDir(r);
}

//Rotaciona à direita e à esquerda(rotação dupla direita)
arvore_avl rotacaoDuplaDir(arvore_avl r){
    r->dir = rotacaoSimplesDir(r->dir);
    return rotacaoSimplesEsq(r);
}

//Balancear a árvore
arvore_avl balancear(arvore_avl raiz){
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

void imprimir_elemento(arvore_avl raiz, tabela *tab){
    dado * temp = (dado *) malloc(sizeof(dado));
    fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);
    fread(temp, sizeof(dado), 1, tab->arquivo_dados);
    printf("[%d, %s, %s, %.1f ]\n", raiz->dado->chave, temp->titulo, temp->genero, temp->lancamento, temp->IMDb);
    free(temp);
}

//Remover elementos da árvore
arvore_avl remover_avl(int valor, arvore_avl raiz){
    //Raiz nula, valor não encontrado
    if(raiz == NULL)
        return NULL;
    else
        //Procura o nó a ser removido
        if(raiz->dado->chave == valor){
            //Remove nós sem filhos(nós folhas)
            if(raiz->esq == NULL && raiz->dir == NULL){
                free(raiz);
                return NULL;
            }
            else{
                //remove nós que possuem 2 filhos
                if(raiz->esq != NULL && raiz->dir != NULL){
                    arvore_avl aux = raiz->esq;
                    while(aux->dir != NULL)
                        aux = aux->dir;
                    raiz->dado->chave = aux->dado->chave;
                    //Elemento encontrado
                    aux->dado->chave = valor;
                    raiz->esq = remover_avl(valor, raiz->esq);
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
            if(valor > raiz->dado->chave)
                raiz->dir = remover_avl(valor, raiz->dir);
            else
                raiz->esq = remover(valor, raiz->esq);
        }

        //Recalcula a altura de todos os nós da árvore
        raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;

        //Verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
}

dado * ler_dado(){
    dado *novo = (dado *) malloc(sizeof(dado));
    getchar();
    printf("Titulo: ");
    int tam = strlen(titulo);
    fgets(novo->tirulo, tam, stdin );
    tirar_enter(novo->titulo);
    printf("Genero: ");
    fgets(novo->genero, 30, stdin );
    tirar_enter(novo->genero);
    printf("Lancamento: ");
    scanf("%d", novo->lancamento);
    printf("IMDb: ");
    scanf("%f", novo->IMDb);
    printf("Codigo: ");
    scanf("%d", novo->codigo);

    return novo;
}

void tirar_enter(char *string){
    string[strlen(string) -1] = '\0';
}

void preOrder_avl(arvore_avl raiz, tabela *tab){
    if(raiz != NULL){
        imprimir_elemento(raiz, tab);
        preOrder(raiz->esq);
        preOrder(raiz->dir);
    }
}

void inOrder_avl(arvore_avl raiz, tabela *tab){
    if(raiz != NULL){
        inOrder(raiz->esq);
        imprimir_elemento(raiz, tab);
        inOrder(raiz->dir);
    }
}

void posOrder_avl(arvore_avl raiz, tabela *tab){
    if(raiz != NULL){
        posOrder(raiz->esq);
        posOrder(raiz->dir);
        imprimir_elemento(raiz, tab);
    }
}

void salvar_arquivo(char *nome, arvore a){
    FILE *arq;
    arq = fopen(nome, "wb");
    if(arq != NULL){
        salvar_auxiliar(a, arq);
        fclose(arq);
    }
}

void salvar_auxiliar(arvore_avl raiz, FILE *arq){
    if(raiz != NULL){
        fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
        salvar_auxiliar(raiz->esq, arq);
        salvar_auxiliar(raiz->dir), arq);
    }
}

arvore_avl carregar_arquivo(char *nome, arvore_avl a){
    FILE *arq;
    arq = fopen(nome, "rb");
    tipo_dado * temp;
    if(arq != NULL){
        temp = (tipo_dado *) malloc(sizeof(tipo_dado));
        while(fread(temp, sizeof(tipo_dado), 1, arq)){
            a = adicionar_avl(temp, a);
            temp = (tipo_dado *) malloc(sizeof(tipo_dado));
        }
        fclose;
    }
    return a;
}

