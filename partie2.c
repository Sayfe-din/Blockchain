#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "exo1.h"
#include "exo2.h"
#include "partie2.h"


//MANIPULATION DES CLES

//Initialiser Key deja alloouee
void init_key(Key* key, long val, long n){

	key->a = val;
	key->n = n;
}

//Initiliser pKey et sKey
//REMARQUE : Pour etre coherent avec la fonction random_prime_number nous avons modifie le type des parametres low_size et up_size 
void init_pair_keys(Key* pKey, Key* sKey, int low_size, int up_size){
	
	//variables d recuperation
	long n, p, q, s, u;
	
	//Generer aleatoirement p et q premier
	p = random_prime_number(low_size, up_size, 10);
	q = random_prime_number(low_size, up_size, 10);
	
	while ( p == q ) {
		q = random_prime_number(3 ,7 , 5000);
		//Verification que p et q sont differents
	}

	//Generer les valeurs des clees
	generate_key_values(p,q,&n,&s,&u);
	
	if( u < 0 )
	{
		long t = (p -1) *( q -1) ;
		u = u + t ; //on aura toujours s*u mod t = 1
	}
	
	//Affectation des valeurs
	init_key(pKey,s,n);
	init_key(sKey,u,n);

}

//Transformer une cle en chaine de caractere
char* key_to_str(Key* key){
	assert(key);
	char* buffer = malloc(sizeof(char)*100);
	assert(buffer);

	sprintf(buffer, "( %lx, %lx )", key->a, key->n);
	
	return buffer;
}

//Transformer une cle en chaine de caractere
Key* str_to_key(char* str){
	assert(str);

	Key* key = malloc(sizeof(Key));
	assert(key);
	
	sscanf(str, "( %lx, %lx )", &(key->a), &(key->n));
	return key;
}



//MANIPULATION DES SIGNATURES

//Initialiser une signature
Signature* init_signature(long* content, int size){
	//Allouer Signature
	assert(content);
	Signature* s=(Signature *)malloc(sizeof(Signature));
	assert(s);
	
	//Initilisation des variables	
	s->tab = content;
	s->len = size;
	
	return s;
}

//cree une signature a partir du message mess et de la cle secrete
Signature* sign(char* mess, Key* sKey){
	assert(mess);
	assert(sKey);
	long *content = encrypt(mess, sKey->a, sKey->n);
	Signature *s = init_signature(content, strlen(mess));
	return s;
}

//Transforme une signature en chaine de caractere
char * signature_to_str ( Signature * sgn ) {
	assert(sgn);
	char * result = malloc (10* sgn->len * sizeof ( char ) ) ;
	result [0]= '#' ;
	int pos = 1;
	char buffer [156];
	for ( int i =0; i < sgn->len ; i ++) {
		sprintf ( buffer , "%lx" , sgn->tab[i]) ;
		for ( int j =0; j < strlen ( buffer ) ; j ++) {
			result [ pos ] = buffer [ j ];
			pos = pos +1;
		}
		result [ pos ] = '#' ;
		pos = pos +1;
	}
	result [ pos ] = '\0' ;
	result = realloc ( result , ( pos +1) * sizeof ( char ) ) ;
	return result ;
}

Signature * str_to_signature ( char * str ) {
	assert(str);
	int len = strlen ( str ) ;
	long * content = ( long *) malloc ( sizeof ( long ) * len ) ;
	int num = 0;
	char buffer [256];

	int pos = 0;
	for ( int i =0; i < len ; i ++) {
		if ( str [ i ] != '#' ) {
			buffer [ pos ] = str [ i ];
			pos = pos +1;
		}
		else {
			if ( pos != 0) {
				buffer [ pos ] = '\0' ;
				sscanf ( buffer , "%lx" , &( content [ num ]) ) ;
				num = num + 1;
				pos = 0;
			}
		}
	}
	content = realloc ( content , num * sizeof ( long ) ) ;
	return init_signature ( content , num ) ;
}


//FONCTION SUPPLEMENTAIRE : Desalloue une Signature 
void desalloue_sign(Signature *s){
	
	if(!s){ return; }
	if(s->tab){
		free(s->tab);
		s->tab=NULL;
	}
	free(s);
}



//DECLARATIONS SIGNEES


Protected* init_protected(Key* pKey, char* mess, Signature* sgn){

	//Allocation de Protected + Verification du Malloc
	Protected* p=(Protected*)malloc(sizeof(Protected));
	assert(p);
	
	//Initialisatioon de la cle publique
	p->pkey=pKey;
	
	//Initialisation de la signature
	p->s=sgn;
	
	//Initialisation du message
	p->mess=mess;
	
	return p;
	
}

//Verifie si la declaration signees est valide
int verify(Protected* pr){
	if(!pr){
	
		return 0;
	}
	
	char* mess=decrypt(pr->s->tab,pr->s->len,pr->pkey->a,pr->pkey->n);
	if(!strcmp(mess,pr->mess)){
		free(mess);
		return 1;
	}
	free(mess);
	return 0;
}

//Transforme un protected en chaine de caractere
char* protected_to_str(Protected* p){
	assert(p);
	//Allocation dynamique + Verification
	char* buffer = malloc(sizeof(char)*256);
	if(!buffer){ return NULL; }
	
	char* s=key_to_str(p->pkey);
	
	buffer = strcpy( buffer, s);
	free(s);
	s=signature_to_str(p->s);
	
	char *a = " ";
	buffer = strcat( buffer, a);
	buffer = strcat( buffer, p->mess);
	buffer = strcat( buffer, a);
	buffer = strcat( buffer, s);
	
	free(s);
	return buffer;
}

//Transforme une chaine de caractere en protected
Protected* str_to_protected(char *str){
	assert(str);
	
	Key* pKey=(Key*)malloc(sizeof(Key));
	assert(pKey);
	
	char* mess=malloc(sizeof(char)*strlen(str));
	assert(mess);
	
	Signature *sgn=NULL;

	int i=0;
	while((str[i]!=')')&&(i<strlen(str))){
		mess[i]=str[i]; //Recuperation de la clef
		i++;
	}
	mess[i]=str[i];
	mess[i+1]='\0'; // Neutralize quelques erreurs
	i=i+2;
	
	sscanf(mess, "( %lx, %lx )",&(pKey->a),&(pKey->n));
	mess[i-1]=' ';
	int j=0;
	while((str[i]!='#')&&(i<strlen(str))){
		mess[j]=str[i]; //Recuperation du message
		j++;
		i++;
	}
	mess[j-1]='\0';
	
	mess=realloc(mess,j*sizeof(char));
	assert(mess);
	
	sgn=str_to_signature(str+i);
	Protected* p=init_protected(pKey,mess,sgn);
	
	return p;
}

//EXERCICE 4
//Simulation du processus de vote

void generate_random_data(int nv,int nc){
	FILE* fkey=fopen("keys.txt","w");
	assert(fkey);
	FILE* fcan=fopen("candidates.txt","w");
	assert(fcan);
	FILE* fdec=fopen("declarations.txt","w");
	assert(fdec);
	
	Key* allp[nv],*alls[nv];
	int can[nc];
	
    	//Creation des electeurs
	for(int i=0; i<nv;i++){
		Key *pkey=(Key*)malloc(sizeof(Key)), *skey=(Key*)malloc(sizeof(Key));
		init_pair_keys(pkey,skey,6,7);
		allp[i]=pkey;
		alls[i]=skey;
        //Ecriture de pKey et sKey dans keys.txt
		fprintf(fkey,"( %lx, %lx ) ( %lx, %lx )\n",pkey->a,pkey->n,skey->a,skey->n);
		fprintf(stdout,"( %d, %d ) ( %d, %d )\n",pkey->a,pkey->n,skey->a,skey->n);
	}
    
    //Tirage aleatoire des candidats
	for(int i=0;i<nc;i++){
		//Indice aleatoire
		int num=rand()%nv;
		can[i]=num;
        	//Ecriture de pKey dans candidates.txt
		fprintf(fcan,"( %lx, %lx )\n",allp[num]->a,allp[num]->n);
	}
	fclose(fkey);
	fclose(fcan);
	
	for(int i=0;i<nv;i++){
		Protected *vote=NULL;
		int num=rand()%nc;
		Key *pKeyC = allp[can[num]]; //Cle publique du Candidats choisi
		Key *sKeyE = alls[i];        //Cle secrete de l'Electeur courant
		//Variables a liberer
		char* mess=key_to_str(pKeyC);
		vote = init_protected(allp[i],mess,sign(mess,sKeyE));
		if(verify(vote)){
			char* buffer=protected_to_str(vote);
			fprintf(fdec,"%s\n",buffer);
			free(buffer);
		}
		desalloue_protected(vote);
	}
	for(int i=0;i<nv;i++){
		free(alls[i]);
	}
	fclose(fdec);
}

//FONCTION SUPPLEMENTAIRE : Desalloue une Protected
void desalloue_protected(Protected *p){

	if(!p){ printf("Protected set to NULL in desalloue_protected");return; }
	/*
	if(p->pkey){
		free(p->pkey);
	}*/
	if(p->s){
		desalloue_sign(p->s);
		p->s=NULL;
	}
	if(p->mess){
		free(p->mess);
		p->mess=NULL;
	}
	free(p);
}

//Creation d'une CellKey (liste chainee de cle)
CellKey* create_cell_key(Key* key){
	assert(key);
	//Allocation dynamique + Verification
	CellKey* c=(CellKey*)malloc(sizeof(CellKey));
	assert(c);

	c->data=key;
	c->next=NULL;

	return c;
}

//Ajout en tete d'une cle dans une CellKey
void ajout_en_tete_key(CellKey **ck,Key* k){
	CellKey *p=create_cell_key(k);
	p->next=*ck;
	*ck=p;
}

//Lecture des cles et Transformation en CellKey
CellKey* read_public_keys(const char *fic){

	//Ouverture du fichier + Verification
	FILE *f=fopen(fic,"r");
	assert(f);
	
	char buffer[255];
	
	Key* pKey1=(Key*)malloc(sizeof(Key));
	if(!pKey1){
		fclose(f);
		assert(pKey1);
	}
	
	if(fgets(buffer,255,f)!=buffer){
		fclose(f);
		assert(NULL);
	}
	
	//Lecture
	sscanf(buffer,"( %lx, %lx )%s",&pKey1->a,&pKey1->n,buffer);
	
	//Initialisation
	CellKey* ck=create_cell_key(pKey1);
	
	while(fgets(buffer,255,f)!=NULL){
		Key* pKey2=(Key*)malloc(sizeof(Key));
		sscanf(buffer,"( %lx, %lx )%s",&pKey2->a,&pKey2->n,buffer);
		ajout_en_tete_key(&ck,pKey2);
	}
	
	fclose(f);
	return ck;
}

//Affichage d'une CellKey
void print_list_keys(CellKey* LCK){
	assert(LCK);
	while(LCK){
		if(LCK->data){
			printf("( %lx, %lx )\n", (LCK->data)->a,(LCK->data)->n);
		}
		LCK=LCK->next;
	}
}

//Suppression d'une cellule
void delete_cell_keys(CellKey* c){
	if(!c){return;}
	if(c->data){
		free(c->data);
		c->data=NULL;
	}
	free(c);
}

//Suppression d'une liste chainee de cle
void delete_list_key(CellKey* LCK){
	if(!LCK){return;}
	CellKey* tmp=LCK->next;
	while(tmp){
		delete_cell_keys(LCK);
		LCK=tmp;
		tmp=tmp->next;
	}
	delete_cell_keys(LCK);
}

//Creation d'une cellule de liste chainee de protected
CellProtected* create_cell_protected(Protected* pr){
	assert(pr);
	//Allocation dynamique + Verification
	CellProtected* cp=(CellProtected*)malloc(sizeof(CellProtected));
	assert(cp);
	
	cp->data=pr;
	cp->next=NULL;
	
	return cp;
}

//Ajout en tete d'un protected dans une liste chainee
void ajout_en_tete_prot(CellProtected** cp,Protected* pr){
	assert(cp);
	assert(pr);
	//Creation d'une cellProtected
	CellProtected *p=create_cell_protected(pr);
	
	//Jointure entre la nouvelle cellule et l'ancienne
	p->next=*cp;
	*cp=p;
}

//Lecture du fichier declarations.txt
CellProtected* read_protected(const char *fic){

	//Ouverture du fichier + Verification
	FILE *f=fopen(fic,"r");
	assert(f);
	
	char buffer[255];
	
	Protected* pr1=NULL;
	
	if(fgets(buffer,255,f)!=buffer){
		printf("Erreur de lecture du fichier %s\n",fic); 
		return NULL; 
	} 
	
	pr1 = str_to_protected(buffer);
	
	
	CellProtected* cp = create_cell_protected(pr1);
	
	while(fgets(buffer,255,f)!=NULL){
		Protected* pr2=NULL;
		pr2=str_to_protected(buffer);
		ajout_en_tete_prot(&cp,pr2);
	}
	
	fclose(f);
	return cp;
}

//Affiche une liste de protected
void print_list_prots(CellProtected* LCP){
	
	while(LCP){
		if(LCP->data){
		
			char *str = protected_to_str(LCP->data);
			printf("%s\n",str);
			free(str);	
		}
		
		LCP = LCP->next;
	}
	
}

//Supprime une CellProtected
void delete_cell_prots(CellProtected* C){
	if(!C){return;}
	
	if(C->data){
		desalloue_protected(C->data);
		C->data=NULL;
	}
	free(C);
}

//Supprime les elements d'une liste chainee de CellProtected
void delete_list_prot(CellProtected* LCP){
	if(LCP){
		CellProtected* tmp=LCP->next;
		while(tmp){
			delete_cell_prots(LCP);
			LCP=tmp;
			tmp=LCP->next;
		}
		delete_cell_prots(LCP);
	}
}

//Verifie les declarations signees de tous les protected de la CellProtected
void verify_all(CellProtected ** LCP){
	assert(LCP);
	assert(*LCP);
	//tmp2 -> precedent, tmp->element courant, tmp1-> suivant
	CellProtected* tmp2=NULL, *tmp=(*LCP);
	CellProtected* tmp1=(*LCP)->next;
	
	//Parcours de la liste 
	while(tmp1){
	
		if(!verify(tmp->data)){
			delete_cell_prots(tmp);
			if(!tmp2){
				*LCP=tmp1;
			}
			else{
				tmp2->next=tmp1;
			}
		}
		
		else{
			tmp2=tmp;
		}
		
		tmp=tmp1;
		tmp1=tmp1->next;
	}
	
	if(!verify(tmp->data)){
		delete_cell_prots(tmp);
		tmp2->next=NULL;
	}
}
























































