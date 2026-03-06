#ifndef CORRETOR_H
#define CORRETOR_H

typedef struct no{
	char key[46];
	struct no *proximo;
} node;

int countword();//abre o dicionario e conta as palavras
void createhashtable(node **table,int size);
void hashatable(node table[], int size);
int isprime(int valor);
#endif
