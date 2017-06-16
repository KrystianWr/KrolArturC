# KrolArturC
Król Artur i Święty Graal

Król Artur wraz ze swymi rycerzami otrzymał misję odnalezienia Świętego Graala. Wiadomo, że Graal znajduje się gdzieś w Anglii (tam też
ma swój zamek król Artur). Podczas wędrówki może jednak spotkać się z przeciwnościami: może natknąć się na Czarnego Rycerza, którego 
musi pokonać (i to za każdym razem, gdy go spotka) lub trafić na Rycerzy Mówiących Ni, których musi ułaskawić przynosząc im krzak (który
może nabyć u sprzedawcy krzaków). Twoim zadaniem jest wskazanie królowi najkrótszej trasy do Świętego Graala.

Uwaga: królowi nie przystoi podróżować z krzakiem (chyba, że ma Misję), więc nie może "na zapas" nabyć krzaku. Dopiero, gdy natknie się 
na Rycerzy Mówiących Ni, musi wyruszyć do sprzedawcy, nabyć krzak i jak najszybciej wrócić do Rycerzy.

Wejście

Na wejściu zostanie podany graf – mapa Anglii. W pierwszej linii pojawi się n – liczba osad w Anglii oraz k – czas potrzebny na 
pokonanie Czarnego Rycerza (w godzinach). W kolejnych n liniach pojawią się opisy dróg wychodzących z i-tej osady w formacie:

typ m c1 d1 ... cm dm

gdzie:
typ 
  opisuje i-tą osadę: 0 oznacza zwyczajną osadę, 1 sprzedawcę krzaków, 2 obozowisko Czarnego Rycerza, 3 postój Rycerzy Mówiących Ni,
  4 oznacza zamek króla Artura (skąd wyrusza na swoją misję) zaś 5 oznacza miejsce, w którym ukryty jest Święty Graal,
m 
  opisuje liczbę dróg wychodzących z i-tej osady,
ci 
  opisuje cel i-tej drogi (numer osady, do której prowadzi),
di 
  opisuje długość i-tej drogi (w godzinach).

Wyjście

Na wyjściu należy wypisać kolejne numery osad, przez które król Artur wraz ze swoją drużynę musi przejść, by jak najszybciej odnaleźć
Świętego Graala.

Przykład

Wejście
7 2
4 2 1 4 4 1
0 2 0 4 2 8
0 2 1 8 3 8
5 2 2 8 4 1
3 3 0 1 3 1 5 1
2 2 4 1 6 1
1 1 5 1


Wyjście
0 4 5 6 5 4 3 
