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
Funkcja sprawdzaj¹ca, czy dany znak jest zdefiniowanym przez nas operatorem
@param c - znak, który sprawdzamy, czy jest operatorem
@return true je¿eli znak jest operatorem, w przeciwnym przypadku false
*/
bool f_jest_operatorem(char c);

/*
Funkcja sprawdzaj¹ca, czy dane wyra¿enie jest typu ONP czy INF
@param wyrazenie - string przechowuj¹cy sprawdzane wyrazenia
@return zwraca "ONP" lub "INF
*/
string f_infCzyOnp(string wyrazenie);




/*
Funkcja zwracaj¹ca wyra¿enie bez zbêdnych znaków
@param wyrazenie - wyra¿enie, z którego usuwamy zbêdne znaki typu spacje, litery albo cyfry
@return zmienna typu string, wyra¿enie bez zbêdnych znaków
*/
string f_usun_zbedne_znaki(string wyrazenie);




/*
Funkcja sprawdzaj¹ca, czy dane wyra¿enie ONP jest wykonalne
@pram onp_wyrazenie - sprawdzane wyra¿enie
@return true je¿eli wykonalne w przeciwnym przypadku false
*/
bool f_onp_wykonalne(string onp_wyrazenie);


/*
Funkcja zamieniaj¹ca wyrazenie ONP na INF
@pram onp_wyrazenie - zamieniane wyra¿enie
@return zamienione wyra¿enie
*/
string f_onp_do_infiks(const string& onp_wyrazenie);




/*
Funkcja zamieniaj¹ca wyrazenie INF na ONP
@pram infiksowe_wyrazenie - zamieniane wyra¿enie
@return zamienione wyra¿enie
*/
string f_infiks_do_onp(string infiksowe_wyrazenie);



/*
Funkcja sprawdzaj¹ca, czy dane wyra¿enie INF jest poprawne
@pram infiksowe_wyrazenie - sprawdzane wyra¿enie
@return true je¿eli poprawne w przeciwnym przypadku false
*/
bool f_sprawdz_poprawnosc_infiksu(const string& infiksowe_wyrazenie);

















/*
Funkcja sprawdzaj¹ca, czy podana liczba znajduje siê w okreœlonym zakresie
@param podana - sprawdzana liczba
@param poczatek - poczatek zakresu, w którym ma byæ liczba
@param koniec - koniec zakresu, w którym ma byæ liczba
@return - TRUE je¿eli liczba jest w zakresie, FALSE gdy nie jest
*/
bool f_czyWzakresie(int podana, int poczatek, int koniec);

/*
Funkcja generuj¹ca losow¹ liczbê z zadanego zakresu
@param poczatek - poczatek zakresu, z którego losowana bêdzie liczba
@param koniec - koniec zakresu, z którego losowana bêdzie liczba
@return - losowa liczba
*/
long long f_generujLiczbe(long long poczatek, long long koniec);

/*
Funkcja zliczaj¹ca iloœæ wyst¹pieñ danej liczby w posortowanej tablicy
@param tab - wskaŸnik do tablicy
@param rozmiar - rozmiar tablicy
@param szukana - liczba, której wyst¹pienia liczymy
@return - loœæ wyst¹pieñ danej liczby
*/
int f_iloscPodanejLiczby(int* tab, int rozmiar, int szukana);

/*
Funkcja znajduj¹ca indeks wyst¹pienia podanej liczby w posortowanej tablicy
@param tab - wskaŸnik do tablicy
@param rozmiar - rozmiar tablicy
@param szukana - liczba, której indeksu szukamy
@param licznik - iloœæ wyst¹pieñ danej liczby
@return - indeks wyst¹pienia podanej liczby
*/
int f_indeksPodanegoElementu(int* tab, int rozmiar, int szukana, int licznik);

/*
Funkcja usuwaj¹ca duplikaty z tablicy oraz zmniejszaj¹ca jej rozmiar
@param tab - wskaŸnik do tablicy
@param rozmiar - referencja do rozmiaru tablicy
@return - wskaŸnik do tablicy bez duplikatów
*/
int* f_usunDuplikaty(int* tab, int& rozmiar);


#endif


