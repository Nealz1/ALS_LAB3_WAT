#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

//DEKLARACJA LISTY
struct Lista
{
  int data;
  struct Lista* nastepny;
};

//FUNCKJA W CELU ZAPISU LISTY DO PLIKU
void ZapiszDoPliku(struct Lista *w, char nazwapliku[50])
{
    struct Lista *wsk = w;
    ofstream  plik;
    int licznik = 1;
    plik.open(nazwapliku);
    
    if(plik.good() == true) //SPRAWDZENIE CZY PLIK UTWORZONO
	{
        while (wsk != NULL)
		{
			//ZAPISYWANIE DANYCH
            plik << wsk->data << " ";
            wsk = wsk->nastepny;
            
            if(licznik%10==0) //IF ZEBY WYPISAC PO 10 ZNAKOW NA WIERSZ
        	{
        	plik << endl;
			}
			licznik++;
        }
    }
    plik.close(); //ZAMKNIECIE PLIKU
}

//WYPISANIE DO KONSOLI CALEJ LISTY
void Wypisz(struct Lista* Lista)
{
	int licznik = 1;
    while (Lista != NULL)// DO MOMENTU KIEDY LISTA NIE BEDZIE NULLEM (NULL - PUSTA) WYPISZE WSZYSKIE ELEMENTY
    {
        cout << Lista->data << " ";
        Lista = Lista->nastepny; //PRZEJSCIE DO NASTEPNEGO ELEMENTU
        
        if(licznik%10==0) //IF ZEBY WYPISAC PO 10 ZNAKOW NA WIERSZ
    	{
    		cout << endl;
		}
		licznik++;
    }
    cout << endl;
}

//FUNKCJA DO DODAWANIA NOWYCH ELEMENTOW NA KONIEC LISTY
void DodajNaKoniec(struct Lista** poczatek, int nowy)
{
    struct Lista* nowa_Lista = (struct Lista*) malloc(sizeof(struct Lista)); //PRZYDZIELENIE PAMIECI
    struct Lista *ostatni = *poczatek;
    
    nowa_Lista->data  = nowy;
    nowa_Lista->nastepny = NULL;
    
    if (*poczatek == NULL) //SPRAWDZENIE CZY LISTA JEST PUSTA
    {
       *poczatek = nowa_Lista;
       return;
    }
    while (ostatni->nastepny != NULL)
    {
       ostatni = ostatni->nastepny; //PRZEJSCIE DO NASTEPNEGO ELEMENTU
    }
    ostatni->nastepny = nowa_Lista;
    return;
}

//FUNCKJA INICJUJACA LISTE ELEMENTOW Z PRZEDZIALU <2,N>
void Inicjuj(struct Lista** poczatek, int liczba)
{
  int i;
  for(i=2; i<=liczba;++i)
  {
      DodajNaKoniec(poczatek, i);
  }
}

//USUNUWANIE DANEGO ELEMENTU Z LISTY
void Usun(struct Lista** poczatek, int klucz)
{
    struct Lista *nc = *poczatek, *poprzedni;
    if (nc != NULL && nc->data == klucz)
    {
        *poczatek = nc->nastepny;
        free(nc);
        return;
    }
    while (nc != NULL && nc->data != klucz)
    {
        poprzedni = nc;
        nc = nc->nastepny;
    }
    if (nc == NULL)
    {
        return;
    }
    poprzedni->nastepny = nc->nastepny;

    free(nc); //ZWOLNIENIE PAMIECI ZMIENNEJ AKA USUNIECIE JEJ
}

//SORTOWANIE od najmniejszej do najwiekszej, BABELKOWE
void SortujNW(struct Lista *start)
{
    int swapped, i;
    struct Lista *sort1;
    struct Lista *sort2 = NULL;

    do
    {
        swapped = 0;
        sort1 = start;
        while (sort1->nastepny != sort2)
        {
            if (sort1->data > sort1->nastepny->data)
            {
                swap(sort1->data, sort1->nastepny->data);
                swapped = 1;
            }
            sort1 = sort1->nastepny;
        }
        sort2 = sort1;
    }
    while (swapped);
}

//USUWANIE DUPLIKATAOW (DZIALA NA NIEPOSORTOWANYCH I POSORTOWANYCH)
void UsunDuplikaty(struct Lista* poczatek)
{
    struct Lista *sprawdz1, *sprawdz2, *duplikat;
    sprawdz1 = poczatek;
 
    while (sprawdz1 != NULL && sprawdz1->nastepny != NULL) 
	{
        sprawdz2 = sprawdz1;
        while (sprawdz2->nastepny != NULL) 
		{
            if (sprawdz1->data == sprawdz2->nastepny->data) 
			{
                duplikat = sprawdz2->nastepny;
                sprawdz2->nastepny = sprawdz2->nastepny->nastepny;
                delete (duplikat);
            }
            else
            {
            sprawdz2 = sprawdz2->nastepny;	
			}
        }
        sprawdz1 = sprawdz1->nastepny;
    }
}

//FUNKCJA LICZACA SITO ATKINA
void sito(struct Lista** poczatek, int liczba, char nazwapliku[50])
{
	struct Lista* nowa = NULL;
	
    int pierwiastekL;
    pierwiastekL = sqrt(liczba);
    
    int x, y, z;
    int i, j;
    
    DodajNaKoniec(&nowa, 2);
    DodajNaKoniec(&nowa, 3);
    DodajNaKoniec(&nowa, 5);
    
    //SZUKANIE LICZB PODEJRZANYCH O BYCIE LICZBAMI PIERWSZYMI
   	for (x = 1; x <= pierwiastekL; x++)
    {
        for (y = 1; y <= pierwiastekL; y++)
        {
            z = 4 * x * x + y * y;
            if (z <= liczba && (z % 60 == 1 || z % 60 == 13 || z % 60 == 17 || z % 60 == 29 || z % 60 == 37 || z % 60 == 41 || z % 60 == 49 || z % 60 == 53))
            {
            	DodajNaKoniec(&nowa,z);
            }

            z = 3 * x * x + y * y;
            if (z <= liczba && (z % 60 == 7 || z % 60 == 19 || z % 60 == 31 || z % 60 == 43))
            {
            	DodajNaKoniec(&nowa,z);
            }

            z = 3 * x * x - y * y;
            if (x > y && z <= liczba && (z % 60 == 11 || z % 60 == 23 || z % 60 == 47 || z % 60 == 59))
            {
            	DodajNaKoniec(&nowa,z);
            }
        }
    }
    
    SortujNW(nowa); //SORTUJEMY PONIEWAZ ZE WZGLEDU NA IFY, LICZBY NIE SA UPORZADKOWANE NP. WYNIK To 2 5 7 13 17 19 29 37 31, DZIEJE SIE TO PRZEZ WARUNKI IFA I DODAWANIE ICH DO NOWEJ LISTY
    UsunDuplikaty(nowa); //WARUNKI SITA ATKINA TWORZA PODWOJONE LICZBY W NIEKTORYCH PRZYPADKACH
    
    //SPRAWDZANIE CZY PODEJRZEWANE LICZBY SA FAKTYCZNIE PIERWSZE, JESLI NIE TO USUWAMY
    for (i = 5; i <= pierwiastekL; i++)
    {
            for (j = i*i; j <= liczba; j+=i)
            {
                Usun(&nowa, j); //USUWANIE LICZB KTORE OKAZALY SIE NIE BYC PIERWSZYMI
            }
    }
    
    Wypisz(nowa);
    ZapiszDoPliku(nowa, nazwapliku);
}


//MAIN, WYWOLANIE FUNCKJI
int main()
{
	//DEKLARACJA LISTY JAK I ZMIENNYCH
    struct Lista* dana = NULL;

    char nazwapliku[50];
    int liczba;

    cout << "Podaj n, gorna czesc przedzialu <2,n>" << endl;
    cin >> liczba;
    
    cout << "Podaj nazwe pliku do zapisu wraz z rozszerzeniem(!)." << endl;
    cin >> nazwapliku;
    
    //WYWOLANIE FUNCKJI
    Inicjuj(&dana, liczba);
    cout << endl << "Liczby pierwsze z przedzialu <2," << liczba << ">" << endl;
    sito(&dana, liczba, nazwapliku);
	cout << endl << "Zapisano do pliku pomyslnie";
    
    return 0;
}
