#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "partie2.h"
#include "partie3.h"

int main(){
	srand(time(NULL));
	
	//Generer des cles, des candidats et des declaratiosn aleatoirement
	generate_random_data(1000,5);
	
	//Lecture des candidats + Affichage
	CellKey* candidat = read_public_keys("candidates.txt");
	printf("\nListe des Candidats :\n");
	print_list_keys(candidat);
	
	//Lecture des votants + Affichage
	CellKey* votant = read_public_keys("keys.txt");
	printf("\nListe des Votants :\n");
	print_list_keys(votant);
	
	//Lecture des declarations + Affichage
	CellProtected* decla = read_protected("declarations.txt");
	printf("\nListe des declarations :\n");
	print_list_prots(decla);
	
	//Calcule du Gagnant + Affichage
	Key* gagnant = compute_winner(decla,candidat,votant, 5, 1000);
	char* winner = key_to_str(gagnant);

	printf("\n\nGagnant :%s\n                 FELICITATION !\n\n", winner);
	free(winner);
	

	//LIberation de la memoire
	delete_list_key(candidat);
	delete_list_key(votant);
	delete_list_prot(decla);
		
	return 0;
}
