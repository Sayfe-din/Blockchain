#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "exo1.h"
#include "exo2.h"


void print_long_vector ( long * result , int size ) {
	printf ( " V e c t o r : [ " ) ;
	for ( int i =0; i < size ; i ++) {
		printf ( "%lx  " , result[ i ]) ;
	}
	printf ( "] \n" ) ;
}


int main(){

	srand(time(NULL));
	
	                                      //EXERCICE II
	
		//Generation de cle :
	long p = random_prime_number (3 ,7 , 5000);
	long q = random_prime_number (3 ,7 , 5000);
	
	while ( p == q ) {
		q = random_prime_number(3 ,7 , 5000);
	}
	
	long n , s , u ;
	generate_key_values(p ,q ,&n ,&s ,&u);
	
		//Pour avoir des cles positives :
		
	if (u <0) {
		long t = (p -1) *( q -1) ;
		u = u + t ; //on aura toujours s*u mod t = 1
	}

		//Afichage des cles en hexadecimal
	printf ( "cle publique = (%lx , %lx ) \n" ,s , n );
	printf ( "cle privee = (%lx , %lx ) \n" ,u , n );

		//Chiffrement:
	char mess [10] = "Hello";
	int len = strlen(mess);
	long * crypted = encrypt ( mess , s , n ) ;

	printf ( "Initial Message : %s \n", mess ) ;
	printf("Encoded representation: \n") ;
	print_long_vector(crypted,len);

		//Dechiffrement
	char * decoded = decrypt ( crypted , len , u , n ) ;
	
	printf ("Decoded : %s \n", decoded);
	
	
	/*                                    EXERCICE I
	
	 	TEST FONCTION GENERATE_KEY_VALUE
	long s, u, n;
	generate_key_values(967, 631, &n, &s, &u);
	printf("p=967, q=631, s=%ld, u=%ld, n=%ld\n",s, u, n);
	
	
		TEST FONCTION IS_PRIME_NAIVE
	long i=3;
	clock_t ti,tf;
	double tcpu;
	while(tcpu<(0.002)){
		ti=clock();
		is_prime_naive(i);
		tf=clock();
		tcpu=((double)(tf-ti))/CLOCKS_PER_SEC;		
		i++;
	}
	
	printf("%ld\n",i);
	*/
	
	
	/*
		TEST MODPOW
	printf("%ld %d \n",modpow_naive(7855555555555, 1255, 55),modpow(7855555555555,1255,55));
	AFFICHAGE TEST :
	./prime 
	45 45 

                	Temps de Performance de MOD_POW Naive et Non Naive
                	
	FILE* f=fopen("temps.txt","w");
	long m=500;
	clock_t ti,tf;
	double tcpu,tcpu1;
	fprintf(f,"M Modpow Naive\n");
	for(int i=50;i<=m;i++){
		ti=clock();
		modpow(7855555555555,i,55);
		tf=clock();
		tcpu=((double)(tf-ti))/CLOCKS_PER_SEC;	
	
		ti=clock();
		modpow_naive(7855555555555,i,55);
		tf=clock();
		tcpu1=((double)(tf-ti))/CLOCKS_PER_SEC;	
		fprintf(f,"%d %f %f \n",i,tcpu , tcpu1);	
		
	}
	fclose(f);

	        TEST RANDOM_PRIME_NUMBER
	        
	long p =random_prime_number(7, 7, 10);
	printf("p= %ld\n",p);
	
	//AFFICHAGE : p = 103  (c'est bien un nombre premier)
	*/
	
	return 0;
}
