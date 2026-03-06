#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "corretor.h"

int countword(){
	int valor = 0;
	char temp[46];
	FILE *dic = fopen("dicionario.txt", "r");
	if(dic == NULL){
		exit(EXIT_FAILURE);
	}
	while(fgets(temp,sizeof(temp),dic) != NULL){
		valor++;
	}
	while(isprime(valor) == 0){
		valor++;
	}
	return valor;
}

int isprime(int valor){
	unsigned long int test = 0;
	test = valor;

	for(unsigned long int i=2;i<test;i++){
		if(test%i == 0){
			return 0;
		}
	}
	return 1;
}

void createhashtable(node **table, int size){
	*table = calloc(size*2, sizeof(node));
	if(*table == NULL){
		exit(EXIT_FAILURE);
	}
}

void hashatable(node table[], int size){
	FILE *dic = fopen("dicionario.txt", "r");
	char currentword[46];
	int base = 31;
	int modulo = size;
	if(dic == NULL){
		exit(EXIT_FAILURE);
	}

	while(fgets(currentword, sizeof(currentword),dic)!= NULL){
		unsigned long int index = 0;
		int cntrl = 0;
		while(currentword[cntrl] != '\0'){
			index = (index * base) + currentword[cntrl];
			cntrl++;
		}
		index = index % modulo;
		if(table[index].key[0] == '\0'){
			strncpy(table[index].key, currentword, sizeof(table[index].key));
			printf("\npalavra: %s    ---- hash: %ld", currentword, index);
		}
		else{
			node *current = &table[index];
			node *newnode = NULL;
			while(current->proximo != NULL){
				current = current->proximo;
			}
			newnode = malloc(sizeof(node));
			if(newnode == NULL){
				exit(EXIT_FAILURE);
			}
			current->proximo = newnode;
			current = current->proximo;
			current->proximo = NULL;
			strncpy(current->key,currentword, sizeof(current->key));
			printf("\npalavra: %s    ---- hash: %ld", currentword, index);
		}
	}
	printf("\n\n\n\n\nsaiu do hash");
}

