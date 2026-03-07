#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<math.h>
#include <ctype.h>
#include "corretor.h"

unsigned long int countwords(){
	FILE *dic = fopen("dicionario.txt","r");
	char buffer[99];
	unsigned long int size = 0;
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
	for(unsigned long int i = 2; i*i<value; i++){
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
			cntrl ++;
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
		cntrl++;
	}
	return (index%module);
}

node* makearray(int module){
	node *newnode = calloc(module, sizeof(node));
	if(newnode == NULL){
		printf("\n falha ao alocar memoria");
		exit(EXIT_FAILURE);
	}
	return newnode;
}

void insertsimple(node **table, int hash, char word[]){
	strncpy((*table)[hash].key, word, sizeof((*table)[hash].key));
}

void insertchained(node *table, char word[]){
	node *current = table;
	while(current->proximo != NULL){
		current = current->proximo;
	}
	current->proximo = calloc(1,sizeof(node));
	current = current->proximo;
	if(current == NULL){
		printf("\n erro ao alocar no encadeado");
		exit(EXIT_FAILURE);
	}
	strncpy(current->key,word,sizeof(current->key));
}

void createtable(node **table){
	unsigned long int size = countwords();
	unsigned long int module = makehashmodule(size);
	unsigned long int hash = 0;
	char buffer[999];
	FILE *dic = fopen("dicionario.txt", "r");

	
	if(dic == NULL){
		exit(EXIT_FAILURE);
	}

	*table = makearray(module);

	while(fgets(buffer, sizeof(buffer),dic) != NULL){
		normalizeword(buffer);
		hash = makeahash(buffer, module);
		if((*table)[hash].key[0] == '\0'){
			insertsimple(table, hash, buffer);
		}
		else{
			insertchained(&(*table)[hash], buffer);
		}
	}
}

void placeholder(){
	return ;
}