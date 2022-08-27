//Andre Guimaraes Barros- 2020102600,Klarine Mendonca Silva -2020103337
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "codigo.h"

#define TAM 257


//cria uma matriz para o codigo de huffman
char** criacodigo(Arv*a){
  char**cod=malloc(TAM*sizeof(char*));//aloca 257 vetores, um para cada caracter
  for(int i=0;i<TAM;i++){
    cod[i]=calloc(altura(a),sizeof(char));//aloca os vetores com o tamanho maximo da altura da arvore de huffman
  }
  return cod;
}

//preenche a matriz com o codigo de huffman, entra com um codigo vazio para haver uma recursao
void preenchecodigo(Arv*a,char**cod,char*codigo) {
  //string com posicao maxima da altura da arvore de huffman
  char e[altura(a)];  //traca o caminho pela esquerda
  char d[altura(a)];  //traca o caminho pela direita

  if (arv_vazia(Arvesq(a))&&arv_vazia(Arvdir(a))){//caso chegue em uma folha, passa o codigo para a matriz
    strcpy(cod[info(a)],codigo);//copia o codigo para a matriz e armazena na posicao do caracter da folha
  }
  //preenche o codigo com 0 caso va para esquerda, e com 1 caso va para direita
  else {
    strcpy(e,codigo);
    strcpy(d,codigo);
    strcat(e,"0");
    strcat(d,"1");

    preenchecodigo(Arvesq(a),cod,e);//faz a recursao para esquerda
    preenchecodigo(Arvdir(a),cod,d);//faz a recursao para direita
  }
}
//libera a matriz com o codigo
void liberacodigo(char**cod){
  for(int i=0;i<TAM;i++){
    free(cod[i]);
  }
  free(cod);
}
