#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

no* inserir(no *raiz, int valor, int *cresceu){
    //Caso base
    if(raiz == NULL){
        no *novo;
        //Alocação de memória
        novo = (no*)malloc(sizeof(no));
        //Inicialização de valores
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->fb = 0;
        * cresceu = 1;
        //Retorno do ponteiro para o nó criado
        return novo;
    } else {
        //Verificação para inserção de valores à esquerda (se <) ou à direita (se >)
        if(valor > raiz->valor){
            raiz->dir = inserir(raiz->dir, valor, cresceu);
            if(*cresceu){
                switch(raiz->fb){
                    case 0:
                        raiz->fb = 1;
                        *cresceu = 1;
                        break;
                    case -1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                    case 1:
                        *cresceu = 0;
                        //o fb seria = 2
                        return rotacionar(raiz);
                }
            }
        } else {
            raiz->esq = inserir(raiz->esq, valor, cresceu);
        }
        return raiz;
    }
}
