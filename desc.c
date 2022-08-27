//Andre Guimaraes Barros- 2020102600,Klarine Mendonca Silva -2020103337

//funcao principal do descompactador (main)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tabela.h"
#include "estruturas.h"
#include "codigo.h"
#include "bitmap.h"
#include "descompactador.h"


#define TAM 257

int main(int argc, char* argv[]){
int i,j;
//inicia a tabela de caracteres
Tabela*tab=iniciatabela();
//abre o arquivo .comp com a entrada no terminal
FILE* arq=fopen(argv[1],"rb");
//verifica erro
if(arq==NULL){
  printf("erro na leitura do arquivo\n");
  return 1;
}
//le os primeiros 257 caracteres correspondentes a tabela, que foi armazenada no inicio do arquivo
fread(retornadec(tab),sizeof(int),257,arq);
//inicia uma lista
Lista*l=inicLista();
//passa a tabela para a lista, iniciando os valores da arvore
passatablista(tab,l);
//forma a arvore de huffman com a lista
Arv*h=huffman(l);
//chama a funcao de descompactacao
descompacta(arq,tab,h,argv[1]);
//libera a arvore de huffman
arv_libera(h);
//fecha o arquivo
fclose(arq);
//libera a memoria da lista
destroilista(l);
//libera a memoria da tabela
liberaTabela(tab);
  return 0;
}
