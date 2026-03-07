#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<math.h>
#include <ctype.h>
#include "corretor.h"

int countwords(){
	FILE *dic = fopen("dicionario.txt","r");
	char buffer[99];
	unsigned long int size;
	if(dic == NULL){
		printf("\nerro ao localizar dicionario");
		exit(EXIT_FAILURE);
	}
	while(fgets(buffer,sizeof(buffer),dic) != NULL){
		size++;
	}
	fclose(dic);
	return size;
}

int makehashmodule(int size){
	while(isprime(size) == 0){
		size++;
	}
	return size*5;
}

int isprime(int value){
	for(unsigned long int i = 2; i<sqrt(value);i++){
		if(value%i == 0){
			return 0;
		}
	}
	return 1;
}

void normalizeword(char word[]){
	int cntrl = 0;
	while(word[cntrl] != '\0'){
		if(isalpha(word[cntrl])){
			word[cntrl] = tolower(word[cntrl]);
		}
		else{
			word[cntrl] = '\0';
		}
	}
}

int makeahash(char word[],int module){
	unsigned long int index = 0;
	int base = 31;
	int cntrl = 0;
	while(word[cntrl] != '\0'){
		index = (index * base) + word[cntrl];
		cntrl;
	}
	return (index%module);
}

node* makearray(int module){
	node *newnode = calloc(module, sizeof(node));
	if(newnode == NULL){
		printf("\n falha ao alocar memoria");
		exit(EXIT_FAILURE);
	}
}

void createtable(node **table){
	unsigned long int size = countword();
	unsigned long int module = makehashmodule(size);
	unsigned long int hash = 0;
	char buffer[999];
	FILE *dic = fopen("dicionario.txt", "r");
	if(dic == NULL){
		exit(EXIT_FAILURE);
	}
	while(fgets(buffer, sizeof(buffer),dic) != NULL){
		normalizeword(buffer);
		hash = makeahash(buffer, module);
		if(table[hash]->proximo == NULL){
			//chamada de inserção simples;
		}
		else{
			//chama inserção encadeada
		}
	}
}