//Andre Guimaraes Barros- 2020102600,Klarine Mendonca Silva -2020103337
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estruturas.h"
#include "codigo.h"
#include "tabela.h"
#include "bitmap.h"

#define TAM 257


//funcao principal de compactacao
void compacta(FILE*arq,char**cod,Tabela*tab,Arv*a,char*nome);
