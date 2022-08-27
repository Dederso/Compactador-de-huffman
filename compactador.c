//Andre Guimaraes Barros- 2020102600,Klarine Mendonca Silva -2020103337
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estruturas.h"
#include "codigo.h"
#include "tabela.h"
#include "bitmap.h"
#include "compactador.h"

#define TAM 257

//funcao primcipal de compactacao, abre o arquivo, faz um bitmap do seus bits, armazena esse bitmap em um arquivo de saida .comp
void compacta(FILE*arq,char**cod,Tabela*tab,Arv*a,char*nome){
  int j=0,k,l=0,t;
  char arqn[50];
  char novo[50];
  char arqex[50];
  unsigned long i=0;

  //pega o nome do arquivo de entrada para gerar o arquivo de saida
  strcpy(arqn,nome);
  //separa o nome da extensao
  char*pt=strtok(arqn,".");
  //pega o nome do arquivo sem extensao
  strcpy(novo,pt);

  pt=strtok(NULL,".");
  //pega a extensao do arquivo
  strcpy(arqex,pt);
  //concatena o nome do arquivo com a nova extensao .comp
  strcat(novo,".comp");
  // pega a quantidade de caracteres na extensao
  t=(int)strlen(arqex);


  //cria o arquivo de compactacao
  FILE*fim=fopen(novo,"wb");
  char*bit=malloc(altura(a));//aloca uma string com o tamanho da arvore de huffman, para escrever o codigo no arquivo

  fseek(arq,0,SEEK_SET);//posiciona no inicio do arquivo

  unsigned char*aux=(char*)malloc(retornaTamanhob(tab));//aloca uma string com o tamanho de caracteres do arquivo armazenado na tabela

  strcpy(aux,"");//evita lixo

  fread(aux,retornaTamanhob(tab),sizeof(unsigned char),arq);//passa o conteudo do arquivo para  a string

  bitmap* bm=bitmapInit(80000000);//inicializa o mapa de bits com o tamanho inicial de 1mb

  for(int i=0;i<TAM;i++) {
        fwrite(&retornadec(tab)[i],sizeof(int),1,fim);//armazena a tabela dentro do arquivo para que haja uma descompactacao
    }

  fwrite(&t,sizeof(int),1,fim); //armazena quantidade t de caracteres da extensao
  fwrite(&arqex,sizeof(char),t,fim); //armazena extensao de quantidade t

  //le arquivo aberto ate o fim
  while (i<retornaTamanhob(tab)) {
        j=0;

        strcpy(bit,cod[(unsigned char)aux[i]]);//passa o codigo do caracter lido pelo arquivo para uma variavel bit
        //enquanto o codigo nao chegar ao fim
        while (bit[j]!='\0') {
          //verifica se o valor da posicao j é 0 ou 1
            if (bit[j]=='1') {
                bitmapAppendLeastSignificantBit(bm,1);//concatena o bit 1 no bitmap
                if(bitmapGetLength(bm)==bitmapGetMaxSize(bm)){//caso o bitmap esteja cheio
                  for (int k=0;k<bitmapGetLength(bm)/8;k++) {
                   fwrite(&bitmapGetContents(bm)[k],sizeof(unsigned char),1,fim);//escreve no arquivo o valor ja armazenado
                  }
                  // zera o bitmap escrito e inicia novamente
                  bitmapLibera(bm);
                  bm = bitmapInit(80000000);
                }
            }
            //verifica se o valor da posicao j é 0 ou 1
            else if(bit[j]=='0'){
               bitmapAppendLeastSignificantBit(bm,0);//concatena o bit 0 no bitmap
               if(bitmapGetLength(bm)==bitmapGetMaxSize(bm)){//caso o bitmap esteja cheio
                 for(int k=0;k<bitmapGetLength(bm)/8;k++){
                  fwrite(&bitmapGetContents(bm)[k],sizeof(unsigned char),1,fim);//escreve no arquivo o valor ja armazenado
                 }
                 // zera o bitmap escrito e inicia novamente
                 bitmapLibera(bm);
                 bm = bitmapInit(80000000);
               }
            }
            j++;
        }
        i++;
    }


    //escreve o caracter de fim de arquivo
    while(cod[256][l]!='\0'){
      if (cod[256][l] == '1'){
        bitmapAppendLeastSignificantBit(bm,1);
        if(bitmapGetLength(bm)==bitmapGetMaxSize(bm)){
          for (int k=0;k<bitmapGetLength(bm)/8;k++) {
           fwrite(&bitmapGetContents(bm)[k],sizeof(unsigned char),1,fim);
          }
          bitmapLibera(bm);
          bm = bitmapInit(80000000);
        }
      }
      if (cod[256][l] == '0'){
        bitmapAppendLeastSignificantBit(bm,0);
        if(bitmapGetLength(bm)==bitmapGetMaxSize(bm)){

          for(int k=0;k<bitmapGetLength(bm)/8;k++){
           fwrite(&bitmapGetContents(bm)[k],sizeof(unsigned char),1,fim);
          }
          bitmapLibera(bm);
          bm = bitmapInit(80000000);
        }
      }
      l++;
    }


    //preenche o ultimo byte com 0
    if(bitmapGetLength(bm)%8!=0){
       l=8-(bitmapGetLength(bm)%8);
       for (k=0;k<l;k++){
          bitmapAppendLeastSignificantBit(bm,0);
       }
    }
    //escreve o bitmap no arquivo
    for(int k=0;k<bitmapGetLength(bm)/8;k++){
     fwrite(&bitmapGetContents(bm)[k],sizeof(unsigned char),1,fim);
    }



  fclose(fim);//fecha arquivo de saida
  free(bit);//libera a string de bits
  free(aux);//libera a string auxiliar
  bitmapLibera(bm);//libera o bitmap
}
