#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openssl/sha.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "partie2.h"
#include "partie3.h"
#include "partie4.h"
#include "partie5.h"

//Creaation d'un block
Block* new_block(){
	//Allocations + Verification pour un Block
	Block* b=(Block*)malloc(sizeof(Block));
	assert(b);
	
	b->author=NULL; //(Key*)malloc(sizeof(Key));
	
	//Allocations + Verification pour hash d'un block
	b->hash=(unsigned char*)malloc(sizeof(unsigned char)*255);
	if(!b->hash){
		free(b);
		return NULL;
	}
	
	//Allocations + Verification pour previous hash d'un block
	b->previous_hash=(unsigned char*)malloc(sizeof(unsigned char)*255);
	if(!b->previous_hash){
		free(b->hash);
		free(b);
		return NULL;
	}
	
	b->votes=NULL;
	b->nonce=0;
	
	return b;
}

//Liberation de la memoire allouee pour un block
void delete_block(Block* b){
	//Verification b != NULL
	if(!b){return;}
	if(b->hash){
		free(b->hash);
		b->hash=NULL;
	}
	if(b->previous_hash){
		free(b->previous_hash);
		b->previous_hash=NULL;
	}
	if(b->votes){
		CellProtected* tmp1=b->votes,*tmp2=tmp1->next;
		while(tmp2){
			desalloue_protected(tmp1->data);
			free(tmp1);
			tmp1=tmp2;
			tmp2=tmp2->next;
		}
		free(tmp1);	
		b->votes=NULL;
	}
	free(b);
}

//Ecriture d'un block dans un fichier
void write_block(const char* fic, Block* b){
	assert(b);
	//Ouverture du fichier
	FILE *f=fopen(fic,"w");
	assert(f);
	
	//Transformation de la cle en str
	char*str=key_to_str(b->author);
	
	//Ajout des autres attributs d'un block dans le fichier fic
	fprintf(f,"%s\n%s\n%s\n%d\n",str,b->hash,b->previous_hash,b->nonce);
	//fprintf(stdout,"Wrote in %s : %s\n%s\n%s\n%d\n",fic,str,b->hash,b->previous_hash,b->nonce);
	
	
	//Liberation de la chaine
	free(str);
	
	//Ajout des declarations de vote
	for(CellProtected* vote=b->votes;vote;vote=vote->next){
		char* buffer=protected_to_str(vote->data);
		fprintf(f,"%s\n",buffer);
		free(buffer);
	}
	
	//Fermeture du fichier
	fclose(f);
}

//Lecture d'un fichier contenant block 
Block* read_block(const char* fic){
	FILE *f=fopen(fic,"r");
	assert(f);

	Block *b=new_block();
	unsigned char buffer[255];

	//Recuperation des 4 premieres lignes
	if(!fgets((char*)buffer,255,f)){printf("Mauvaise Lecture de %s",fic);fclose(f); assert(NULL);}
	
	//Suppression du character "\n"
	buffer[strcspn((char*)buffer,"\n")]='\0';
	
	Key* k=str_to_key((char*)buffer);
	b->author=k;
	
	if(!fgets((char*)buffer,255,f)){printf("Mauvaise Lecture de %s",fic);fclose(f); assert(NULL);}

	buffer[strcspn((char*)buffer,"\n")]='\0';
	
	strcpy((char*)b->hash,(char*)buffer);
	
	if(!fgets((char*)buffer,255,f)){printf("Mauvaise Lecture de %s",fic);fclose(f); assert(NULL);}
	
	buffer[strcspn((char*)buffer,"\n")]='\0';
	
	//Cas Genesis
	if(!strcmp((char*)buffer,"(null)")){
		free(b->previous_hash);
		b->previous_hash=NULL;
	}
	//Cas normal
	else{
		strcpy((char*)b->previous_hash,(char*)buffer);
	}
	
	if(!fgets((char*)buffer,255,f)){printf("Mauvaise Lecture de %s",fic);fclose(f); assert(NULL);}

	b->nonce=atoi((char*)buffer);
	//Lecture de la premiere declaration
	if(!fgets((char*)buffer,255,f)){
		printf("Erreur de lecture du fichier %s\n",fic);
		fclose(f);
		assert(NULL);
	} 
	
	//Transformation de la declaration en str
	
	Protected* pr1=str_to_protected((char*)buffer);
	
	CellProtected* cp = create_cell_protected(pr1);
	
	//Variable tmp permettant d'ajouter en fin de liste en temps constant;
	CellProtected* tmp=cp;
	
	//Lecture des declarations restante
	while(fgets((char*)buffer,255,f)!=NULL){
		Protected* pr2=NULL;
		pr2=str_to_protected((char*)buffer);
		tmp->next=create_cell_protected(pr2);
		tmp=tmp->next;
	}
	b->votes=cp;
	
	//fermeture du fichier
	fclose(f);
	return b;
}

//Transformation d'un block en str
char* block_to_str(Block* b){
	assert(b);
	//Transformation de la cle en str
	char* str=key_to_str(b->author),*res;
	assert(str);

	//Calcule de la taille totale des chaines de caracteres
	int size=strlen(str)+strlen((char*)b->hash)+1;
	if(b->previous_hash){
		size=size+strlen((char*)b->previous_hash);
	}
	
	res=(char*)malloc(sizeof(char)*size);
	if(!res){free(str); return NULL;}

	//Methode de construction de la chaine identique pour chaque block

	strcpy(res,str);
	free(str);
	if(b->previous_hash){
		strcat(res,(char*)b->previous_hash);
	}
	
	for(CellProtected* vote=b->votes;vote;vote=vote->next){
		char* buffer=protected_to_str(vote->data);
		size=size+strlen(buffer);
		//Agrandissement de l'espace pour chaque declaration
		res=(char*)realloc(res,sizeof(char)*(size));
		if(!res){free(buffer); return NULL;}
		strcat(res,buffer);
		free(buffer);
	}
	int i=0,nonce=b->nonce;
	while(nonce){
		nonce=nonce/10;
		i++;
	}
	str=(char*)malloc(sizeof(char)*(size+i+1));
	
	if(!str){free(res);return NULL;}

	sprintf(str,"%s%d",res,b->nonce);
	free(res);
	return str;
}

//Retourne la valeur hachee d'une chaine de caractere par algorithme SHA256
char* hashing(char* s){
	unsigned char *str=SHA256((unsigned char*)s,strlen((char*)s),0);
	
	char *str2=(char*)malloc(sizeof(char)*(2*SHA256_DIGEST_LENGTH+1));
	if(!str2){return NULL;}
	str2[0]='\0';
	for(int i=0;i<SHA256_DIGEST_LENGTH;i++){
		sprintf(str2,"%s%02x",str2,str[i]);
	}
	
	return str2;
}

//Fonction pour rendre un block valide
void compute_proof_of_work(Block* b,int d){
	if(!d){
		return;
	}
	char *str=block_to_str(b),*str2=hashing(str);
	char cmp[d+1];
	memset(cmp,'0',d);
	while(strncmp((const char *)str2,(const char *)cmp,d)){
		free(str);
		free(str2);
		b->nonce++;
		str=block_to_str(b);
		str2=hashing(str);
		/*int i ;
		for ( i = 0; i < 4 ; i++){
			printf ("%02x ", str2[i]) ;
		}
		putchar('\n') ;*/
	}
	//printf("%s\n",str2);
	strcpy((char*)b->hash,str2);				
	free(str);
	free(str2);
}


//Verifie si un block est valide
int verify_block(Block* b, int d){
	char *str=block_to_str(b),*str2=hashing(str);
	char cmp[d+1];
	memset(cmp,'0',d);
	//On compare les d premiers caracteres de str2 et cmp
	if(!strncmp((const char *)str2,(const char *)cmp,d)){
		free(str);
		//printf("Verified: %s\n",str2);
		free(str2);
		return 1; 	
	}
	
	//printf("NOT Verified: HASH FOUND:   %s  with PH:  %s\n",str2,b->previous_hash);
	free(str);
	free(str2);
	return 0;
}
















