#ifndef LIBFILES_H
#define LIBFILES_H
#include <iostream>
#include <fstream>
using namespace std;


/*
Funkcja otwieraj¹ca zapis do pliku
@param zapis - referencja do obiektu strumienia wyjœciowego pliku
@param nazwaPliku - referencja do nazwy pliku
*/
void f_zapisDoPliku(ofstream& zapis, string& nazwaPliku);

/*
Funkcja otwieraj¹ca zapis do pliku
@param odczyt - referencja do obiektu strumienia wejœciowego pliku
@param nazwaPliku - referencja do nazwy pliku
*/
void f_odczytZpliku(ifstream& odczyt, string& nazwaPliku);

#endif


