#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//to mozna modyfikowac
#define ResultSize 10
#define RozmiarZbioruZKtoregoBedziemyLosowac (ResultSize+1)

void WypelnijTablice (size_t , int *);
void WypiszTab (size_t , int *);
void Losuj (int *, size_t, int *, size_t );
bool CzyWTablicyJestTakaLiczba (int ,int *, size_t );
void UsunLiczbeZLosowania (int *, size_t, int );
int PierwszaLiczbaKtorejBrakuje (int *, size_t );

int main (){

	int ZbiorLiczbZKtorychBedziemyLosowac[RozmiarZbioruZKtoregoBedziemyLosowac];
	int ResultTab[ResultSize];
	srand(time(NULL));

	printf("Zbiór liczb z którego będziemy losowac:");
	WypelnijTablice(RozmiarZbioruZKtoregoBedziemyLosowac, ZbiorLiczbZKtorychBedziemyLosowac);
	WypiszTab(RozmiarZbioruZKtoregoBedziemyLosowac, ZbiorLiczbZKtorychBedziemyLosowac);
	printf ("\n\nTablica wynikowa:");
	Losuj(ZbiorLiczbZKtorychBedziemyLosowac, RozmiarZbioruZKtoregoBedziemyLosowac, ResultTab, ResultSize);
	WypiszTab(ResultSize, ResultTab);
	printf("\nLiczby ktorej brakuje to : %d", PierwszaLiczbaKtorejBrakuje(ResultTab, ResultSize));

}

void WypelnijTablice (size_t rozmiar, int *tab){
	for (int i=0; i<rozmiar; i++) tab[i]	= i;
}

void WypiszTab (size_t rozmiar, int *tab){
	for (int i=0; i<rozmiar; i++){
		printf("\ntab[%d] = %d", i, tab[i]);
	}
}

void Losuj (int *TablicaZLiczbamiDoLosowania, size_t RozmiarTablicyZLiczbamiDoLosowania, int *TablicaWynikowa, size_t iloscLiczbDoWylosowania){
	static int temp=0;
	for (int i=0; i<iloscLiczbDoWylosowania;){
		temp = rand()%RozmiarTablicyZLiczbamiDoLosowania;
		if (CzyWTablicyJestTakaLiczba(temp, TablicaZLiczbamiDoLosowania, RozmiarTablicyZLiczbamiDoLosowania))  {
			TablicaWynikowa[i++]=temp;
			UsunLiczbeZLosowania(TablicaZLiczbamiDoLosowania, RozmiarTablicyZLiczbamiDoLosowania, temp);
		}
	}
}

bool CzyWTablicyJestTakaLiczba (int szukanaLiczba,int *tab, size_t rozmiar){
	for (int i=0; i<rozmiar; i++)
		if (tab[i]==szukanaLiczba) return true;
	return false;
}

void UsunLiczbeZLosowania (int *tab, size_t rozmiar, int liczba){
	tab[liczba] = rozmiar+1;
}

int PierwszaLiczbaKtorejBrakuje (int *tab, size_t rozmiar){
	for (int i=0; i<=rozmiar; i++){
		for (int j=0; j<rozmiar; j++){
			if (tab[j]==i){
				break;
			}else if ((j+1) == rozmiar) return i;
		}
	}
	return -1;
}

