//Andre Guimaraes Barros- 2020102600,Klarine Mendonca Silva -2020103337
#ifndef CODIGO_H
#define CODIGO_H

#include "estruturas.h"

//cria uma matriz para o codigo da arvore de huffman
char** criacodigo(Arv*a);
//preenche a matriz com o codigo de huffman,usa uma string vazia para que haja recursao
void preenchecodigo(Arv* a,char**cod,char*codigo);
//libera a matriz
void liberacodigo(char** dic);

#endif
