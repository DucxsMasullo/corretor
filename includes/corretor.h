#ifndef CORRETOR_H
#define CORRETOR_H

typedef struct no{
	char key[46];
	struct no *proximo;
} node;

int countword();//abre o dicionario e conta as palavras
int isprime(int value);
int makehashmodule(int size);
#endif
