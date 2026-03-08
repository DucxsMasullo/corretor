#ifndef CORRETOR_H
#define CORRETOR_H

typedef struct no{
	char key[46];
	struct no *proximo;
} node;

void createtable(node **table);//cria a hashtable
unsigned long int countwords();//abre o dicionario e conta as palavras
int isprime(int value);//verifica se é primo
int makehashmodule(int size);//cria um modulo dado tamanho do vetor
node* makearray(int module);//cria o vetor dado tamanho do modulo
void normalizeword(char word[]);//torna palavra minuscula terminando '\0'
int makeahash(char word[],int module);//cria um hash dada string
void insertsimple(node **table, int hash, char word[]);//insere ao vetor
void insertchained(node *table, char word[]);//insere como proximo a um item
void lookforerros(int module, node table[]);
int verifyson(char buffer[],node *actual);

#endif
