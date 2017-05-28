
#ifndef SRC_FUNKCJE_H_
#define SRC_FUNKCJE_H_
#include <iostream>
using namespace std;

struct DrogaArtura
{
int typ_obiektu;
int liczba_drog;
int *tablica_celow;
DrogaArtura(){
	cin >> typ_obiektu >> liczba_drog;
	tablica_celow = new int[2*liczba_drog];
	for(int i=0;i<2*liczba_drog;i++) cin>>tablica_celow[i];
	}
~DrogaArtura(){ delete tablica_celow;}
};

struct Droga
{
int liczba;
bool zamkniety;
Droga(){
		liczba = 9999;
		zamkniety = false;
		}
};

struct SciezkaArtura
{
int liczba;
bool wyjatek;
SciezkaArtura *next;
SciezkaArtura(){
				liczba = 0;
				wyjatek = false;
				next = NULL;
				}
};

struct BlokInfo
{
int liczba_wiosek;
int czasBK;
BlokInfo(){
		cin>>liczba_wiosek>>czasBK;
		}
};

struct Kolejka
{
int index;
Kolejka *next;
Kolejka(){ next = NULL; index = 0;}
};


void program();
void szukaj_zamku(DrogaArtura *tab,int wioski,int &obiekt);
void Dijkstry(DrogaArtura *tab,BlokInfo info,SciezkaArtura *sciezka,int startowy_obiekt,int obiekt_szukany);
int DijkstryCD(DrogaArtura *tab,BlokInfo info,SciezkaArtura *sciezka,int startowy_obiekt,int obiekt_szukany);
void przeglad_sasiadow(DrogaArtura *tab,Droga *droga,SciezkaArtura *sciezka,int KDroga,int MSasiad);
void BlizszySasiad(Droga *droga,int wioski,int &KDroga,int &MSasiad);
void LogikaSciezki(DrogaArtura *tab,Droga *droga,BlokInfo info,SciezkaArtura *sciezka,int MSasiad);
void aktualizacja_sasiadow(DrogaArtura *tab,Droga *droga,int MSasiad,int wartosc);
void WrzucDoKolejki(SciezkaArtura *sciezka,int poczatek,int wybor_obiektu);
void WypiszKolejke();
void WypiszTraseArtura(SciezkaArtura *sciezka,int start,int szukam,int licznik);


#endif /* SRC_FUNKCJE_H_ */
