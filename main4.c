#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "partie2.h"
#include "partie3.h"
#include "partie4.h"

int main(){
	
	srand(time(NULL));
	
	/*  TEST Hashing 
	char* str=hashing("Rosetta code");
	printf("%s\n",str);
	*/
	
	generate_random_data(100, 5);
	
	//Creation Block + Initialisation des attributs
	Block* b=new_block();

	b->votes=read_protected("declarations.txt");
	
	CellKey* LCK=read_public_keys("keys.txt");

	b->author=LCK->data;
	
	//Calcule du temps d'execution de compute_proof_of_work selon le nombre de zero
	
	//Ouverture du fichier
	FILE* f=fopen("temps_compute.txt","w");
	clock_t ti,tf;
	double tcpu;
	for(int i=1;i<=5;i++){
		printf("%d zeros: \n",i);
		ti=clock();
		compute_proof_of_work(b,i);
		tf=clock();
		tcpu=((double)(tf-ti))/CLOCKS_PER_SEC;
		char* str=block_to_str(b),*str2=hashing(str);
		fprintf(f, "%.2f %s\n", tcpu,str2);
		fprintf(stdout, "%.2f %s\n", tcpu,str2);
		free(str);
		free(str2);
	}
	
	/*  TEST Verify_block
	
	verify_block(b,1);
	*/
	
	//Fermeture fichier
	fclose(f);
	
	//Liberation de la memoire
	delete_list_key(LCK->next);
	free(LCK);
	delete_block(b);

	return 0;
}
