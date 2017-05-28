#include <iostream>
#include "funkcje.h"

using namespace std;

int main()
{
	program();
	return 0;
}

void program()
{
int start=4;             //zamek
int szukam = 5;          //gral
BlokInfo info;
DrogaArtura *szlak = new DrogaArtura[info.liczba_wiosek];
SciezkaArtura *sciezka = new SciezkaArtura[info.liczba_wiosek];

	Dijkstry(szlak,info,sciezka,start,szukam);

	szukaj_zamku(szlak,info.liczba_wiosek,start);
	szukaj_zamku(szlak,info.liczba_wiosek,szukam);

	WypiszTraseArtura(sciezka,start,szukam,0);

delete sciezka;
delete szlak;
}
