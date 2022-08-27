//Andre Guimaraes Barros- 2020102600,Klarine Mendonca Silva -2020103337

//funcao principal do compactador (main)
#include <stdlib.h>
#include <stdio.h>
#include "tabela.h"
#include "estruturas.h"
#include "codigo.h"
#include "bitmap.h"
#include "compactador.h"

#define TAM 257

int main(int argc, char* argv[]){
int i,j;
//inicia uma tabela para preencher com os caracteres do arquivo
Tabela*tab=iniciatabela();
//abre o arquivo com a entrada no terminal
FILE* arq=fopen(argv[1],"rb");// "rb"=read binary
//verifica erro
if(arq==NULL){
  printf("erro na leitura do arquivo\n");
  return 1;
}

//preenche a tabela de frequencia com os dados do arquivo aberto
preenchetab(arq,tab);

//inicia a lista
Lista*l=inicLista();
//passa os caracteres para a lista e inicializa seus valores na estrutura
passatablista(tab,l);

//faz a arvore de huffman com a lista inicializada e seus valores
Arv*h=huffman(l);
//cria uma matriz para o codigo de huffman
char**cod=criacodigo(h);
//preenche a matriz com codigo de huffman atraves da arvore
preenchecodigo(h,cod,"");
//chama a funcao de compactacao usando todas as estruturas
compacta(arq,cod,tab,h,argv[1]);
//libera a arvore
arv_libera(h);
//fecha o arquivo
fclose(arq);
//libera a lista
destroilista(l);
//libera a matriz do codigo
liberacodigo(cod);
//libera a tabela de caracter
liberaTabela(tab);
  return 0;
}
