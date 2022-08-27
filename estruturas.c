//Andre Guimaraes Barros- 2020102600,Klarine Mendonca Silva -2020103337
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estruturas.h"

#define TAM 257

struct arv{
    int car;//caracter
    int fim;//fim do arquivo
    Arv* esq;// filho esquerdo
    Arv* dir;// filho direito
    Arv* prox;// proximo da lista
    int rec;// quantidade de vezes que ele apareceu
};

struct lista{// lista
  Arv* prim;
  Arv* ult;
};
//Cria uma árvore vazia
Arv* arv_criavazia (void){
  return NULL;
}

//cria uma árvore com a informação do nó raiz c, e
//com subárvore esquerda e e subárvore direita d
Arv* arv_cria (int n,Arv* e, Arv* d){
  Arv* p=malloc(sizeof(Arv));
  p->car=n;
  p->esq=e;
  p->dir=d;
  p->prox=NULL;
  if(n==256){
    p->fim=1;
  }
  else{
    p->fim=0;
  }
  p->rec=0;
  return p;
}

//libera o espaço de memória ocupado pela árvore a
Arv* arv_libera (Arv* a){
  if (!arv_vazia(a)){
    arv_libera(a->esq);
    arv_libera(a->dir);
    free(a);
  }
  return NULL;
}

//retorna true se a árvore estiver vazia e false
//caso contrário
int arv_vazia (Arv* a){
  return a==NULL;
}

//indica a ocorrência (1) ou não (0) do caracter c
int arv_pertence (Arv* a, int n){
  if (arv_vazia(a)){
    return 0;
  }
  else
    if(a->car==n){
      return 1;
    }
    return arv_pertence(a->esq,n)||arv_pertence(a->dir,n);
}

//imprime as informações dos nós da árvore
void arv_imprime (Arv* a){
  printf("<");
  if(!arv_vazia(a)){
    printf("caracter %d ; recorrencia %d   ",a->car,a->rec);
    arv_imprime(a->esq);
    arv_imprime(a->dir);
  }
  printf(">");
}

//retorna a mãe de um dado no
Arv* arv_pai (Arv* a, int n){
  Arv*p=a;
  if(!arv_vazia(a)){
    if(!arv_vazia(a->esq)){
      if(a->esq->car==n){
        return a;
      }
    }
    if(!arv_vazia(a->dir)){
      if(a->dir->car==n){
        return a;
      }
    }

    p=arv_pai(a->esq,n);

    if(p!=NULL){
      return p;
    }
    p=arv_pai(a->dir,n);

    return p;
  }
  return NULL;
}

//retorna a quantidade de folhas de uma arvore binaria
int folhas (Arv* a){
  int folha=0;
  if(arv_vazia(a)){
    return 0;
  }
  if(arv_vazia(a->esq)&&arv_vazia(a->dir)){
    return 1;
  }
  folha=folhas(a->esq)+folhas(a->dir);
  return folha;
}

//retorna o numero de ocorrencias de um dado caracter na arvore
int ocorrencias (Arv* a,int n){
  int o=0;
  if(arv_vazia(a)){
    return 0;
  }
  if(a->car==n){
    o++;
  }
  o=ocorrencias(a->esq,n)+ocorrencias(a->dir,n)+o;
  return o;
}
//retorna altura da arvore
int altura(Arv* a){
  int e=0,d=0;
  if(arv_vazia(a)){
      return 0;
  }
//acha a altura dos dois lados
  e=altura(a->esq);
  d=altura(a->dir);
//escolhe o maior
  if (e > d) {
    return e+1;
  }
  return d+1;
}
//filho esquerdo
Arv* Arvesq(Arv*a){
  return a->esq;
}
// filho direito
Arv* Arvdir(Arv*a){
  return a->dir;
}

//retorna o campo informacao de um dado no
int info (Arv* a){
  return a->car;
}
//determina o fim do arquivo
int retornafim (Arv* a){
  return a->fim;
}
//--------------------------------------------------//
// inicia a lista
Lista* inicLista(){
  Lista*nova =malloc(sizeof(Lista));
  nova->prim=NULL;
  nova->ult=NULL;

  return nova;
}



//poe em ordem de recorrencia
void addlista(Lista* l, Arv* a){
  Arv* p;
  Arv* t;
  int freq=a->rec;

  //se a lista esta vazia a arvore e a primeira, entra em primeiro e em ultimo
  if(l->prim==NULL){
     l->prim=a;
     l->ult=a;
     a->prox=NULL;
  }
//organiza com base na frequencia do no
  if(freq<l->prim->rec){
     a->prox=l->prim;
     l->prim=a;
  }
  else{
     p=l->prim;
     t=p->prox;

     while(t!=NULL&&freq>t->rec){
         p=t;
         t=t->prox;
     }

     if(t==NULL){
         p->prox=a;
         l->ult=a;
         a->prox=NULL;
     }
     else{
        a->prox=t;
        p->prox=a;
     }
  }
}
//retira um no da lista
void retiralista(Lista*l,Arv*a){
  Arv*p;
  Arv*t;
  p=l->prim;
  t=p;
  if(p==a){
    l->prim=p->prox;
    p->prox=NULL;
    return;
  }
  //acha o no
  while(p->prox!=NULL||p->prox!=a){
    t=p;
    p=p->prox;
  }
  //ve se há erro
  if(l->ult==p&&p->prox->car!=a->car){
    printf("erro, no nao encontrado");
    return;
  }
  //tira os ponteiros da listta
  if(l->prim==p){
    l->prim=p->prox;
    p->prox=NULL;
  }
  if(l->ult==p){
    t->prox=NULL;
  }
  else{
    t->prox=p->prox;
    p->prox=NULL;
  }
};
//passa a tabela frequencia para a lista
void passatablista(Tabela*t,Lista*l){
  int i;
  for(i=0;i<TAM;i++){
    if(retornadec(t)[i]>0){
      Arv*a=arv_cria(i,arv_criavazia(),arv_criavazia());//cria os nos da lista
      a->rec=retornadec(t)[i];
      addlista(l,a);//adiciona no na lista
    }
  }
}
//imprime a lista
void imprimelista(Lista*l){
  Arv*a;
  a=l->prim;
  while(a!=NULL){
    printf("caracter %d ; recorrencia %d\n",a->car,a->rec);
    a=a->prox;
  }
}
//cria a arvore de huffman
Arv* huffman(Lista*l){
  Arv*p;
  Arv*t;
  Arv*r;
  //verifica se a lista esta vazia
  if(l->prim==NULL){
    return NULL;
  }

  while(l->prim!=l->ult){
    //pega os dois primeiros nos
    t=l->prim;
    r=t->prox;
    //cria um no com a soma das frequencias
    p=arv_cria(257,t,r);//caracter 257 de identificacao de um no nao folha
    p->rec=t->rec+r->rec;
    addlista(l,p);//aidiciona na lista o novo no
    //retira os antigos nos da lista, ate que so sobre um unico no pai
    retiralista(l,t);
    retiralista(l,r);
  }
  return l->prim;
}
//libera a memoria da lista
void destroilista(Lista*l){
  free(l);
}
