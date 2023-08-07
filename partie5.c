#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "partie2.h"
#include "partie3.h"
#include "partie4.h"
#include "partie5.h"

//Creation d'un noeud
CellTree* create_node(Block* b){

	//Allocation + Verification
	CellTree* father=(CellTree*)malloc(sizeof(CellTree));
	if(!father){return NULL;}
	
	father->block=b;
	father->father=NULL;
	father->nextBro=NULL;
	father->firstChild=NULL;
	father->height=0;
	
	return father;
}

//Met a jour la hauteur du noeud father quand l’un de ses fils a ete modifie
int update_height(CellTree* father,CellTree* child){

	if((child->height+1)>father->height){
		father->height=child->height+1;
		return 1;
	}
	
	return 0;
}


//Ajout d'un fils au noeud + mise à jour de la hauteur
void add_child(CellTree* father,CellTree* child){
	if(!father){ return; }
	if(!child){ return; }
	
	//Ajout en tete de liste
	child->nextBro=father->firstChild;
	child->father=father;
	father->firstChild=child;
	
	//Mise a jour de la hauteur
	CellTree* tmp=father,*c=child;
	while(tmp){
		if(update_height(tmp,c)){
			c=tmp;
			tmp=tmp->father;
		}
		
		else{
			tmp=NULL;
		}
	}
}

//Affichage d'un arbre
void print_tree(CellTree* t,int i){
	if(!t){return;}
	
	int j=i;
	while(j){
		putchar(' ');
		j--;
	}
	printf("%d\n",t->height);
	print_tree(t->nextBro,i);
	print_tree(t->firstChild,i+1);
}

//Suppression d'un noeud
void delete_node(CellTree* node){
	if(!node){return;}
	
	delete_block(node->block);
	free(node);
}

//Suppression d'un arbre
void delete_tree(CellTree* t){
	if(!t){return;}
	
	delete_tree(t->firstChild);
	delete_tree(t->nextBro);
	delete_node(t);
}

//Renvoie noeud du fils avec la plus grande hauteur
CellTree* highest_child(CellTree* cell){
	if(!cell){return NULL;}
	int max=cell->height-1;
	
	CellTree* tmp=cell->firstChild,*res=NULL;
	while(tmp){
		if(tmp->height==max){
			res=tmp;
			tmp=NULL;
		}
		else{
			tmp=tmp->nextBro;
		}
	}
	return res;
}

//Retourne le dernier bloc de la plus longue chaine
CellTree* last_node(CellTree* tree){
	CellTree* tmp = highest_child(tree);
	if(!tmp){return tree;}
	while(tmp->firstChild){ 
		tmp=highest_child(tmp);
	}
	
	return tmp;
}


//Fusion de deux listes chainees de declarations signees
CellProtected* merge_declarations(CellProtected* p1,CellProtected* p2){
	if(!p1||!p2){ return p1?p1:p2; }
	
	CellProtected* tmp=p1->next;
	while(tmp->next){
		tmp=tmp->next;
	}
	tmp->next=p2;
	return p1;
}

//Retourne la liste obtenue par fusion de declaration contenue dans les blocs de la plus longue chaîne
CellProtected* merge_decl_tree(CellTree* t){
	if(!t){return NULL;}
	
	CellTree *tmp=highest_child(t);
	CellProtected *res=t->block->votes;
	
	while(tmp){
		//res en deuxieme arguement pour ne pas le parcourir si plus longue tmp->block->votes 
		res=merge_declarations(tmp->block->votes,res);
		tmp=highest_child(tmp);
	}
	return res;
}

//Soumission d'un vote -> ajout dans le fichier "Pending_votes.txt"
void submit_vote(Protected* p){
	FILE* f=fopen("Blockchain/Pending_votes.txt","a");
	if(!f){return;}
	
	char* s=protected_to_str(p);
	fprintf(f,"%s\n",s);
	fclose(f);
	free(s);
}

//Creation d'un bloc valide grace a "Pending_votes.txt" + Suppresion du fichier + Ecriture dans "Pending_block.txt"
void create_block(CellTree* tree,Key* author,int d){
	assert(author);
	//Creation des declarations
	CellProtected* tmp = read_protected("./Blockchain/Pending_votes.txt");
	
	
	//Creation du block
	Block* b=new_block();
	b->author=author;
	b->votes=tmp;
	if(!tree){
		free(b->previous_hash);
		b->previous_hash=NULL;
	}
	else{
		b->previous_hash=last_node(tree)->block->hash;
	}
	
	//Validation du block
	compute_proof_of_work(b,d);
	
	//Suppression du fichier
	remove("./Blockchain/Pending_votes.txt");
	
	//Ecriture du fichier
	
	write_block("./Blockchain/Pending_block", b);
	
	//Liberation de la memoire
	delete_block(b);
}

//Verifie que le block de "Pending_block.txt" est valide
void add_block(int d, char* name){
	Block* b = read_block("./Blockchain/Pending_block");
	assert(b);
	if(verify_block(b,d)){
		//printf("Block valide : %s\n",b->hash);
		write_block(name,b);
	}
	else{
		char* s= block_to_str(b);
		//printf("Block invalide : %s",b->hash);
		free(s);
	}
	
	remove("./Blockchain/Pending_block");
}

//Construction de l’arbre correspondant aux blocs contenus dans le repertoire ”Blockchain"
CellTree* read_tree(){
	
	DIR *rep=opendir("./Blockchain/");
	struct dirent * dir;
	int nb = 0;
	while((dir=readdir(rep))){
		if(strcmp(dir->d_name,".")&&strcmp(dir->d_name,"..")&&strcmp(dir->d_name,"Pending_votes.txt")&&strcmp(dir->d_name,"Pending_block")){
			nb++;
		}
		
	}
	closedir(rep);
	rep=opendir("./Blockchain/");
	int i=0,j=0;
	CellTree *T[nb];
	CellTree *tree =NULL;
	if(rep){
		struct dirent *ent=readdir(rep);
		while(ent&&(i<nb)){
			if(strcmp(ent->d_name,".")&&strcmp(ent->d_name,"..")&&strcmp(ent->d_name,"Pending_votes.txt")&&strcmp(ent->d_name,"Pending_block")){
				char nom[strlen(ent->d_name)+20];
				sprintf(nom,"./Blockchain/%s",ent->d_name);
				Block* b=read_block(nom);
				T[i]=create_node(b);
				if(!T[i]->block->previous_hash){
					tree=T[i];
				}
				i++;
			}
			ent=readdir(rep);
		}
		
		closedir(rep);
		
	}
	i=0;
	while(i<nb){
		CellTree* tmp=T[i];
		j=0;
		assert(tmp);
		assert(tmp->block);
		while(j<nb){
			if(T[j]->block->previous_hash){
				if(!strcmp((char*)tmp->block->hash,(char*)T[j]->block->previous_hash)){
					add_child(tmp,T[j]);
				}
			}
			j++;
		}
		i++;
	}
	return tree;

}

//Determine le gagnant de l’election
Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV){
	
	//Fusion des votes
	CellProtected *p = merge_decl_tree(tree);
	
	//Verification
	verify_all(&p);
	
	//Calcul du gagnant
	Key* w=compute_winner(p, candidates,voters, sizeC, sizeV);
	
	//Retour des pointeurs next a la normale pour les champs votes des blocks de tree
	CellProtected *tmp=p;
	int i=0;
	while(tmp){
		tmp=p->next;
		if(i==10){
			p->next=NULL;
			i=0;
			p=tmp;
		}
		i++;
	}
	return w;

}








