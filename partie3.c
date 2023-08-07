#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "partie2.h"
#include "partie3.h"
#include "partie4.h"

//Creation HashCell
HashCell* create_hashcell(Key* key){

	//Allocation Dynamique + Verification
	HashCell* h = (HashCell*)malloc(sizeof(HashCell));
	assert(h);
	
	h->key=key;
	h->val=0;
	
	return h;

}

//Fonction de hachage
int hash_function(Key* key, int size){
	
	//Verufification des arguments
	if(key == NULL){
		printf("Error hash_function argument Key");
		return -1;
	}
	
	int m = (key->a + key->n)%size;
	
	return m;
}

//Trouver la position de key dans t
int find_position(HashTable* t, Key* key){
	
	//Verification des parametres
	if(!t||!key){ 
		printf("Error find_position argument");
		return -1; 
	}
	//Calcule de la position grace a la fonction de hachage
	int m = hash_function(key, t->size);
	
	
	//probing lineaire, il faut verifier tout le tableau à partir de m	
	while((t->tab[m]->val != -1)){
		
		
		//CAS 1 : key presente
		if((t->tab[m]->key->a == key->a) && (key->n == 	t->tab[m]->key->n)){
			
			return m;
		}
		m++;
		m=m%t->size;		
	}
	
	//CAS 2 : key non presente et emplacment libre
	return m; 
}

//Creation d'une table de hachage à partir d'une liste de cle
HashTable* create_hashtable(CellKey* keys, int size){
	
	//Allocation Dynamique + Verification
	HashTable* ht=(HashTable*)malloc(sizeof(HashTable));
	assert(ht);
	ht->tab=(HashCell **)malloc(sizeof(HashCell*)*size);
	if(!ht->tab){
		free(ht);
		assert(NULL);
	}
	
	int i=0;
	while(i<size){
		ht->tab[i]=(HashCell*)malloc(sizeof(HashCell));
		assert(ht->tab[i]);
		ht->tab[i]->key=NULL;
		ht->tab[i]->val=-1;	  //Token representant un emplacement libre
		i++;
	}
	
	ht->size=size;

	//Parcours de la liste	
	while(keys){
		if(keys->data){
			int m = find_position(ht,keys->data);
		
			if(ht->tab[m]->val==-1){
				free(ht->tab[m]);
				HashCell* hc=create_hashcell(keys->data);
				ht->tab[m]=hc;
			}
		}	
		keys = keys->next;
		
	}
	
	return ht;
	
}

//Desalloue une table de hachage
void delete_hashtable(HashTable* t){
	assert(t);
	int size = 0;
	
	while(size < t->size){
		free(t->tab[size]);
		size++;
	}
	
	free(t->tab);
	free(t);
}

//Recherche du gagnant
Key* compute_winner(CellProtected* decl, CellKey* candidates,CellKey* voters, int sizeC, int sizeV){
	HashTable *hc=create_hashtable(candidates,2*sizeC),*hv=create_hashtable(voters,2*sizeV);
	
	while(decl){
		int m=find_position(hv,decl->data->pkey);
		
		if(hv->tab[m]){
			if(hv->tab[m]->val==0){
				Key* k = str_to_key(decl->data->mess);
				int m2= find_position(hc,k);
				if(hc->tab[m2]){
					hc->tab[m2]->val++;
					hv->tab[m]->val++;
				}
				free(k);
			}
		}
		decl=decl->next;
	}
	
	int i=0,max=0;
	Key* k;
	while(i<hc->size){
		if(hc->tab[i]->val>max){
			max=hc->tab[i]->val;
			k=hc->tab[i]->key;
		}
		i++;
	}
	
	delete_hashtable(hc);
	delete_hashtable(hv);
	
	return k;
}






















