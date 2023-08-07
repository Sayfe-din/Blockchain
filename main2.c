#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "exo1.h"
#include "exo2.h"
#include "partie2.h"

void print_long_vector ( long * result , int size ) {
	printf ( " V e c t o r : [ " ) ;
	for ( int i =0; i < size ; i ++) {
		printf ( "%lx  " , result[ i ]) ;
	}
	printf ( "] \n" ) ;
}

int main ( void ){
	srand( time ( NULL ));
	
	//Testing Init Keys
 	Key * pKey = malloc ( sizeof ( Key ) ) ;
 	Key * sKey = malloc ( sizeof ( Key ) ) ;
	init_pair_keys ( pKey , sKey ,3 ,7) ;
 	printf ( "pKey : %lx , %lx \n" , pKey->a, pKey -> n ) ;
	printf ( "sKey : %lx , %lx \n" , sKey->a , sKey-> n ) ;


 	//Testing Key Serialization
	char * chaine = key_to_str ( pKey ) ;
	printf ( "key_to_str : %s \n", chaine ) ;
	Key * k = str_to_key ( chaine ) ;
	printf ( "str_to_key: %lx , %lx \n" , k->a, k-> n ) ;
	
	
 	//Testing signature
 		//Candidate keys:
	Key * pKeyC = malloc ( sizeof ( Key ) ) ;
 	Key * sKeyC = malloc ( sizeof ( Key ) ) ;
 	init_pair_keys ( pKeyC , sKeyC ,3 ,7) ;
 	
 		//Declaration:
 	char * mess = key_to_str ( pKeyC ) ;
 	printf ( "%s vote pour %s \n" , key_to_str ( pKey ) , mess );
 	Signature * sgn = sign ( mess , sKey ) ;
 	printf ( " Signature : " ) ;
 	print_long_vector( sgn->tab, sgn->len) ;
 	chaine = signature_to_str ( sgn ) ;
 	printf ( " signature_to_str %s \n", chaine ) ;
 	sgn = str_to_signature ( chaine ) ;
 	printf ( "str_to_signature : " ) ;
 	print_long_vector ( sgn->tab, sgn ->len ) ;
 	
 	
 	//Testing protected:
 	Protected * pr = init_protected ( pKey , mess , sgn ) ;
 	
 	
	//Verification:
 	if ( verify ( pr ) ) {
 		printf ("Signature VALIDE\n" ) ;
 	} else {
 		printf ( "Signature NON VALIDE\n" ) ;
 	}
 	chaine = protected_to_str ( pr ) ;
 	printf ( "protected_to_str : %s\n" , chaine );
 	
 	pr = str_to_protected ( chaine ) ;
 	printf ( "str_to_protected : %s %s %s \n", key_to_str ( pr->pkey ) ,pr->mess , signature_to_str ( pr->s) ) ;
	
	
	//Desallocation 
	desalloue_protected(pr);
 	free ( sKey ) ; 
 	free ( pKeyC ) ;
 	free ( sKeyC ) ;
	
	/*           TEST
	
	
	generate_random_data(50,5);
	
	CellKey* LCK = read_public_keys("keys.txt");
	print_list_keys(LCK);
	delete_list_key(LCK);
	
	
	
	CellProtected *LCP= read_protected("declarations.txt");
	verify_all(&LCP);
	print_list_prots(LCP);
	delete_list_prot(LCP);
	*/
	
	return 0;
}
