#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"corretor.h"

int main(void){
	node *table = NULL;
	createtable(&table);

	int module = makehashmodule(countwords());
	lookforerros(module, table);
	
}
//erro ao ler strings da biblia