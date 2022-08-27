//Andre Guimaraes Barros- 2020102600,Klarine Mendonca Silva -2020103337
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estruturas.h"
#include "codigo.h"
#include "tabela.h"
#include "bitmap.h"
#include "descompactador.h"

#define TAM 257


//funcao de descompactacao de arquivos, abre o arquivo .comp, usa a tabela de caracteres escrito nele, junto com a arvore de huffman, e gera o arquivo original
void descompacta(FILE*arq,Tabela*tab,Arv*a,char*nome){
  int i=0,j=0,k=0,t=0;
  //chama dois ponteiros auxiliares para a arvore de huffman
  Arv*h=a;
  Arv*aux=a;
  char arqn[50]="\0";
  char novo[50]="\0";
  char arqex[50]="\0";
  unsigned char c;
  unsigned char e;
  //pega o nome do arquivo pela entrada do terminal
  strcpy(arqn,nome);//atribui o nome do arquivo a string arqn
  strcpy(arqex,"");//evita lixo
  char*pt=strtok(arqn,".");//separa o nome da extensao .comp

  strcpy(novo,pt);//passa o nome para a string novo



  fread(&t,sizeof(int),1,arq); //recupera quantidade t de caracteres da extensao
  fread(&arqex,sizeof(unsigned char),t,arq); //recupera extensao de quantidade t

  strcat(novo,".");//concatena o ponto da extensao com o nome
  strcat(novo,arqex);//contatena a extensao com o nome com .

  FILE*fim=fopen(novo,"wb");//cria o arquivo original


  //le o arquivo ate o final
  while(fread(&c,sizeof(unsigned char),1,arq)){
    for(i=7;i>=0;i--){//le o byte do bit menos significativo para o mais significativo
      j=c&(1<<i);//anda i posicoes para esquerda dentro do byte c e atribui o valor a j
        if(j>0){//se for maior que 0, entao ele e 1, e vai para direita da arvore
          h=Arvdir(h);
        }
        else// caso nao seja menor que 0, e 0 e vai para a esquerda da arvore
          h=Arvesq(h);

      if(arv_vazia(Arvdir(h))&&arv_vazia(Arvesq(h))){// caso atinja uma folha
        if(retornafim(h)==1){// finaliza o processo e fecha o arquivo se encontrar o caracter de fim de arquivo
          fclose(fim);
          return;
        }
        else// caso nao seja o fim do arquivo, escreve o caracter do no folha no arquivo
          e=info(h);
          fwrite(&e,sizeof(unsigned char),1,fim);
          h=aux;// retorna o ponteiro da arvore para o topo
      }
    }
  }
  // fecha o arquivo
  fclose(fim);
}
