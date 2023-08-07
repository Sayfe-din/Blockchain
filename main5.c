#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <openssl/sha.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "partie2.h"
#include "partie3.h"
#include "partie4.h"
#include "partie5.h"

int main(){
	srand(time(NULL));
	
	//Generation de 1000 citoyen et 4 candidats
	generate_random_data(1000, 5);
	
	//si l'on veut creer le fichier directement dans le main : mkdir("./Blockchain/",700);, il faudra donc le supprimer grâce au makefile (make clean)
	
	
	//Lecture des declarations de vote, des cles de citoyens et de candidats
	CellProtected *decla = read_protected("declarations.txt");
	CellKey *votants = read_public_keys("keys.txt");
	CellKey *candidats = read_public_keys("candidates.txt");
	
	
	CellProtected *tmp = decla;
	int i = 0, j = 0,find=0;
	Block* b=new_block();
	free(b->previous_hash);
	b->previous_hash=NULL;
	
	CellTree* tree=create_node(b);
	
	while(tmp != NULL){
		Protected *tmp2 = tmp->data;
		
		//Soumission de tous les votes
		submit_vote(tmp2);
		i++;
		
		//Tous les 10 votes, creation de bloc + ajout au blockchain
		if(i == 10){
			if(!find){
				//Block Genesis
				create_block(NULL,tmp2->pkey,1);
				find++;
			}
			else{
				create_block(tree,tmp2->pkey,1);
			}
			char nom[256];
			sprintf(nom, "%s%d%s","./Blockchain/block", j,".txt");
			
			add_block(1, nom);
			
			b=read_block(nom);
			CellTree* t=create_node(b);
			add_child(tree,t);
			j++;
			i=0;
		}
		
		tmp = tmp->next;
		
	}
	
	//Lecture et Affichage du Blockchain
	CellTree* tree2 = read_tree();
	printf("\nBLOCKCHAIN\n");
	print_tree(tree2,0);
	
	//Calcule du Gagnant
	Key * gagnant = compute_winner_BT(tree2,candidats,votants,5,1000);
	char* str= key_to_str(gagnant);
	printf("Gagnant : %s\n",str);
	free(str);
	
	//Liberation de la memoire
	delete_tree(tree2);
	delete_list_key(votants);
	delete_list_key(candidats);
	delete_list_prot(decla);
		
	return 0;
}
