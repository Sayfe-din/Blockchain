#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include "exo1.h"
#include <math.h>

//REMARQUE : "Dans le cadre de ce projet, on considerera uniquement des entiers avec au plus 7 bits" (2^7-1 = 127, 2^(7-1) = 64)

//IMPLEMENTATION PAR UNE METHODE NAIVE

int is_prime_naive(long p){
	
	for(int i = 3; i < p; i++){
		if(p%i==0){ // par definition : si le reste est nul alors il est divisible
			return 0;
		}
	}
	
	return 1;
}

//EXPONENTIATION MODULAIRE RAPIDE

long modpow_naive(long a, long m, long n){

	long r = 1;
	
	for(int i=1;i<=m;i++){
		r = (a*r)%n;
	}
	
	return r;
}

int modpow(long a, long m, long n){
	
	if(m==0){
		return 1;
	}
	
	else if(m%2==0){
		long b = modpow(a, m/2, n);
		return (b*b)%n;
	}
	
	else{
		long m2 = ((long)(m/2));
		long b = modpow(a, m2, n);
		return (((b*b)%n)*a)%n;
	}
}

//TEST DE MILLER-RABIN

//Test si a est temoin de Miller de p
int witness ( long a , long b , long d , long p ) {
	long x = modpow (a ,d , p ) ;
	if ( x == 1) {
		return 0;
	}
	for ( long i = 0; i < b ; i ++) {
		if ( x == p -1) {
		return 0;
		}
 		x = modpow (x ,2 , p ) ;
	}
 	return 1;
}

//Genere aleatoirement un nombre entre low et up inclus
long rand_long ( long low , long up ) {
	return rand() % (up - low +1) + low;
}

//Test de Miller : 1->p probablement premier 0->p non premier
int is_prime_miller ( long p , int k ) {
	if ( p == 2) {
		return 1;
	}
	if (!( p & 1) || p <= 1) { //on verifie que p est impair et different de 1
		return 0;
	}
	//on determine b et d :
	long b = 0;
	long d = p - 1;
	while (!( d & 1) ) { //tant que d n’est pas impair
		d = d /2;
		b = b +1;
	}
	// On genere k valeurs pour a, et on teste si c’est un temoin :
	long a ;
	int i ;
	for ( i = 0; i < k ; i ++) {
		a = rand_long (2 , p -1) ;
		if ( witness (a ,b ,d , p ) ) {
			return 0;
		}
	}
	return 1;
}

//GENERATION DE NOMBRES PREMIERS

long random_prime_number(int low_size, int up_size, int k){
	long min = 2, max = 2;

	for(int i = 1; i <= low_size-1; i++){
		min = min *2;
	}

	for(int i = 1; i <= up_size; i++){
		max = max *2;
	}

	max--;
	/* nous avons rencontre un probleme avec la fonction pow, nous avons
	decide de la reecrire dans cette fonction (voir ci-dessus)
	
	long min = pow(2, (low_size-1));
	long max = pow(2, up_size) - 1;*/

	//generer le primer nombre entre low_size et up_size
	long p = rand_long(min, max);

	//tant que p n'est pas premier
	while(is_prime_miller(p,k) != 1){
		
		p = rand_long(min, max);
	}
	
	return p;

}
	
