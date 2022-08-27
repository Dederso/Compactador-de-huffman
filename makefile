
PROJ_NAME=compactadordehuffman

C_SOURCE=$(wildcard *.c)

H_SOURCE=$(wildcard *.h)

OBJ=$(C_SOURCE:.c=.o)

CC=gcc

CC_FLAGS=-c


all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) tabela.c comp.c estruturas.c codigo.c bitmap.c compactador.c -o Compacta
	$(CC) tabela.c desc.c estruturas.c codigo.c bitmap.c descompactador.c -o Descompacta
	rm -rf *.o

clean:
	rm -rf *.o *~ Compacta Descompacta *.comp