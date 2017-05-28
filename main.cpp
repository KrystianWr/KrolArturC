#include <iostream>
#include "funkcje.h"

using namespace std;

Kolejka *ogon = NULL;
int misja=0;
bool flaga=false;

void szukaj_zamku(DrogaArtura *tab,int wioski,int &obiekt)
{
int licznik=0;
bool p=1;

	while(p)
	{
		if(tab[licznik].typ_obiektu == obiekt) {p=0; obiekt = licznik;}
		else licznik++;
	}
}

void Dijkstry(DrogaArtura *tab,BlokInfo info,SciezkaArtura *sciezka,int startowy_obiekt,int obiekt_szukany)  //szukany na mapie to obiekt
{
int najK_droga=0;
int najM_sasiad=-1;
int szukam = obiekt_szukany;
int start = startowy_obiekt;

Droga *droga = new Droga[info.liczba_wiosek];

	szukaj_zamku(tab,info.liczba_wiosek,start);
	szukaj_zamku(tab,info.liczba_wiosek,szukam);

	sciezka[start].liczba=start;
	droga[start].liczba = 0;        //zeruje punkt poczatkowy

	for(int i=0;i<2*tab[start].liczba_drog;i+=2)                  //przejrzenie sasiadow od pkt startowego
	{
		droga[tab[start].tablica_celow[i]].liczba = tab[start].tablica_celow[i+1];
		sciezka[tab[start].tablica_celow[i]].liczba = start;

	}

	droga[start].zamkniety = true;               //zamykam obiekt

	while(droga[szukam].zamkniety != true || misja%2!=0)
	{
		LogikaSciezki(tab,droga,info,sciezka,najM_sasiad);
		BlizszySasiad(droga,info.liczba_wiosek,najK_droga,najM_sasiad);
		przeglad_sasiadow(tab,droga,sciezka,najK_droga,najM_sasiad);
	}
delete droga;
}

int DijkstryCD(DrogaArtura *tab,BlokInfo info,SciezkaArtura *sciezka,int startowy_obiekt,int obiekt_szukany)  //szukany na mapie to obiekt
{
int najK_droga=0;
int najM_sasiad=-1;
int szukam = obiekt_szukany;
int start = startowy_obiekt;
int pomocnicza;

Droga *droga = new Droga[info.liczba_wiosek];

	szukaj_zamku(tab,info.liczba_wiosek,start);
	szukaj_zamku(tab,info.liczba_wiosek,szukam);

	sciezka[start].liczba=start;
	droga[start].liczba = 0;        //zeruje punkt poczatkowy

	for(int i=0;i<2*tab[start].liczba_drog;i+=2)                  //przejrzenie sasiadow od pkt startowego
	{
		droga[tab[start].tablica_celow[i]].liczba = tab[start].tablica_celow[i+1];
		sciezka[tab[start].tablica_celow[i]].liczba = start;
	}

	droga[start].zamkniety = true;               //zamykam obiekt

	while(droga[szukam].zamkniety != true || misja%2!=0)
	{
		LogikaSciezki(tab,droga,info,sciezka,najM_sasiad);
		BlizszySasiad(droga,info.liczba_wiosek,najK_droga,najM_sasiad);
		przeglad_sasiadow(tab,droga,sciezka,najK_droga,najM_sasiad);
	}
	pomocnicza = droga[szukam].liczba;

	WrzucDoKolejki(sciezka,start,szukam);

delete droga;

return pomocnicza;
}

void przeglad_sasiadow(DrogaArtura *tab,Droga *droga,SciezkaArtura *sciezka,int KDroga,int MSasiad)
{
int pom=0;
	for(int i=0;i<2*tab[MSasiad].liczba_drog;i+=2)                  //przejrzenie sasiadow
		if(droga[tab[MSasiad].tablica_celow[i]].zamkniety != true && droga[tab[MSasiad].tablica_celow[i]].liczba == 9999)
		{
			droga[tab[MSasiad].tablica_celow[i]].liczba = tab[MSasiad].tablica_celow[i+1] + KDroga;
			sciezka[tab[MSasiad].tablica_celow[i]].liczba = MSasiad;
		}
		else if(droga[tab[MSasiad].tablica_celow[i]].zamkniety != true)               //aktualizacja etykiety gdy mniejsza
		{
			pom = tab[MSasiad].tablica_celow[i+1]+KDroga;
			if(droga[tab[MSasiad].tablica_celow[i]].liczba > pom)
			{
				droga[tab[MSasiad].tablica_celow[i]].liczba = pom;
				sciezka[tab[MSasiad].tablica_celow[i]].liczba = MSasiad;
			}
		}
		else if(tab[MSasiad].liczba_drog == 1 && droga[tab[MSasiad].tablica_celow[i]].zamkniety == true)    //gdy jedna droga i zamknieta
		{
			droga[MSasiad].liczba =  droga[tab[MSasiad].tablica_celow[i]].liczba + tab[MSasiad].tablica_celow[i+1];
		}
	droga[MSasiad].zamkniety = true;

}

void LogikaSciezki(DrogaArtura *tab,Droga *droga,BlokInfo info,SciezkaArtura *sciezka,int MSasiad)
{
int pomocnicza;
	if(MSasiad != -1)      //-1 to moje pierwsze wywolanie Dijkstry
	{
		switch(tab[MSasiad].typ_obiektu)
		{
		case 0:                           //zwykla osada dla bezpieczenstwa
			break;
		case 1:                           //sprzedawca krzakow
			if(misja%2 == 1)
			{
				misja--;
				SciezkaArtura *trasa = new SciezkaArtura[info.liczba_wiosek];
				pomocnicza=DijkstryCD(tab,info,trasa,1,3);
				droga[MSasiad].liczba+=pomocnicza;
				aktualizacja_sasiadow(tab,droga,MSasiad,pomocnicza);
			delete trasa;
			}
			break;
		case 2:							 //Czarny Rycerz (BK)
				droga[MSasiad].liczba+=info.czasBK;
				aktualizacja_sasiadow(tab,droga,MSasiad,info.czasBK);
			break;
		case 3:							 //Rycerze NI (chca krzak)
			if(misja%2==0)
			{
				misja++;
				sciezka[MSasiad].wyjatek = true;
				SciezkaArtura *trasa = new SciezkaArtura[info.liczba_wiosek];
				pomocnicza=DijkstryCD(tab,info,trasa,3,1);
				droga[MSasiad].liczba+=pomocnicza;
				aktualizacja_sasiadow(tab,droga,MSasiad,pomocnicza);
			delete trasa;
			}
			break;
		}
	}
}

void BlizszySasiad(Droga *droga,int wioski,int &KDroga,int &MSasiad)
{
	KDroga = 9999;
	for(int i=0;i<wioski;i++)
		if(droga[i].zamkniety != true && KDroga > droga[i].liczba)
			{
				KDroga = droga[i].liczba;
				MSasiad = i;
			}
}
void aktualizacja_sasiadow(DrogaArtura *tab,Droga *droga,int MSasiad,int wartosc)
{
	for(int i=0;i<2*tab[MSasiad].liczba_drog;i+=2)
	{
		if(droga[tab[MSasiad].tablica_celow[i]].zamkniety != true)
			droga[tab[MSasiad].tablica_celow[i]].liczba+=wartosc;
		else if(tab[MSasiad].liczba_drog == 1 && droga[tab[MSasiad].tablica_celow[i]].zamkniety == true)
			{
			droga[tab[MSasiad].tablica_celow[i]].liczba+=wartosc;
			}
	}
}
void WrzucDoKolejki(SciezkaArtura *sciezka,int poczatek,int wybor_obiektu)
{
Kolejka *nowy = new Kolejka;
Kolejka *pomoc = NULL;

	if(sciezka[wybor_obiektu].liczba!=poczatek)
		{
			if(flaga==true)
			{
				nowy->index = wybor_obiektu;
				pomoc = ogon;
				ogon = nowy;
				nowy->next = pomoc;
			}
			flaga = true;
			WrzucDoKolejki(sciezka,poczatek,sciezka[wybor_obiektu].liczba);
		}
		else if(sciezka[wybor_obiektu].liczba==poczatek)
		{
			Kolejka *nowy2 = new Kolejka;
			Kolejka *pomoc2 = NULL;

			nowy->index = wybor_obiektu; nowy2->index = sciezka[wybor_obiektu].liczba;
			pomoc = ogon;
			ogon = nowy;
			nowy->next = pomoc;

			pomoc2 = ogon;
			ogon = nowy2;
			nowy2->next = pomoc2;

		}
	flaga  = false;
}
void WypiszTraseArtura(SciezkaArtura *sciezka,int start,int szukam,int licznik)
{
int pom = licznik+1;
		if(sciezka[szukam].liczba!=start)
			WypiszTraseArtura(sciezka,start,sciezka[szukam].liczba,pom);

		cout<<sciezka[szukam].liczba<<" ";

		if(sciezka[szukam].wyjatek == true)
			WypiszKolejke();

		if(licznik==0)                             //wypisanie koncowego elementu sciezki
				cout<<szukam<<" ";
}
void WypiszKolejke()
{
Kolejka *pomoc = NULL;
	pomoc = ogon;
	while(pomoc != NULL)
	{
		cout<<pomoc->index<<" ";
		pomoc = pomoc->next;
	}
}
