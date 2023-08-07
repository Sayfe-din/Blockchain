#ifndef HASH
#define HASH

//STRUCTURES

typedef struct block{
	Key* author;
	CellProtected* votes; //liste de declaration
	unsigned char* hash;
	unsigned char* previous_hash; //valeur hache du block precedent
	int nonce;
}Block;

//FONCTIONS

Block* new_block();

void delete_block(Block* b);

void write_block(const char* fic,Block *b);

Block* read_block(const char* fic);

char* block_to_str(Block* b);

char* hashing(char* s);

void compute_proof_of_work(Block* b,int d);

int verify_block(Block* b, int d);


#endif
