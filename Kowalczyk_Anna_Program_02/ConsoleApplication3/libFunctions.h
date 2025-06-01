#ifndef LIBFUNCTIONS_H
#define LIBFUNCTIONS_H
#include <iostream>
#include <fstream>
#include <random>
#include <stack>
#include <unordered_map>

using namespace std;

// Zawiera operatory wraz z ich priorytetem
extern std::unordered_map<char, int> priorytety;

/*
Funkcja sprawdzaj�ca, czy dany znak jest zdefiniowanym przez nas operatorem
@param c - znak, kt�ry sprawdzamy, czy jest operatorem
@return true je�eli znak jest operatorem, w przeciwnym przypadku false
*/
bool f_jest_operatorem(char c);

/*
Funkcja sprawdzaj�ca, czy dane wyra�enie jest typu ONP czy INF
@param wyrazenie - string przechowuj�cy sprawdzane wyrazenia
@return zwraca "ONP" lub "INF
*/
string f_infCzyOnp(string wyrazenie);




/*
Funkcja zwracaj�ca wyra�enie bez zb�dnych znak�w
@param wyrazenie - wyra�enie, z kt�rego usuwamy zb�dne znaki typu spacje, litery albo cyfry
@return zmienna typu string, wyra�enie bez zb�dnych znak�w
*/
string f_usun_zbedne_znaki(string wyrazenie);




/*
Funkcja sprawdzaj�ca, czy dane wyra�enie ONP jest wykonalne
@pram onp_wyrazenie - sprawdzane wyra�enie
@return true je�eli wykonalne w przeciwnym przypadku false
*/
bool f_onp_wykonalne(string onp_wyrazenie);


/*
Funkcja zamieniaj�ca wyrazenie ONP na INF
@pram onp_wyrazenie - zamieniane wyra�enie
@return zamienione wyra�enie
*/
string f_onp_do_infiks(const string& onp_wyrazenie);




/*
Funkcja zamieniaj�ca wyrazenie INF na ONP
@pram infiksowe_wyrazenie - zamieniane wyra�enie
@return zamienione wyra�enie
*/
string f_infiks_do_onp(string infiksowe_wyrazenie);



/*
Funkcja sprawdzaj�ca, czy dane wyra�enie INF jest poprawne
@pram infiksowe_wyrazenie - sprawdzane wyra�enie
@return true je�eli poprawne w przeciwnym przypadku false
*/
bool f_sprawdz_poprawnosc_infiksu(const string& infiksowe_wyrazenie);

















/*
Funkcja sprawdzaj�ca, czy podana liczba znajduje si� w okre�lonym zakresie
@param podana - sprawdzana liczba
@param poczatek - poczatek zakresu, w kt�rym ma by� liczba
@param koniec - koniec zakresu, w kt�rym ma by� liczba
@return - TRUE je�eli liczba jest w zakresie, FALSE gdy nie jest
*/
bool f_czyWzakresie(int podana, int poczatek, int koniec);

/*
Funkcja generuj�ca losow� liczb� z zadanego zakresu
@param poczatek - poczatek zakresu, z kt�rego losowana b�dzie liczba
@param koniec - koniec zakresu, z kt�rego losowana b�dzie liczba
@return - losowa liczba
*/
long long f_generujLiczbe(long long poczatek, long long koniec);

/*
Funkcja zliczaj�ca ilo�� wyst�pie� danej liczby w posortowanej tablicy
@param tab - wska�nik do tablicy
@param rozmiar - rozmiar tablicy
@param szukana - liczba, kt�rej wyst�pienia liczymy
@return - lo�� wyst�pie� danej liczby
*/
int f_iloscPodanejLiczby(int* tab, int rozmiar, int szukana);

/*
Funkcja znajduj�ca indeks wyst�pienia podanej liczby w posortowanej tablicy
@param tab - wska�nik do tablicy
@param rozmiar - rozmiar tablicy
@param szukana - liczba, kt�rej indeksu szukamy
@param licznik - ilo�� wyst�pie� danej liczby
@return - indeks wyst�pienia podanej liczby
*/
int f_indeksPodanegoElementu(int* tab, int rozmiar, int szukana, int licznik);

/*
Funkcja usuwaj�ca duplikaty z tablicy oraz zmniejszaj�ca jej rozmiar
@param tab - wska�nik do tablicy
@param rozmiar - referencja do rozmiaru tablicy
@return - wska�nik do tablicy bez duplikat�w
*/
int* f_usunDuplikaty(int* tab, int& rozmiar);


#endif


