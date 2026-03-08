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

int verifyhash(char buffer[], int hash, node table){
	node *current = &table;
	if(buffer[0] == '\0'){
		return -1;
	}

	if(strcmp(buffer,table.key)==0){
		return 0;
	}
	else if(table.proximo != NULL){
		return verifyson(buffer, table.proximo);
	}
	return 1;
}

int verifyson(char buffer[],node *actual){
	if(strcmp(buffer, actual->key)==0){
		return 0;
	}
	else if(actual->proximo != NULL){
		return verifyson(buffer, actual->proximo);
	}
	else{
		return 1;
	}
}

void clearbuffer(char buffer[], int size){
	for(int i=0;i<=size;i++){
		buffer[i]='\0';
	}
}
	

void lookforerros(int module, node table[]){
	FILE *arq = fopen("arquivo.txt", "r");
	FILE *erros = fopen("erros.txt","w");
	char line[1000];
	char buffer[1000];
	int cntrl = 0;
	if(arq == NULL){
		printf("\n erro ao ler arquivo");
		exit(EXIT_FAILURE);
	}
	while(fgets(line, sizeof(line),arq) != NULL){
		for(int i=0; line[i]!= '\n';i++){
			if(isalpha(line[i])){
				buffer[cntrl]=line[i];
				cntrl++;
			}
			else{
				normalizeword(buffer);
				int hash = makeahash(buffer, module);
				switch(verifyhash(buffer,hash,table[hash])){
					case -1:
					break;
					case 0:
					break;
					case 1:
					fprintf(erros, "erro em : %s\n", buffer);
					break;
				}
				clearbuffer(buffer, sizeof(buffer));
				cntrl = 0;
			}
		}
	}
	fclose(erros);
}	