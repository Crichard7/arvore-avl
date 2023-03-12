#ifndef AVL_H
#define AVL_H

typedef struct filme{
    char *titulo;
    char genero[31];
    int lancamento;
    float IMDb;
    int codigo;
} dado;

typedef struct indice{
    int chave;
    int indice;
} tipo_dado;

typedef struct no_avl {
    tipo_dado *dado;
    struct no_avl *esq, *dir;
    int altura;
} no_avl;

typedef no_avl * arvore_avl;

typedef struct tabela{
        FILE *arquivo_dados;
        arvore_avl indices;
} tabela;

//Tabela
int inicializarTabela(tabela *tab);
void finalizar(tabela *tab);
void adicionarFilme(tabela *tab, dados *filme);

//opção - Criar novo nó
arvore_avl novo_no_avl(int valor);
//opção - Comparar altura
int maior(int a, int b);
//opção - Calcular altura de um nó
int alturaDoNo(arvore_avl No);
//opção - Calcular o fator de balanço de um nó
int fatorDeBalanco(arvore_avl No);
//opção - Rotacionar uma vez à esquerda
arvore_avl rotacaoSimplesEsq_avl(arvore_avl r);
//opção - Rotacionar um vez à direita
arvore_avl rotacaoSimplesDir_avl(arvore_avl r);
//opção - Rotacionar à esquerda e à direita(rotação dupla esquerda)
arvore_avl rotacaoDuplaEsq_avl(arvore_avl r);
//opção - Rotacionar à direita e à esquerda(rotação dupla direita)
arvore_avl rotacaoDuplaDir_avl(arvore_avl r);
//opção - Inserir
arvore_avl adicionar_avl(int valor, arvore_avl raiz);
//opção - Balancear
arvore_avl balancear(arvore_avl raiz);
//opção - Remover
arvore_avl remover_avl(int valor, arvore_avl raiz);
//opção - Imprimir pré ordem
void preOrder_avl(arvore_avl raiz, tabela *tab);
//opção - Imprimir em ordem
void inOrder_avl(arvore_avl raiz, tabela *tab);
//opção - Imprimir pós ordem
void posOrder_avl(arvore_avl raiz, tabela *tab);
void imprimir_elemento(arvore_avl raiz, tabela *tab);
tipo_dado * maior_elemento(arvore_avl raiz);
tipo_dado * menor_elemento(arvore_avl raiz);
dado * ler_dados();
void tirar_enter(char *string);

filme * procurarFilme(tabela *tab, int chave);

void salvar_arquivo(char *nome, arvore_avl a);
void salvar_auxiliar(arvore_avl, FILE *arq);
arvore_avl carregar_arquivo(char *nome, arvore_avl a);


#endif
