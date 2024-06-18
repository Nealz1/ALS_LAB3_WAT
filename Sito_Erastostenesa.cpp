#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <fstream>

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
    		cout<< endl;
		}
		licznik++;
    }
    printf("\n");
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
      DodajNaKoniec(poczatek,i);
  }
}

//USUNUWANIE DANEGO ELEMENTU Z LISTY
void usun_z_Listy(struct Lista** poczatek, int klucz)
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

//FUNCKJA SPRAWDZAJACA CZY DANA LICZBA JEST PIERWSZA, JESLI TAK ZWROCI 1, JESLI NIE ZWROCI 0
int Czypierwsza(int n)
{
    int i;
    if(n<2)
    {
        return 0;
    }
    for(i=2;i*i<=n;++i)
    {
        if(n%i==0) //SZUKANIE PODZIELNIKOW LICZBY
        {
            return 0;
        }
    }
    return 1;
}

//FUNKCJA LICZACA SITO ERASTOTENESA
void sito(struct Lista** poczatek, int liczba)
{
    struct Lista *element = *poczatek;
    int i,j;
    for(i=2;i*i<=liczba;++i)
    {
        if(Czypierwsza(i)==1)
        {
            for(j=i*i; j<=liczba; j+=i)
            {
                usun_z_Listy(&element,j);
            }
        }
    }
}

//MAIN, WYWOLANIE FUNCKJI
int main()
{
	//DEKLARACJA LISTY JAK I ZMIENNYCH
    struct Lista* dana = NULL; //poczatek listy bedzie pustym znakiem

    char nazwapliku[50];
    int liczba;

    cout << "Podaj n, gorna czesc przedzialu <2,n>" << endl;
    cin >> liczba;
    
    cout << "Podaj nazwe pliku do zapisu wraz z rozszerzeniem(!)." << endl;
    cin >> nazwapliku;
    
    //WYWOLANIE FUNCKJI
    Inicjuj(&dana, liczba);
    sito(&dana, liczba);
    ZapiszDoPliku(dana,nazwapliku);
    
    cout << endl << "Liczby pierwsze z przedzialu <2," << liczba << ">" << endl;
    Wypisz(dana);
    cout << endl << "Zapisano do pliku pomyslnie" << endl;
    
    return 0;
}
