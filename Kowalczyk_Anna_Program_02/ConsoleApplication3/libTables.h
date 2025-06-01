#ifndef LIBTABLES_H
#define LIBTABLES_H
#include <iostream>
#include <fstream>
using namespace std;


/*
Funkcja tworz¹ca dynamiczn¹ tablicê o podanym rozmiarze@param zapis - referencja do obiektu strumienia wyjœciowego pliku
@param rozmiarTablicy - rozmiar tworzonej tablicy
@return - wskaŸnik do tablicy
*/
int* f_utworzTablice(int rozmiarTablicy);

/*
Funkcja wype³niaj¹ca tablicê danymi wczytanymi z pliku
@param tab - wskaŸnik do tablicy
@param rozmiarTablicy - rozmiar tablicy
@param odczyt - referencja do obiektu strumienia wejœciowego pliku
*/
void f_wypelnijTablice(int* tab, int rozmiarTablicy, ifstream& odczyt);

/*
Funkcja wype³niaj¹ca tablicê danymi wygenerowanymi losowo z zadanego zakresu
@param tab - wskaŸnik do tablicy
@param rozmiarTablicy - rozmiar tablicy
@param poczatek - poczatek zakresu, z którego losowane bêd¹ liczby
@param koniec - koniec zakresu, z którego losowane bêd¹ liczby
*/
void f_wypelnijTabliceGenerowanymi(int* tab, int rozmiarTablicy, long long poczatek, long long koniec);

/*
Funkcja wyœwietlaj¹ca zawartoœæ tablicy
@param tab - wskaŸnik do tablicy
@param wymiarN - rozmiar tablicy
*/
void f_wyswietlTablice(int* tab, int wymiarN);

/*
Funkcja wypisuj¹ca zawartoœæ tablicy, wypisuj¹ca maksymalnie 200 pierwszych elementów w wierszu
@param tab - wskaŸnik do tablicy
@param wymiarN - rozmiar tablicy
*/
void f_wypiszTablice(int* tablica, int rozmiar);






#endif


