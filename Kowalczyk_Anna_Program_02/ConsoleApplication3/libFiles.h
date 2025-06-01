#ifndef LIBFILES_H
#define LIBFILES_H
#include <iostream>
#include <fstream>
using namespace std;


/*
Funkcja otwieraj�ca zapis do pliku
@param zapis - referencja do obiektu strumienia wyj�ciowego pliku
@param nazwaPliku - referencja do nazwy pliku
*/
void f_zapisDoPliku(ofstream& zapis, string& nazwaPliku);

/*
Funkcja otwieraj�ca zapis do pliku
@param odczyt - referencja do obiektu strumienia wej�ciowego pliku
@param nazwaPliku - referencja do nazwy pliku
*/
void f_odczytZpliku(ifstream& odczyt, string& nazwaPliku);

#endif


