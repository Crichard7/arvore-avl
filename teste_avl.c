#include "avl.h"
#include <stdio.h>


int main(){
    no *busca, *raiz = NULL;
    int opcao, valor;

    do{
        //printf("\nArvore AVL\n1- Inserir\n2 - Imprimir em ordem\n3 - Buscar valor\n4 - Calcualr altura\n5 - Calcular quantidade de nos\n6 - Calcular quantidade de folhas\n7 - Remover\n0 - Sair");
        //printf("\nDigite uma opcao: \n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                //Inserir
                //printf("\nDigite o valor a ser inserido: \n");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                break;
            case 2:
                //Imprimir em Ordem
                preOrder(raiz);
                printf("\n");
                inOrder(raiz);
                printf("\n");
                posOrder(raiz);
                printf("\n");
                break;
            /*case 3:
                //Buscar
                //printf("\nDigite o valor que ser procurado: \n");
                scanf("%d", &valor);
                busca = buscar(raiz, valor);
                if(busca != NULL){
                    printf("\nValor encontrado: %d\n", busca->valor);
                }
                else{
                    printf("\nValor nao encontrado\n");
                }
                break;
            case 4:
                //Calcular altura
                printf("%d", altura(raiz));
                printf("\n");
                break;
            case 5:
                printf("%d", qtd_nos(raiz));
                printf("\n");
                break;
            case 6:
                printf("%d", qtd_folhas(raiz));
                printf("\n");
                break;*/
            case 7:
                //printf("\nDigite o valor que ser removido: \n");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                break;
            default:
                if(opcao != 0)
                printf("\nOpcao Invalida!!!\n");
        }
    }while(opcao != 0);
}
