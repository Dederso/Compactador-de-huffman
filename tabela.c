//Andre Guimaraes Barros- 2020102600,Klarine Mendonca Silva -2020103337
#include<stdlib.h>
#include<stdio.h>
#include "tabela.h"

#define TAM 257
//tabela com o vetor de ocorrencias e o tamanho de caracteres lidos no arquivo
struct tabela{
  int* dec;
  long tamb;
};

//inicia a tabela
Tabela* iniciatabela(){
  Tabela* tab=malloc(sizeof(Tabela));
  tab->dec=malloc(sizeof(int)*TAM);//aloca 257 posicoes, para cada caracter e para os caracteres extras

  for(int i=0;i<TAM;i++){//inicia o valor de todos os carecteres como 0
    tab->dec[i]=0;
  }
  tab->dec[256]=1;// coloca o valor de fim de arquivo como um
  return tab;
}

//aumenta a decorrencia da tabela de um caracterindice
void acrescenta(Tabela* tab,int indice){
  tab->dec[indice]++;
}

//diminui a decorrencia da tabela de um caracter indice
void decrescenta(Tabela* tab,int indice){
  tab->dec[indice]--;
}

//retorna a ocorrencia do caracter
int retornaOcorrenciaTab(Tabela* tab,int indice){
  int aux;
  aux=tab->dec[indice];
  return aux;
}

//retorna a soma de todas as ocorrencias da tabela
int ocorrenciasgeraisTabela(Tabela* tab){
  int soma=0,i,aux;

  for(i=0;i<TAM;i++){
    aux=tab->dec[i];
    soma+=aux;
  }
  return soma;
}
// retorna a tabela de ocorrencias
int* retornadec(Tabela* tab){
  return  tab->dec;
}
//retorna o char de um indice da tabela
char retornachar(int indice){
  char c=indice;
  return c;
}
// imprime a tabela
void imprimeTabela(Tabela*tab){
  int i;
  for(i=0;i<TAM;i++){
    printf("%d:%d ocorrencias\n",i,tab->dec[i]);
  }
}
//preenche a tabela com o conteudo do arquivo
Tabela* preenchetab(FILE* arq,Tabela*tab){
    char c;

    fseek(arq,0,SEEK_END);//posiciona no final do arquivo

    unsigned long tamanho = ftell(arq);//pega o tamanho do arquivo

    fseek(arq,0,SEEK_SET);//volta para o inicio

    unsigned char*aux=(char*)malloc(tamanho);//aloca um vetor com o tamanho do arquivo
    fread(aux,tamanho,sizeof(unsigned char),arq);//preenche o vetor com o conteudo do arquivo
    tab->tamb=tamanho;//armazena o tamanho do arquivo na tabela
    long i=0;
    while (i<tamanho){
        tab->dec[(unsigned char)aux[i]]++;//preenche a tabela com a ocorrencia do caracter i
        i++;
    }
    tab->dec[256]==1;//define o fim do arquivo como um
    free(aux);//libera o auxiliar
 }
//retorna o tamanho do arquivo
 long retornaTamanhob(Tabela*tab){
  return tab->tamb;
}
//libera a memoria da tabela
void liberaTabela(Tabela*tab){
  free(tab->dec);
  free(tab);
}
