#ifndef P3
#define P3

//SRUCTURES
typedef struct hashcell{
	//Cle public
	Key* key; 
	// -1 si emplacement libredans Hashtable, si HashCell votant : , 0 pas vote, 1 vote sinon HashCell candidates : nombre de voix pour un candidat
	int val; 
} HashCell;

typedef struct hashtable{
	HashCell** tab; //table de hachage
	int size; //taille de tab
} HashTable;


//FONCTIONS 
HashCell* create_hashcell(Key* key);

int hash_function(Key* key, int size);

int find_position(HashTable* t, Key* key);

HashTable* create_hashtable(CellKey* keys,int size);

void delete_hashtable(HashTable* t);

Key* compute_winner(CellProtected* decl, CellKey* candidates,CellKey* voters, int sizeC, int sizeV);

#endif
