//Andre Guimaraes Barros- 2020102600,Klarine Mendonca Silva -2020103337
#ifndef estruturas_h
#define estruturas_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tabela.h"

typedef struct arv Arv;

typedef struct lista Lista;


//Cria uma árvore vazia
Arv* arv_criavazia (void);

//cria uma árvore com a informação do nó raiz n, e
//com subárvore esquerda e e subárvore direita d
Arv* arv_cria (int n,Arv* e, Arv* d);

//libera o espaço de memória ocupado pela árvore a
Arv* arv_libera (Arv* a);

//retorna true se a árvore estiver vazia e false
//caso contrário
int arv_vazia (Arv* a);

//indica a ocorrência (1) ou não (0) do int n
int arv_pertence (Arv* a, int n);

//imprime as informações dos nós da árvore
void arv_imprime (Arv* a);

//retorna a mãe de um dado no
Arv* arv_pai (Arv* a, int n);

//retorna a quantidade de folhas de uma arvore binaria
int folhas (Arv* a);

//retorna o numero de ocorrencias de um dado caracter na arvore
int ocorrencias (Arv* a, int n);

//retorna a altura de uma arvore a
int altura(Arv* a);

//retorna o filho esquerdo de uma arvore a
Arv* Arvesq(Arv*a);

//retorna o filho dirieto de uma arvore a
Arv* Arvdir(Arv*a);


//retorna o campo informacao de um dado no
int info (Arv* a);

//retorna se e o caracter final de um arquivo
int retornafim(Arv* a);
//inicia lista encadeada
Lista* inicLista();
//adiciona uma arvore a lista
void addlista(Lista* l, Arv* a);
//retira a arvore da lista
void retiralista(Lista*l,Arv*a);
//imprime a lista
void imprimelista(Lista*l);
//passa os caracteres da tabela t para a lista
void passatablista(Tabela*t,Lista*l);
//faz uma arvore de huffman com base na lista l
Arv* huffman(Lista*l);
// libera a memoria alocada da lista
void destroilista(Lista*l);

#endif
