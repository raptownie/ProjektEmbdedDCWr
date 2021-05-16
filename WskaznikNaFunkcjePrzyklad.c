/*
 * main.c
 *
 *  Created on: 16.05.2021
 *      Author: Kamil
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define RozmiarTablicy 100

/***
 * void qsort ( void * tab, size_t num, size_t size, int ( * comparator ) ( const void *, const void * ) );
 * Funkcja ta (compare) powinna dzia³ac w nastêpuj¹cy sposób: Jeœli wartoœc pierwszego elementu jest mniejsza od wartoœci drugiego,
 * Zwracana wartoœc powinna byc ujemna. Jezeli pierwszy argument jest wiekszy od drugiego, funkcja powinna zwrocic wartosc dodatnia.
 * W przypadku kiedy obie przekazane wartosci sa rowne funkcja powinna zwrocic wartosc zerowa.
 */

typedef int (* Porownianie_t)(const void *, const void *);
int Porownanie (const void *a, const void *b);

int main (){
	Porownianie_t pPorownanie;
	pPorownanie = Porownanie;
	int i;
	int tab[RozmiarTablicy];
	printf("Wylosowane liczby to:");
	srand(time(NULL));
	for(i=0; i<RozmiarTablicy; i++){
		tab[i] = rand()%100+1;
		printf("\ntab[%d]=%d", i, tab[i]);
	}

	qsort(tab, RozmiarTablicy, sizeof(int), pPorownanie);

	for(i=0; i<RozmiarTablicy; i++){
		printf("\ntab[%d]=%d", i, tab[i]);
	}
}


int Porownanie (const void *a, const void *b){
	int A = *(int *)a;
	int B = *(int *)b;
	if (A > B) return 1;
	if (A == B) return 0;
	return -1;
}
