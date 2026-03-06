#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"corretor.h"

int main(void){
	node *table = NULL;
	int size = countword();
	createhashtable(&table, size);
	hashatable(table ,size);

	int cntrl = 1;
	FILE *exit = fopen("saida.txt", "w");
	while(cntrl <= size){
		if(table[cntrl].key[0]!= '\0'){
			fprintf(exit,"chave: %s hash: %d\n",table[cntrl].key, cntrl);
			cntrl++;
		}
		else{
			cntrl++;
		}
	}
	fclose(exit);
	printf("\nfim da execucao");

}

