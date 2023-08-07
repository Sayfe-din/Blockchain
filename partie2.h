#ifndef P2
#define P2

//STRUCTURES 

//Structure Key 
typedef struct _key{
	long a;
	long n;
}Key;

//Structure Signature
typedef struct _signature{
	int len;
	long* tab;
}Signature;

//Structure Protected
typedef struct _prot{
	Key* pkey;	//clee publique 
	char* mess;	//declaration de vote 
	Signature* s;	//signature
}Protected;

//FONCTIONS :

void init_key(Key* key, long val, long n);

void init_pair_keys(Key* pKey, Key* sKey, int low_size, int up_size);

char* key_to_str(Key* key);

Key* str_to_key(char* str);

Signature* init_signature(long* content, int size);

Signature* sign(char* mess, Key* sKey);

char * signature_to_str ( Signature * sgn );

Signature * str_to_signature ( char * str ) ;

void desalloue_sign(Signature *s);

Protected* init_protected(Key* pKey, char* mess, Signature* sgn);

int verify(Protected* pr);

char* protected_to_str(Protected* p);

Protected* str_to_protected(char *str);

void generate_random_data(int nv, int nc);

void desalloue_protected(Protected *p);


//STRUCTURES
//liste de Key
typedef struct _cellKey{
	Key* data;
	struct _cellKey* next;
} CellKey;

//liste de protected
typedef struct _cellProtected{
	Protected* data;
	struct _cellProtected* next;
} CellProtected;


//FONCTIONS
CellKey* create_cell_key(Key* key);

void ajout_en_tete_key(CellKey **ck,Key* k);

CellKey* read_public_keys(const char *fic);

void print_list_keys(CellKey* LCK);

void delete_cell_keys(CellKey* c);

void delete_list_key(CellKey* LCK);

CellProtected* create_cell_protected(Protected* pr);

void ajout_en_tete_prot(CellProtected** cp,Protected* pr);

CellProtected* read_protected(const char *fic);

void print_list_prots(CellProtected* LCP);

void delete_cell_prots(CellProtected* C);

void delete_list_prot(CellProtected* LCP);

void verify_all(CellProtected ** LCP);


#endif


