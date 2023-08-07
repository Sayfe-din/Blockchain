#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "exo1.h"
#include "exo2.h"

//GENERATION D’UNE PAIRE (CLE PUBLIQUE, CLE SECRETE)

//Algorithme d'Euclide
long extended_gcd(long s, long t, long *u, long *v){

	if(s==0){
		*u = 0;
		*v = 1;
		return t;
	}	
	
	long uPrim, vPrim;
	long gcd = extended_gcd(t%s, s, &uPrim, &vPrim);
	*u = vPrim - (t/s) * uPrim;
	*v = uPrim;
	return gcd;
	
}

//Generer les valeurs de pKey et sKey
void generate_key_values(long p, long q, long *n, long *s, long *u){
	
	//calcule de n
	*n = p * q;
	
	//calcule de t
	long t = (p-1)*(q-1);
	
	//recherche de s tel que pgcd(s,t)=1
	long s2;
	long v, pgcd = 0;
	
	while(pgcd != 1){
		s2 = rand()%t;	
		pgcd = extended_gcd(s2, t, u, &v);
	}
	
	*s = s2;
}

//Chiffre la chaine de caractere chaine avec la cle publique (s,n)
long* encrypt(char* chaine,long s,long n){
	//Allocation Dynamique + Verification du Malloc
	long* tab=(long*)malloc(sizeof(long)*strlen(chaine));
	assert(tab);
	
	//Parcours de la chaine de chaine de caractère
	for(int i = 0; chaine[i]!='\0'; i++){
		tab[i]=(long)modpow((long)(int)chaine[i],s,n);
	}
	
	return tab;
}

//Dechiffre le tableau de long crypted avce la cle privee (u,n)
char* decrypt(long* crypted,int size, long u,long n){
	//Allocation Dynamique + Verification du Malloc
	char* chaine=(char*)malloc(sizeof(char)*(size+1));
	assert(chaine);
	
	//Parcours du tableau de long
	for(int i=0; i<size; i++){
		chaine[i]= (char)modpow(crypted[i],u,n);
	}
	
	chaine[size]='\0';
	return chaine;
}






























