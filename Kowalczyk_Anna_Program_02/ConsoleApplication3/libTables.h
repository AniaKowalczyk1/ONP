#ifndef LIBTABLES_H
#define LIBTABLES_H
#include <iostream>
#include <fstream>
using namespace std;


/*
Funkcja tworz�ca dynamiczn� tablic� o podanym rozmiarze@param zapis - referencja do obiektu strumienia wyj�ciowego pliku
@param rozmiarTablicy - rozmiar tworzonej tablicy
@return - wska�nik do tablicy
*/
int* f_utworzTablice(int rozmiarTablicy);

/*
Funkcja wype�niaj�ca tablic� danymi wczytanymi z pliku
@param tab - wska�nik do tablicy
@param rozmiarTablicy - rozmiar tablicy
@param odczyt - referencja do obiektu strumienia wej�ciowego pliku
*/
void f_wypelnijTablice(int* tab, int rozmiarTablicy, ifstream& odczyt);

/*
Funkcja wype�niaj�ca tablic� danymi wygenerowanymi losowo z zadanego zakresu
@param tab - wska�nik do tablicy
@param rozmiarTablicy - rozmiar tablicy
@param poczatek - poczatek zakresu, z kt�rego losowane b�d� liczby
@param koniec - koniec zakresu, z kt�rego losowane b�d� liczby
*/
void f_wypelnijTabliceGenerowanymi(int* tab, int rozmiarTablicy, long long poczatek, long long koniec);

/*
Funkcja wy�wietlaj�ca zawarto�� tablicy
@param tab - wska�nik do tablicy
@param wymiarN - rozmiar tablicy
*/
void f_wyswietlTablice(int* tab, int wymiarN);

/*
Funkcja wypisuj�ca zawarto�� tablicy, wypisuj�ca maksymalnie 200 pierwszych element�w w wierszu
@param tab - wska�nik do tablicy
@param wymiarN - rozmiar tablicy
*/
void f_wypiszTablice(int* tablica, int rozmiar);






#endif


