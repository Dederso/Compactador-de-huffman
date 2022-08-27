//Andre Guimaraes Barros- 2020102600,Klarine Mendonca Silva -2020103337
#ifndef tabela_h
#define tabela_h

#include<stdlib.h>
#include<stdio.h>


typedef struct tabela Tabela;

//inicia tabela
Tabela* iniciatabela();

//acrescenta um ao caracter
void acrescenta(Tabela* tab,int indice);

//decrescenta um ao caracter
void decrescenta(Tabela* tab,int indice);

//retorna a ocorrência de certo caracter na tabela
int retornaOcorrenciaTab(Tabela* tab,int indice);

//retorna a soma de todas as ocorrencias
int ocorrenciasgeraisTabela(Tabela* tab);
//retorna a tabela
int* retornadec(Tabela*tab);
//retorna o caracter de um indice
char retornachar(int indice);
//imprime a tabela
void imprimeTabela(Tabela*tab);
//preenche a tabela com os caracteres do arquivo
Tabela* preenchetab(FILE* arq,Tabela*tab);
//retorna o tamanho do arquivo
long retornaTamanhob(Tabela*tab);
//libera a memoria da tabela
void liberaTabela(Tabela*tab);







#endif
